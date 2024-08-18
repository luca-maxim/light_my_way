#include <Servo.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

//Servo Driver
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  125 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)
#define SERVOMID1 294
#define SERVOMID2 294
#define SERVOMID3 313
#define SERVOMID4 308
#define SERVOMID5 306
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

// our servo # counter
uint8_t servonum = 5;

// Define pins for buttons, servos, and LEDs
const int buttonPins[5] = {49,47,45,43,41};
const int carButton = 39;
const int ledPins[5] = {42,40,38,36,34};

int buttonStates[5];       // Current state of buttons
bool servoUp[5] = {false}; // State of servos
bool blinking[5] = {false}; // Blinking state of LEDs
unsigned long previousMillis = 0; // Last time the LEDs were updated
const long interval = 500;       // Interval at which to blink (milliseconds)
bool ledStates[5] = {LOW}; // Current state of LEDs

// Variables for double press detection
unsigned long lastPressTime[2] = {0, 0}; // Last time the button was pressed
int pressCount[2] = {0, 0};              // Count of presses within the time frame
const long doublePressInterval = 500;    // Interval to detect double press (milliseconds)

void setup() {
  // Initialize buttons, LEDs, and servos
  for (int i = 0; i < 5; i++) {
    //pinMode(buttonPins[i], INPUT);
    //pinMode(ledPins[i], OUTPUT);
  }

  //pinMode(carButton, INPUT);
  
  //Setup servo driver
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  Serial.begin(9600);
  delay(10);

  for (int i = 0; i < 5; i++) {
    pwm.setPWM(i, 0, SERVOMIN);
    //digitalWrite(ledPins[i], LOW); 
  }

  delay(10);
}

void loop() {
  /*
  // Read button states and print messages
  for (int i = 0; i < 5; i++) {
    buttonStates[i] = digitalRead(buttonPins[i]);
    if (buttonStates[i] == HIGH) {
      //handleButtonPress(i);
      Serial.print("B");
      Serial.println(i + 1);
    }
  }
  
  //Read Car Button
  int carButtonState = digitalRead(carButton);
  if (carButtonState == HIGH){
    Serial.println("CB");
  }
  */

  // Handle incoming serial messages
  if (Serial.available()) {
    char incoming = Serial.read();
    if (incoming >= '1' && incoming <= '5') {
      int index = incoming - '1'; // Convert ASCII to index (0-4)
      handleServoAndLED(index, true);
    } else if (incoming == 'D') {
      for (int i = 0; i < 5; i++) {
        handleServoAndLED(i, false);
      }
    }
  }
/*
  // Handle LED blinking
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis= currentMillis;

    for (int i = 0; i < 5; i++) {
      if (blinking[i]){
        ledStates[i] = !ledStates[i];
        digitalWrite(ledPins[i], ledStates[i]);
      }
    }
  }
*/
  delay(100);  // delay in between reads for stability
}

void handleServoAndLED(int index, bool up) {
  int servomid = 0;

  switch (index){
    case 0:
      servomid = SERVOMID1;
      break;
    case 1:
      servomid = SERVOMID2;
      break;
    case 2:
      servomid = SERVOMID3;
      break;
    case 3:
      servomid = SERVOMID4;
      break;
    case 4:
      servomid = SERVOMID5;
      break;
  }

  if (up && !servoUp[index]) {

    for (uint16_t pulselen = SERVOMIN; pulselen < servomid; pulselen++) {
      pwm.setPWM(index, 0, pulselen);
    }

    servoUp[index] = true;
    blinking[index] = true;  // Start blinking
  } else if (!up && servoUp[index]) {

    for (uint16_t pulselen = servomid; pulselen > SERVOMIN; pulselen--) {
      pwm.setPWM(index, 0, pulselen);
    }

    servoUp[index] = false;
    blinking[index] = false; // Stop blinking
    //digitalWrite(ledPins[index], LOW);  // Ensure the LED is off
  }
}

  void handleButtonPress(int index) {
    unsigned long currentMillis = millis();

    if (currentMillis - lastPressTime[index] <= doublePressInterval) {
      pressCount[index]++;
      if (pressCount[index] == 2) {
        // Double press detected
        Serial.print("Double B");
        Serial.println(index + 1);
        pressCount[index] = 0; // Reset press count
      }
    } else {
      // Single press detected
      Serial.print("B");
      Serial.println(index + 1);
      pressCount[index] = 1; // Reset press count
    }

    lastPressTime[index] = currentMillis; // Update last press time
  }
