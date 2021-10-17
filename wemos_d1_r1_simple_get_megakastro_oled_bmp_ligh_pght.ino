    /* This sketch sends data via HTTP GET requests to esp8266-shop.com and returns the website in html format which is printed on the console */ 
#include <ESPWiFi.h>
#include <ESPHTTPClient.h>
#include <JsonListener.h>
#include <Wire.h>
#include "SSD1306Wire.h" 
#include "OLEDDisplayUi.h" 
#include <Adafruit_BMP085.h>
SSD1306Wire  display(0x3c, D3, D4);
OLEDDisplayUi   ui( &display );

 
#define DHTPIN D5    // what digital pin we're connected to  pin2 to D4 on esp board

/***************************
 * Begin Atmosphere and Light Sensor Settings
 **************** **********/
void readLight();
Adafruit_BMP085 bmp;
void readAtmosphere();

const int Light_ADDR = 0b0100011;   // address:0x23
const int Atom_ADDR = 0b1110111;  // address:0x77
int tempLight = 0;
int tempAtom = 0;

const int I2C_DISPLAY_ADDRESS = 0x3c;
#if defined(ESP8266)
//const int SDA_PIN = D1;
//const int SDC_PIN = D2;

const int SDA_PIN = D3;
const int SDC_PIN = D4;
#else
//const int SDA_PIN = GPIO5;
//const int SDC_PIN = GPIO4 

const int SDA_PIN = GPIO0;
const int SDC_PIN = GPIO2 
#endif


// Uncomment whatever DHT sensor type you're using!
// #define DHTTYPE DHT11  // DHT 11
//#define DHTTYPE DHT21  // DHT 21
//#define DHTTYPE DHT22  // DHT 22data

// DHT dht(DHTPIN,DHTTYPE);

    const char* ssid = "**************";     
    char* password = "***********";     
  
   char* host = "www.megakastro.gr";
   int Temperature_Cel = 0; //temperature
   int Temperature_Fehr ;
   int T ;
   int Humidity = 0; //humidity
   int RH ;
 
float HeatIndex_Fehr ;
float HeatIndex_Cel ;
long readTime = 0; 
long uploadTime = 0; 

void readTemperatureHumidity();

    void setup() { Serial.begin(115200); // start of SETUP
    
    delay(10); // We start by connecting to a WiFi network Serial.println();
    Serial.println(); 
    Serial.print("Connecting to ");
    Serial.println(ssid);
    /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default, would try to act as both a client and an access-point and could cause network-issues with your other WiFi-devices on your WiFi-network. */
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
    delay(500);
    Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: "); 
    delay(1000);
    Serial.println(WiFi.localIP()); } 


    
    int value = 0;
    
    void loop() { delay(5000); ++value; 


    
    Serial.print("connecting to ");
    Serial.println(host); // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
    }
    
    // Wait a few seconds between measurements.
  delay(2000);

 
 //Read Temperature Humidity every 5 seconds
  if(millis() - readTime > 5000){
 
readTemperatureHumidity();
readLight();
// readAtmosphere();
  Serial.print("Humidity: ");
  Serial.print(Humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(Temperature_Cel);
  Serial.print(" *C ");
  Serial.print(Temperature_Fehr);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(HeatIndex_Cel);
  Serial.print(" *C ");
  Serial.print(HeatIndex_Fehr);
  Serial.println(" *F\n");
  Serial.print(tempLight);
  Serial.println(" Lux");
  Serial.print("Pressure:");
  Serial.print(tempAtom);
  Serial.println(" Pascal");

  }

    String data = "Humidity="
          +                        (String) Humidity
          +  "&Temperature_Cel="  +(String) Temperature_Cel
          +  "&Temperature_Fehr=" +(String) Temperature_Fehr
          +  "&HeatIndex_Cel="    +(String) HeatIndex_Cel
          +  "&HeatIndex_Fehr="   +(String) HeatIndex_Fehr 
          +  "&Light="            +(String) tempLight
          +  "&Pressure="         +(String) tempAtom;
        Serial.println(data);  
    
    // We now create a URI for the request 
    //this url contains the informtation we want to send to the server
    //if esp8266 only requests the website, the url is empty
    String url = "/dataCollector.php?"+data;
  
    //Upload Temperature Humidity every 60 seconds
  if(millis() - uploadTime > 60000){
    display.init();
  display.clear();

  display.print(Temperature_Cel);
   String temp1 = "Temperature_Cel="+String(Temperature_Cel)+"oC" ;
  String temp2=" Humidity="+String(Humidity)+"%";
display.drawString(0 , 0 , temp1);
display.drawString(0 , 8 , temp2);
display.display();
 
    Serial.print("Requesting URL: ");
    Serial.println(url); // This will send the request to the server
    client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
    if (millis() - timeout > 5000)
    { Serial.println(">>> Client Timeout !");
    client.stop(); return; } } // Read all the lines of the reply from server and print them to Serial
    while (client.available())
    { String line = client.readStringUntil('\r'); Serial.print(line);
    }
    Serial.println();
    Serial.println("closing connection"); 
       uploadTime = millis();
  }
    } // here ends loop *************************************************************8

    //read temperature humidity data
