//----------------------VRT APP------------------------

/*
App com a função de gerenciar todos os perifericos do computador de bordo dentro do foguete

São eles:
 - Modulo GPS
 - Modulo GSM
 - Modulo WIFI
 - Modulo ALTIMETRO
 - Modulo ACELEROMENTRO
*/

//----------------------BIBLIOTECAS--------------------

#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

//----------------------VARIAVEIS----------------------

//----------------------CONSTANTES---------------------

const int GPSRx = 4;
const int GPSTx = 3;
const int GPSBaudRate = 9600;

//----------------------FUNÇOES------------------------

void jsonCreate();
void customDelay(unsigned long ms);
void createJsonChildGps(JsonObject infor_gps);


//----------------------OBEJTOS----------------------
SoftwareSerial ssGps(GPSRx,GPSTx); //Instancia um objeto da SoftwareSerial para o gps
TinyGPSPlus gps;    //Instancia obejto gps da TinyGPSPlus


void setup(){
ssGps.begin(GPSBaudRate);
Serial.begin(115200);

Serial.println("==============================================================================================================");
Serial.println("==============================================================================================================");
Serial.println("=========================                                                      ===============================");
Serial.println("=========================              Management System VRT  1.0              ===============================");
Serial.println("=========================                    GPS Module  1.0                   ===============================");
Serial.println("=========================                                                      ===============================");
Serial.println("==============================================================================================================");
Serial.println("==============================================================================================================");


}

void loop(){


    jsonCreate();
    
    customDelay(1000);


}

//---------------------------------------FUNÇOES---------------------------------------------
//Função contruida para montar o json do Modulo GPS

void jsonCreate(){

const size_t capacity = JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(2) + 4*JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(6);
DynamicJsonDocument doc(capacity);

//Cria o PAI 
JsonObject infor_gps = doc.createNestedObject("infor_gps");

//Criar os Filhos
createJsonChildGps(infor_gps);


serializeJsonPretty(doc, Serial);


}

//constroi os filhos do objeto infor_gps
void createJsonChildGps(JsonObject infor_gps){
            
        JsonObject infor_gps_location = infor_gps.createNestedObject("location");
        infor_gps_location["lat"] = gps.location.lat();
        infor_gps_location["lng"] = gps.location.lng();
        infor_gps_location["rawlat"] = gps.location.rawLat().negative ? "-" : "+";
        infor_gps_location["rawlng"] = gps.location.rawLng().negative ? "-" : "+";

        JsonObject infor_gps_date = infor_gps.createNestedObject("date");
        infor_gps_date["year"] = gps.date.year();
        infor_gps_date["month"] = gps.date.month();
        infor_gps_date["day"] = gps.date.day();

        JsonObject infor_gps_time = infor_gps.createNestedObject("time");
        infor_gps_time["hour"] = gps.time.hour()-3;
        infor_gps_time["minute"] = gps.time.minute();
        infor_gps_time["second"] = gps.time.second();

        JsonObject infor_gps_speed = infor_gps.createNestedObject("speed");
        infor_gps_speed["mph"] = gps.speed.mph();
        infor_gps_speed["mps"] = gps.speed.mps();
        infor_gps_speed["kmph"] = gps.speed.kmph();

        JsonObject infor_gps_altitude = infor_gps.createNestedObject("altitude");
        infor_gps_altitude["meters"] = gps.altitude.meters();
        infor_gps_altitude["miles"] = gps.altitude.miles();
        infor_gps_altitude["kilometers"] = gps.altitude.kilometers();

        JsonObject infor_gps_satellites = infor_gps.createNestedObject("satellites");
        infor_gps_satellites["satellites"] = gps.satellites.value();
        infor_gps_satellites["hdop"] = gps.hdop.value();

}






void customDelay(unsigned long ms){ //delay personalizado para aguarda um certo tempo para acomular dados

    unsigned long start = millis();

    do
    {
     while(ssGps.available())               //delay para agrupar mais dados
        gps.encode(ssGps.read());
    } while (millis()-start < ms);
    
}