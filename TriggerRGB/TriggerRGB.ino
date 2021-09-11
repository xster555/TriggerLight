 #include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 59

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define LED_PIN 5
#define INTERRUPT1_PIN 2
#define INTERRUPT2_PIN 3

// Define the array of leds
CRGB leds[NUM_LEDS];

int brightness1;
int brightness2;
int brightnessDecayStep;
volatile bool firePulse1;
volatile bool firePulse2;

int sensorPin = A0;    // select the input pin for the potentiometer
int deltaBrightness = 8;  // variable to store the value coming from the sensor

unsigned long tDelay;
unsigned long tFire1;
unsigned long tFire2;

void handlePulse1() {
  tFire1 = millis();
//  deltaBrightness = analogRead(sensorPin);
//  deltaBrightness = map(tDelay, 0, 1023, 1, 20);
  brightness1 = 255;
  firePulse1 = true;
}

void handlePulse2() {
  tFire2 = millis();
//  deltaBrightness = analogRead(sensorPin);
//  tDelay = map(tDelay, 0, 1023, 1, 20);
  brightness2 = 255;
  firePulse2 = true;
}


void setup() { 
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
  pinMode(INTERRUPT1_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT1_PIN), handlePulse1, RISING);
  pinMode(INTERRUPT2_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT2_PIN), handlePulse2, RISING);
  
  firePulse1 = false;
  firePulse2 = false;
  brightness1 = 255;
  brightness2 = 255;

//  tDelay = analogRead(sensorPin);
//  tDelay = map(tDelay, 0, 1023, 1, 20);

  tDelay = 5;
  tFire1 = 0;
  tFire2 = 0;
}

void loop() {
//  turnOnRGB();
//  delay(500);
//  turnOffRGB();
//  delay(500);
  
  if(firePulse1 && millis() - tFire1 > tDelay) {
    if(brightness1 > 0) {
      for(int i = 0; i < 59; i++) {
        if(i%2 == 0) {
          leds[i] = CHSV(180, 190, brightness1);
        }
      }
      FastLED.show();
      tFire1 = millis();
      brightness1 -= deltaBrightness;
    } else {
      firePulse1 = false;  
    }
  } else {
    for(int i = 0; i < 59; i++) {
      if(i%2 == 0) {
        leds[i] = CRGB::Black;
      }
    }
    FastLED.show();
  }

  if(firePulse2 && millis() - tFire2 > tDelay) {
    if(brightness2 > 0) {
      for(int i = 0; i < 59; i++) {
        if(i%2 == 1) {
          leds[i] = CHSV(30, 190, brightness2);
        }
      }
      FastLED.show();
      tFire2 = millis();
      brightness2 -= deltaBrightness;
    } else {
      firePulse2 = false;
    }

  } else {
    for(int i = 0; i < 59; i++) {
        if(i%2 == 1) {
          leds[i] = CRGB::Black;
        }
      }
    FastLED.show();
  }
}

void turnOnRGB() {
  for(int i = 0; i < 59; i++) {
    leds[i] = CHSV(180, 190, brightness1); 
  }
  FastLED.show();
}

void turnOffRGB() {
  for(int i = 0; i < 59; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}

