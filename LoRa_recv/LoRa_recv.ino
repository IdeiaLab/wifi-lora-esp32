// Bibliotecas para LoRa
#include <SPI.h>
#include <LoRa.h>


// Bibliotecas para o display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Definição dos pinos para a esp32
#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 14
#define DIO0 26

//433E6 for Asia
//866E6 for Europe
//915E6 for North America
#define BAND 915E6

// Definição do OLED
#define OLED_SDA 4
#define OLED_SCL 15
#define OLED_RST 16

// Altura e largura do display OLED, em pixels
#define SCREEN_WIDTH 128  
#define SCREEN_HEIGHT 64  

// String que armazena o que foi recebido pelo emissor LoRa
String receivedData;

// Essa variável marca o momento da execução em que um pacote foi
// recebido pela última vez
u_long lastPacketTime = -1;

bool waiting = false;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);

void setup()
{
  Serial.begin(115200);

  // Reset do display OLED via software
  pinMode(OLED_RST, OUTPUT);
  digitalWrite(OLED_RST, LOW);
  delay(20);
  digitalWrite(OLED_RST, HIGH);

  Wire.begin(OLED_SDA, OLED_SCL);

  // Inicialização do display
  int intialized = display.begin(SSD1306_SWITCHCAPVCC, 0x3C, false, false);

  if (not intialized) 
  {
    Serial.println(F("SSD1306 allocation failed!"));
    while (true);
  }

  // Preparação do display
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Receptor LoRa");
  display.display();

  Serial.println("Teste de recebimento LoRa");

  // Inicialização LoRa
  SPI.begin(SCK, MISO, MOSI, DIO0);
  LoRa.setPins(SS, RST, DIO0);

  intialized = LoRa.begin(BAND);

  if (not intialized) 
  {
    Serial.println("Starting LoRa Failed");
    while (true);
  }

  // Mostra a tela de splash IdeiaLab
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
  // Guarda o tamanho do pacote, 0 se não houver
  int packetSize = LoRa.parsePacket();

  if(packetSize > 0) 
  {
    Serial.print("Recebeu pacote ");

    // Desativa o estado de espera
    waiting = false; 

    // Reseta a variável receivedData
    receivedData = "";

    // Lê e grava a string recebida
    while (LoRa.available()) 
    {
      // Adiciona cada linha à variável receivedData
      receivedData += LoRa.readString();
      Serial.print(receivedData);
    }

    // Guarda o valor RSSI: Received Signal Strength Indicator.
    // É a força do sinal, quanto maior, melhor
    int rssi = LoRa.rssi();
    
    Serial.print(" com RSSI ");
    Serial.println(rssi);

    // Desenha as informações na tela
    drawScreen(receivedData, rssi, lastPacketTime);
    
    // Marca o momento em que esse pacote foi recebido
    lastPacketTime = millis();
  }

  // Guarda o tempo decorrido entre o recebimento do último pacote e agora
  u_long timeSinceLastPacket = millis() - lastPacketTime;

  // Mostra uma tela diferente se o tempo desde o último pacote for maior
  // que 2,5 segundos (2500 milissegundos) e não estiver em estado de espera
  if(timeSinceLastPacket > 2500UL and not waiting)
  {
    drawWaitingScreen(receivedData);

    // Reativa o estado de espera, ou seja, esta tela é impressa apenas uma vez
    // até o próximo estado de espera
    waiting = true;
  }
}

/// Essa função desenha no display uma tela com informações sobre o último pacote recebido
void drawScreen(String receivedData, int rssi, u_long lastPacketTime)
{
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Receptor LoRa\n");

  display.println("Pacote recebido!");

  display.println(receivedData);
  display.print("RSSI ");
  display.println(rssi);

  display.println();

  display.print("Latencia: ");
  display.print(millis() - lastPacketTime);
  display.println("ms");

  display.display();
}

/// Essa função desenha no display a tela de espera por novos pacotes
void drawWaitingScreen(String receivedData)
{
    display.clearDisplay();
    display.setCursor(0, 0);
    
    display.println("Ultimo pacote:");
    display.println(receivedData);

    display.print("Aguardando novo\npacote...");

    display.display();
}