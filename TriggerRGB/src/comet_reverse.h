#include <Arduino.h>
#define FASTLED_INTERNAL
#include <FastLED.h>

extern CRGB g_LEDs[];


void CometReverseResetPos() {
    
    crPos0 = 0;
    crPos1 = NUM_LEDS - 1;
    
}

bool CometReverseReachEnd() {
    return (crPos0 > crPos1);
}

void DrawCometReverse(){
    const int deltaHue  = 4;

    static byte hue0 = HUE_AQUA;
    static byte hue1 = HUE_AQUA;
    static int iDirection0 = 1;

    // hue0 += deltaHue;
    // hue1 += deltaHue;

    if(!CometReverseReachEnd()) {
        for (int i = 0; i < cometSize; i++) {
            g_LEDs[crPos0 + i].setHue(
                g_LEDs[crPos0 + i].getLuma() + hue0
            );
            
            g_LEDs[crPos1 - i].setHue(
                g_LEDs[crPos1 - i].getLuma() + hue1
            );
        }

        crPos0 += iDirection0;
        crPos1 -= iDirection0;
    }
}
