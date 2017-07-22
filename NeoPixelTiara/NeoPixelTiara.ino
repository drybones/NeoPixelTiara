//Random Flash animation for Neopixel circuits
//by Dano Wall and Becky Stern for Adafruit Industries
//based on the Sparkle Skirt, minus the accelerometer
#include <Adafruit_NeoPixel.h>

#define PIN 0
 
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(7, PIN, NEO_GRB + NEO_KHZ800);
 
// Here is where you can put in your favorite colors that will appear!
// just add new {nnn, nnn, nnn}, lines. They will be picked out randomly
//                          R   G   B
uint8_t myColors[][3] = {{255, 255, 255},  
                         {64, 255, 230},    
                         {173, 56, 107},   
                          };
                               
// don't edit the line below
#define FAVCOLORS sizeof(myColors) / 3

uint8_t glowingPixels[FAVCOLORS][2]; // state for the currently glwowing pixels

void setup() {
  strip.begin();
  strip.setBrightness(40);
  strip.show(); // Initialize all pixels to 'off'
}
 
void loop() {
flashRandom(5, 1);  // first number is 'wait' delay, shorter num == shorter twinkle
//flashRandom(5, 3);  // second number is how many neopixels to simultaneously light up
flashRandom(5, 2);
}
 
void flashRandom(int wait, uint8_t howmany) {
 
  for(uint16_t i=0; i<howmany; i++) {
    // get a random pixel from the list
    int j = random(strip.numPixels());

    // pick a random favorite color!
    int c = random(FAVCOLORS);

    glowingPixels[i][0] = j;
    glowingPixels[i][1] = c;
  }    

  // now we will 'fade' them in 5 steps
  for (int x=0; x < 5; x++) {
    for(uint16_t i=0; i<howmany; i++) {
      int c = glowingPixels[i][1];
      int red = myColors[c][0];
      int green = myColors[c][1];
      int blue = myColors[c][2]; 

      int r = red * (x+1); r /= 5;
      int g = green * (x+1); g /= 5;
      int b = blue * (x+1); b /= 5;

      strip.setPixelColor(glowingPixels[i][0], strip.Color(r, g, b));
    }
    strip.show();
    delay(wait);
  }

  // & fade out in 5 steps
  for (int x=5; x >= 0; x--) {
    for(uint16_t i=0; i<howmany; i++) {
      int c = glowingPixels[i][1];
      int red = myColors[c][0];
      int green = myColors[c][1];
      int blue = myColors[c][2]; 

      int r = red * x; r /= 5;
      int g = green * x; g /= 5;
      int b = blue * x; b /= 5;

      strip.setPixelColor(glowingPixels[i][0], strip.Color(r, g, b));
    }
    strip.show();
    delay(wait);
  }
  // LEDs will be off when done (they are faded to 0)
}

