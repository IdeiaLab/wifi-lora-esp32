/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/ttgo-lora32-sx1276-arduino-ide/

  Modified by Jonatha Menezes
*********/

// Biblioteca para Wi-FI
#include <WiFi.h>

// Bibliotecas para LoRa
#include <SPI.h>
#include <LoRa.h>

// Bibliotecas para o display OLED
#include <Wire.h>
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

// Biblioteca MQTT
#include "CayenneMQTTESP32.h"

// Biblioteca que gera um atraso aleatório
#include "RandomDelay.hpp"

// Definição dos pinos para LoRa
#define SCK 5    //SPI serial clock
#define MISO 19  // SPI master input slave output
#define MOSI 27  // SPI master output slave input
#define SS 18    // LoRa Send Signal
#define RST 14   // Reset
#define DIO0 26  // Digital INPUT / OUTPUT

// LoRa banda larga
//433E6 Asia
//866E6 Europe
//915E6 America do Norte
#define BAND 915E6

// Pinos OLED
#define OLED_SDA 4  // I2C serial data
#define OLED_SCL 15  // I2C serial clock
#define OLED_RST 16  // Reset 
#define SCREEN_WIDTH 128 // Largura do display OLED, em pixels
#define SCREEN_HEIGHT 64  // Altura do display OLED, em pixels

// Nome e senha do Wi-Fi
#define WLAN_SSID "GEFIE"
#define WLAN_PASS "@F4bul0s0@$"

// Cayenne MQTT setup
#define CLIENT_ID "f6a1e3e0-2baf-11ee-8485-5b7d3ef089d0"
#define MQTT_USER "975475b0-2baf-11ee-9ab8-d511caccfe8c"
#define MQTT_PASS "9d2933bbc762e39dd8ef8de17b828ffbb82ece97"
#define MQTT_PORT 1883
#define MQTT_SERVER "mqtt.mydevices.com"

// Definição do pacote
constexpr u_long PACKAGE_LOWER_DELAY_LIMIT = 500;  // Mínimo de atraso, em milissegundos, entre pacotes
constexpr u_long PACKAGE_UPPER_DELAY_LIMIT = 2500; // Máximo de atraso, em milissegundos, entre pacotes
constexpr auto PACKAGE = "IdeiaLab -> "; // Pacote a ser enviado

// Criação do objeto "display" da classe Adafruit_SSD1306
Adafruit_SSD1306 display = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST); 

// Contador de pacotes enviados
uint8_t counter = 0;  

// u_long é o tipo long (int32) sem sinal (0 a 2^32 - 1)
u_long initTime, lastPackageTime = 0, currentDelay = 0;

void setup() 
{
  // Inicializa monitor serial
  Serial.begin(115200);

  // Variável booleana que receberá o retorno das inicializações
  int initialized;

  // Reset do display OLED via software
  pinMode(OLED_RST, OUTPUT);
  digitalWrite(OLED_RST, LOW);
  delay(20);
  digitalWrite(OLED_RST, HIGH);

  // Inicializa OLED
  Wire.begin(OLED_SDA, OLED_SCL);

  // Endereço 0x3C para 128x32
  initialized = display.begin(SSD1306_SWITCHCAPVCC, 0x3c, false, false);

  if (not initialized) 
  {  
    Serial.println(F("SSD1306 allocation failed"));
    while(true);// Loop infinito
  }

  // Preparação do display
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.display();

  // Pinos SPI LoRa
  SPI.begin(SCK, MISO, MOSI, SS);

  // Definição dos pinos LoRa
  LoRa.setPins(SS, RST, DIO0);

  // Tenta inicialização do LoRa
  initialized = LoRa.begin(BAND);
  if (not initialized) 
  {
    Serial.println(F("LoRa initialization failed"));
    while(true);
  }

  //Tenta conexão com Wi-Fi
  if(WiFi.begin(WLAN_SSID, WLAN_PASS) == WL_CONNECT_FAILED) 
  {
    Serial.println(F("Wi-Fi initialization failed"));
    while(true);
  }

  // Inicializa MQTT 
  // Cayenne.begin(MQTT_USER, MQTT_PASS, CLIENT_ID, WLAN_SSID, WLAN_PASS); 

  // Mostra texto splash do IdeiaLab
  display.clearDisplay();
  display.setTextSize(3);
  display.setCursor(0, 10);
  display.print(" Ideia\n  Lab");
  display.display();
  
  delay(2000);
  
  display.setTextSize(1);
  initTime = millis(); // Marca o tempo de inicialização
}

