/* This Program is written by 
Abdullah Al Jobayer
Electrical & Electronic Engineer 
Guithub Profile link- https://github.com/jobayer-ee
***************/

#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
Servo myservo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int trigPin = 9;
const int echoPin = 8;
const int servoPin = 7;
int servoRotationCount = 0;
void setup() {
  myservo.attach(servoPin);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}
void loop() {
  long duration, distance;
  // Send a short pulse to trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the duration of the pulse from the echo pin
  duration = pulseIn(echoPin, HIGH);
  // Calculate the distance in centimeters
  distance = (duration / 2) / 29.1;
  // Check if the distance is less than or equal to 25 cm
  if (distance <= 10) {
    // If the distance is within 25 cm, open the toll barrier (servo 90 degrees)
    myservo.write(0);
    delay(2000); // Delay to keep the barrier open for 3 seconds
    myservo.write(90); // Close the barrier (back to 0 degrees)
    // Increment the counter when the servo rotates to 90 degrees
    servoRotationCount++;
  }
  // Print the distance and servo rotation count to the serial monitor for debugging
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  Serial.print("Servo Rotations: ");
  Serial.println(servoRotationCount);

  // Display the count on the LCD
  lcd.clear(); // Clear the LCD screen
  lcd.setCursor(0, 0); // Set the cursor to the first row, first column
  lcd.print("Car Passed ="); // Display the text
  lcd.setCursor(0, 1); // Set the cursor to the second row, first column
  lcd.print(servoRotationCount); // Display the count
}
