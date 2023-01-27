#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ST7789.h"
#include "DHT.h"


#define DHTTYPE DHT22
#define DHT22_Pin 5
#define TFT_DC 8
#define TFT_RST 9
#define TFT_CS 10


//Klassendefinition
//Maximale Pixel 320x240
//setTextSize ist defniert: 1 =10 Pixel
class Display{

  private:
    Adafruit_ST7789 tft;
    DHT dht;
    byte  pinSenorVcc;
    float temp, hum;
    byte  width, high, startX, startY, endX,endY, textSize,size,radius;
    
  public:

    Display();
    //Anlegen eines Objektes der Klasse Adafruit 
    //welche im Konstruktor(weiter unten also in der cpp) initialisiert wird um auf 
    //Funktionen zuzugreifen
    //Außerhalb geht auch
    //Adafruit tft=Adafruit(); oder Adafruit tft();
    void globalBegin();
    void greetingsScreen(byte startX,byte startY,byte size);
    void header(byte startX, byte startY, byte radius,byte width,byte high, uint16_t color);
    void roundBlock(byte startX, byte startY, byte radius,byte width,byte high, uint16_t color);
    void block(byte startX, byte startY,byte width, byte high,uint16_t color);
    float temperature(byte startX,byte startY,byte textSize);
    float humidity(byte startX,byte startY,byte textSize);
//    void icon();
};

//Klassenbeschreibung mit Initialisierung der Klassen um damit zu arbeiten
Display::Display():tft(TFT_CS, TFT_DC,TFT_RST), dht(DHT22_Pin,DHTTYPE){

}

void Display::globalBegin(){
  Serial.begin(9600);
  tft.init(240,320);
  tft.fillScreen(ST77XX_BLACK);
  tft.setRotation(3);
  
  dht.begin();
};

void Display::header(byte startX, byte startY,byte width,byte high,  byte radius, uint16_t color){

tft.fillRoundRect(startX, startY,width,high, radius,color);

};
void Display::roundBlock(byte startX, byte startY,byte width,byte high,  byte radius, uint16_t color){

tft.fillRoundRect(startX, startY,width,high, radius,color);
};

void Display::block(byte startX, byte startY,byte width,byte high,uint16_t color){

  tft.fillRect(startX,startY,width,high,color);
};

void Display::greetingsScreen(byte startX,byte startY,byte textSize){
  tft.setCursor(startX,startY);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_BLUE);
  tft.setTextSize(textSize);
  tft.println("BOOT SYSTEM");
} ;

float Display::temperature(byte startX,byte startY,byte textSize){
  
  tft.setCursor(startX,startY);
  tft.setTextColor(0xC3BF,0x0000);
  tft.setTextSize(textSize);
  temp= dht.readTemperature();
  return tft.println(temp);
};
float Display::humidity(byte startX,byte startY,byte textSize){

  tft.setCursor(startX,startY);
  tft.setTextColor(0xC3BF,0x0000);
  tft.setTextSize(textSize);
  hum= dht.readHumidity();
  return tft.println(hum);
};

Display TwoInch;

void setup() {

  TwoInch.globalBegin();
  TwoInch.header(0,0,240,70,35,0xFE4C);
  TwoInch.block(0,30,50,40,0xFE4C);
  TwoInch.block(200,0,40,20,0xFE4C);
  TwoInch.roundBlock(60,20,240,100,35,ST77XX_BLACK);
  TwoInch.block(0,80,60,70,0xA55F);
  TwoInch.block(0,160,60,70,0x865F);
  //TwoInch.greetingsScreen(0,0,3);
}

void loop() {
    delay(30000);
    TwoInch.temperature(80,95,6);
    TwoInch.humidity(80,175,6);

}
