/**
 * FILE NAME: motor_checkout
 * AUTHOR: Samuel Goldman
 * PURPOSE: test all three motors each controlled via single 
 *          mosfet circuits.
 */
 
const int RIGHT_MOTOR_PIN = 9;
const int LEFT_MOTOR_PIN = 10;
const int DOWN_MOTOR_PIN = 11;

void setup() {
  // Setup the motor control pins for output
  pinMode(RIGHT_MOTOR_PIN, OUTPUT);
  pinMode(LEFT_MOTOR_PIN, OUTPUT);
  pinMode(DOWN_MOTOR_PIN, OUTPUT);

  // Set all motors to full speed
  analogWrite(RIGHT_MOTOR_PIN, 255);
  analogWrite(LEFT_MOTOR_PIN, 255);
  analogWrite(DOWN_MOTOR_PIN, 255);

  // Run all motors for 2.5 seconds
  delay(2500);

  // Stop all motors to conclude testing
  analogWrite(RIGHT_MOTOR_PIN, 0);
  analogWrite(LEFT_MOTOR_PIN, 0);
  analogWrite(DOWN_MOTOR_PIN, 0);
}

void loop() {
  // Nothing to do
}
