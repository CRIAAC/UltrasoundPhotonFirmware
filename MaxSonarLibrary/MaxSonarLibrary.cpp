#include "MaxSonarLibrary.h"

MaxSonarLibrary::MaxSonarLibrary()
{
    lastFilteredValues = vector<vector<long> >(6, vector<long>());     // [sensors][filterBaseValues]
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
    if (Size() < 1) {
        return;
    }

    for (int i = 0; i < lst_MaxSonarSensor.size(); i++) {
        lst_MaxSonarSensor[i].Init();
    }

    lastFilteredValues =
        vector<vector<long> >(lst_MaxSonarSensor.size(), vector<long>());         // [sensors][filterBaseValues]
}


void MaxSonarLibrary::TriggerAll()
{
    if (Size() < 1) {
        return;
    }

    LoopState(LOW);
    delayMicroseconds(40);
    LoopState(HIGH);
    delayMicroseconds(40);
    LoopState(LOW);
}


void MaxSonarLibrary::Update()
{
    if (Size() < 1) {
        return;
    }

    for (int i = 0; i < lst_MaxSonarSensor.size(); i++) {
        lst_MaxSonarSensor[i].GetmV();
    }
}


void MaxSonarLibrary::Update(JsonObject *json)
{
    if (json == NULL) {
        return;
    }

    if (Size() < 1) {
        return;
    }

    JsonArray& data = json->createNestedArray("ListMaxSonarSensor");

    for (int i = 0; i < lst_MaxSonarSensor.size(); i++) {
        // Distance correction
        long distance = (lst_MaxSonarSensor[i].GetmV() / 4.7) / 2.0;
        data.add(FilterData(i, distance, false), 0);         // Filtering
    }
}


int MaxSonarLibrary::Size()
{
    return lst_MaxSonarSensor.size();
}


void MaxSonarLibrary::LoopState(uint8_t State)
{
    for (int i = 0; i < lst_MaxSonarSensor.size(); i++) {
        lst_MaxSonarSensor[i].Trigger(State);
    }
}


long MaxSonarLibrary::FilterData(int sensor, long distance, bool modeFilter)
{
    if (modeFilter) {
        // TODO: Mode filter
    }else {  // Median filter
        if (lastFilteredValues[sensor].size() == filterBaseValues) {
            lastFilteredValues[sensor].erase(lastFilteredValues[sensor].begin());
            lastFilteredValues[sensor].push_back(distance);

            vector<long> sensorValues = lastFilteredValues[sensor];
            sort(sensorValues.begin(), sensorValues.end());

            if (sensorValues.size() % 2 ==
                0) {
                return (sensorValues[sensorValues.size() / 2] +
                        sensorValues[sensorValues.size() / 2] - 1) / 2;
            } else {
                return sensorValues[sensorValues.size() / 2];
            }
        }else {
            lastFilteredValues[sensor].push_back(distance);
            return distance;             // Unfiltered data since there's not enough original data
                                         // for comparison
        }
    }
}