void loop() 
{
  showInformation();

  // Atualiza o tempo atual de execução
  u_long currentTime = millis();

  // Verifica se o tempo corrido desde o envio do último pacote
  // é maior que o tempo de atraso (delay) atual; 
  // que é inicialmente 0, mas é gerado um número após o primeiro envio
  bool delayOver = (currentTime - lastPackageTime) > currentDelay;

  // O método loop retorna cedo caso o tempo de delay ainda não tenha passado
  if (not delayOver) 
  { return; }
  
  // Gera-se um tempo de atraso pseudo-aleatório, dado os limites inferior e superior;
  currentDelay = RandomDelay::randomDelay(PACKAGE_LOWER_DELAY_LIMIT, PACKAGE_UPPER_DELAY_LIMIT);
  // O ponto no tempo de envio passa a ser o tempo atual
  lastPackageTime = currentTime;

  // Define-se parte do pacote a ser enviado, a constante PACKAGE
  // concatenada ao valor de string da variável counter
  String loraPacket = PACKAGE + String(counter);

  counter++;

  // Por fim, o envio do pacote
  LoRa.beginPacket();
  // Enviando o pacote definido concatenado ao tempo atual
  LoRa.print(loraPacket + " " + getCurrentTime());
  LoRa.endPacket();

  // Chama CAYENNE_OUT_DEFAULT() e CAYENNE_IN_DEFAULT()
  // Cayenne.loop(); 
}

CAYENNE_OUT_DEFAULT() 
{ }

CAYENNE_IN_DEFAULT()
{ }

/// Mostra no display informações a respeito do enviador
void showInformation() 
{
  // Tempo que resta até o envio do próximo pacote
  u_long timeUntilNext = currentDelay - (millis() - lastPackageTime); 

  display.clearDisplay();
  
  display.setCursor(0, 0);
  display.println("Enviador LoRa\n");
  display.print(R"(Pacote:")");
  display.print(PACKAGE);
  display.println(R"(")");

  display.print("Contador:");
  display.println(counter);

  display.print("Tempo corrido:");
  display.println(getCurrentTime());

  display.print("Proximo pacote:");
  display.print(timeUntilNext);
  display.println("ms");
  
  // Animação simples com sublinhas
  // Mapeia o valor de timeUntilNext, que pode ser de 0 a currentDelay
  // Para um valor entre 0 e 21
  int underscores = map(timeUntilNext, 0, currentDelay, 0, 21);
  
  for(int i = 0; i < underscores; i++)
  {
    // Imprime underscores vezes o caractere '_'
    display.print("_"); 
  }

  display.display();
}

/// Função que retorna uma String formatada com o tempo de execução do programa
String getCurrentTime() 
{
  u_long totalMilisseconds = millis() - initTime;
  u_long totalSeconds = totalMilisseconds / 1000;

  u_long minutes = totalSeconds / 60;

  // Retorna em minutos e segundos caso o tempo seja menos que uma hora
  if (minutes < 60) 
  {
    u_long seconds = totalSeconds % 60;
    return String(minutes) + "m" + String(seconds) + "s";
  }
  
  // Retorna horas e minutos caso o tempo seja uma hora ou mais
  u_long hours = minutes / 60;
  return String(hours) + "h" + String(minutes) + "m";
}