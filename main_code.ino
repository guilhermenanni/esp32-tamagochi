#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

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
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
}

void loop(){
  status_bar();
  animations();
  delay(2000);
}

void pkg_capture(){
//ainda vou fazer essa parte, mas basicamente, 
//caputra bem sucedida: state = 1;
//caputra mal sucedida: state = 2;
//sem caputra a mais de 30 minutos:
//state = 0
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
