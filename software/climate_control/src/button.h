#include <constants.h>


class Button
{
    /* Handles debouncing and decoding short/long clicks */
    clickTypes state = clickTypes::noClick;
    bool filteredState = false;

    uint32_t debounceTime;
    uint32_t filterOnTime;
    uint32_t filterOffTime;
    

    uint8_t pinNumber;

    public:
    Button(uint8_t pinNumber)
    {
        this->pinNumber = pinNumber;
        pinMode(pinNumber, INPUT_PULLUP);
    }

    int poll()
    {
        uint16_t rawState = digitalReadInverse(pinNumber);
        bool keyChanged = false;

        // Do debouncing
        if (rawState == filteredState)
        {
            debounceTime = millis();
        }
        else if (getElapsedTime(debounceTime) > debouncingTime)
        {
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
                state = clickTypes::longClick;
            }
            else if (keyChanged && !filteredState)
            {
                state = clickTypes::singleClick;
            }
        }
        else if ((state == clickTypes::longClick) &&
                 !filteredState)
        {
            state = clickTypes::noClick;
        }
        else if (state == clickTypes::singleClick)
        {
            if (!filteredState &&
                getElapsedTime(filterOffTime) > groupClickInterval)
            {
                state = clickTypes::noClick;
            }
            else if (keyChanged && !filteredState)
            {
                state = clickTypes::doubleClick;
            }
        }
        else if (state == clickTypes::doubleClick)
        {
            if (!filteredState &&
                getElapsedTime(filterOffTime) > groupClickInterval)
            {
                state = clickTypes::noClick;
            }
            else if (keyChanged && !filteredState)
            {
                state = clickTypes::tripleClick;
            }
        }
        else if (state == clickTypes::tripleClick)
        {
            if (!filteredState &&
                getElapsedTime(filterOffTime) > groupClickInterval)
            {
                state = clickTypes::noClick;
            }
        }
        return state;
    }
    bool isActive()
    {
        return getElapsedTime(filterOnTime) > inactiveTime;
    }
};
