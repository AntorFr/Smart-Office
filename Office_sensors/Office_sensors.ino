#include <Adafruit_NeoPixel.h>
#include <NewPing.h>

#define NEO_PIN            6
#define NEO_NUMPIXELS      16
#define NB_AFFICHAGE       3
#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 100 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NEO_NUMPIXELS, NEO_PIN, NEO_GRB + NEO_KHZ800);
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

int delayval = 1; 
int echantillon = 100;
int volume,light,mouv,dist;
long ech_volume,ech_light,ech_mouv,ech_dist;
int max_bright = 50;
boolean affichage;

void setup() {
  // put your setup code here, to run once:
    pixels.begin(); // This initializes the NeoPixel library.
    pinMode(9, INPUT);
    pinMode(5, INPUT);
    pinMode(A4, INPUT);
    pinMode(10, INPUT);
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);
    pinMode(A0, INPUT);
    
    affichage = true;
    ech_volume =0;
    ech_light =0;
    ech_mouv =0;

}

void loop() {
  // put your main code here, to run repeatedly:
  
  
 //Serial.println("tactile :"+String(digitalRead(9)));
 Serial.println("Mouvement :"+String(digitalRead(5)));
 //Serial.println("Obstacle :"+String(analogRead(A4)));
 
 for(int i=0;i<(echantillon);i++) {
   volume = analogRead(A1); // Reads the value from the Analog PIN A0
   light = analogRead(A2); // Reads the value from the Analog PIN A0
   mouv = digitalRead(7);

   unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
   dist = (uS / US_ROUNDTRIP_CM); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
   
   ech_volume = ech_volume + volume;  
   ech_light = ech_light + (1000-light);
   ech_mouv = max(ech_mouv,(1-mouv));
   ech_dist = ech_dist + dist;
   
   delay(delayval); 
 }
 
 ech_volume = ech_volume * 100 / (echantillon);
 ech_light = ech_light / (echantillon);
 ech_dist = (ech_dist / (echantillon) ) * 10000 / MAX_DISTANCE;
 
 //Serial.println("volume "+String(ech_volume));
 //Serial.println("light " +String(ech_light));
 //Serial.println("distance " +String(ech_dist));
 //delay(delayval); 
 
if (ech_mouv>0) {affichage = !affichage;}

if (affichage) {
   mesure_level(ech_light,0);
   mesure_level(ech_volume,1);
   mesure_level(ech_dist,2);
} else {
  empty();
}
 

ech_volume = 0;
ech_light = 0;
ech_mouv = 0;
ech_dist = 0;
 
}

void mesure_level(int mesure,int order){
  long nb_mesure;
  int color,R_color, G_color, B_color;
  if (mesure > 1000) {mesure = 1000;}
  if (mesure < 0) {mesure = 0;}

  nb_mesure = (max_bright * (long)mesure ) /1000 * (long)(NEO_NUMPIXELS/NB_AFFICHAGE) ;
  //Serial.println("mesure : "+String(mesure));
  //Serial.println("nb_mesure : "+String(nb_mesure));

   for(int i=0;i<NEO_NUMPIXELS/NB_AFFICHAGE;i++){
       color = min(max_bright,max(0,nb_mesure-(i*max_bright)));
       if(order==0) { R_color=0;G_color=color;B_color=0;}
       else if (order==1) { R_color=0;G_color=0;B_color=color;}
       else if (order==2) { R_color=color;G_color=0;B_color=0;}
       else { R_color=color;G_color=color;B_color=color;}
       pixels.setPixelColor(i+(order*NEO_NUMPIXELS/NB_AFFICHAGE), pixels.Color(R_color,G_color,B_color)); 
   }
   pixels.show();
}

void empty() {
  for(int i=0;i<NEO_NUMPIXELS;i++){
     pixels.setPixelColor(i, pixels.Color(0 ,0,0));
  }
  pixels.show();
}
