#include <WiFi.h>

const char* ssid     = "MannyComputer";
const char* password = "blueberry";
WiFiServer server(80);
int manual = 0;
int relayPin1 = 15;  //This is the Arduino Pin that will control Relay #1 which controls Water pump
int relayPin2 = 2;  //This is the Arduino Pin that will control Relay #2
int relayPin3 = 0;  //This is the Arduino Pin that will control Relay #3
int relayPin4 = 4;  //This is the Arduino Pin that will control Relay #4
int relayPin5 = 16;  //This is the Arduino Pin that will control Relay #5 which controls Water pump
int relayPin6 = 17;  //This is the Arduino Pin that will control Relay #6
int relayPin7 = 5;  //This is the Arduino Pin that will control Relay #7
int relayPin8 = 18;  //This is the Arduino Pin that will control Relay #8
#define SensorPin1 34 //Tells us that 12 on arduino will read take value from moisture sensor
#define SensorPin2 35 //Tells us that 14 on arduino will read take value from moisture sensor
#define SensorPin3 32//Tells us that 27 on arduino will read take value from moisture sensor
#define SensorPin4 33 //Tells us that 26 on arduino will read take value from moisture sensor
float sensorValue1 = 0;  //will tell us what are sensor value is 
float sensorValue2 = 0;  //will tell us what are sensor value is 
float sensorValue3 = 0;  //will tell us what are sensor value is 
float sensorValue4 = 0;  //will tell us what are sensor value is 
int SensorVCCPin1 = 12; // Will tell us which pin powers the Moisture sensor
int SensorVCCPin2 = 14; // Will tell us which pin powers the Moisture sensor
int SensorVCCPin3 = 27; // Will tell us which pin powers the Moisture sensor
int SensorVCCPin4 = 26; // Will tell us which pin powers the Moisture sensor
void setup() {
   // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);
  pinMode(relayPin3, OUTPUT);
  pinMode(relayPin4, OUTPUT);
  pinMode(relayPin5, OUTPUT);
  pinMode(relayPin6, OUTPUT);
  pinMode(relayPin7, OUTPUT);
  pinMode(relayPin8, OUTPUT);
  pinMode(SensorVCCPin1, OUTPUT) ;
  pinMode(SensorVCCPin2, OUTPUT);
  pinMode(SensorVCCPin3, OUTPUT) ;
  pinMode(SensorVCCPin4, OUTPUT);
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
  digitalWrite(relayPin1, HIGH);
  digitalWrite(relayPin2, HIGH);
  digitalWrite(relayPin3, HIGH);
  digitalWrite(relayPin4, HIGH);
  digitalWrite(relayPin5, HIGH);
  digitalWrite(relayPin6, HIGH);
  digitalWrite(relayPin7, HIGH);
  digitalWrite(relayPin8, HIGH);  
  digitalWrite(SensorVCCPin1, LOW);
  digitalWrite(SensorVCCPin2, LOW);
  digitalWrite(SensorVCCPin3, LOW);
  digitalWrite(SensorVCCPin4, LOW);
  Serial.println("Set up complete");
}

