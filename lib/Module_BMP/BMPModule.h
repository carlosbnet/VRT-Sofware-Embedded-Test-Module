#ifndef BMPModule_h
#define BMPModule_h


#include <Arduino.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>

#define DEFAULT_ADDRESS  0x76
#define DEFAULT_DELAY_MS 2000

class BMPModule : public TwoWire, public Adafruit_BMP280
{
private:

    uint32_t _port;

public:




    //Contrutor
    BMPModule();
    BMPModule(byte port);


    //Metodos
    void begin();
    
    

    void header();
    DynamicJsonDocument buildJson();
    void createJsonChild(JsonObject jsonObject);
    DynamicJsonDocument createJson();

};


#endif