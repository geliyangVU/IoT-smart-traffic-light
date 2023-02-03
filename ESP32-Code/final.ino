#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <WiFi.h>
#include <MQTTPubSubClient.h>
#include <stdio.h>


const char* ssid = "GL-MT300N-V2-7fe";
const char* pass = "goodlife";

WiFiClient client;
MQTTPubSubClient mqtt;

#define SDA 13 //Define SDA pins
#define SCL 14 //Define SCL pins
#define trigPin 32 // define trigPin
#define echoPin 33 // define echoPin.
#define MAX_DISTANCE 700 // Maximum sensor distance is rated at 400-500cm.
#define RED_LED 19
#define GREEN_LED 5
//timeOut= 2*MAX_DISTANCE /100 /340 *1000000 = MAX_DISTANCE*58.8
float timeOut = MAX_DISTANCE * 60;
int soundVelocity = 340; // define sound speed=340m/s

float distance;
float pre_distance;
int red=0;
int green=0;
int count=0;
LiquidCrystal_I2C lcd(0x3F,16,2); 


void setup() {
 pinMode(trigPin,OUTPUT);// set trigPin to output mode
 pinMode(echoPin,INPUT); // set echoPin to input mode

 pinMode(RED_LED,OUTPUT);
 pinMode(GREEN_LED,OUTPUT);
 Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.

 Wire.begin(SDA, SCL); // attach the IIC pin
 lcd.init(); // LCD driver initialization
 lcd.backlight(); // Turn on the backlight

 lcd.setCursor(0,0); // Move the cursor to row 0, column 0
 lcd.print("Smart traffic light"); // The print content is displayed on the LCD

 Serial.begin(115200);
    WiFi.begin(ssid, pass);

    Serial.print("connecting to wifi...");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(1000);
    }
    Serial.println(" connected!");

    Serial.print("connecting to host...");
    while (!client.connect("192.168.8.113", 1883)) {
        Serial.print(".");
        delay(1000);
    }
    Serial.println(" connected!");

    // initialize mqtt client
    mqtt.begin(client);

    Serial.print("connecting to mqtt broker...");
    while (!mqtt.connect("arduino", "public", "public")) {
        Serial.print(".");
        delay(1000);
    }
    Serial.println(" connected!");

    // subscribe callback which is called when every packet has come
    mqtt.subscribe([](const String& topic, const String& payload, const size_t size) {
        Serial.println("mqtt received: " + topic + " - " + payload);
    });

    // subscribe topic and callback which is called when /hello has come
    mqtt.subscribe("/traffic/light0/wait", [](const String& payload, const size_t size) {
        updateLCD();
        Serial.print(count);
        if(count==1){
            digitalWrite(RED_LED, LOW);
            digitalWrite(GREEN_LED, HIGH);
            delay(5000);
            count=0;
            clearLCD();
        }
        count++;
    });


    mqtt.subscribe("/traffic/light0/led", [](const String& payload, const size_t size) {
      char ledchar= payload.charAt(0);
      updateLED(ledchar);
    });


}

void loop() {
  mqtt.update();
//  Serial.printf("Distance: ");
 distance = getSonar();

  // Serial.print(distance); // Send ping, get distance in cm and print result
//  Serial.println("cm");

mqtt.publish("/traffic/light0/led", "a");
// delay(5000);
mqtt.publish("/traffic/light0/led", "b");
//  delay(5000);
}


void updateLCD(){
lcd.setCursor(0,1); // Move the cursor to row 1, column 0
 lcd.print("Extended green light next."); // The count is displayed every second
}


void clearLCD(){
   Serial.println("clearLCD was called");

lcd.setCursor(0,1); // Move the cursor to row 1, column 0
 lcd.print("Normal light"); // The count is displayed every second
}

void updateLED(char ledLightPayload){

  if(ledLightPayload=='a'){
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
    delay(500);


  }else{
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
    delay(500);

  }
}



float getSonar() {
 unsigned long pingTime;
 float distance;
 // make trigPin output high level lasting for 10us to trigger HC_SR04
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);
 // Wait HC-SR04 returning to the high level and measure out this waiting time
 pingTime = pulseIn(echoPin, HIGH, timeOut);
 // calculate the distance according to the time
 distance = (float)pingTime * soundVelocity / 2 / 10000;
String stringOne = String(distance, 3);// using a float and the decimal places
 Serial.println(stringOne);
if(distance<30 && distance>2){
  mqtt.publish("/traffic/light0/wait", "wait");
}
mqtt.publish("/traffic/light0/value", stringOne);
 return distance; // return the distance value

}