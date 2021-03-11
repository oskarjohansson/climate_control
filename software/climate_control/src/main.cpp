#include <Arduino.h>
#include <utils.h>
#include <button.h>
#include <heater.h>
#include <constants.h>

/*
uint8_t getSoc();

inline uint32_t getElapsedTime(uint32_t sinceTime);
void flash(uint8_t pin, uint8_t flashes, uint16_t time_on, uint16_t time_off);
void goToSleep();
void wakeFromSleep();
*/
Button switchButton(switchPin);
Heater heater(heaterPwmPin, boostEnablePin, ledPin);

void setup()
{
}

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