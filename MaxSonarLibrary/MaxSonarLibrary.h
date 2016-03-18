#ifndef MAXSONAR_LIBRARY_H
#define MAXSONAR_LIBRARY_H

#include <application.h>
#include <vector>
#include <algorithm>
#include "SparkJson.h"
#include "MuxLibrary.h"
#include "MaxSonarSensor.h"

using namespace std;

class MaxSonarLibrary
{
        void LoopState(uint8_t State);
        MuxLibrary* mux;

        vector<vector<long>> lastFilteredValues;
        const int filterBaseValues = 5;

        long FilterData(int sensor, long distance, bool modeFilter);

public:
        vector<MaxSonarSensor> lst_MaxSonarSensor;
        MaxSonarLibrary();
        ~MaxSonarLibrary();
        void Add(MaxSonarSensor sensor);
        void Init();
        void TriggerAll();
        void Update();
        void Update(JsonObject* json);
        int Size();

};

#endif
