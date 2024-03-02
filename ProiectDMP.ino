#include <Servo.h>
#define MOTOR_SPEED 250

int mot1 = 6;
int mot3 = 3;
int left = 13;   // pin sensor left
int right = 12;  // pin sensor right
int Left = 0;
int Right = 0;

Servo myservo; 
volatile bool waterDetected = false;

int waterSensorPin = A0;  
int threshold = 200;

void LEFT(void);
void RIGHT(void);
void STOP(void);

void setup() {

  Serial.begin(9600);
  myservo.attach(10);
  delay(1000);
  myservo.write(90);
  delay(1000);
  myservo.write(0);

  pinMode(waterSensorPin, INPUT);

  pinMode(mot1, OUTPUT);
  pinMode(mot3, OUTPUT);

  pinMode(left, INPUT);
  pinMode(right, INPUT);
}



void loop() {
  water();

  analogWrite(mot3, MOTOR_SPEED);
  analogWrite(mot1, MOTOR_SPEED);
  Left = digitalRead(left);
  Right = digitalRead(right);

  delay(10);
  Serial.print("Left: ");
  Serial.print(Left);
  delay(10);
  Serial.print(" Right: ");
  Serial.println(Right);

  if (Left == 0 && Right == 0) {
    Serial.println("Chose front");
    FRONT();
  }

  else if (Left == 1 && Right == 1) {
    Serial.println("Chose stop");
    STOP();
  }

  else if (Left == 0 && Right == 1) {
    Serial.println("Chose left");
    LEFT();
  }

  else if (Right == 0 && Left == 1) {
    Serial.println("Chose right");
    RIGHT();
  }
}

void water() {
  int sensorValue = analogRead(waterSensorPin);
  delay(20);
  Serial.print("Water sensor :");
  Serial.println(sensorValue);
  if (sensorValue > threshold) {
    if (waterDetected == false) {
      myservo.write(90);
    }
    waterDetected = true;
  } else {
    if (waterDetected == true) {
      myservo.write(0);
    }
    waterDetected = false;
  }
}


void FRONT() {
  analogWrite(mot1, MOTOR_SPEED);
  analogWrite(mot3, MOTOR_SPEED);
}

void LEFT(void) {

  analogWrite(mot3, 0);
  analogWrite(mot1, MOTOR_SPEED);
}

void RIGHT(void) {

  analogWrite(mot1, 0); 
  analogWrite(mot3, MOTOR_SPEED); 
}

void STOP(void) {

  analogWrite(mot1, 0);
  analogWrite(mot3, 0);
}
