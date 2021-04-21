#include <Arduino.h>
#include <utils.h>
#include <button.h>
#include <heater.h>
#include <constants.h>

/*
DONE: Verify debouncing and click pattern detection
DONE: Verify Led output
DONE: Verify boost circuit working

TODO: Verify getSoc()
TODO: Verify sleep function (measure current draw)
TODO: Verify heater function
*/
Button switchButton(switchPin);
Heater heater(heaterPwmPin, boostEnablePin, ledPin);

// For battery soc led
uint8_t queueIndex = 0;
unsigned long socLastCycle = 5000;

void setup()
{
  Serial.begin(9600);
  //Serial.println("Hello World!");
  pinMode(ledPin,INPUT);
  flash(ledPin, 3, 250, 250);
  pinMode(boostEnablePin,OUTPUT);
  digitalWrite(boostEnablePin,HIGH);
  analogReference(INTERNAL1V1);
}

void loop()
{
  unsigned long now = millis();
  // Read battery status
  uint8_t Soc = getSoc();
  if (Soc)
  {
    // Check if button is pressed
    int click = switchButton.poll();
    switch (click)
    {
      case clickTypes::singleClick:
        //Serial.println("Single click detected!");
        socLastCycle = now + socLedCycle;
        if (heater.isActive())
          heater.increment();
        break;
      case clickTypes::doubleClick:
        //Serial.println("Double click detected!");
        socLastCycle = now + socLedCycle;
        if (heater.isActive())
          heater.decrement();
        break;
      case clickTypes::tripleClick:
      { // Get battery status
        //Serial.println("Triple click detected!");
        socLastCycle = now + socLedCycle;
        //heater.pause();
        //delay(10);
        //uint8_t soc = getSoc();
        //flash(ledPin, soc+1, 500, 250);
        //heater.resume();
        break;
      }
      case clickTypes::longClick:
        if (heater.isActive())
        {
          //Serial.println("Turning off heater!");
          heater.off();
        }
        else
        {
          //Serial.println("Turning on heater!");
          heater.on();
        }
        break;
      
    }
    // If neither heater active nor switchbutton active
    if (!(switchButton.isActive() || heater.isActive()))
    {
      //Serial.println("Inactive, going to sleep!");
      delay(25);
      goToSleep();
    }

    // Blink battery level led
    else if((now>socLastCycle))
    {
      Serial.print(Soc); Serial.print(" "); Serial.println(analogRead(batSensePin));
      uint8_t ledMode = socLedPattern[Soc-1][queueIndex];
      if(ledMode) 
      {        
        pinMode(ledPin, OUTPUT);
        digitalWrite(ledPin, LOW);
      }
      else 
      {
        pinMode(ledPin, INPUT);
      }

      queueIndex = (queueIndex + 1) % (sizeof(socLedPattern[Soc])+1);
      // If queueIndex is zero, wait another 5s
      if(queueIndex<1){
        socLastCycle = now + socLedCycle;
        pinMode(ledPin, OUTPUT);
        digitalWrite(ledPin, LOW);
      }
      else 
      {
        socLastCycle = now + socLedTimestep;
      }
    }





  }
  else
  {
    delay(25);
    //disable heater
    heater.off();
    //disable led
    pinMode(ledPin, INPUT);
    // Sleep
    goToSleep();
  }
}