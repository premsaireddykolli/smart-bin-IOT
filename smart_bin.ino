#include <Servo.h>

// Define pins for ultrasonic sensor
const int trigPin = 9;
const int echoPin = 10;

// Define pin for rain sensor and IR sensor
const int rainSensorPin = A0;   // Analog pin for rain detection
const int irSensorPin = 8;      // Digital pin for IR sensor

// Create Servo objects
Servo servo1;
Servo servo2;

void setup() {
  // Attach servos to their respective pins
  servo1.attach(3);  // Servo 1 (for ultrasonic sensor control) on pin 3
  servo2.attach(6);  // Servo 2 (for rain and IR sensor control) on pin 6

  // Initialize serial communication for debugging
  Serial.begin(9600);

  // Set up ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Set up IR sensor pin
  pinMode(irSensorPin, INPUT);

  // Initial servo positions
  servo1.write(0);      // Start servo1 at 0 degrees
  servo2.write(180);    // Start servo2 at 180 degrees as specified
}

void loop() {
  // --- Ultrasonic Sensor Control for servo1 ---
  long duration, distance;

  // Clear the trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Trigger ultrasonic sensor
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo pin and calculate distance
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  // Debugging distance
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Rotate servo1 based on distance
  if (distance <= 10) {
    servo1.write(180);  // Rotate to 180 degrees
    delay(1000);        // Hold for 1 second
  } else {
    servo1.write(0);     // Return to 0 degrees
  }

  // --- Rain and IR Sensor Control for servo2 ---
  int rainValue = analogRead(rainSensorPin);
  int irValue = digitalRead(irSensorPin); // Reads HIGH when object detected

  // Debugging sensor values
  Serial.print("Rain Sensor Value: ");
  Serial.println(rainValue);
  Serial.print("IR Sensor Value: ");
  Serial.println(irValue);

  // Check for moisture or IR detection
  if (rainValue > 600) {   // Moisture detected (adjust threshold as needed)
    servo2.write(90);      // Rotate to 90 degrees on moisture detection
  } else if (irValue == LOW) {  // Check if IR detects object
    servo2.write(0);       // Rotate to 0 degrees if object detected by IR
  } else {
    servo2.write(180);     // Return to 180 degrees if no detection
  }

  delay(5000);  // Delay for sensor refresh rate
}
