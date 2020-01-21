#define PWM_RANGE 255

#define LEFT_IN1_PIN 6
#define LEFT_IN2_PIN 7
#define LEFT_SPEED_PIN 10
#define RIGHT_IN1_PIN A1
#define RIGHT_IN2_PIN A2
#define RIGHT_SPEED_PIN 9

#define LEFT_ENGINE_OFFSET 184
#define RIGHT_ENGINE_OFFSET 201

#define INTERRUPT_PIN 2

int received_bit = 0; // VOLATILE ????

int instr[4];

int data_frame[24];

/*
 * 0 - left engine % power
 * 1 - left engine direction (0 forward, 1 backward)
 * 2 - right engine % power
 * 3 - right engine direction
 */
////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() 
  {
    randomSeed(analogRead(0));
    engine_init(LEFT_IN1_PIN, LEFT_IN2_PIN, LEFT_SPEED_PIN);
    engine_init(RIGHT_IN1_PIN, RIGHT_IN2_PIN, RIGHT_SPEED_PIN);

    attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), irq_receiver_handler, CHANGE); // CHANGE ?????
    
    setup_timer();
  }

void loop() 
  {  
      my_decode();
      engine_control(LEFT_IN1_PIN, LEFT_IN2_PIN, LEFT_SPEED_PIN, LEFT_ENGINE_OFFSET, instr[0], instr[1]);
      engine_control(RIGHT_IN1_PIN, RIGHT_IN2_PIN, RIGHT_SPEED_PIN, RIGHT_ENGINE_OFFSET, instr[2], instr[3]) ;
      delay(100);    
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

void my_decode()
  {

  }
void irq_receiver_handler()
  {
    received_bit = 1;
  }
void setup_timer()
  {
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1  = 0;
    OCR1A = 1999;
    TCCR1B |= (1 << WGM12);
    TCCR1B |= (1 << CS11);  
    TIMSK1 |= (1 << OCIE1A);
  }
ISR(TIMER1_COMPA_vect)
  {
    shift_array();
    data_frame[0] = received_bit ;
    received_bit = 0;
  }
void shift_array()
  {
    int tmp = 0;
    int tmp2 = 0;
    for(int i = 0; i < 23; i++)
      { 
        tmp2 = data_frame[i];
        data_frame[i] = tmp;
        tmp = tmp2;
      }
  }
