void PWMmoteur1(int valeur, int sens)//0 = 0%, 255 = 100%; 0 = courant positif, -1 = courant négatif
{
  analogWrite(PWM1, valeur);
  if(sens == 0)
  {
    digitalWrite(sens1, LOW);
  }
  else
  {
    digitalWrite(sens1, HIGH);
  }    
}

void PWMmoteur2(int valeur, int sens)//0 = 0%, 255 = 100%; 0 = courant positif, -1 = courant négatif
{
  analogWrite(PWM2, valeur);
  if(sens == 0)
  {
    digitalWrite(sens2, LOW);
  }
  else
  {
    digitalWrite(sens2, HIGH);
  }
}

void PWMmoteur3(int valeur, int sens)//0 = 0%, 255 = 100%; 0 = courant positif, -1 = courant négatif
{
  analogWrite(PWM3, valeur);
  if(sens == 0)
  {
    digitalWrite(sens3, LOW);
  }
  else
  {
    digitalWrite(sens3, HIGH);
  }
}
