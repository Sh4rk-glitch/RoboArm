#include <Arduino.h>


/* Include the HCPCA9685 library */
#include "HCPCA9685.h"

/* I2C slave address for the device/module. For the HCMODU0097 the default I2C address
   is 0x40 */
#define  I2CAdd 0x40

/* Create an instance of the library */
HCPCA9685 pwm(I2CAdd);

//initial parking position of the motor
const int servo_joint_L_parking_pos = 60;
const int servo_joint_R_parking_pos = 60;
const int servo_joint_1_parking_pos = 70;
const int servo_joint_2_parking_pos = 47;
const int servo_joint_3_parking_pos = 63;
const int servo_joint_4_parking_pos = 63;

//Degree of robot servo sensitivity - Intervals
int servo_joint_L_pos_increment = 20;
int servo_joint_R_pos_increment = 20;
int servo_joint_1_pos_increment = 20;
int servo_joint_2_pos_increment = 50;
int servo_joint_3_pos_increment = 60;
int servo_joint_4_pos_increment = 40;

//Keep track of the current value of the motor positions
int servo_joint_L_parking_pos_i = servo_joint_L_parking_pos;
int servo_joint_R_parking_pos_i = servo_joint_R_parking_pos;
int servo_joint_1_parking_pos_i = servo_joint_1_parking_pos;
int servo_joint_2_parking_pos_i = servo_joint_2_parking_pos;
int servo_joint_3_parking_pos_i = servo_joint_3_parking_pos;
int servo_joint_4_parking_pos_i = servo_joint_4_parking_pos;


//Minimum and maximum angle of servo motor
int servo_joint_L_min_pos = 10;
int servo_joint_L_max_pos = 180;

int servo_joint_R_min_pos = 10;
int servo_joint_R_max_pos = 180;

int servo_joint_1_min_pos = 10;
int servo_joint_1_max_pos = 400;

int servo_joint_2_min_pos = 10;
int servo_joint_2_max_pos = 380;

int servo_joint_3_min_pos = 10;
int servo_joint_3_max_pos = 380;

int servo_joint_4_min_pos = 10;
int servo_joint_4_max_pos = 120;

int servo_L_pos = 0;
int servo_R_pos = 0;
int servo_joint_1_pos = 0;
int servo_joint_2_pos = 0;
int servo_joint_3_pos = 0;
int servo_joint_4_pos = 0;

char state = 0; // Changes value from ASCII to char
int response_time = 5;
int response_time_4 = 2;
int loop_check = 0;
int response_time_fast = 20;
int action_delay = 600;

//Posiion of motor for example demos
unsigned int Pos;

// Define pin connections & motor's steps per revolution
const int dirPin = 4;
const int stepPin = 5;
const int stepsPerRevolution = 120;
int stepDelay = 4500;
const int stepsPerRevolutionSmall = 60;
int stepDelaySmall = 9500;

// WEB INTERFACE
// Control source flags
bool webControlActive = false;
bool gloveConnected = false;

// Serial input buffer
String serialBuf = "";

// forward declaration
void processState(char stateChar);
// END WEB INTERFACE
void setup()
{
  // Declare pins as Outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  /* Initialise the library and set it to 'servo mode' */
  pwm.Init(SERVO_MODE);

  /* Wake the device up */
  pwm.Sleep(false);

  Serial.begin(4800); // Initialise default communication rate of the Bluetooth module


  delay(3000);
  //wakeUp(); -- Uncomment for Example Demo 1
  //flexMotors(); -- Uncomment for Example Demo 1

}
//Boiler plate function - These functions move the servo motors in a specific direction for a duration.

void gripperServoForward() {

  if (servo_joint_4_parking_pos_i > servo_joint_4_min_pos) {
    pwm.Servo(5, servo_joint_4_parking_pos_i);
    delay(response_time); //Delay the time takee to turn the servo by the given increment
    Serial.println(servo_joint_4_parking_pos_i);
    servo_joint_4_parking_pos_i = servo_joint_4_parking_pos_i - servo_joint_4_pos_increment;

  }
}

