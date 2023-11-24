#include <SPI.h>
#include <LoRa.h>

#include <Wire.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 14
#define DIO0 26

//433E6 for Asia
//866E6 for Europe
//915E6 for North America
#define BAND 866E6

#define OLED_SDA 4
#define OLED_SCL 15
#define OLED_RST 16

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

String LoRaData;
unsigned long tempoUltimoPacote = -1;
bool noAguardo = false;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);

void setup() {
  Serial.begin(115200);

  pinMode(OLED_RST, OUTPUT);
  digitalWrite(OLED_RST, LOW);
  delay(20);
  digitalWrite(OLED_RST, HIGH);

  Wire.begin(OLED_SDA, OLED_SCL);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C, false, false)) {
    Serial.println(F("SSD1306 allocation failed!"));
    while (true);
  }

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Receptor LoRa");
  display.display();

  Serial.println("Teste de recebimento LoRa");

  SPI.begin(SCK, MISO, MOSI, DIO0);
  LoRa.setPins(SS, RST, DIO0);

  if (!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa Failed");
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(3);
  display.setCursor(0, 10);
  display.print(" Ideia\n  Lab");
  display.display();

  delay(2000);

  display.setTextSize(1);
  display.clearDisplay();
}

void loop() 
{
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    Serial.print("Recebeu pacote ");
    noAguardo = false; 

    while (LoRa.available()) {
      LoRaData = LoRa.readString();
      Serial.print(LoRaData);
    }

    int rssi = LoRa.rssi();
    Serial.print(" com RSSI ");
    Serial.println(rssi);

    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Receptor LoRa");
    display.setCursor(0, 20);
    display.print("Pacote recebido!");
    display.setCursor(0, 30);
    display.print(LoRaData);
    display.setCursor(0, 40);
    display.print("RSSI ");
    display.setCursor(30, 40);
    display.println(rssi);
    display.setCursor(0, 50);
    display.print("Latencia:");
    display.print(millis() - tempoUltimoPacote);
    display.print("ms");

    // display.print("Tamanho:");
    // display.println(packetSize);

    display.display();
    tempoUltimoPacote = millis();
    
    return;
  }

  if(millis() - tempoUltimoPacote > 2500UL and not noAguardo)
  {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Ultimo pacote:");
    display.println(LoRaData);
    display.print("Aguardando novo\npacote...");
    display.display();
    noAguardo = true;
  }
}