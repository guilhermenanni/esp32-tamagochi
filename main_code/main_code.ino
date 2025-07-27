#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <BLEService.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLE2902.h>



#define device_name "bluesp"
#define device_uudi "6e400001-b5a3-f393-e0a9-e50e24dcca9e"

BLEServer* pServer = nullptr;
BLECharacteristic* pCharacteristic = nullptr;
bool isConnected = false;

#define screen_width 128
#define screen_height 64
Adafruit_SSD1306 display(screen_width, screen_height, &Wire, -1);


int state = 0;
// 0 = neutro
// 1 = feliz
// 2 = triste

const char* frame_neutral= ":|";
const char* frame_happy = ":)";
const char* frame_sad = ":(";
const char* frame_blink = ";)";

void setup(){
  setup_screen();
  setup_wifi();  
}

void loop(){
  status_bar();
  animations(); 
}

class connToCell: public BLEServerCallbacks{
    void onConnect(BLEServer *pServer) {
      isConnected = true;
      display.println("conectado com sucesso !");  
    }

    void onDisconnect(BLEServer *pServer) {
      isConnected = false;
      display.println("erro de conexão!")
      }
    }


void setup_screen(){
  display.begin(SSD1306_SWITCHCAPVCC 0x3C);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.clearDisplay();
}

void setup_wifi(){
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);  
}

void animations(){
  display.fillRect(0, 16, screen_width, screen_height - 16, SSD1306_BLACK); 
  display.setCursor(64, 32);
  switch(state){
    case 0:
      display.println(frame_neutral);
      break;
    case 1:
      display.println(frame_happy);
      break;
    case 2:
      display.println(frame_sad);
      break;
  }
  display.display();
 }

 void status_bar() {
  display.fillRect(0, 0, screen_width, 16, SSD1306_BlACK);
  
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("1:42"); //simula uma hora
  display.setCursor(125, 0);
  display.println("100%"); // simula uma porcentagem de bateria

  display.display();
}
