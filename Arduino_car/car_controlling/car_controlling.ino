void setup() { 
  //rusza 184? left
  pinMode(10, OUTPUT); //Sygnał PWM silnika nr 1
  pinMode(6, OUTPUT); //Sygnały sterujące kierunkiem obrotów silnika nr 1
  pinMode(7, OUTPUT);
  //9en a1a2
  //rusza 200?
  pinMode(9, OUTPUT); //Sygnał PWM silnika nr 1
  pinMode(A1, OUTPUT); //Sygnały sterujące kierunkiem obrotów silnika nr 1
  pinMode(A2, OUTPUT);
  
  digitalWrite(6, LOW); //Silnik nr 1 - obroty w lewo
  digitalWrite(7, HIGH);

  digitalWrite(A1, LOW); //Silnik nr 1 - obroty w lewo
  digitalWrite(A2, HIGH);

  Serial.begin(9600);
} 
void loop()  { 
  for (int i = 150; i <= 255; i++) {
      //analogWrite(10, i); //Spokojne rozpędzanie silnika
      //analogWrite(9,i); //Spokojne rozpędzanie silnika
      Serial.print(i);
      Serial.println();
      delay(100);
  }
}
void recive_decode()
{}
void engine_control(int power, int dir)
{
  //LEFT ENIGINE
  //dir



  
  digitalWrite(6, LOW); //Silnik nr 1 - obroty w lewo
  digitalWrite(7, HIGH);
  //speed
  analogWrite(10, power);
}
}
