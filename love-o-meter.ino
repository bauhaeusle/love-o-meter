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
#define NUMPIXELS      12
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
int val;
float fhue;


void loop() {

  NUMPIXELS

  val = analogRead(TOUCH_PIN);
  Serial.print("analog 0 is: ");
  Serial.println(val);
  fhue = map(val, 700, 1023, 0, 255);
  
  Serial.print("hue is: ");
  Serial.println(hue%(255/NUMPIXELS));
  if (fhue > 20.0) {
    hue = (int) fhue;
  } else {
    hue = 0;
  }
  for (int i = 0; i < NUMPIXELS%(255/hue); i++) {
    pixels.setPixelColor(i, pixels.Color(hue,0,0));
  }
  delay(100);
  pixels.show();
  
}
