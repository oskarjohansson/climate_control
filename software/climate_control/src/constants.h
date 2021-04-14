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

const unsigned long socLedTimestep = 400;   // Timestep
const unsigned long socLedCycle = 5000;     // How often the soc should cycle
const uint8_t socLedPattern[3][5] = {{0,1,1,1,1},{0,1,0,1,1},{0,1,0,1,0}}; // The pattern for the three battery levels

const float voltPerInc = 0.0062; // Magic number ;-) 1.1 * ((100 + 30) / 30) / 1024; // internal_ref * voltage_division⁽⁻¹⁾ / resolution
const int underVoltThreshold = 447; //2.8 / voltPerInc;

const int batSocVoltageLevels = 3;
const unsigned int batSocVoltage[] = {underVoltThreshold, 535, 624};
                                      /*{(unsigned int)(3.48 / voltPerInc),  // ~20%
                                      (unsigned int)(3.60 / voltPerInc),  // ~40%
                                      (unsigned int)(3.71 / voltPerInc),  // ~60%
                                      (unsigned int)(3.90 / voltPerInc),  // ~80%
                                      (unsigned int)(4.15 / voltPerInc)}; // ~ 95%*/

enum clickTypes {
    noClick,
    singleClick,
    doubleClick,
    tripleClick,
    longClick
};

const int heaterStartLevel = 1;
const int heaterNumberOfLevels = 2;
const int heaterLevels[] = {100, 175, 255};

#endif