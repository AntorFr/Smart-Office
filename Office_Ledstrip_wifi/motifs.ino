
void color(int red, int green, int blue) {
  // Update the colors.
  static unsigned long previousMillis = 0;

  unsigned long currentMillis = millis();
  
  if(currentMillis - previousMillis > 1000) {

    for(int i = 0; i < LED_COUNT; i++)
    {
      strip.setPixelColor(i, strip.Color(red, green, blue));
    }
    strip.show();
    
    previousMillis = currentMillis;
  }
}


void noir() {
  // Update the colors.
  static unsigned long previousMillis =0;

  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > 1000) {

    for(byte i = 0; i < LED_COUNT; i++)
    {
      strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
    strip.show(); 

    previousMillis = currentMillis;
  }
}

void Blink(int Initred, int Initgreen, int Initblue, int ledspeed) {
  // Update the colors.
  static unsigned long y = 0;
  static boolean sens = true;
  static unsigned long previousMillis =0;
  byte red,green,blue;
  
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > ledspeed) {
    
    float intensit = -1*pow(y/20.1,2);
    red = Initred*exp(intensit);
    green = Initgreen*exp(intensit);
    blue = Initblue*exp(intensit);
    
    for(byte i = 0; i < LED_COUNT; i++)
    {
      strip.setPixelColor(i, strip.Color(red, green, blue));
    }
    // Write the colors to the LED strip.
    strip.show(); 
    
    previousMillis = currentMillis;
    
    if (sens) y++;
    else y--;
    
    if(y>=60) sens=false;
    if(y<=0) sens =true;
  }
}

void StarTrek(int Initred, int Initgreen, int Initblue) {
  // Update the colors.
  static int y = 0;
  static unsigned long previousMillis =0;

  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > ledspeed * 1.5 ) {

    for(int i = 0; i < LED_COUNT/2; i++)
    {

      byte red,green,blue;
      if(i > y) {
        red = 0;
        green = 0;
        blue = 0;
      } 
      else {
        red = Initred/(1+(y-i)*32);
        green = Initgreen/(1+(y-i)*32);
        blue = Initblue/(1+(y-i)*32);
      }
      strip.setPixelColor(i, strip.Color(red, green, blue));
    }
    // Write the colors to the LED strip.
    y++;

    if (y == (LED_COUNT/2)) {
      y=0;
    }
    strip.show();
    previousMillis = currentMillis;
  }
}



void K2000(int Initred, int Initgreen, int Initblue) {
  // Update the colors.
  static boolean sens = true;
  static int y = 0;
  static unsigned long previousMillis =0;

  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > ledspeed ) {

    for(byte i = 0; i < LED_COUNT; i++)
    {
      byte red,green,blue;
      if(i > y) {
        red = 0;
        green = 0;
        blue = 0;
      } 
      else {
        red = Initred/(1+(y-i)*32);
        green = Initgreen/(1+(y-i)*32);
        blue = Initblue/(1+(y-i)*32);
      }
      if (sens) {
        strip.setPixelColor(i, strip.Color(red, green, blue));
      } 
      else {
        strip.setPixelColor(LED_COUNT-i, strip.Color(red, green, blue));
      }

    }
    // Write the colors to the LED strip.
    strip.show();  

    y++;

    //Serial.println(y); 
    if (y == (LED_COUNT)) {
      //Serial.println("Changement de sens."); 
      sens = !sens;
      y=0;
    }
    previousMillis = currentMillis;
  }
}

void Variation(int ledspeed) {
  uint16_t i, j;
  unsigned long currentMillis = millis();
  
  if(currentMillis - previousMillis > ledspeed ) {
    for(j=0; j<256; j++) {
      for(i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, Wheel((i+j) & 255));
      }
      strip.show();
    }
  }
  previousMillis = currentMillis;
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
