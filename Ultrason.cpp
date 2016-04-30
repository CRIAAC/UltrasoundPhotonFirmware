// This #include statement was automatically added by the Particle IDE.
#include "SparkJson.h"

// This #include statement was automatically added by the Particle IDE.
#include "MaxSonarSensor.h"

// This #include statement was automatically added by the Particle IDE.
#include "MaxSonarLibrary.h"

// This #include statement was automatically added by the Particle IDE.
#include "MuxLibrary.h"

#include "application.h"
#define DELAY_ULTRASOUND_DATA 50

#define DELAY_ULTRASOUND_DATA 50

SYSTEM_MODE(SEMI_AUTOMATIC);
STARTUP(WiFi.selectAntenna(ANT_AUTO));

MaxSonarLibrary mslib;
char myIpString[24];

// UDP Port used for two way communication
unsigned int localPort = 8888;
UDP Udp;

void setup()
{
    WiFi.on();
    WiFi.clearCredentials();
    // Max 5 credentials
    WiFi.setCredentials("CRIAAC", "liara_lab", WPA2, WLAN_CIPHER_AES_TKIP);
    //WiFi.setCredentials("HeightballVoyage", "Bonjours123", WPA2, WLAN_CIPHER_AES_TKIP);
    //WiFi.setCredentials("LIARA", "liara_lab", WPA2, WLAN_CIPHER_AES_TKIP);
    WiFi.connect();
    Particle.connect();

    Serial.begin(9600);
    Udp.begin(localPort);

    mslib.Add(MaxSonarSensor(A0, D0));
    mslib.Add(MaxSonarSensor(A1, D1));
    mslib.Add(MaxSonarSensor(A2, D2));
    mslib.Add(MaxSonarSensor(A3, D3));
    mslib.Add(MaxSonarSensor(A4, D4));
    mslib.Add(MaxSonarSensor(A5, D5));

    IPAddress myIp = WiFi.localIP();
    sprintf(myIpString, "%d.%d.%d.%d", myIp[0], myIp[1], myIp[2], myIp[3]);

    Serial.println(myIp);

    mslib.Init();
    Serial.println("Init End");
}


void loop()
{
    int dataSize = 0;
    if ((dataSize = Udp.parsePacket()) > 0 && !(Udp.remoteIP() == WiFi.localIP())) {
        // TEMP: Else IP is not stored correctly
        IPAddress myIp = WiFi.localIP();
        sprintf(myIpString, "%d.%d.%d.%d", myIp[0], myIp[1], myIp[2], myIp[3]);
        // END TEMP

        mslib.TriggerAll();
        Udp.flush();
        StaticJsonBuffer<900> jsonBuffer;
        JsonObject& root = jsonBuffer.createObject();
        root["Photon"] = myIpString;

        delay(DELAY_ULTRASOUND_DATA);
        mslib.Update(&root);
        char buffer[205];
        root.printTo(buffer, sizeof(buffer));

        root.printTo(Serial);
        Serial.println("");

        IPAddress ipAddress = Udp.remoteIP();
        int port = Udp.remotePort();
        Udp.beginPacket(ipAddress, port);
        Udp.write(buffer);
        Udp.endPacket();
        Udp.flush();
    }
}
