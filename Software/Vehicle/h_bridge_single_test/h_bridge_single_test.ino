 /**
  * FILE NAME: h_bridge_single_test
  * AUTHOR: Samuel Goldman
  * PURPOSE: Test out a breadboard version of an h bridge with
  *          mosfets and two control signals, A and B.
  */

void setup() {
  // Setup pins for output
  pinMode(5, OUTPUT); //A
  pinMode(6, OUTPUT); //B

  // Wait 5 seconds to run the test
  delay(5000);

  // Run the circuit forward at full speed
  analogWrite(5, 255);
  analogWrite(6, 0);

  // Wait two seconds
  delay(2000);

  // Switch to backwards at full speed
  analogWrite(5, 0);
  analogWrite(6, 255);
}

void loop() {
  // put your main code here, to run repeatedly:

}
