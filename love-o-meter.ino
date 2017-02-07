// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            14
#define TOUCH_PIN      0

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      29
// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second
int hue;
void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code
  Serial.begin(38400);
  hue=0;
  digitalWrite(6,HIGH);
  pixels.begin(); // This initializes the NeoPixel library.
}
long touch_input;
float fhue;

long getSaturation(int input) {
  long saturation = map(input, 0, 1024, 0, 255);
  if (saturation > 0) {
    return saturation;
  }
  return 0;
}

int getPixelCount(int input) {
  long count = map(input, 0, 1024, 0, NUMPIXELS);
  if (count > 0) {
    return count;
  }
  return 0;
}

void loop() {

  touch_input = 1023 - analogRead(TOUCH_PIN);
  long sat = getSaturation(touch_input);
  int pixel_count = getPixelCount(touch_input);
  
  Serial.printf("touch_input is:   %i\n", touch_input);
  Serial.printf("saturation is:    %i\n", sat);
  Serial.printf("count is:         %i\n", pixel_count);
  
  for (int i = 0; i < NUMPIXELS; i++) {
    if (i <= pixel_count) {
      pixels.setPixelColor(i, pixels.Color(sat,0,0));  
    } else {
      pixels.setPixelColor(i, pixels.Color(0,0,0));  
    }
    
  }
  delay(100);
  pixels.show();
  
}
