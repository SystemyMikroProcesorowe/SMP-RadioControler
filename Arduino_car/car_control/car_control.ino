#define PWM_RANGE 255

#define LEFT_IN1_PIN 6
#define LEFT_IN2_PIN 7
#define LEFT_SPEED_PIN 10
#define RIGHT_IN1_PIN A1
#define RIGHT_IN2_PIN A2
#define RIGHT_SPEED_PIN 9

#define LEFT_ENGINE_OFFSET 184
#define RIGHT_ENGINE_OFFSET 201

#define INTERRUPT_PIN_RISE 2
#define INTERRUPT_PIN_FALL 3

volatile int received_bit = 0; 

int instr[4];

volatile int data_frame[18];
volatile int frame_full = 0;

volatile bool transmission = false;
int tst_arr[] = {0, 1,0,0,0,1,0,1,1, 0,1,1,1,0,1,0,0, 1};
/*
 * 0 - left engine % power
 * 1 - left engine direction (0 forward, 1 backward)
 * 2 - right engine % power
 * 3 - right engine direction
 */
////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() 
  {
    Serial.begin(9600);
    engine_init(LEFT_IN1_PIN, LEFT_IN2_PIN, LEFT_SPEED_PIN);
    engine_init(RIGHT_IN1_PIN, RIGHT_IN2_PIN, RIGHT_SPEED_PIN);

    attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN_RISE), irq_receive_rise, RISING );
    attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN_FALL), irq_receive_fall, FALLING );

    cli();
    setup_timer0();
    sei();

    //pinMode(7, OUTPUT); // for test only
  }

void loop() 
  {    
    //mock_transmission();
    is_ready();
  }
////////////////////////////////////////////////////////////////////////////////////////////////////
void engine_control(int IN1, int IN2, int SPEED, int ENGINE_OFFSET, int POWER, int DIR)
  {
    if(DIR == 0)
      {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
      }
    else
      {
        digitalWrite(IN1, HIGH); 
        digitalWrite(IN2, LOW); 
      }
    
    analogWrite(SPEED, ENGINE_OFFSET + (POWER * (PWM_RANGE - ENGINE_OFFSET)));
  }


void engine_init(int IN1, int IN2, int SPEED)
  {
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(SPEED, OUTPUT);
  }


void irq_receive_rise()
  {
    if(!transmission)
    {
      TCCR0B |= (1 << CS01) | (1 << CS00); // enable timer for clocking
      transmission = true;
    }
    received_bit = 0;           
  }


void irq_receive_fall()
  {
    received_bit = 1;
  }


void setup_timer0()
  {
//timer for clocking signal
//interrupt every 0,5ms
    TCCR0A = 0;// set entire TCCR0A register to 0
    TCCR0B = 0;// same for TCCR0B
    TCNT0  = 62;//initialize counter value to half (we need to count to 1/2 of period at the start
    OCR0A = 124;// pre = 64 / int freq = 2khz/0,5ms
    TCCR0A |= (1 << WGM01); // turn on CTC mode
    
    TCCR0B &= ~(1<< CS02);  // clock is off at the start
    TCCR0B &= ~(1<< CS01);
    TCCR0B &= ~(1<< CS00);
    
    TIMSK0 |= (1 << OCIE0A); // enable timer compare interrupt
  }


ISR(TIMER0_COMPA_vect)
  {
    shift_array();
    data_frame[0] = received_bit;
    frame_full++;
    TCNT0  = 0; // let timer count again
  }


void is_ready()
  {
    if(frame_full == 18)
    {
      transmission = false;
      TCCR0B &= ~(1<< CS02);  // turn off the clock altogether
      TCCR0B &= ~(1<< CS01);
      TCCR0B &= ~(1<< CS00);
      frame_full = 0;
      TCNT0 = 62; // at the start of the frame timer must count for only half of period
      decode_data();
      engine_control(LEFT_IN1_PIN, LEFT_IN2_PIN, LEFT_SPEED_PIN, LEFT_ENGINE_OFFSET, instr[0], instr[1]);
      engine_control(RIGHT_IN1_PIN, RIGHT_IN2_PIN, RIGHT_SPEED_PIN, RIGHT_ENGINE_OFFSET, instr[2], instr[3]);

      /*
      Serial.print("RAMKA ZEBRANA:");
      if(compare())
      {
        Serial.println("GIT");
      }
      else
      {
        Serial.println("NIEGIT");
      }
      */
      
    }
  }

bool compare()
{
  for (int i = 0; i<18; i=i+1)
    {
      if (data_frame[i] != tst_arr[i]) return false;
    }
  
  return true;
}

void mock_transmission()
{
  for (int i = 0; i<18; i=i+1)
    {
      if (tst_arr[i] == 0)
        {
          digitalWrite(LOW,7);
          delay(0.5);
          digitalWrite(HIGH,7);
          delay(0.5);
        }
       else
        {
          digitalWrite(HIGH,7);
          delay(0.5);
          digitalWrite(LOW,7);
          delay(0.5);
        }       
    }       
}

void shift_array()
  {
    int tmp = 0;
    int tmp2 = 0;
    for(int i = 0; i < 18; i++)
      { 
        tmp2 = data_frame[i];
        data_frame[i] = tmp;
        tmp = tmp2;
      }
  }

void decode_data()
  {
    instr[1] = data_frame[8];
    instr[3] = data_frame[16];
    instr[0] = bin_to_dec(7);
    instr[2] = bin_to_dec(15);
  }

  
int bin_to_dec(int offset)
  {
    int tmp = 0;
    int e = 7;

    for(int i = offset; i >= offset - 6; i--)
      {
        if(data_frame[i])
        {
          tmp += pow(2, e);
        } 
        e--;
      }
          
    return tmp;
  }
