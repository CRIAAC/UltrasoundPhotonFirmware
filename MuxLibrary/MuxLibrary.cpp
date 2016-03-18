#include "MuxLibrary.h"

MuxLibrary::MuxLibrary()
{
    isDigital = false;
    S0Pin = D5;
    S1Pin = D4;
    S2Pin = D3;
    S3Pin = D2;
    SigPin = A0;
}


MuxLibrary::MuxLibrary(int s0Pin, int s1Pin, int s2Pin, int s3Pin, int sigPin, bool digital)
{
    S0Pin = s0Pin;
    S1Pin = s1Pin;
    S2Pin = s2Pin;
    S3Pin = s3Pin;
    SigPin = sigPin;
    isDigital = digital;
}


MuxLibrary::~MuxLibrary()
{
}


int MuxLibrary::readAnalogValue(int MuxPin)
{
    int controlPin[] = {S0Pin, S1Pin, S2Pin, S3Pin};

    int muxChannel[16][4] = {
        {0, 0, 0, 0}, //channel 0
        {1, 0, 0, 0}, //channel 1
        {0, 1, 0, 0}, //channel 2
        {1, 1, 0, 0}, //channel 3
        {0, 0, 1, 0}, //channel 4
        {1, 0, 1, 0}, //channel 5
        {0, 1, 1, 0}, //channel 6
        {1, 1, 1, 0}, //channel 7
        {0, 0, 0, 1}, //channel 8
        {1, 0, 0, 1}, //channel 9
        {0, 1, 0, 1}, //channel 10
        {1, 1, 0, 1}, //channel 11
        {0, 0, 1, 1}, //channel 12
        {1, 0, 1, 1}, //channel 13
        {0, 1, 1, 1}, //channel 14
        {1, 1, 1, 1}  //channel 15
    };

    //loop through the 4 sig
    for (int i = 0; i < 4; i++) {
        digitalWrite(controlPin[i], muxChannel[MuxPin][i]);
    }
    return analogRead(SigPin);
}


int MuxLibrary::ReadMux(int MuxPin)
{
    if (isDigital) {
        return readAnalogValue(MuxPin) < 2048 ? LOW : HIGH;
    }else {
        return readAnalogValue(MuxPin);
    }
}


int MuxLibrary::ReadMuxDigital(int MuxPin)
{
    return readAnalogValue(MuxPin) < 2048 ? LOW : HIGH;
}


void MuxLibrary::Init()
{

    pinMode(S0Pin, OUTPUT);
    pinMode(S1Pin, OUTPUT);
    pinMode(S2Pin, OUTPUT);
    pinMode(S3Pin, OUTPUT);

    digitalWrite(S0Pin, LOW);
    digitalWrite(S1Pin, LOW);
    digitalWrite(S2Pin, LOW);
    digitalWrite(S3Pin, LOW);
}


//Accesseur
bool MuxLibrary::GetIsDigital()
{
    return isDigital;
}


void MuxLibrary::SetIsDigital(bool Value)
{
    isDigital = Value;
}


int MuxLibrary::GetS0Pin()
{
    return S0Pin;
}


void MuxLibrary::SetS0Pin(int PinNumber)
{
    S0Pin = PinNumber;
}


int MuxLibrary::GetS1Pin()
{
    return S1Pin;
}


void MuxLibrary::SetS1Pin(int PinNumber)
{
    S1Pin = PinNumber;
}


int MuxLibrary::GetS2Pin()
{
    return S2Pin;
}


void MuxLibrary::SetS2Pin(int PinNumber)
{
    S2Pin = PinNumber;
}


int MuxLibrary::GetS3Pin()
{
    return S3Pin;
}


void MuxLibrary::SetS3Pin(int PinNumber)
{
    S3Pin = PinNumber;
}
