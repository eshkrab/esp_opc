#include "OPC.h"
#include <WiFi.h>
#include <Adafruit_NeoPixel.h>

const char* ssid     = "the worst wifi";
const char* password = "rogerroger";

const char* host = "192.168.0.100";
const int server_port = 7000;
bool connected;

#define LED_PIN 13
#define NUM_PIXELS 15

Adafruit_NeoPixel leds = Adafruit_NeoPixel(NUM_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  delay(100);


  //TEST
  //uint8_t buf[4];
  //buf[0] = 1;
  //buf[1] = 2;
  //buf[2] = 3;
  //buf[3] = 4;
  //
  //msg.parse(buf);
  //Serial.println(msg.cmd);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.disconnect(true);
  delay(500);
  WiFi.begin(ssid, password);

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  //set in sta mode
  WiFi.mode(WIFI_STA);
  delay(100);
  
  //register event handler
  WiFi.onEvent(WiFiEvent);
  delay(100);

}

void loop() {
  
  WiFiClient client;
  if (!client.connect(host, server_port)) {
    Serial.println("connection failed");
    return;
  }
  Serial.println("connection worked");
  //client.print("hi spencer. how do i escape");

  Serial.println("after print");
  unsigned long timeout = millis();
  //while (client.available() == 0) {
  //  Serial.println("in while loop");  
  //  Serial.println(millis() - timeout);
  //    if (millis() - timeout > 5000) {
  //      Serial.println(">>> Client Timeout !");
  //      client.stop();
  //      return;
  //    }
  //  delay(50);
  //}

  //int num_bytes = client.available();

    // Read all the lines of the reply from server and print them to Serial
    Serial.println(millis());
    if(client.available()) {
        Serial.print(client.read());
    }else {
      Serial.println("nothing");
    }
    delay(100);
  //4 IS THE SMALLEST POSSIBLE MESSAGE
  //if(num_bytes >= 6) {
  //  //String line = client.readStringUntil('\r');
  //  //Serial.print(line);
  //  uint8_t buf[MAX_DATA_LEN + 3];
  //  client.read(buf, num_bytes);
  //
  //  Serial.println("msg: ");
  //  for (int i=0; i<num_bytes; i++) {
  //    Serial.print(buf[i]);
  //  }
  //  Serial.println();
  //  
  //  OPCMessage msg = OPCMessage();
  //  msg.parse(buf);
  //
  //  Serial.println("got an opc message:");
  //  Serial.println(msg.chan);
  //  Serial.println(msg.cmd);
  //  Serial.println(msg.len);
  //  
  //
  //  for (int i=0; i<msg.len; i=i+3) {
  //    leds.setPixelColor(i/3, msg.data[i]);
  //    leds.setPixelColor(i/3+1, msg.data[i]+1);
  //    leds.setPixelColor(i/3+2, msg.data[i]+2);
  //  }
  //  leds.show();
  //}
  //else{
  //  while(client.available()){
  //    Serial.print("b: ");
  //    Serial.println(client.read());  
  //  }  
  //}

   client.stop();
   delay(500);

}

//wifi event handler
void WiFiEvent(WiFiEvent_t event){
  switch(event) {
    case SYSTEM_EVENT_STA_GOT_IP:
      //When connected set 
      Serial.print("WiFi connected! IP address: ");
      Serial.println(WiFi.localIP());  
      connected = true;
      break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
      Serial.println("WiFi lost connection");
      connected = false;
      break;
  }
}
