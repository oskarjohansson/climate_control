#ifndef __CONSTANTS__
#define __CONSTANTS__
const int switchPin = 2;       //PD2
const int switchInterrupt = 0; //PD2

const int boostEnablePin = 3; //PD3
const int boostMosPin = 4;    //PD4
const int heaterPwmPin = 5;   //PD5
const int usbDetectPin = 16;  //PC2
const int ledPin = 10;        //PB2
const int batSensePin = A0;

const int debouncingTime = 50;
const int groupClickInterval = 300;
const int longClickDuration = 1000;
const int inactiveTime = 5000;

const float voltPerInc = 1.1 * (130 / 30) / 1024; // internal_ref * voltage_division⁽⁻¹⁾ / resolution
const int underVoltThreshold = 2.8 / voltPerInc;

const int batSocVoltageLevels = 5;
const unsigned int batSocVoltage[] = {(unsigned int)(3.48 / voltPerInc),  // ~20%
                                      (unsigned int)(3.60 / voltPerInc),  // ~40%
                                      (unsigned int)(3.71 / voltPerInc),  // ~60%
                                      (unsigned int)(3.90 / voltPerInc),  // ~80%
                                      (unsigned int)(4.15 / voltPerInc)}; // ~ 95%

enum clickTypes {
    noClick,
    singleClick,
    doubleClick,
    tripleClick,
    longClick
};

const int heaterIncrement = 64;
const int heaterStartValue = 128;

#endif