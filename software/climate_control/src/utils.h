#include <avr/sleep.h>
#include <constants.h>

inline uint32_t getElapsedTime(uint32_t sinceTime)
{
    return millis() - sinceTime;
}

uint8_t getSoc()
{
    uint16_t batVoltage = analogRead(batSensePin);

    for (int i = batSocVoltageLevels; i; i--)
    {
        if (batVoltage > batSocVoltage[i])
        {
            return i;
        }
    }
    return 0;
}

void wakeFromSleep()
{
    sleep_disable();
    detachInterrupt(switchInterrupt);
}

void goToSleep()
{
    sleep_enable();
    attachInterrupt(switchInterrupt, wakeFromSleep, LOW);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_cpu();
}

void flash(uint8_t pin, uint8_t flashes, uint16_t time_on, uint16_t time_off)
{
    digitalWrite(pin, LOW);
    delay(time_off);
    for (int i = 0; i < flashes; i++)
    {
        digitalWrite(pin, HIGH);
        delay(time_on);
        digitalWrite(pin, LOW);
        delay(time_off);
    }
}

inline uint8_t digitalReadInverse(uint8_t pinNumber)
{
    return !digitalRead(pinNumber);
}