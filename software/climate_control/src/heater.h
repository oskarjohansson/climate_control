#include <constants.h>

class Heater
{
    uint8_t currentLevel;
    bool active;


    uint8_t pwmPin;
    uint8_t enablePin;
    uint8_t ledPin;

    public:
    Heater(uint8_t pwmPin, uint8_t enablePin, uint8_t ledPin)
    {
        this->pwmPin = pwmPin;
        this->enablePin = enablePin;
        this->ledPin = ledPin;
        digitalWrite(pwmPin, LOW);
        digitalWrite(enablePin, LOW);

        currentLevel = 0;
        active = false;
    }
    
    void pause()
    {
        digitalWrite(pwmPin, LOW);
        digitalWrite(enablePin, LOW);
        active = false;
    }
    void resume()
    {
        analogWrite(pwmPin, currentLevel);
        digitalWrite(enablePin, HIGH);
        active = true;
    }
    void off()
    {
        digitalWrite(pwmPin, LOW);
        digitalWrite(enablePin, LOW);
        active = false;
        currentLevel = 0;
    }

    void increment()
    {
        if (!active && !currentLevel)
            currentLevel = heaterStartValue;
        else if (currentLevel >  255-heaterIncrement)
            currentLevel = 255;
        else
            currentLevel += heaterIncrement;
        active = true;
        digitalWrite(enablePin, HIGH);
        analogWrite(pwmPin, currentLevel);
    }
    void decrement()
    {
        if (!active && !currentLevel)
            currentLevel = heaterStartValue;
        else if (currentLevel <  heaterIncrement)
            currentLevel = 0;
        else
            currentLevel -= heaterIncrement;
        active = true;
        digitalWrite(enablePin, HIGH);
        analogWrite(pwmPin, currentLevel);

    }
    bool isActive()
    {
        return active;
    }
};
