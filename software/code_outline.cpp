#include <avr/sleep.h>


const int switchPin = 2;         //PD2
const int switchInterrupt = 0;   //PD2

const int boostEnablePin = 3;    //PD3
const int boostMosPin = 4;       //PD4
const int heaterPwmPin = 5;      //PD5
const int usbDetectPin = 16;     //PC2
const int ledPin = 10;           //PB2
const int batSensePin = 

const int debouncingTime = 50;
const int groupClickInterval = 500;
const int longClickDuration = 1000;
const int inactiveTime = 5000;

const float voltPerInc = 1.1 * (130/30) / 1024 // internal_ref * voltage_division⁽⁻¹⁾ / resolution
const int underVoltThreshold = 2.8 / voltPerInc
const int batSocVoltage[] = {2.8/voltPerInc, 3.38/voltPerInc, 3.48/voltPerInc, 3.55/voltPerInc, 3.60/voltPerInc, 3.65/voltPerInc, 3.71/voltPerInc, 3.79/voltPerInc, 3.9/voltPerInc, 4.05/voltPerInc, 4.15/voltPerInc}	//at 0%, 10%,.. 100% soc Must be checked.

uint8_t getSoc(){
	batVoltage = analogRead(batSensePin)
	for (int i=10; i; i--)
	{
		if (batVoltage > batSocVoltage[i])
		{
			if (i == 10)
				return 100;
			//Linear interpolation
			
			batSocVoltage[i]*() + batSocVoltage*()
			return i; //0-10
		}
	}
	return 0;
}


enum clickTypes{
    noClick,
    singleClick,
    doubleClick,
    tripleClick,
    longClick
};

inline uint8_t digitalReadInverse(uint8_t pinNumber){return !digitalRead(pinNumber);}
inline uint32_t getElapsedTime(uint32_t sinceTime);
void goToSleep();
void wakeFromSleep()

class Heater
{
    void Heater(enablePin, )
};

class Button{
    /* Handles debouncing and decoding short/long clicks */
    clickTypes state = clickTypes::noClick;
    bool filteredState = false;
    
    uint32_t debounceTime;
    uint32_t filterOnTime;
    uint32_t filterOffTime;
    
    uint8_t pinNumber;

    void (*onSingleClick)();  
    void (*onDoubleClick)();
    void (*onTripleClick)();
    void (*onLongClick)();  
    
    attachOnSingleClick(void (*func)()){onSingleClick = &func;}
    attachOnDoubleClick(void (*func)()){onDoubleClick = &func;}
    attachOnTripleClick(void (*func)()){onTripleClick = &func;}
    attachOnLongClick(void (*func)()){onLongClick = &func;}

    void Button(uint8_t pinNumber)
    {
        this::pinNumber = pinNumber;
        pinMode(pinNumber, INPUT_PULLUP)
    }
    void poll()
    {
        rawState = digitalReadInverse(pinNumber);
        bool keyChanged = false;

        // Do debouncing
        if (rawState == filteredState)
        {
            debounceTime = millis();
        }
        else if ( getElapsedTime(debounceTime) > debounceTime )
            filteredState = rawState;
            keyChanged = true;
            if (filteredState)
            {
                filterOnTime = millis();
            }
            else
            {
                filterOffTime = millis();
            }
        }

        // Check for number of clicks
        if (state == clickTypes::noClick)
        {
            if (filteredState &&
                (getElapsedTime(filterOnTime) > longClickDuration))
            {
                state = clickTypes::longClick
                if onLongClick
                    onLongClick();
            }
            else if (keyChanged && !filteredState)
            {
                state == clickTypes::singleClick
            }
        }
        else if ((state == clickTypes::longClick) &&
            ! filteredState)
        {
            state = clickTypes::noClick
        }
        else if(state == clickTypes::singleClick)
        {
            if(!filteredState &&
               getElapsedTime(filterOffTime) > groupClickInterval)
            {
                if onSingleClick
                    onSingleClick();
                state = clickTypes::noClick;
            }
            else if (keyChanged && !filteredState)
            {
                state == clickTypes::doubleClick
            }
        }
        else if(state == clickTypes::doubleClick)
        {
            if(!filteredState &&
               getElapsedTime(filterOffTime) > groupClickInterval)
            {
                if onDoubleClick
                    onDoubleClick();
                state = clickTypes::noClick;
            }
            else if (keyChanged && !filteredState)
            {
                state == clickTypes::tripleClic
                if onTripleClick
                    onTripleClick();
            }
        }
        else if(state == clickTypes::tripleClick)
        {
            if(!filteredState &&
               getElapsedTime(filterOffTime) > groupClickInterval)
            {
                state = clickTypes::noClick;
            }
        }
    }

    bool isActive()
    {
        return  getElapsedTime(filterOnTime) > inactiveTime; 
    }
};

Button switchButton(switchPin)

void setup()
{
    pinMode(boostEnablePin, OUTPUT);)
    pinMode(boostMosPin, OUTPUT);)
    pinMode(heaterPwmPin, OUTPUT);)
    pinMode(usbDetectPin, OUTPUT);)
    pinMode(ledPin, OUTPUT);)

    switchButton.attachOnSingleClick(NUL)
    switchButton.attachOnDoubleClick(NUL)
    switchButton.attachOnTripleClick(NUL)
    switchButton.attachOnTripleClick(NUL)
}

void loop()
{
    if getSoc()
    {
        // Check if button is pressed
        switchButton.poll();

        // If neither heater active nor switchbutton active
        if !(switchButton.isActive() || heater.isActive())
            goToSleep();
    }
    else 
    {
        //disable heater
        //disable leds
        goToSleep();
    }
}


inline uint32_t getElapsedTime(uint32_t sinceTime)
{
    return millis() - sinceTime;    
}

void goToSleep()
{
    sleep_enable();
    attachInterrupt(wakeFromSleep, wake, LOW);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_cpu();
}

void wakeFromSleep()
{
    sleep_disable();
    detachInterrupt(switchInterrupt);
}