void gripperServoBackward() {

  if (servo_joint_4_parking_pos_i < servo_joint_4_max_pos) {
    pwm.Servo(5, servo_joint_4_parking_pos_i);
    delay(response_time);
    Serial.println(servo_joint_4_parking_pos_i);
    servo_joint_4_parking_pos_i = servo_joint_4_parking_pos_i + servo_joint_4_pos_increment;

  }

}

void wristServoCW() {

  if (servo_joint_3_parking_pos_i > servo_joint_3_min_pos) {
    pwm.Servo(4, servo_joint_3_parking_pos_i);
    delay(response_time_4);
    Serial.println(servo_joint_3_parking_pos_i);
    servo_joint_3_parking_pos_i = servo_joint_3_parking_pos_i - servo_joint_3_pos_increment;

  }

}

void wristServoCCW() {

  if (servo_joint_3_parking_pos_i < servo_joint_3_max_pos) {
    pwm.Servo(4, servo_joint_3_parking_pos_i);
    delay(response_time_4);
    Serial.println(servo_joint_3_parking_pos_i);
    servo_joint_3_parking_pos_i = servo_joint_3_parking_pos_i + servo_joint_3_pos_increment;

  }

}

void wristServo1Forward() {

  if (servo_joint_2_parking_pos_i < servo_joint_2_max_pos) {
    pwm.Servo(3, servo_joint_2_parking_pos_i);
    delay(response_time);
    Serial.println(servo_joint_2_parking_pos_i);

    servo_joint_2_parking_pos_i = servo_joint_2_parking_pos_i + servo_joint_2_pos_increment;

  }


}

void wristServo1Backward() {

  if (servo_joint_2_parking_pos_i > servo_joint_2_min_pos) {
    pwm.Servo(3, servo_joint_2_parking_pos_i);
    delay(response_time);
    Serial.println(servo_joint_2_parking_pos_i);

    servo_joint_2_parking_pos_i = servo_joint_2_parking_pos_i - servo_joint_2_pos_increment;

  }

}


void elbowServoForward() {

  if (servo_joint_L_parking_pos_i < servo_joint_L_max_pos) {
    pwm.Servo(0, servo_joint_L_parking_pos_i);
    pwm.Servo(1, (servo_joint_L_max_pos - servo_joint_L_parking_pos_i));

    delay(response_time);
    Serial.println(servo_joint_L_parking_pos_i);

    servo_joint_L_parking_pos_i = servo_joint_L_parking_pos_i + servo_joint_L_pos_increment;
    servo_joint_R_parking_pos_i = servo_joint_L_max_pos - servo_joint_L_parking_pos_i;

  }
}

void elbowServoBackward() {
  if (servo_joint_L_parking_pos_i > servo_joint_L_min_pos) {
    pwm.Servo(0, servo_joint_L_parking_pos_i);
    pwm.Servo(1, (servo_joint_L_max_pos - servo_joint_L_parking_pos_i));

    delay(response_time);
    Serial.println(servo_joint_L_parking_pos_i);


    servo_joint_L_parking_pos_i = servo_joint_L_parking_pos_i - servo_joint_L_pos_increment;
    servo_joint_R_parking_pos_i = servo_joint_L_max_pos - servo_joint_L_parking_pos_i;

  }

}

void shoulderServoForward() {

  if (servo_joint_1_parking_pos_i < servo_joint_1_max_pos) {
    pwm.Servo(2, servo_joint_1_parking_pos_i);
    delay(response_time);
    Serial.println(servo_joint_1_parking_pos_i);

    servo_joint_1_parking_pos_i = servo_joint_1_parking_pos_i + servo_joint_1_pos_increment;

  }

}

