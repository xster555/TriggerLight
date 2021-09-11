#include <Arduino.h>
#define FASTLED_INTERNAL
#include <FastLED.h>

extern CRGB g_LEDs[];

void CometResetPos() {
    if(NUM_LEDS % 2 == 1) {
        cPos0 = NUM_LEDS / 2 - 1;
        cPos1 = NUM_LEDS / 2;
    } else {
        cPos0 = NUM_LEDS / 2;
        cPos1 = NUM_LEDS / 2;
    }
}

bool CometReachEnd() {
    return (cPos0 > (NUM_LEDS - cometSize));
}


void DrawComet(){
    const int deltaHue  = 4;

    static byte hue0 = HUE_ORANGE;
    static byte hue1 = HUE_ORANGE;
    static int iDirection0 = 1;

    // hue0 += deltaHue;
    // hue1 += deltaHue;

    if(!CometReachEnd()) {
        cPos0 += iDirection0;
        cPos1 -= iDirection0;
    
        for (int i = 0; i < cometSize; i++) {
            g_LEDs[cPos0 + i].setHue(
                hue0
            );
            g_LEDs[cPos1 - i].setHue(
                hue0
            );
        }
    }
}


