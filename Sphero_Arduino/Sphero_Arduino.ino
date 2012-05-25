//Définition des PINS
//Numériques
int RESET = 7;
int PWM1 = 3;
int PWM2 = 5;
int PWM3 = 6;
int sens1H1 = 8;
int sens1H2 = 9;
int sens2H1 = 10;
int sens2H2 = 11;
int sens3H1 = 12;
int sens3H2 = 13;
//Analogiques
int AcceleroX = 2;
int AcceleroY = 3;
int AcceleroZ = 4;
int GyroX = 0;
int GyroY = 1;

void setup() {
  pinMode(RESET,OUTPUT);
  Serial.begin(115200);
  digitalWrite(RESET, HIGH);
  delay(10);
  digitalWrite(RESET, LOW);
  delay(2000);
  
  pinMode(sens1H1, OUTPUT);
  pinMode(sens2H1, OUTPUT);
  pinMode(sens3H1, OUTPUT);
  pinMode(sens1H2, OUTPUT);
  pinMode(sens2H2, OUTPUT);
  pinMode(sens3H2, OUTPUT);
  pinMode(PWM1, OUTPUT);
  pinMode(PWM2, OUTPUT);
  pinMode(PWM3, OUTPUT);
}  
  
  char temp;
  
void loop () {
  /*while(!isConnected())
  {
    continue;
  }*/
  while(true)
  {
    if(Serial.available() > 0)
    {
      delay(3);
      temp = Serial.read();
      if(temp != 0b01010010)
      {
        Serial.println("marche pas...");
        Serial.println(temp, BIN);
        Serial.flush();
        continue;
      }
      getCommande();
    }
    
  }
}  
