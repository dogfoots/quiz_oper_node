#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#define PINSIG1 D1
//#define PINSIG2 D1
//#define PINSIG3 D2
//define PINSIG4 D7

//Your Domain name with URL path or IP address with path
//String reqUrl = "http://192.168.35.96:9090/?sig=1";
String reqUrl = "http://192.168.100.101:9090/?sig=";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 100;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  Serial.println();

  //WiFi.begin("SK_WiFiGIGA282B", "1702031846");
  WiFi.begin("QUIZ_OPER", "q1q2q3q4!!!");

  int cnt = 0;
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    if(cnt%2 == 1){
      digitalWrite(LED_BUILTIN, LOW);  // Turn the LED on (Note that LOW is the voltage level
    }else{
      digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
    }
    delay(500);
    Serial.print(".");
    cnt ++;
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  
  digitalWrite(LED_BUILTIN, LOW);  // Turn the LED on (Note that LOW is the voltage level
  //button in
  //pinMode(D1, INPUT);
  //pinMode(PINSIG1, INPUT);
  pinMode(PINSIG1, INPUT);
  //pinMode(PINSIG3, INPUT);
  //pinMode(PINSIG4, INPUT);
  //pinMode(D3, INPUT);
  //pinMode(D4, INPUT);
  //pinMode(D0, OUTPUT);
  
}

void sendSig(String sig){
  if(WiFi.status()== WL_CONNECTED){
    WiFiClient client;
    HTTPClient http;
    
    // Your Domain name with URL path or IP address with path
    http.begin(client, (reqUrl+sig).c_str());

    // If you need Node-RED/server authentication, insert user and password below
    //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");
      
    // Send HTTP GET request
    int httpResponseCode = http.GET();
    
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      Serial.println(payload);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
}

void loop() {

  //int var1 = digitalRead(PINSIG1);
  int var1 = digitalRead(PINSIG1);
  //int var3 = digitalRead(PINSIG3);
  //int var4 = digitalRead(PINSIG4);

  
  String sig = "";
  /*if(var1 == HIGH && var2 == LOW && var3 == LOW){
    sig = "1";
  }else if(var1 == HIGH && var2 == HIGH && var3 == LOW){
    sig = "2";
  }else if(var1 == HIGH && var2 == LOW && var3 == HIGH){
    sig = "3";
  }else if(var1 == HIGH && var2 == HIGH && var3 == HIGH){
    sig = "4";
  }*/
  if(var1 == HIGH){
    sig = "1";
  }
  

  if(sig != ""){
    digitalWrite(D0, HIGH);  // Turn the LED off by making the voltage HIGH
    sendSig(sig);
  }else{
    digitalWrite(D0, LOW);  // Turn the LED off by making the voltage HIGH
  } 
}