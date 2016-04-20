
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#define MSR_PIN D4       // Motion sensor Right Pin
#define MSL_PIN D5       // Motion sensor Left Pin

// Existing WiFi network
const char* ssid     = "Niji-Phone";
const char* password = "";

int MSR = 0, MSL = 0, MS =0;
int cnt_MSR = 0, cnt_MSL = 0, cnt_MS = 0;
bool presence_R = false, presence_L = false, presence = false;
int Hist_R[10], Hist_L[10], Hist[10];


unsigned long previousMillis = 0;
const long sensor_interval = 60000;  // Wait this long until reading again
const long updt_interval   = 120000;  // Wait this long until reading again

const String api_user = "4a0RDk";
const String api_secret = "c9pBLXmnSaoFiDcA";

WiFiClient client;

void setup(void)
{
  pinMode(MSR_PIN, INPUT);
  pinMode(MSL_PIN, INPUT);
  
  // Open the Arduino IDE Serial Monitor to see what the code is doing
  Serial.begin(9600);

  Serial.println("WeMos Motion Client");
  Serial.println("");

  // Connect to your WiFi network
  WiFi.begin(ssid);
  Serial.print("Connecting");

  // Wait for successful connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to: ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("");
  Serial.print("Mac adresse: ");
  Serial.println(WiFi.macAddress());
  Serial.println("");
  
  //read_motion_sensor();
  
  MSR = digitalRead(MSR_PIN);
  MSL = digitalRead(MSL_PIN);

}


void loop(void)
{
    read_motion_sensor();
   
}

void read_motion_sensor(void) {
  unsigned long currentMillis = millis();
  
  int old_MSR = MSR;
  int old_MSL = MSL;
  int old_MS = MS;
  
  MSR = digitalRead(MSR_PIN);
  MSL = digitalRead(MSL_PIN);
  
  if(MSR == MSL) {
    MS = MSR;
  }
  
  if (old_MSR!=MSR && MSR == LOW) {
    Serial.println("MSR to low");
  }
   
  if (old_MSR!=MSR && MSR == HIGH) {
    cnt_MSR++;
    Serial.println("cnt_MSR :"+String(cnt_MSR));
  }

  if (old_MSL!=MSL && MSL == HIGH) {
    cnt_MSL++;
    Serial.println("cnt_MSL :"+String(cnt_MSL));
  }
  
  if (old_MS!=MS && MS == HIGH) {
    cnt_MS++;
    Serial.println("cnt_MS :"+String(cnt_MS));
  }
    
  if (currentMillis - previousMillis >= sensor_interval) {
      previousMillis = currentMillis;
      
      memcpy(&Hist_R[1], &Hist_R[0], (sizeof(Hist_R)-1)*sizeof(*Hist_R));
      memcpy(&Hist_L[1], &Hist_L[0], (sizeof(Hist_L)-1)*sizeof(*Hist_L));
      memcpy(&Hist[1], &Hist[0], (sizeof(Hist)-1)*sizeof(*Hist));
     
      Hist_R[0] = cnt_MSR;
      Hist_L[0] = cnt_MSL;
      Hist[0] = cnt_MS;
      
      cnt_MSR = 0;
      cnt_MSL = 0;
      cnt_MS = 0;
      
      int somme = 0;
      int old_presence = presence;
      
      if(!presence) {
         for (int i = 0 ; i < 10 ; i++) {   
          somme += Hist_R[i];
           if(i<3 && somme > 5) {
             presence = true;
             break;
           }
         }
         if (somme >= 10) {
            presence = true;
         }

      } else {
        for (int i = 0 ; i < 10 ; i++) {   
          somme += Hist_R[i];
         }
         if (somme < 3) {
            presence = false;
         }
      }
    if(old_presence != presence) {
      Serial.println("Presence vient de changer");
      eedomus_writedata("390035", (presence?"1":"O"));
    }
  }
}

void eedomus_writedata(String periph_id, String value){
  String data="";
  data="action=periph.value&periph_id="+periph_id+"&value="+value+"&api_secret="+api_secret+"&api_user="+api_user;
  
  //Serial.println(data);
 
  // Listen for http requests
  if (client.connect("api.eedomus.com",80)) { // REPLACE WITH YOUR SERVER ADDRESS
		client.println("POST /set?"+data+" HTTP/1.1"); 
		client.println("Host: api.eedomus.com"); // SERVER ADDRESS HERE TOO
		client.println("Content-Type: application/x-www-form-urlencoded"); 
		client.print("Content-Length: "); 
		client.println(data.length()); 
		client.println(); 
		client.print(data); 
   }else {
      Serial.println("erreur connection - api.eedomus.com");
   } 

   if (client.connected()) { 
      client.stop();	// DISCONNECT FROM THE SERVER
   }
  
}
