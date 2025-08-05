
#include <FastLED.h>

#define NUM_LEDS    30  //Strip lenght
#define BRIGHTNESS  255 //Grand master

CRGB leds[NUM_LEDS];  //Framebuffer

enum stateEnum {  //Master state
  avail,
  toAvail,
  busy,
  toBusy,
  init
};
stateEnum state = init;

int animFrame;  //Animation frame index

void setup() {
  //Setup serial
  Serial.begin(115200);

  //Setup LED strip
  FastLED.addLeds<WS2811, 5, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);

  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Green;
  }

  FastLED.show();

}

void loop()
{
  //Handle serial input
  switch (Serial.read())
  {
    case 48: //(ASCII 0) Available
      state = toAvail;
      animFrame = 0;
      break;

    case 49: //(ASCII 1) Busy
      state = toBusy;
      animFrame = 0;
      break;
    
    default:  //If invalid data byte, do nothing
      break;
  }
  
  
  //Render animantion to framebuffer
  switch (state) {
    case toAvail: //Transitioning to green
        leds[animFrame] = CRGB::Green;  //Set next pixel to green
        animFrame++;

        if(animFrame == NUM_LEDS)  //If at end of strip, go to steady state
          state = avail;
      break;

    case toBusy: //Transitioning to red
      leds[animFrame] = CRGB::Red;  //Set next pixel to green
      animFrame++;

      if(animFrame == NUM_LEDS)  //If at end of strip, go to steady state
        state = avail;
    break;

    case init:  //Default at bootup
      leds[0] = CRGB::Green;
      leds[1] = CRGB::Red;
    break;
    
    default:  //Otherwise in steady state so do nothing
      break;
  }

  FastLED.show(); //Output frame
  delay(50); //Sleep for 50ms, thus animations play at 20fps
}