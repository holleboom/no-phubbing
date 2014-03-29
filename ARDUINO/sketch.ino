
#include <Adafruit_NeoPixel.h>  //Adafruit Neo Pixel ring library
#include <MeetAndroid.h>;      // Amarino library
#include <HSBColor.h>          // HSB to RGB library


#define PIN 13      // LED pin
#define debug 0    // Debug aan of uit

#define TWITTER 9



boolean running = false;
boolean phubbing = false;

int h;

MeetAndroid meetAndroid;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);


int idle_saturation = 50;
int idle_brightness = 15;

int phubbing_brightness = 99;
int phubbing_saturation = 99;

int pickupAngle = 10;
int phubbingAngle = 25;


void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600); // initialization
  meetAndroid.registerFunction(switchModes, 'A');  // Koppel elk ontvangen bericht aan functie


}

void loop() {
  meetAndroid.receive(); // Start met luisteren op seriële poort.

}


void switchModes(byte flag, byte numOfValues){
  float orientation[numOfValues];
  meetAndroid.getFloatValues(orientation);

  int rotation = orientation[0];

  if(rotation<241){
    h = map(rotation, 0, 240, 0, 255);  // Hoek mappen naar byte value
  } 
  else {
    h = map(rotation, 240, 360, 255, 0);  // Hoek mappen naar byte value
  }


  int angle = abs(orientation[1]);  // Hoek absoluut maken

  if(angle >= 90){
    angle = abs(angle-180);
  }

  Serial.println(angle);

  if(running == false){
    for(uint16_t i=0; i<idle_brightness+1; i++) {
      int rgb[3] = { 
        0,0,0       };

      H2R_HSBtoRGB(h, idle_saturation, i, rgb);
      for(uint16_t j=0; j<16; j++) {
        strip.setPixelColor(j,rgb[0],rgb[1],rgb[2]);
      }
      strip.show();
      delay(25);
    }
    running = true;
  }

  if(angle<phubbingAngle)
    {
      if(phubbing == true){
        
        if(debug){
              Serial.println("Telefoon op tafel");
        }

        }
      

      int b = map(angle, 0, phubbingAngle, idle_brightness, 0);  // Definieer/map brightness
      //int b = idle_brightness;
      int rgb[3] = {
        0,0,0            };
      H2R_HSBtoRGB(h, idle_saturation, b, rgb);

      setColor(rgb[0],rgb[1],rgb[2],0); // Stel kleur in zonder knipperfrequentie.

    }

//  else if(angle>=pickupAngle && angle<phubbingAngle)
//
//    {
//      if(debug){
//        if(!phubbing){
//          Serial.println("Telefoon opgepakt");
//        }
//      }
//      int s = map(angle, pickupAngle, phubbingAngle, idle_saturation-10, 0);  // Definieer/map brightness
//      int b = map(angle, pickupAngle, phubbingAngle, idle_brightness-10, 0);  // Definieer/map brightness
//      int rgb[3] = { 
//        0,0,0       };
//      H2R_HSBtoRGB(h, b, b, rgb);
//      setColor(rgb[0],rgb[1],rgb[2],0); // Stel kleur in zonder knipperfrequentie.
//    }
  else if(angle>=phubbingAngle)
    {
      if(phubbing == false){
        if(debug){
          Serial.println("Telefoon in gebruik");
        }

      } 

      int b = map(angle, phubbingAngle, 45, 0, 99);  // Definieer/map brightness
      int s = b;
      int rgb[3] = { 
        0,0,0       };               
      H2R_HSBtoRGB(0, s, b, rgb);        
      setColor(rgb[0],rgb[1],rgb[2],0);
      delay(100);
      setColor(rgb[0],rgb[1],0,0);


    }
  

}

void setColor(int r, int g, int b, int wait){
  for(uint16_t i=0; i<16; i++) {
    strip.setPixelColor(i,r,g,b);
  }
  strip.show();
  if(wait>0){
    delay(wait);
    for(uint16_t i=0; i<16; i++) {
      strip.setPixelColor(i,0,0,0);
    }
    strip.show();
    delay(wait/2); 
  }
}

