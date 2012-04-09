//Définition des PINS
//Numériques
int RESET = 7;
int PWM1 = 3;
int PWM2 = 5;
int PWM3 = 6;
int sens1 = 0;
int sens2 = 1;
int sens3 = 2;
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
  
  pinMode(sens1, OUTPUT);
  pinMode(sens2, OUTPUT);
  pinMode(sens3, OUTPUT);
  pinMode(PWM1, OUTPUT);
  pinMode(PWM2, OUTPUT);
  pinMode(PWM3, OUTPUT);
  
}  
  
void loop () {
  Serial.println("la connection fonctionne !");
  delay(1000);
}  
