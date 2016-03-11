#include "MaxSonarLibrary.h"

 MaxSonarLibrary::MaxSonarLibrary()
 {
     
 }
 
MaxSonarLibrary::~MaxSonarLibrary()
{

}

void MaxSonarLibrary::Add(MaxSonarSensor sensor)
{
    lst_MaxSonarSensor.push_back(sensor);
}

void MaxSonarLibrary::Init()
{
    if(Size()<1)
     return;
    for(int i =0; i< lst_MaxSonarSensor.size();i++)
    {
        lst_MaxSonarSensor[i].Init();
    }
    
}
   
void MaxSonarLibrary::TriggerAll()
{
    if(Size()<1)
     return;
    LoopState(LOW);
    delayMicroseconds(40);
    LoopState(HIGH);
    delayMicroseconds(40);
    LoopState(LOW);
    
}

void MaxSonarLibrary::Update()
{
    if(Size()<1)
     return;
    for(int i=0;i< lst_MaxSonarSensor.size();i++)
    {
        lst_MaxSonarSensor[i].GetmV();
    }
}

void MaxSonarLibrary::Update(JsonObject* json)
{
    if(json ==NULL)
        return;
    if(Size()<1)
      return;
    JsonArray& data = json->createNestedArray("ListMaxSonarSensor");
    for(int i=0;i< lst_MaxSonarSensor.size();i++)
    {
      // Original / Theory
      // data.add((lst_MaxSonarSensor[i].GetmV()/6.4)/2.0,0);

      // Distance correction
      data.add((lst_MaxSonarSensor[i].GetmV()/4.7)/2.0,0);
    }
}

int MaxSonarLibrary::Size()
{
    return lst_MaxSonarSensor.size();
}

void MaxSonarLibrary::LoopState(uint8_t State)
{
    for(int i =0; i< lst_MaxSonarSensor.size();i++)
    {
        lst_MaxSonarSensor[i].Trigger(State);
    }
    
}


