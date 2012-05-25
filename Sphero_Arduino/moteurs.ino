int sns1 = -25;
int sns2 = -25;
int sns3 = -25;

int lstPWM1 = 0;
int lstPWM2 = 0;
int lstPWM3 = 0;

void PWMmoteur1(int valeur, int sens)//0 = 0%, 255 = 100%; 0 = courant positif, -1 = courant négatif
{
  if(sens == 0 && sns1 != 0)
  {
    analogWrite(PWM1, 0);
    delay(1);
    digitalWrite(sens1H1, LOW);
    digitalWrite(sens1H2, HIGH);
    sns1 = 0;
    analogWrite(PWM1, valeur);
  }
  else if(sens == -1 && sns1 != -1)
  {
    analogWrite(PWM1, 0);
    delay(1);
    digitalWrite(sens1H1, HIGH);
    digitalWrite(sens1H2, LOW);
    sns1 = -1;
    analogWrite(PWM1, valeur);
  }
  else if(valeur != lstPWM1)
  {
    analogWrite(PWM1, valeur);
  }
}

void PWMmoteur2(int valeur, int sens)//0 = 0%, 255 = 100%; 0 = courant positif, -1 = courant négatif
{
  if(sens == 0 && sns2 != 0)
  {
    analogWrite(PWM2, 0);
    delay(1);
    digitalWrite(sens2H1, LOW);
    digitalWrite(sens2H2, HIGH);
    sns2 = 0;
    analogWrite(PWM2, valeur);
  }
  else if(sens == -1 && sns2 != -1)
  {
    analogWrite(PWM2, 0);
    delay(1);
    digitalWrite(sens2H1, HIGH);
    digitalWrite(sens2H2, LOW);
    sns2 = -1;
    analogWrite(PWM2, valeur);
  }
  else if(valeur != lstPWM1)
  {
    analogWrite(PWM2, valeur);
  }
}

void PWMmoteur3(int valeur, int sens)//0 = 0%, 255 = 100%; 0 = courant positif, -1 = courant négatif
{
  if(sens == 0 && sns3 != 0)
  {
    analogWrite(PWM3, 0);
    delay(1);
    digitalWrite(sens3H1, LOW);
    digitalWrite(sens3H2, HIGH);
    sns3 = 0;
    analogWrite(PWM3, valeur);
  }
  else if(sens == -1 && sns3 != -1)
  {
    analogWrite(PWM3, 0);
    delay(1);
    digitalWrite(sens3H1, HIGH);
    digitalWrite(sens3H2, LOW);
    sns3 = -1;
    analogWrite(PWM3, valeur);
  }
  else if(valeur != lstPWM1)
  {
    analogWrite(PWM3, valeur);
  }
}
