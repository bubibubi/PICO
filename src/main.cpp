#include <Arduino.h>

#define PUMP_ON HIGH
#define PUMP_OFF LOW

bool pumpIsOn;
int oldPressure;



void setup()
{
  Serial.begin(9600);
  delay(1000);
  Serial.println(F("SETUP"));

  Serial.println(F("Set D0 as output"));
  pinMode(16, OUTPUT);

  Serial.println(F("Turn OFF the pump"));
  digitalWrite(16, PUMP_OFF);

  pumpIsOn = false;
  oldPressure = -10;
}

void loop()
{
  int pressure = analogRead(A0);

  if (abs(oldPressure - pressure) > 5)
  {
    oldPressure = pressure;
    if (pumpIsOn)
    {
      if (pressure > 800)
        pumpIsOn = false;
    }
    else
    {
      if (pressure < 400)
        pumpIsOn = true;
    }

    if (pumpIsOn)
      digitalWrite(16, PUMP_ON);
    else
      digitalWrite(16, PUMP_OFF);

    Serial.printf("Pressure: %i, Pump is %s\n", pressure, pumpIsOn ? "ON" : "OFF");
  }
}