boolean co = false;
void pong()
{
  if(Serial.read() == '\n')
  {
    Serial.write(0b01011000);
    Serial.write(0b11001100);
    Serial.write('\n');
  }
  Serial.flush();
}

void sendAccelero()
{
  //not implemented yet
}

void sendGyro()
{
  //not implemented yet
}

void setMoteurs()
{
  unsigned char moteurs[3];
  int sens[3];
  int i;
  unsigned char temp = 0b00000000;
  for(i=0; i<3; i++)
  {
    moteurs[i] = temp | Serial.read();
    if(Serial.read() == 0b11111111)
    {
      sens[i] = -1;
    }
    else
   {
    sens[i] = 0;
   } 
  }
  if(Serial.read() != '\n')
  {
    return;
  }
  PWMmoteur1(moteurs[0], sens[0]);
  PWMmoteur1(moteurs[1], sens[1]);
  PWMmoteur1(moteurs[2], sens[2]);
}

void stopAll()
{
  co = false;
  PWMmoteur1(0, 0);
  PWMmoteur1(0, 0);
  PWMmoteur1(0, 0);
}


boolean isConnected(void)
{
  if(co == false)
  {
    if(Serial.available() > 0)
    {
      if(Serial.read() != 0b01010010)
      {
        Serial.flush();
        return false;
      }
      if(Serial.read() == 0b11001100)
      {
        pong();
        co = true;
        return true;
      }
    }
  }
  else
  {
    return true;
  }
}

void clignote()
{
  if(Serial.read() != '\n')
  {
    for(int i(0);i<2;i++)
    {
      digitalWrite(LED, HIGH);
      delay(1000);
      digitalWrite(LED, LOW);
    }
    return;
  }
  digitalWrite(LED, HIGH);
  delay(2000);
  digitalWrite(LED, LOW);
  Serial.flush();
}

void getCommande(void)
{
  delay(30);
  char message = Serial.read();
  switch(message)
  {
    case 0b11001100:
      pong();
      break;
    case 0b10110110:
      sendAccelero();
      break;
    case 0b01101101:
      sendGyro();
      break;
    case 0b10101010:
      setMoteurs();
      break;
    case 0b01110111:
      stopAll();
      break;
    case 0b01010101:
      clignote();
      break;
    default:
      Serial.flush();
      break;
  }
}
