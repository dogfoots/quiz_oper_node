#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

//Your Domain name with URL path or IP address with path
String reqUrl = "http://192.168.35.96:9090/?sig=2";

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

  WiFi.begin("SK_WiFiGIGA282B", "1702031846");

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
  pinMode(D0, INPUT);
  pinMode(D1, OUTPUT);
  
}

void sendSig(){
  if(WiFi.status()== WL_CONNECTED){
    WiFiClient client;
    HTTPClient http;
    
    // Your Domain name with URL path or IP address with path
    http.begin(client, reqUrl.c_str());

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

  int var = digitalRead(D0);

  if(var == HIGH){
    digitalWrite(D1, HIGH);  // Turn the LED off by making the voltage HIGH
    /*
    */
    sendSig();
  }else{
    digitalWrite(D1, LOW);  // Turn the LED off by making the voltage HIGH

  }
  
}