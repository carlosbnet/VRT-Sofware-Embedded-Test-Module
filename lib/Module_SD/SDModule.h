#ifndef SDModule_h
#define SDModule_h

//Libs necessarias para funcionar
#include <Arduino.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <SD.h>

//Arduino UNO Default Config
#define DEFAULT_PIN_CS 4
#define DEFAULT_PIN_MOSI 11
#define DEFAULT_PIN_MISO 12
#define DEFAULT_PIN_CLK 13

//Arduino Mega Default Config

#define DEFAULT_PIN_MOSI_MEGA 51
#define DEFAULT_PIN_MISO_MEGA 50
#define DEFAULT_PIN_CLK_MEGA 52


class SDModule : public String
{
private:


public:
    
    //Variaveis
    uint8_t pin_cs;
    uint8_t pin_mosi;
    uint8_t pin_miso;
    uint8_t pin_clk;
    uint32_t clock;

    //Contrutor
    SDModule(uint8_t board);// 0 - Arduino UNO / 1 - Arduino Mega 2560
    SDModule(uint8_t pin_cs, uint8_t board);
    SDModule(uint8_t pin_cs, uint8_t pin_mosi,uint8_t pin_miso, uint8_t pin_clk);

    //Metodos
    boolean begin();
    boolean begin(uint8_t pin_cs);
    boolean begin(uint32_t clock, uint8_t pin_cs);
    void dataSave(DynamicJsonDocument data);
    String createNameFile();
    void headerSD();
        
};

#endif