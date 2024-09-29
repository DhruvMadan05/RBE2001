#include <Arduino.h>
#include <Romi32U4.h>

Romi32U4Motors motors;
Romi32U4Encoders encoders;
Romi32U4ButtonA buttonA;

const float wheelDiameter = 7.0; // cm (wheel diameter of Romi)
const float countsPerRevolution = 1440.0; // Encoder counts per wheel revolution
const float wheelBase = 14.5; // cm (distance between wheels)

// void turnDegrees(float degrees, bool isRightTurn);
// void moveDistance(float distance);

void setup() {
  Serial.begin(9600);
  // Wait for button press before starting
  buttonA.waitForButton();
}

// Function to turn the robot a certain number of degrees
void turnDegrees(float degrees, bool isRightTurn) {
  float turnCircumference = 3.14 * wheelBase; // Circumference of the turning circle
  float distanceToTurn = (turnCircumference * degrees) / 360.0; // Distance each wheel needs to travel
  float countsToTurn = (countsPerRevolution * distanceToTurn) / (3.14 * wheelDiameter);

  encoders.getCountsAndResetLeft();  // Reset encoder counts
  encoders.getCountsAndResetRight();

  if (isRightTurn) {
    motors.setSpeeds(100, -100);  // Turn right: one wheel forward, the other backward
  } else {
    motors.setSpeeds(-100, 100);  // Turn left: one wheel backward, the other forward
  }

  // Keep turning until the required counts are reached
  while (abs(encoders.getCountsLeft()) < countsToTurn && abs(encoders.getCountsRight()) < countsToTurn) {
    // Wait until turn is complete
  }

  motors.setSpeeds(0, 0);  // Stop motors after turn
  delay(500);  // Small pause
}

// Function to move the robot a certain distance in cm
void moveDistance(float distance) {
  float countsToMove = (countsPerRevolution * distance) / (3.14 * wheelDiameter);
  
  encoders.getCountsAndResetLeft();  // Reset encoder counts
  encoders.getCountsAndResetRight();

  motors.setSpeeds(100, 100);  // Move forward

  // Keep moving until the required counts are reached
  while (abs(encoders.getCountsLeft()) < countsToMove && abs(encoders.getCountsRight()) < countsToMove) {
    // Wait until move is complete
  }

  motors.setSpeeds(0, 0);  // Stop motors after move
  delay(500);  // Small pause
}

void loop() {
  turnDegrees(94, true);   // Turn right 94 degrees
  moveDistance(15);        // Move forward 15 cm
  turnDegrees(180, false); // Turn left 180 degrees
  moveDistance(13);        // Move forward 13 cm
  turnDegrees(51, true);   // Turn right 51 degrees

  // Stop the robot after completing all actions
  motors.setSpeeds(0, 0);
  buttonA.waitForButton();
}


