#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define LED_BACK    5
#define LED_LEFT    4
#define LED_RIGHT   6

#define LED_COUNT 64

char state = 0;
int light_delay = 50;

Adafruit_NeoPixel strip_back(LED_COUNT, LED_BACK, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_left(LED_COUNT, LED_LEFT, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_right(LED_COUNT, LED_RIGHT, NEO_GRB + NEO_KHZ800);

void setup(){
  strip_back.begin();
  strip_back.show();
  strip_back.setBrightness(150);

  strip_left.begin();
  strip_left.show();
  strip_left.setBrightness(150);

  strip_right.begin();
  strip_right.show();
  strip_right.setBrightness(150);

  Serial.begin(9600);
  delay(1000);
}

void loop(){
  rightBlink();
  delay(3000);

  leftBlink();
  delay(3000);

  stopStop();
  delay(3000);

  hazardBlink();
  delay(3000);
}


void rightBlink() {
  for (int i = 0; i < 4; i++){
    colorBlinkersRight(strip_right.Color(255,   100,   0), 50);
    delay(400);
    colorBlinkersRight(strip_right.Color(0,   0,   0), 25);
    delay(300);
  }
}
void colorBlinkersRight(uint32_t c, int wait){
  for(int i = 0; i<=15; i++){
    strip_right.setPixelColor(i, c);
  }
  for(int i = 0; i<=15; i++){
    strip_back.setPixelColor(i, c);
  }
  
  strip_right.show();
  strip_back.show();
  delay(wait);
  strip_right.clear();
  strip_back.clear();
  delay(wait);
}



void leftBlink() {
  for (int i = 0; i < 4; i++){
    colorBlinkersLeft(strip_left.Color(255,   100,   0), 50);
    delay(400);
    colorBlinkersLeft(strip_left.Color(0,   0,   0), 25);
    delay(300);
  }
}
void colorBlinkersLeft(uint32_t c, int wait){
  for(int i = 0; i<=15; i++){
    strip_left.setPixelColor(i, c);
  }
  for(int i = 16; i<=31; i++){
    strip_back.setPixelColor(i, c);
  }
  
  strip_left.show();
  strip_back.show();
  delay(wait);
  strip_left.clear();
  strip_back.clear();
  delay(wait);
}


void stopStop(){
//  colorStopLeft(strip_left.Color(255, 0, 0), 2000);
//  colorStopLeft(strip_right.Color(255, 0, 0), 2000);
//  colorStopBack(strip_left.Color(255, 0, 0), 2000);

  
  colorStop(strip_left.Color(255, 0, 0), 2000);
}
void colorStop(uint32_t c, int wait){
  for(int i = 0; i<=15; i++){
    strip_left.setPixelColor(i, c);
    strip_right.setPixelColor(i, c);
  }
  for(int i = 0; i<=31; i++){
    strip_back.setPixelColor(i, c);
  }
  
  strip_left.show();
  strip_right.show();
  strip_back.show();
  delay(wait);
  strip_left.clear();
  strip_right.clear();
  strip_back.clear();
}


void hazardBlink(){
  uint32_t c = (255, 100, 0); 
  while(1){
    for(int i = 0; i<=16; i++){
      strip_left.setPixelColor(i, c);
      strip_right.setPixelColor(i, c);
    }
    for(int i = 0; i<=31; i++){
      strip_back.setPixelColor(i, c);
    }
    strip_left.show();
    strip_right.show();
    strip_back.show();
    delay(50);
    strip_left.clear();
    strip_right.clear();
    strip_back.clear();
  }
}
