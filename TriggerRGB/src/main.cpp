
#include <Arduino.h>            // Arduino Framework
#define FASTLED_INTERNAL        // Suppress build banner
#include <FastLED.h>


#define NUM_LEDS    25          // Led number
#define LED_PIN     5           // Led data pin
#define SENSOR1_Pin A0          // Custom control 1
#define SENSOR2_Pin A1          // Custom control 2
#define INTERRUPT1_PIN 2        // Trigger input 1
#define INTERRUPT2_PIN 3        // Trigger input 2

CRGB g_LEDs[NUM_LEDS] = {0};    // Frame buffer for FastLED

int g_lineHeight = 0;
int g_Brightness = 255;           // 0-255 LED brightness scale

volatile bool firePulse1 = false;
volatile bool firePulse2 = false;
unsigned long tDelay = 15;
unsigned long tFire1 = 0;
unsigned long tFire2 = 0;
unsigned long tDelayCheck = 0;


// Comet status
const int cometSize = 2;
int cPos0 = NUM_LEDS / 2 - 1;
int cPos1 = NUM_LEDS / 2;
int crPos0 = 0;
int crPos1 = NUM_LEDS - 1;


#include "comet.h"
#include "comet_reverse.h"
#include "comet_utils.h"


void handlePulse1() {
  tFire1 = millis();
  firePulse1 = true;
  CometResetPos();
}

void handlePulse2() {
  tFire2 = millis();
  firePulse2 = true;
  CometReverseResetPos();
}


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  FastLED.addLeds<WS2812B, LED_PIN, GRB>(g_LEDs, NUM_LEDS);               // Add our LED strip to the FastLED library
  FastLED.setBrightness(g_Brightness);
  FastLED.setMaxPowerInMilliWatts(900);

  pinMode(INTERRUPT1_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT1_PIN), handlePulse1, RISING);
  pinMode(INTERRUPT2_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT2_PIN), handlePulse2, RISING);
  
  ClearLED();
  CometResetPos();
  CometReverseResetPos();
}

void loop() {
  // Analog input1 custom function
  tDelay = analogRead(SENSOR1_Pin);
  tDelay = map(tDelay, 0, 1023, 10, 30);

  // Use analog input 1 to control led decay time
  if(millis() - tDelayCheck > tDelay) {
    if(firePulse1) {
      if(CometReachEnd()) {
        firePulse1 = false;      
      }
      tFire1 = millis();
      DrawComet();
    } 

    if(firePulse2) {
      if(CometReverseReachEnd()) {
        firePulse2 = false;    
      }
      tFire2 = millis();
      DrawCometReverse();
    } 
    FadeLED();
      
    FastLED.show(g_Brightness);

    tDelayCheck = millis();
  }
}