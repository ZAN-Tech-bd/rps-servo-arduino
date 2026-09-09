#include <Servo.h>

Servo myServo;

const int trigPin = 7;
const int echoPin = 8;
const int servoPin = 9;

const int obstacleDistance = 15; // cm — adjust based on testing

int angles[] = {0, 90, 180}; // rock, paper, scissors positions

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  myServo.attach(servoPin);
  myServo.write(0);   // move to 0 degrees first
  Serial.println("Servo initialized at 0 degrees.");
  delay(1000);

  randomSeed(analogRead(A0)); // seed randomness from a floating pin
}

long getDistanceCM() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000); // 30ms timeout
  if (duration == 0) return -1; // no echo received

  long distance = duration * 0.034 / 2; // convert to cm
  return distance;
}

void loop() {
  long distance = getDistanceCM();

  if (distance > 0 && distance <= obstacleDistance) {
    int choice = angles[random(0, 3)]; // pick 0, 90, or 180
    myServo.write(choice);

    Serial.print("Obstacle detected! Servo moved to: ");
    Serial.println(choice);

    delay(2000); // hold the "move" for 2 seconds

    myServo.write(0); // reset back to 0 before next round
    delay(500);       // small buffer before re-checking
  }
}