void loop() {


    
    while (manual == 0){
         Serial.println("Auto On");
         
         digitalWrite(SensorVCCPin1, HIGH); //Turns on moisture sensor
         delay(250);
         sensorValue1 = analogRead(SensorPin1); //Reads sensor level information
         sensorValue1 = sensorValue1/100.0; // Divides it by 100
         Serial.println("Sensor Value 1 is ");//Tells us what sensor value is
         Serial.print(sensorValue1);
         Serial.print("\n");      // New line in serial monitor
         digitalWrite(SensorVCCPin1, LOW); //Turns off moisture sensor
         delay(250);
        
         //Sensor Pin 2
         digitalWrite(SensorVCCPin2, HIGH); //Turns on moisture sensor
         delay(250);
         sensorValue2 = analogRead(SensorPin2); //Reads sensor level information
         sensorValue2 = sensorValue2/100.0; // Divides it by 100
         Serial.println("Sensor Value 2 is ");//Tells us what sensor value is
         Serial.print(sensorValue2);
         Serial.print("\n");      // New line in serial monitor
         digitalWrite(SensorVCCPin2, LOW); //Turns off moisture sensor
         delay(250);
         
         //Sensor Pin 3
         digitalWrite(SensorVCCPin3, HIGH); //Turns on moisture sensor
         delay(250);
         sensorValue3 = analogRead(SensorPin3); //Reads sensor level information
         sensorValue3 = sensorValue3/100.0; // Divides it by 100
         Serial.println("Sensor Value 3 is ");//Tells us what sensor value is
         Serial.print(sensorValue3);
         Serial.print("\n");      // New line in serial monitor
         digitalWrite(SensorVCCPin3, LOW); //Turns off moisture sensor
         delay(250);
         
         //Sensor Pin 4 
         digitalWrite(SensorVCCPin4, HIGH); //Turns on moisture sensor
         delay(250);
         sensorValue4 = analogRead(SensorPin4); //Reads sensor level information
         sensorValue4 = sensorValue4/100.0; // Divides it by 100
         Serial.println("Sensor Value 4 is ");//Tells us what sensor value is
         Serial.print(sensorValue4);
         Serial.print("\n");      // New line in serial monitor
         Serial.print("\n");      // New line in serial monitor
         Serial.print("\n");      // New line in serial monitor
         digitalWrite(SensorVCCPin4, LOW); //Turns off moisture sensor
         delay(250);
         //Checking to see if Water Pump 1 needs to be turn on
        

         if (sensorValue1 > 39.00) { //If the sensor value is high (if the plant is dry)
          digitalWrite(relayPin1, LOW); //Turns water pump on
          Serial.println("Water pump 1 is on\n"); //Prints message that water pump is on
          delay(5000); //will delay for 1000 miliseconds which is = 1 second
          digitalWrite(relayPin1, HIGH); //Turns water pump off
          Serial.println("Water pump 1 is off\n"); //Prints message that water pump is off
         }
         delay(250);
        
         //Checking to see if Water Pump 2 needs to be turn on
         if (sensorValue2 >39.00) { //If the sensor value is high (if the plant is dry)
          digitalWrite(relayPin2, LOW); //Turns water pump on
          Serial.println("Water pump 2 is on\n"); //Prints message that water pump is on
          delay(5000); //will delay for 1000 miliseconds which is = 1 second
          digitalWrite(relayPin2, HIGH); //Turns water pump off
          Serial.println("Water pump 2 is off\n"); //Prints message that water pump is off
         }
         delay(500);



         
         //Checking to see if Water Pump 3 needs to be turn on
         if (sensorValue3 >39.00) { //If the sensor value is high (if the plant is dry)
          digitalWrite(relayPin3, LOW); //Turns water pump on
          Serial.println("Water pump 3 is on\n"); //Prints message that water pump is on
          delay(5000); //will delay for 1000 miliseconds which is = 1 second
          digitalWrite(relayPin3, HIGH); //Turns water pump off
          Serial.println("Water pump 3 is off\n"); //Prints message that water pump is off
         }
         delay(500);
         
         //Checking to see if Water Pump 4 needs to be turn on
         if (sensorValue4 > 38.00) { //If the sensor value is high (if the plant is dry)
          digitalWrite(relayPin4, LOW); //Turns water pump on
          Serial.println("Water pump 4 is on\n"); //Prints message that water pump is on
          delay(5000); //will delay for 1000 miliseconds which is = 1 second
          digitalWrite(relayPin4, HIGH); //Turns water pump off
          Serial.println("Water pump 4 is off\n"); //Prints message that water pump is off
         }
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
         if (req.indexOf("/Water_Pump_1/1") != -1){
         //Write what happens in Water Pump 1
          digitalWrite(relayPin1, LOW);
          delay(1000);
          digitalWrite(relayPin1, HIGH);
         }
         else if (req.indexOf("/Water_Pump_2/1") != -1){
         //Write what happens in Water Pump 2
          digitalWrite(relayPin2, LOW);
          delay(1000);
          digitalWrite(relayPin2, HIGH);
         }
         else if (req.indexOf("/Water_Pump_3/1") != -1){
         //Write what happens in Water Pump 3
          digitalWrite(relayPin3, LOW);
          delay(1000);
          digitalWrite(relayPin3, HIGH);         
         }
         else if (req.indexOf("/Water_Pump_4/1") != -1){
         //Write what happens in Water Pump 4
          digitalWrite(relayPin4, LOW);
          delay(1000);
          digitalWrite(relayPin4, HIGH);       
         }
         else if (req.indexOf("/F_pump/1") != -1){
         //Write what happens in Fertilizer pump
          digitalWrite(relayPin5, LOW);
          delay(1000);
          digitalWrite(relayPin5, HIGH);
         }
         else if (req.indexOf("/auto/1") != -1){
            
            Serial.println("Auto Mode On Selected");
            manual = 0;
         }
       
      }

}
}
