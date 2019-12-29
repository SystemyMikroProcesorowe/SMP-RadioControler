#define PWM_RANGE 255

#define LEFT_IN1_PIN 6
#define LEFT_IN2_PIN 7
#define LEFT_SPEED_PIN 10
#define RIGHT_IN1_PIN A1
#define RIGHT_IN2_PIN A2
#define RIGHT_SPEED_PIN 9

#define LEFT_ENGINE_OFFSET 184
#define RIGHT_ENGINE_OFFSET 201

int instr[4];
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
  }

void loop() 
  {
  if(recive())
    {
      my_decode();
      engine_control(LEFT_IN1_PIN, LEFT_IN2_PIN, LEFT_SPEED_PIN, LEFT_ENGINE_OFFSET, instr[0], instr[1]);
      engine_control(RIGHT_IN1_PIN, RIGHT_IN2_PIN, RIGHT_SPEED_PIN, RIGHT_ENGINE_OFFSET, instr[2], instr[3]) ;
      delay(100);
    }
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
  /*  
   * decoding thing from recive() function and saving it to instr array
   * 
   * now it is writing in random stuff
   */
    instr[0] = random(101);
    instr[2] = random(101);
    if(random(101)>80)
      {
        instr[1] = random(2);
        instr[3] = random(2);
      } 
  }
bool recive()
  {
    /*
     * waiting for reciving full frame of data
     * if accomplished, then save this as something 
     * 
     * now its a simulation of reciving nothing sometimes
     */
    if(random(10) > 5)
      {
        delay(random(5, 25));
        return true;
      }
    else
      {
        delay(random(5, 25));
        return false;
      }
  }
