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
        analogWrite(pwmPin, heaterLevels[currentLevel]);
        digitalWrite(enablePin, HIGH);
        active = true;
    }
    void off()
    {
        digitalWrite(pwmPin, LOW);
        digitalWrite(enablePin, LOW);
        active = false;
        currentLevel = 0;
        pinMode(ledPin, INPUT);
    }
    void on()
    {
        currentLevel = heaterStartLevel;
        digitalWrite(enablePin, HIGH);
        analogWrite(pwmPin, heaterLevels[currentLevel]);
        pinMode(ledPin, OUTPUT);
        digitalWrite(ledPin, LOW);
        active = true;
    }

    void increment()
    {
        if (currentLevel < (heaterNumberOfLevels))
            currentLevel ++;
        active = true;
        digitalWrite(enablePin, HIGH);
        analogWrite(pwmPin, heaterLevels[currentLevel]);
        flash(ledPin, currentLevel+1, 200, 200);
        pinMode(ledPin, OUTPUT);
        digitalWrite(ledPin, LOW);
    }
    void decrement()
    {
        if (currentLevel > 0)
            currentLevel --;
        active = true;
        digitalWrite(enablePin, HIGH);
        analogWrite(pwmPin, heaterLevels[currentLevel]);
        flash(ledPin, currentLevel+1, 200, 200);
        pinMode(ledPin, OUTPUT);
        digitalWrite(ledPin, LOW);
    }
    bool isActive()
    {
        return active;
    }
};