void shoulderServoBackward() {


  if (servo_joint_1_parking_pos_i > servo_joint_1_min_pos) {
    pwm.Servo(2, servo_joint_1_parking_pos_i);
    delay(response_time);
    Serial.println(servo_joint_1_parking_pos_i);

    servo_joint_1_parking_pos_i = servo_joint_1_parking_pos_i - servo_joint_1_pos_increment;

  }
}

void baseRotateLeft() {
  //clockwise
  digitalWrite(dirPin, HIGH);
  // Spin motor
  for (int x = 0; x < stepsPerRevolution; x++)
  {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(stepDelay);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(stepDelay);
  }
  delay(response_time); // Wait a second
}


void baseRotateRight() {

  //counterclockwise
  digitalWrite(dirPin, LOW);
  // Spin motor
  for (int x = 0; x < stepsPerRevolution; x++)
  {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(stepDelay);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(stepDelay);
  }
  delay(response_time); // Wait a second
}


// WEB INTERFACE
void loop() {

  // Read incoming serial data into a line buffer (handles both single-char and line protocols)
  while (Serial.available() > 0) {
    char c = (char)Serial.read();
    // accumulate until newline or carriage return
    if (c == '\n' || c == '\r') {
      if (serialBuf.length() > 0) {
        // process a full line
        String line = serialBuf;
        serialBuf = "";
        // Handle line-based commands and notifications
        if (line.startsWith("!")) {
          // Web commands or control messages (prefixed with '!')
          String cmd = line.substring(1);
          if (cmd == "WEB_ON") {
            webControlActive = true;
            Serial.println("ACK:WEB_ON");
            continue;
          }
          if (cmd == "WEB_OFF") {
            webControlActive = false;
            Serial.println("ACK:WEB_OFF");
            continue;
          }
          // Movement commands from web: expect single-char after '!'
          if (cmd.length() >= 1) {
            char st = cmd.charAt(0);
            processState(st);
            continue;
          }
        }

        // Glove detection: if a glove handshake or keyword arrives, mark connected and notify
        if (line.startsWith("GLOVE") || line == "G") {
          gloveConnected = true;
          Serial.println("NOTIFY:GLOVE_CONNECTED");
          continue;
        }

        // If web control is active, ignore raw movement commands from other sources
        if (!webControlActive && line.length() == 1) {
          char st = line.charAt(0);
          processState(st);
        }
      }
    } else {
      serialBuf += c;
      if (serialBuf.length() > 64) serialBuf = serialBuf.substring(0, 64);
    }
  }
}

// Process a single-character command (previously inlined in loop)
void processState(char stateChar) {
  // echo the command for debugging/monitoring
  Serial.print(stateChar);

  if (stateChar == 'S') {
    baseRotateLeft();
    delay(response_time);
    return;
  }
  if (stateChar == 'O') {
    baseRotateRight();
    delay(response_time);
    return;
  }
  if (stateChar == 'c') {
    shoulderServoForward();
    delay(response_time);
    return;
  }
  if (stateChar == 'C') {
    shoulderServoBackward();
    delay(response_time);
    return;
  }
  if (stateChar == 'p') {
    elbowServoForward();
    delay(response_time);
    return;
  }
  if (stateChar == 'P') {
    elbowServoBackward();
    delay(response_time);
    return;
  }
  if (stateChar == 'U') {
    wristServo1Backward();
    delay(response_time);
    return;
  }
  if (stateChar == 'G') {
    wristServo1Forward();
    delay(response_time);
    return;
  }
  if (stateChar == 'R') {
    wristServoCW();
    delay(response_time);
    return;
  }
  if (stateChar == 'L') {
    wristServoCCW();
    delay(response_time);
    return;
  }
  if (stateChar == 'F') {
    gripperServoBackward();
    delay(response_time);
    return;
  }
  if (stateChar == 'f') {
    gripperServoForward();
    delay(response_time);
    return;
  }
}

// END WEB INTERFACE