void readTemperatureHumidity(){
  int j;
  unsigned int loopCnt;
  int chr[40] = {0};
  unsigned long time1;
bgn:
  delay(2000);
  //Set interface mode 2 to: output
  //Output low level 20ms (>18ms)
  //Output high level 40μs
  pinMode(D5, OUTPUT);
  digitalWrite(D5, LOW);
  delay(20);
  digitalWrite(D5, HIGH);
  delayMicroseconds(40);
  digitalWrite(D5, LOW);
  //Set interface mode 2: input
  pinMode(D5, INPUT);
  //High level response signal
  loopCnt = 10000;
  while (digitalRead(D5) != HIGH){
    if (loopCnt-- == 0){
      //If don't return to high level for a long time, output a prompt and start over
      Serial.println("HIGH");
      goto bgn;
    }
  }
  //Low level response signal
  loopCnt = 30000;
  while (digitalRead(D5) != LOW){
    if (loopCnt-- == 0){
      //If don't return low for a long time, output a prompt and start over
      Serial.println("LOW");
      goto bgn;
    }
  }
  //Start reading the value of bit1-40
  for (int i = 0; i < 40; i++){
    while (digitalRead(D5) == LOW){}
    //When the high level occurs, write down the time "time"
    time1 = micros();
    while (digitalRead(D5) == HIGH){}
    //When there is a low level, write down the time and subtract the time just saved
    //If the value obtained is greater than 50μs, it is ‘1’, otherwise it is ‘0’
    //And save it in an array
    if (micros() - time1  > 50){
      chr[i] = 1;
    } else {
      chr[i] = 0;
    }
  }

  //Humidity, 8-bit bit, converted to a value
  Humidity = chr[0] * 128 + chr[1] * 64 + chr[2] * 32 + chr[3] * 16 + chr[4] * 8 + chr[5] * 4 + chr[6] * 2 + chr[7];
  //Temperature, 8-bit bit, converted to a value
  
  Temperature_Cel = chr[16] * 128 + chr[17] * 64 + chr[18] * 32 + chr[19] * 16 + chr[20] * 8 + chr[21] * 4 + chr[22] * 2 + chr[23];
Temperature_Fehr=32+(1.8*Temperature_Cel);
RH = Humidity;
T=Temperature_Fehr;
HeatIndex_Fehr= -42.379 + 2.04901523*T + 10.14333127*RH - 0.22475541*T*RH - 0.00683783*T*T - 0.05481717*RH*RH + 0.00122874*T*T*RH + 0.00085282*T*RH*RH - 0.00000199*T*T*RH*RH;
  HeatIndex_Cel= (HeatIndex_Fehr-32)/1.8;  
    Serial.print("temp:");
    Serial.print(Temperature_Cel);
    Serial.print("    humi:");
    Serial.println(Humidity);
 
}

void readLight(){
    Serial.println("Print Light intensity!");
  // reset
  Wire.beginTransmission(Light_ADDR);
  Wire.write(0b00000111);
  Wire.endTransmission();
 
  Wire.beginTransmission(Light_ADDR);
  Wire.write(0b00100000);
  Wire.endTransmission();
  // typical read delay 120ms
  delay(120);
  Wire.requestFrom(Light_ADDR, 2); // 2byte every time
  for (tempLight = 0; Wire.available() >= 1; ) {
    char c = Wire.read();
    tempLight = (tempLight << 8) + (c & 0xFF);
  }
  tempLight = tempLight / 1.2;
  Serial.print("light: ");
  Serial.println(tempLight);
}


void readAtmosphere(){
  tempAtom = bmp.readPressure();
  Serial.print("Pressure = ");
  Serial.print(tempAtom);
  Serial.println(" Pascal");
}



