#include "Arduino.h"
#include "SDModule.h"
#include <ArduinoJson.h>
#include <SPI.h>
#include <SD.h>

SDModule::SDModule(uint8_t board)
{
    switch (board)
    {
    case 0:

        this->pin_cs = DEFAULT_PIN_CS;
        this->pin_mosi = DEFAULT_PIN_MOSI;
        this->pin_miso = DEFAULT_PIN_MISO;
        this->pin_clk = DEFAULT_PIN_CLK;

        break;

    case 1:

        this->pin_cs = DEFAULT_PIN_CS;
        this->pin_mosi = DEFAULT_PIN_MOSI_MEGA;
        this->pin_miso = DEFAULT_PIN_MISO_MEGA;
        this->pin_clk = DEFAULT_PIN_CLK_MEGA;

        break;
    }
}

SDModule::SDModule(uint8_t pin_cs, uint8_t board)
{

    switch (board)
    {
    case 0:

        this->pin_cs = pin_cs;
        this->pin_mosi = DEFAULT_PIN_MOSI;
        this->pin_miso = DEFAULT_PIN_MISO;
        this->pin_clk = DEFAULT_PIN_CLK;

        break;

    case 1:

        this->pin_cs = pin_cs;
        this->pin_mosi = DEFAULT_PIN_MOSI_MEGA;
        this->pin_miso = DEFAULT_PIN_MISO_MEGA;
        this->pin_clk = DEFAULT_PIN_CLK_MEGA;

        break;
    }
}

SDModule::SDModule(uint8_t pin_cs, uint8_t pin_mosi, uint8_t pin_miso, uint8_t pin_clk)
{

    this->pin_cs = pin_cs;
    this->pin_mosi = pin_mosi;
    this->pin_miso = pin_miso;
    this->pin_clk = pin_clk;

}

boolean SDModule::begin()
{

  return SD.begin(pin_cs);

}

boolean SDModule::begin(uint8_t pin_cs_m)
{

   return SD.begin(pin_cs_m);

}


boolean SDModule::begin(uint32_t clock, uint8_t pin_cs)
{

    return SD.begin(clock, pin_cs);

}

void SDModule::dataSave(DynamicJsonDocument data)
{

     File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    serializeJson(data,dataFile);
    dataFile.println();
    dataFile.close();
    // print to the serial port too:
    
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }

}

void SDModule::headerSD(){

Serial.println("==============================================================================================================");
Serial.println("==============================================================================================================");
Serial.println("=========================                                                      ===============================");
Serial.println("=========================              Management System VRT  1.0              ===============================");
Serial.println("=========================                    SD Module  1.0                   ===============================");
Serial.println("=========================                                                      ===============================");
Serial.println("==============================================================================================================");
Serial.println("==============================================================================================================");


 }