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

void setup()
{
  pinMode(ledPin,OUTPUT);
  pinMode(boostEnablePin,OUTPUT);
  digitalWrite(boostEnablePin,HIGH);
}

/* Test:
void loop()
{
  int click = switchButton.poll();
    switch (click)
    {
    case clickTypes::singleClick:
      flash(ledPin, 1, 250, 250);
      break;
    case clickTypes::doubleClick:
      flash(ledPin, 2, 250, 250);
      break;
    case clickTypes::tripleClick:
      flash(ledPin, 3, 250, 250);
      break;
    case clickTypes::longClick:
      flash(ledPin, 1, 750, 750);
      break;
    }
}*/


void loop()
{
  if (getSoc())
  {
    // Check if button is pressed
    int click = switchButton.poll();
    switch (click)
    {
    case clickTypes::singleClick:
      heater.increment();
      break;
    case clickTypes::doubleClick:
      heater.decrement();
      break;
    case clickTypes::tripleClick:
    { // Get battery status
      heater.pause();
      delay(10);
      uint8_t soc = getSoc();
      if (soc)
        flash(ledPin, soc, 500, 250);
      else
        flash(ledPin, 10, 150, 100);
      heater.resume();
      break;
    }
    case clickTypes::longClick:
      heater.off();
      break;
    }
    // If neither heater active nor switchbutton active
    if (!(switchButton.isActive() || heater.isActive()))
      goToSleep();
  }
  else
  {
    //disable heater, led and go to sleep
    heater.off();
    digitalWrite(ledPin, LOW);
    goToSleep();
  }
}