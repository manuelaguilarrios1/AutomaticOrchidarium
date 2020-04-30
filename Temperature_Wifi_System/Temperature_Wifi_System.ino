#include <DHT.h>
#include <WiFi.h>

const char* ssid     = "MannyComputer";
const char* password = "blueberry";
int hb = 0; //heating bulb var
int lght = 0; //light var
int fan = 0; //fan variable 
WiFiServer server(80);
int manual = 0;
//Constants
#define DHTPIN 4     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino
//Relay variables
int relayPin1 = 19;  //This is the Arduino Pin that will control Relay #1 which controls Water pump
int relayPin2 = 18;  //This is the Arduino Pin that will control Relay #2
int relayPin3 = 5;  //This is the Arduino Pin that will control Relay #3
int relayPin4 = 17;  //This is the Arduino Pin that will control Relay #4
//DTH Variables
int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);
  pinMode(relayPin3, OUTPUT);
  pinMode(relayPin4, OUTPUT);
  dht.begin();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}
//Range for celsius 16.5 - 26.5 celsius
void loop() {
  while (manual == 0){
  Serial.println("Auto On");
  // put your main code here, to run repeatedly:
  delay(5000);
  //Read data and store it to variables hum and temp
  hum = dht.readHumidity();
  temp = dht.readTemperature();
  //Print temp and humidity values to serial monitor
  Serial.println("Humidity: ");
  Serial.print(hum);
  Serial.print(" %, Temp: ");
  Serial.print(temp);
  Serial.println(" Celsius");
  if (temp < 18) {
    digitalWrite(relayPin2, HIGH);
    Serial.print("Heat is on\n");
  }
  else {
    digitalWrite(relayPin2, LOW);
    Serial.print("Heat is off\n");
  }
  if (temp > 26) {
    digitalWrite(relayPin1, HIGH);
    Serial.print("Fan on high/n");
  }
  delay(2000); //Delay 2 sec.
  delay(100);

  WiFiClient client = server.available();   // listen for incoming clients
  if (client) {
  String req = client.readStringUntil('\r');
  client.flush();
  if (req.indexOf("/manual/1") !=-1)
  Serial.println("Manual Mode On Selected");
  manual = 1;  
        
      }
  }
  while(manual == 1){ 
    WiFiClient client = server.available();   // listen for incoming clients
       if (client) {
         String req = client.readStringUntil('\r');
         client.flush();
         if (req.indexOf("/Heating_bulb/1") != -1){
         //Write what happens in haeting bulb
         if (hb == 0){
          digitalWrite(relayPin2, LOW); //turn heating bulb on
         }
         else if (hb == 1){
          digitalWrite(relayPin2, HIGH); //turn heating bulb off
         }
         delay(1000);
         }

         else if (req.indexOf("/Light/1") != -1){
         //Write what happens in haeting bulb
         if (lght == 0){
          digitalWrite(relayPin3, LOW); //turn light on
         }
         else if (lght == 1){
          digitalWrite(relayPin3, HIGH); //turn light off
         }
         delay(1000);
         }
         else if (req.indexOf("/Fan/1") != -1){
         //Write what happens in heating bulb
         if (fan == 0){
          digitalWrite(relayPin1, LOW); //turn fan high
         }
         else if (fan == 1){
          digitalWrite(relayPin1, HIGH); //turn fan low
         }
         delay(1000);
         }
         else if (req.indexOf("/auto/1") != -1){
            
            Serial.println("Auto Mode On Selected");
            manual = 0;
         }
         
  }
 }
}
