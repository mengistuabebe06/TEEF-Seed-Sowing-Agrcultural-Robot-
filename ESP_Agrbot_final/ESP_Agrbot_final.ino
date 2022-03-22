 
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>
SoftwareSerial s(3,1);
#include <ArduinoJson.h>

 
/* Set these to your desired credentials. */
const char *ssid = "MatiG";  //ENTER YOUR WIFI SETTINGS
const char *password = "12031203";
 
//Web/Server address to read/write from 
const char *host = "192.168.137.150";   
//const char *host = "192.168.137.247";   

 
 int trigPin = D5;
 int echoPin = D6;
 int trigPinX = D7;
 int echoPinX = D8;
// defining variables
 long duration,duration1;
 int distance,distance1;
//=======================================================================
//                    Power on setup
//=======================================================================
 
void setup() {


pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input

pinMode(trigPinX, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPinX, INPUT); // Sets the echoPin as an Input

  pinMode(D0,INPUT);
  pinMode(D1,INPUT);
 Serial.begin(9600);
  s.begin(9600);
  while (!Serial) continue;

  
  delay(1000);
 // Serial.begin(115200);
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  //Serial.println("");
 
//  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  //If connection successful show IP address in serial monitor
 /* Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
  */
}
 
//=======================================================================
//                    Main Program Loop
//=======================================================================
void loop() {

  /*StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(s);
  if (root == JsonObject::invalid())
    return;
  root.prettyPrintTo(Serial);
  int rowspacing=root["rowspacing"];
    Serial.println(rowspacing);
    int farmland=root["farmland"];
    Serial.println(farmland);

    */
 
     
   //insertData(rowspacing,farmland);
  insertData();
   fetchingData();
   
  // recivedData();
}
void coordinate(){
  /////Y-AXIS
 digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
//Serial.print("Y-axis : ");
//Serial.println(distance);
//Serial.write(distance);

///////////////X-AXIS
 digitalWrite(trigPinX, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPinX, HIGH);
delayMicroseconds(10);
digitalWrite(trigPinX, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration1 = pulseIn(echoPinX, HIGH);
// Calculating the distance
 distance1= duration1*0.034/2;
// Prints the distance on the Serial Monitor
//Serial.print("X-AXIS: ");
//Serial.println(distance1);
//Serial.write(distance1);
  }

void insertData(){
  // put your main code here, to run repeatedly:
  HTTPClient http;    //Declare object of class HTTPClient
  
coordinate();
 int x_axis,y_axis;
 x_axis=distance;
 y_axis=distance1;
 
  String postion, postion1,pos, SeedLevelString,RowSpacingString,CriticalLevelString,farmlandcoverageString,postData;
   //postion="8,45"; 
   
  int SeedLevel=digitalRead(D0);
  int rowspacing=20;
  int CriticalLevel=digitalRead(D1);
  
 int farmland=800;
  //int SeedLevel=20192;
    SeedLevelString = String(SeedLevel);   
     RowSpacingString = String(rowspacing);
     CriticalLevelString = String(CriticalLevel);
     farmlandcoverageString=String(farmland);
     postion=String(x_axis);
      postion1=String(y_axis);
      
      pos=postion+","+postion1;
  //Post Data
 // postData = "postion=" + postion + "&SeedLevel=" + SeedLevelString + "&RowSpacing=" + RowSpacingString + "&CriticalLevel=" + CriticalLevelString + "&farmlandcoverage=" +farmlandcoverageString;
   postData = "postion=" + pos + "&SeedLevel=" + SeedLevelString + "&RowSpacing=" + RowSpacingString + "&CriticalLevel=" + CriticalLevelString + "&farmlandcoverage=" +farmlandcoverageString;
  
  http.begin("http://192.168.137.150/Agrobot/InsertDB.php");              //Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header
 
  int httpCode = http.POST(postData);   //Send the request
  //int httpCode1 = http.POST(postData1); 
  String payload = http.getString();    //Get the response payload

 
Serial.println(pos);
 Serial.println(SeedLevelString);   
 Serial.println(RowSpacingString);
 Serial.println( CriticalLevelString);
 Serial.println( farmlandcoverageString);
  Serial.println(payload);    //Print request response payload
 
  http.end();  //Close connection

  delay(4000);  //Here there is 4 seconds delay plus 1 second delay below, so Post Data at every 5 seconds
 
}
void fetchingData(){
         
     HTTPClient http; //Object of class HTTPClient
    http.begin("http://192.168.137.150//Agrobot/read_agrobot.php");   
    int httpCode = http.GET();

    if (httpCode > 0) 
    {
      
    //  const size_t bufferSize = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(8) + 370;
      StaticJsonBuffer<1000> jsonBuffer;
      JsonObject& root = jsonBuffer.parseObject(http.getString());
 
      int RowSpacing = root["RowSpacing"]; 
      int InputDistance = root["InputDistance"]; 
      int ControlValue = root["ControlValue"]; 
      //s.write(InputDistance);
      
/*/ sendtoArdiuno();
   //Send data from this module to the Ardiuo module
  StaticJsonBuffer<1000> jsonBufferr;
  JsonObject& data = jsonBuffer.createObject();
  data["RowSpacing"] =RowSpacing;
  data["InputDistance"] = InputDistance;
  data["ControlValue"]=ControlValue;
  */
    
     Serial.print("RowSpacing:");
      Serial.println(RowSpacing);
      Serial.print("InputDistance:");
      Serial.println(InputDistance);
      Serial.print("ControlValue:");
      Serial.println(ControlValue);
      
    }
    http.end(); //Close connection
      delay(6000);
  }
 /* void recivedData(){

     StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(s);
  if (root == JsonObject::invalid())
    return;
 
  Serial.println("JSON received and parsed");
  root.prettyPrintTo(Serial);
  Serial.print("Data 1 ");
  Serial.println("");
  int data1=root["data1"];
  Serial.print(data1);
  Serial.print("   Data 2 ");
  int data2=root["data2"];
  Serial.print(data2);
  Serial.println("");
  Serial.println("---------------------xxxxx--------------------");
  }
*/

