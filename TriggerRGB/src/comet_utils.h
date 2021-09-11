#include <Arduino.h>
#define FASTLED_INTERNAL
#include <FastLED.h>

extern CRGB g_LEDs[];

const byte fadeAmt = 128;


void FadeLED() {
// Random   ly fade the LEDs
    for (int j = 0; j < NUM_LEDS; j++) {
        // if (random(10) > 5)
        g_LEDs[j] = g_LEDs[j].fadeToBlackBy(fadeAmt);  
    }
}

void ClearLED() {
    for(int i = 0; i < NUM_LEDS; i++) {
        g_LEDs[i] = CRGB::Black;
    }
}