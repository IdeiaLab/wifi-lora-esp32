/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/ttgo-lora32-sx1276-arduino-ide/

  Modified by Jonatha Menezes
*********/

//Library for Wi-Fi
#include <WiFi.h>

//Libraries for LoRa
#include <SPI.h>
#include <LoRa.h>

//Libraries for OLED Display
#include <Wire.h>
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

//Libraries for MQTT
#include "CayenneMQTTESP32.h"

//Includes random delay function
#include "RandomDelay.h"

//define the pins used by the LoRa transceiver module
#define SCK 5    //SPI serial clock
#define MISO 19  // SPI master input slave output
#define MOSI 27  // SPI master output slave input
#define SS 18    // LoRa Send Signal (?)
#define RST 14   // Reset
#define DIO0 26  // Digital INPUT / OUTPUT

//LoRa bandwidth
//433E6 for Asia
//866E6 for Europe
//915E6 for North America
#define BAND 866E6

//OLED pins
#define OLED_SDA 4   // I2C serial data
#define OLED_SCL 15  // I2C serial clock
#define OLED_RST 16  // Reset 
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

//Wi-Fi setup
#define WLAN_SSID "GEFIE"
#define WLAN_PASS "@F4bul0s0@$"

//Cayenne MQTT setup
#define CLIENT_ID "f6a1e3e0-2baf-11ee-8485-5b7d3ef089d0"
#define MQTT_USER "975475b0-2baf-11ee-9ab8-d511caccfe8c"
#define MQTT_PASS "9d2933bbc762e39dd8ef8de17b828ffbb82ece97"
#define MQTT_PORT 1883
#define MQTT_SERVER "mqtt.mydevices.com"

//Package setup
#define PACKAGE_LOWER_DELAY_LIMIT 500  //milisseconds of delay between packets, lower bound
#define PACKAGE_UPPER_DELAY_LIMIT 2500 //milisseconds of delay between packets, upper bound
#define PACKAGE "IdeiaLab -> "

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST); 

int counter = 0;  //Packet counter
ulong initTime, lastPackageTime = 0UL, currentDelay = 0UL; //"ulong" is an unsigned long alias, defined in RandomDelay

void setup() 
{
  //Initialize Serial Monitor
  Serial.begin(115200);

  //Reset OLED display via software
  pinMode(OLED_RST, OUTPUT);
  digitalWrite(OLED_RST, LOW);
  delay(20);
  digitalWrite(OLED_RST, HIGH);

  //Initialize OLED
  Wire.begin(OLED_SDA, OLED_SCL);
  
  if (not display.begin(SSD1306_SWITCHCAPVCC, 0x3c, false, false)) {  // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);// Don't proceed, loop forever
  }

  //Display preparations
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.display();

  //SPI LoRa pins
  SPI.begin(SCK, MISO, MOSI, SS);

  //setup LoRa transceiver module
  LoRa.setPins(SS, RST, DIO0);

  if (not LoRa.begin(BAND)) //Tries LoRa initialization
  {
    while (1);
  }

  // if(WiFi.begin(WLAN_SSID, WLAN_PASS) == WL_CONNECT_FAILED) //Tries connection to Wi-Fi
  // {
  //   while(1);
  // }

  Cayenne.begin(MQTT_USER, MQTT_PASS, CLIENT_ID, WLAN_SSID, WLAN_PASS); //MQTT initialization

  //Display IdeiaLab splash text
  display.clearDisplay();
  display.setTextSize(3);
  display.setCursor(0, 10);
  display.print(" Ideia\n  Lab");
  display.display();
  
  delay(2000);

  display.setTextSize(1);
  initTime = millis(); //Sets the initialization time
}

void loop() 
{
  showInformation();

  unsigned long currentTime = millis();

  if (not (currentTime - lastPackageTime > currentDelay) ) return; 
  //loop() only gets past this if when the difference 
  //between current time and last package is greater than the delay

  currentDelay = RandomDelay::randomDelay(PACKAGE_LOWER_DELAY_LIMIT, PACKAGE_UPPER_DELAY_LIMIT); //Returns a new delay
  lastPackageTime = currentTime;

  String loraPacket = PACKAGE + String(counter++); //Concatenate constant with counter

  //Send LoRa packet to receiver
  LoRa.beginPacket();
  LoRa.println(loraPacket);
  LoRa.print(getCurrentTime());
  LoRa.endPacket();

  Cayenne.loop(); //Calls CAYENNE_OUT_DEFAULT() and CAYENNE_IN_DEFAULT()
}

CAYENNE_OUT_DEFAULT() //Writes current counter value to dashboard
{
  Cayenne.virtualWrite(0, counter - 1);
}

CAYENNE_IN_DEFAULT()
{ }

///Displays relevant information regarding the packages
void showInformation() 
{
  ulong timeUntilNext = currentDelay - (millis() - lastPackageTime); //Time remaining to send next package

  display.clearDisplay();
  
  display.setCursor(0, 0);
  display.println("Enviador LoRa\n");
  
  display.print("Pacote:\"");
  display.print(PACKAGE);
  display.println('\"');

  display.print("Contador:");
  display.println(counter);

  display.print("Tempo corrido:");
  display.println(getCurrentTime());

  display.print("Proximo pacote:");
  display.print(timeUntilNext);
  display.println("ms");
  
  //Time until next package animation
  for(int i = 0; i < map(timeUntilNext, 0, currentDelay, 0, 21); i++)
  {
    display.print("_"); //Prints less characters as timeUntilNext decreases
  }

  display.display();
}

///Returns a string containing the application's current minutes and seconds
String getCurrentTime() 
{
  ulong totalMilisseconds = millis() - initTime;
  ulong totalSeconds = totalMilisseconds / 1000;

  ulong minutes = totalSeconds / 60;
  if (minutes < 60) //Returns minutes and seconds if less than an hour
  {
    ulong seconds = totalSeconds % 60;
    return String(minutes) + "m" + String(seconds) + "s";
  }
  
  //Returns hours and minutes if total time is one hour or more
  ulong hours = minutes / 60;
  return String(hours) + "h" + String(minutes) + "m";
}