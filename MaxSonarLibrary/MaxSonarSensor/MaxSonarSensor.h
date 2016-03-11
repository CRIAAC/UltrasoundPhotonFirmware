#ifndef MAX_SONAR_SENSOR_H
#define MAX_SONAR_SENSOR_H
#include <application.h>
#include "MuxLibrary.h"
class MaxSonarSensor
{
    
    uint8_t analogReadPin;
    uint8_t digitalTriggerPin;
    double mVConstant ;
    double value;
    MuxLibrary* mux;
    
    public:
    MaxSonarSensor();
    ~MaxSonarSensor();
    MaxSonarSensor(uint8_t AnalogReadPin,uint8_t DigitalTrigger);
    MaxSonarSensor(uint8_t AnalogReadPin,uint8_t DigitalTrigger,MuxLibrary* _Mux);
    void Update();
    void Init();
    void Trigger(uint8_t State);
    double GetmV();
    

};
#endif

