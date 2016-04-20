typedef struct {
  int rgb[3] ;
} rgb_color;



void color(int red, int green, int blue) {
  // Update the colors.
  static unsigned long previousMillis =0;

  unsigned long currentMillis = millis();
  
  if(currentMillis - previousMillis > 1000) {

    for(byte i = 0; i < LED_COUNT; i++)
    {
      colors[i] = (rgb_color){ red, green, blue};
    }
    // Write the colors to the LED strip.
    ledStrip.write(colors, LED_COUNT);  

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
      colors[i] = (rgb_color){ 0, 0, 0};
    }
    // Write the colors to the LED strip.
    ledStrip.write(colors, LED_COUNT);  

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
      colors[i] = (rgb_color){ red, green, blue};
    }
    // Write the colors to the LED strip.
    ledStrip.write(colors, LED_COUNT);  
    
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
  int Ledmax = 30;

    //for(byte i = 0; i < LED_COUNT/2; i++)
    for(byte i = 0; i < Ledmax/2; i++)
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
      
      for (byte j = 0; j < LED_COUNT/(Ledmax); j++) 
      {
       colors[j*Ledmax+i] = (rgb_color){ red, green, blue};
       colors[j*Ledmax+Ledmax-1-i] = (rgb_color){ red, green, blue};
      }
    }
    // Write the colors to the LED strip.
    ledStrip.write(colors, LED_COUNT);  

    y++;

    if (y == (Ledmax/2)) {
      y=0;
    }
    previousMillis = currentMillis;
  }
}



void K2000(int Initred, int Initgreen, int Initblue) {
  // Update the colors.
  static boolean sens = true;
  static int y = 0;
  static unsigned long previousMillis =0;
  int Ledmax = 30;

  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > ledspeed ) {

    //for(byte i = 0; i < LED_COUNT; i++)
    for(byte i = 0; i < Ledmax; i++)
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
        colors[i] = (rgb_color){ red, green, blue};
        colors[LED_COUNT-1-i] = (rgb_color){ red, green, blue};
      } 
      else {
        colors[Ledmax-1-i] = (rgb_color){ red, green,blue };
        colors[LED_COUNT-Ledmax+i] = (rgb_color){ red, green,blue };
      }

    }
    // Write the colors to the LED strip.
    ledStrip.write(colors, LED_COUNT);  

    y++;

    //Serial.println(y); 
    if (y == (Ledmax)) {
      //Serial.println("Changement de sens."); 
      sens = !sens;
      y=0;
    }
    previousMillis = currentMillis;
  }
}

void Variation(int ledspeed) {
  // Update the colors.
  // ledspeed = 25
  static unsigned long y = 0;
  static unsigned long previousMillis =0;

  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > ledspeed) {

    byte red,green,blue;
    // fade from blue to violet
    if (y<256*1) { 
      red = y;
      green = 0;
      blue = 255;
    } 
    // fade from violet to red
    else if (y< (256*2)) { 
      red = 255;
      green= 0;
      blue = (256*2-1) - y;
  
    } 
    // fade from red to yellow
    else if (y< (256*3))  { 
      blue = 0;
      red = 255;
      green = y - (256*2);
  
    } 
    // fade from yellow to green
    else if (y< (256*4)) { 
      blue = 0;
      green = 255;
      red = (256*4-1) - y;
  
    } 
    // fade from green to teal
    else if (y<(256*5)) { 
      red= 0;
      green = 255;
      blue = y - (256*4); 
    } 
    // fade from teal to blue
    else if (y<(255*6)) {
     red = 0;
     blue = 255; 
     green = (256*6-1) - y;
    
    }     
    
    for(byte i = 0; i < LED_COUNT; i++)
    {
      colors[i] = (rgb_color){ red, green, blue};
    }
    // Write the colors to the LED strip.
    ledStrip.write(colors, LED_COUNT);  
    
    previousMillis = currentMillis;
    y++;
    if (y> 256*6) y=0;
  }
}

void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
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
