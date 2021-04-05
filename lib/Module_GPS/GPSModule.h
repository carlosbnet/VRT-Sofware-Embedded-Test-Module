#ifndef GPSModule_h
#define GPSModule_h

#include <SoftwareSerial.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include <TinyGPS++.h>

#define DEFAULT_RX_PIN  4
#define DEFAULT_TX_PIN  3
#define DEFAULT_BAUD_RATE  9600
#define DEFAULT_DELAY_MS 1000

class GPSModule : public SoftwareSerial, public TinyGPSPlus
{
private:

    uint32_t _baud;

public:


    //Variaveis
    uint8_t RX_PIN;
    uint8_t TX_PIN;


    //Contrutor
    GPSModule();
    GPSModule(uint8_t rx, uint8_t tx);


    //Metodos
    void begin();
    void begin(uint32_t baud);
    TinyGPSPlus init();

    void headerGps();
    DynamicJsonDocument buildJson();
    void createJsonChild(JsonObject jsonObject);
    void customDelay(uint32_t MS);
    DynamicJsonDocument createJson();


};


#endif