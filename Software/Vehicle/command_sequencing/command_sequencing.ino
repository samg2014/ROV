/**
   FILE NAME: command_sequencing
   AUTHOR: Samuel Goldman
   PURPOSE: run the vehicle by sending a sequence of commands
            to be run later.
*/

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

// Flags to determine what run mode the vehicle is in
bool EDIT_MODE = false;
bool RUN_NORM = false;
bool RUN_DEBUG = false;

// A list of commands to be executed
String COMMANDS[50];
int COMMANDS_LENGTH = 0; // How many commands are actually in the list

// Index to execute now
int EXECUTE_INDEX = -1;

void setup() {
  // initialize serial:
  Serial.begin(9600);

  // reserve 200 bytes for the inputString:
  inputString.reserve(200);

  // Setup pins for motor control
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop() {
  // Handle new input
  if (stringComplete) {

    // Enter edit mode if possible
    if (inputString == "--edit") {
      if (RUN_NORM == true || RUN_DEBUG == true) {
        Serial.println("The program is running. To edit it, run '--halt'.");
      } else if (EXECUTE_INDEX != -1) {
        Serial.println("The program is paused. To edit it, run '--halt'.");
      } else {
        EDIT_MODE = true;
        Serial.println("Entering program editer...");
      }
    }

    // Quit the command sequence editor
    if (inputString == "--quit") {
      EDIT_MODE = false;
      Serial.println("Exiting program editer...");
    }

    // Handle the execute command
    if (inputString.startsWith("--execute")) {
      if (EDIT_MODE == true) {
        Serial.println("In edit mode, cannot execute now!");
      }
      else if (RUN_NORM == true) {
        Serial.println("Already running normally!");
      }
      else if (RUN_DEBUG == true) {
        Serial.println("Already running in debug mode!");
      }
      else {
        int index = inputString.indexOf(" ");
        if (index == -1) {
          if (EXECUTE_INDEX == -1)
            EXECUTE_INDEX = 0;
          Serial.println((String)"Starting execution at index=" + EXECUTE_INDEX + "...");
          RUN_NORM = true;
        }
        else {
          int temp = inputString.substring(index + 1).toInt();
          if (temp > COMMANDS_LENGTH - 1) {
            Serial.println("Starting index out of bounds!");
          } else {
            EXECUTE_INDEX = temp;
            Serial.println((String)"Starting execution at index=" + EXECUTE_INDEX + "...");
            RUN_NORM = true;
          }
        }
      }
    }

    // Execute commands in debug mode
    if (inputString.startsWith("--debug")) {
      if (EDIT_MODE == true) {
        Serial.println("In edit mode, cannot execute now!");
      }
      else if (RUN_NORM == true) {
        Serial.println("Already running normally!");
      }
      else if (RUN_DEBUG == true) {
        Serial.println("Already running in debug mode!");
      }
      else {
        int index = inputString.indexOf(" ");
        if (index == -1) {
          if (EXECUTE_INDEX == -1)
            EXECUTE_INDEX = 0;
          Serial.println((String)"Starting execution at index=" + EXECUTE_INDEX + "...");
          RUN_DEBUG = true;
        }
        else {
          int temp = inputString.substring(index + 1).toInt();
          if (temp > COMMANDS_LENGTH - 1) {
            Serial.println("Starting index out of bounds!");
          } else {
            EXECUTE_INDEX = temp;
            Serial.println((String)"Starting execution at index=" + EXECUTE_INDEX + "...");
            RUN_DEBUG = true;
          }
        }
      }
    }

    if (inputString == "--halt") {
      Serial.println("Halting execution...");
      RUN_NORM = false;
      RUN_DEBUG = false;
      EXECUTE_INDEX = -1;
    }

    if (inputString == "--pause") {
      Serial.println("Pausing execution...");
      RUN_NORM = false;
      RUN_DEBUG = false;
    }

    if (inputString == "--print") {
      int i;
      Serial.println("\tStart Program");
      for (i = 0; i < COMMANDS_LENGTH; i++) {
        Serial.println(COMMANDS[i]);
      }
      Serial.println("\tEnd Program");
    }

    // Add a command if in edit mode and there is enough space
    if (inputString.startsWith("--add")) {
      if (EDIT_MODE) {
        String command = inputString.substring(inputString.indexOf(" ") + 1);
        if (COMMANDS_LENGTH < 50) {
          COMMANDS[COMMANDS_LENGTH] = command;
          COMMANDS_LENGTH++;

          Serial.println((String)"Added command " + command + " for a total of " + COMMANDS_LENGTH + " commands...");
        } else {
          Serial.println("Maximum number of commands (50) has been exeeded!");
        }
      } else {
        Serial.println("Not in edit mode!");
      }
    }

    inputString = "";
    stringComplete = false;
  }

  // If executing, execute the next command
  if (RUN_NORM || RUN_DEBUG) {
    run_next();
  }
}

void run_next() {
  String current = COMMANDS[EXECUTE_INDEX];

  // Handle the different commands:

  if (current.startsWith("INIT")) {
    int pin = current.substring(current.indexOf("-") + 1).toInt();
    print_debug((String) "Initializing pin " + pin + "...");
    pinMode(pin, OUTPUT);
  }
  if (current.startsWith("PRINT")) {
    Serial.println("PRINT: " + current.substring(current.indexOf("-") + 1));
  }
  if (current.startsWith("PAUSE")) {
    int pause = current.substring(current.indexOf("-") + 1).toInt();
    print_debug((String) "Pausing for " + pause + " milliseconds...");
    delay(pause);
  }
  if (current.startsWith("DIGSET")) {
    String values = current.substring(current.indexOf("-") + 1);
    int pin = values.substring(0, values.indexOf("-")).toInt();
    String value = values.substring(values.indexOf("-") + 1);
    if (value == "HIGH") {
      print_debug((String) "Setting pin " + pin + " to " + value + "...");
      digitalWrite(pin, HIGH);
    }
    if (value == "LOW") {
      print_debug((String) "Setting pin " + pin + " to " + value + "...");
      digitalWrite(pin, LOW);
    }
  }
  if (current.startsWith("ALGSET")) {
    String values = current.substring(current.indexOf("-") + 1);
    int pin = values.substring(0, values.indexOf("-")).toInt();
    int value = values.substring(values.indexOf("-") + 1).toInt();
    if (value >= 0 && value <= 255) {
      print_debug((String) "Setting pin " + pin + " to " + value + "...");
      analogWrite(pin, value);
    }
  }
  if (current.startsWith("GOTO")) {
    int goTo = current.substring(current.indexOf("-") + 1).toInt();
    if (goTo < COMMANDS_LENGTH) {
      EXECUTE_INDEX = goTo;
      print_debug((String) "Going to " + goTo + "...");
      return;
    }
    else {
      print_debug((String) "Cannot go to " + goTo + "...");
    }
  }

  if (EXECUTE_INDEX + 1 < COMMANDS_LENGTH) {
    EXECUTE_INDEX ++;
  } else {
    print_debug("Reached the end of the program...");
    EXECUTE_INDEX = -1;
    RUN_NORM = false;
    RUN_DEBUG = false;
  }

}

void print_debug(String val) {
  if (RUN_DEBUG)
    Serial.println(val);
}


// Read in from serial
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    if (inChar == ';') {
      stringComplete = true;
      return;
    }
    // add it to the inputString:
    inputString += inChar;
  }
}


