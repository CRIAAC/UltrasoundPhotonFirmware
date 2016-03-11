#ifndef MUX_LIBRARY_H
#define MUX_LIBRARY_H

#include <application.h>

class MuxLibrary
{
    bool isDigital;
    int S0Pin;
    int S1Pin;
    int S2Pin;
    int S3Pin;
    int SigPin;
    int readAnalogValue(int MuxPin);
    public:
    MuxLibrary();
    MuxLibrary(int s0Pin,int s1Pin,int s2Pin, int s3Pin,int sigPin, bool digital);
    ~MuxLibrary();
 
    int ReadMux(int MuxPin);
    int ReadMuxDigital(int MuxPin);

    //To Be Add in the futur.
 //  void WriteMux(int MuxPin,int Value);
    void Init();
    
    bool GetIsDigital();
    void SetIsDigital(bool Value);
    
    int GetS0Pin();
    void SetS0Pin(int PinNumber);
    int GetS1Pin();
    void SetS1Pin(int PinNumber);
    int GetS2Pin();
    void SetS2Pin(int PinNumber);
    int GetS3Pin();
    void SetS3Pin(int PinNumber);
};
#endif
