#include <avr/sleep.h>
#include <constants.h>

inline uint32_t getElapsedTime(uint32_t sinceTime)
{
    return millis() - sinceTime;
}

uint8_t getSoc()
{
    int batVoltage = 0;
    for (int i = 0; i < batteryReads; i++)
    {
        batVoltage += analogRead(batSensePin);
    }
    batVoltage /= batteryReads;

    for (int i = batSocVoltageLevels; i; i--)
    {
        //Serial.print(batVoltage); Serial.print(" "); Serial.print(batSocVoltage[i-1]); Serial.print(" ");
        if (batVoltage > batSocVoltage[i-1])
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
    //Serial.println("Waking from sleep");
}

void goToSleep()
{

    do{
        while(!digitalRead(switchPin));
        delay(10);
    }while(!digitalRead(switchPin));


    byte adcsra_save = ADCSRA;
    ADCSRA = 0;

    attachInterrupt(switchInterrupt, wakeFromSleep, LOW);

    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();


    sleep_mode();

    /* wake up here */
    //sleep_disable();  // Sleep disable is performed in pin change ISR.
    //detachInterrupt(switchInterrupt);

    power_adc_enable();
    ADCSRA = adcsra_save;
    analogReference(INTERNAL1V1);
}

void flash(uint8_t pin, uint8_t flashes, uint16_t time_on, uint16_t time_off)
{
    delay(time_off);
    for (int i = 0; i < flashes; i++)
    {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);
        delay(time_on);
        pinMode(pin, INPUT);
        delay(time_off);
    }
}

inline uint8_t digitalReadInverse(uint8_t pinNumber)
{
    return !digitalRead(pinNumber);
}