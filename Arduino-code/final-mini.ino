#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL3T8TgLCHY"
#define BLYNK_TEMPLATE_NAME "MOTOR"
#define BLYNK_AUTH_TOKEN "o4cf7h-cKHzR4KFvNtttN4s0JrsPa6tQ"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h> 

// Motor PINs
#define ENA 18
#define IN1 2
#define IN2 4
#define IN3 5
#define IN4 13
#define ENB 19
 


bool forward = 0;
bool backward = 0;
bool left = 0;
bool right = 0;
int MF= 12; 
int ENC=22;
int pinValue1;
Servo myServo1;
int servoPin1=15;
Servo myServo;
int servoPin2=14;
int Speed;


char auth[] = BLYNK_AUTH_TOKEN; //Enter your Blynk application auth token
char ssid[] = "jiofi"; //Enter your WIFI name
char pass[] = "12345678"; //Enter your WIFI password

void setup() {
  // Initialize the serial monitor
  Serial.begin(9600);
  // Set the motor pins as the output pin
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
   
  pinMode(ENC,OUTPUT);
 
  myServo1.attach(servoPin1);
  myServo.attach(servoPin2);

  // Initialize the blynk communication
  Blynk.begin(auth, ssid, pass);
}

// Get values from the widgets
BLYNK_WRITE(V0) {
  forward = param.asInt();
}

BLYNK_WRITE(V1) {
  backward = param.asInt();
}

BLYNK_WRITE(V2) {
  left = param.asInt();
}

BLYNK_WRITE(V3) {
  right = param.asInt();
}

BLYNK_WRITE(V4) {
  Speed = param.asInt();
}
BLYNK_WRITE(V5){
  int servoValue =param.asInt();
  myServo1.write(servoValue);
  Blynk.virtualWrite(V5,servoValue);
}
BLYNK_WRITE(V6){
  int servoValue1 =param.asInt();
  myServo.write(servoValue1);
  Blynk.virtualWrite(V6,servoValue1);
}
BLYNK_WRITE(V8) {
  pinValue1=param.asInt();
  analogWrite(ENC,pinValue1);
  Blynk.virtualWrite(V8,pinValue1);
  Serial.println(pinValue1);
  
  
}

void loop() {
  // Run the blynk library
  Blynk.run();
  smartcar();
}

// Check widget values using the IF condition
void smartcar() {
  if (forward == 1) {
    Forward();
    Serial.println("Forward");
  } else if (backward == 1) {
    Backward();
    Serial.println("Backward");
  } else if (left == 1) {
    Left();
    Serial.println("Left");
  } else if (right == 1) {
    Right();
    Serial.println("Right");
  }
 /* else if (conv == 1) {
    Conv();
    Serial.println("CONV");
  } */ 
  else {
    Stop();
    Serial.println("Stop");
  }
}

// Motor control functions
void Forward() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

}

void Backward() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void Left() {
  analogWrite(ENA, Speed); // Adjust speed for turning
  analogWrite(ENB, Speed); // Adjust speed for turning
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void Right() {
  analogWrite(ENA, Speed ); // Adjust speed for turning
  analogWrite(ENB, Speed ); // Adjust speed for turning
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
/*void Conv()
{
  analogWrite(ENC, Speed);
  digitalWrite(IN5,HIGH);
  digitalWrite(IN6,LOW);
   
}*/
void Stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
