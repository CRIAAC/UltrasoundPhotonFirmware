
#include "MaxSonarSensor.h"

MaxSonarSensor::MaxSonarSensor()
{
    analogReadPin =0;
    digitalTriggerPin = 0;
   
    value = 0;
    mVConstant = 0.8;
    mux =NULL;
    
    
}

MaxSonarSensor::~MaxSonarSensor()
{
   
    analogReadPin =0;
    digitalTriggerPin = 0;
    value = 0;
    mVConstant = 0.8;

}

MaxSonarSensor::MaxSonarSensor(uint8_t AnalogReadPin,uint8_t DigitalTriggerPin)
{
    mux = NULL;
    analogReadPin = AnalogReadPin;
    digitalTriggerPin = DigitalTriggerPin;
   
    value = 0;
    mVConstant = 0.8;
   
}


MaxSonarSensor::MaxSonarSensor(uint8_t AnalogReadPin,uint8_t DigitalTriggerPin,MuxLibrary* _Mux)
{
    mux = _Mux;
    analogReadPin = AnalogReadPin;
    digitalTriggerPin = DigitalTriggerPin;
   
    value = 0;
    mVConstant = 0.8;
   
}

void MaxSonarSensor::Init()
{
     pinMode(digitalTriggerPin,OUTPUT);
    
}

void MaxSonarSensor::Update()
{
    
}

void MaxSonarSensor::Trigger(uint8_t State)
{
    digitalWrite(digitalTriggerPin,State);
}

double  MaxSonarSensor::GetmV()
{
   if(mux==NULL)
   {
       value = analogRead(analogReadPin);
   }else
   {
       value = mux->ReadMux(analogReadPin);
   }
    value = value / mVConstant;
    return value;
    
}