// ORIGINAL CODE (COMMENTED OUT) - start
/*
void loop() {

  if (Serial.available() > 0) { // Checks whether data is coming from the serial port

    state = Serial.read(); // Reads the data from the serial port
    Serial.print(state); // Prints out the value sent


    //For the naming of the motors, refer to the article / tutorial
    //Move (Base Rotation) Stepper Motor Left
    if (state == 'S') {
      baseRotateLeft();
      delay(response_time);
    }

    //Move (Base Rotation) Stepper Motor Right
    if (state == 'O') {
      baseRotateRight();
      delay(response_time);
    }


    //Move Shoulder Down
    if (state == 'c') {

      shoulderServoForward();
      delay(response_time);

    }

    //Move Shoulder Up
    if (state == 'C') {

      shoulderServoBackward();
      delay(response_time);

    }

    //Move Elbow Down
    if (state == 'p') {

      elbowServoForward();
      delay(response_time);

    }

    //Move Elbow Up
    if (state == 'P') {

      elbowServoBackward();
      delay(response_time);

    }


    //Move Wrist 1 UP
    if (state == 'U') {

      wristServo1Backward();
      delay(response_time);
    }

    //Move Move Wrist 1 Down
    if (state == 'G') {

      wristServo1Forward();
      delay(response_time);

    }


    //Move Wrist 2 Clockwise
    if (state == 'R') {

      wristServoCW();
      delay(response_time);

    }

    //Move Wrist 2 Counter-CW
    if (state == 'L') {

      wristServoCCW();
      delay(response_time);

    }


    //Open Claw Grip
    if (state == 'F') {
      gripperServoBackward();
      delay(response_time);

    }

    //Close Claw Grip
    if (state == 'f') {
      gripperServoForward();
      delay(response_time);
    }


  }
}

*/
// ORIGINAL CODE (COMMENTED OUT) - end


void wakeUp() {

  //Pre-Program Function - Wake Up Robot on Start

  if (loop_check == 0) {

    //    //Shoulder Raise
    for (Pos = 0; Pos < 10; Pos++)
    {

      pwm.Servo(1, Pos);
      delay(response_time_fast);
    }

    //  //Move Elbow Backwards
    for (Pos = 400; Pos > 390; Pos--)
    {

      pwm.Servo(2, Pos);

      delay(response_time_fast);
    }

    //Move Wrist 1 Forward
    for (Pos = 10; Pos < 20; Pos++)
    {
      pwm.Servo(3, Pos);
      delay(response_time);
    }

    //Move Wrist 2 Backwards
    for (Pos = 380; Pos > 50; Pos--)
    {
      pwm.Servo(4, Pos);
      delay(response_time);
    }

    //Move Wrist 2 Backwards
    for (Pos = 50; Pos < 150; Pos++)
    {
      pwm.Servo(4, Pos);
      delay(response_time);
    }

    //Move Wrist 1 Forward
    for (Pos = 19; Pos < 100; Pos++)
    {
      pwm.Servo(3, Pos);
      delay(response_time);
    }
    loop_check = 0;

  }
}

void flexMotors() {

  //Example Demo Pre-program Function to Make Robot Wake Up (Motor by Motor)

  if (loop_check == 0) {

    delay(action_delay);

    //Move Wrist 1 Forward
    for (Pos = 100; Pos > 10; Pos--)
    {
      pwm.Servo(3, Pos);
      delay(10);
    }

    delay(action_delay);

    //Move Wrist 1 Forward
    for (Pos = 10; Pos < 70; Pos++)
    {
      pwm.Servo(3, Pos);
      delay(10);
    }

    delay(action_delay);

    baseRotateLeft();
    delay(action_delay);


    //Move Wrist 2 Backwards
    for (Pos = 200; Pos < 380; Pos++)
    {
      pwm.Servo(4, Pos);
      delay(10);
    }

    delay(action_delay);

    loop_check = 1;


  }
}
