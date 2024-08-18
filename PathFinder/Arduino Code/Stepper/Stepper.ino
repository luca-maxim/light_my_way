#include <AccelStepper.h>

// Define the stepper motor and the pins that is connected to
AccelStepper stepper(1, 2, 5); // (Type of driver: with 2 pins, STEP, DIR)

bool motorRunning = false;

void setup() {
  // Set maximum speed value for the stepper
  stepper.setMaxSpeed(1000);
  stepper.setAcceleration(10);

  Serial.begin(9600);
}

void loop() {
  // Check for serial input
  if (Serial.available()) {
    char incoming = Serial.read();
    if (incoming == 'S' || incoming == 's') {
      motorRunning = true; // Start the motor
      Serial.println("Motor started");
    } else if (incoming == 'D' || incoming == 'd') {
      motorRunning = false; // Stop the motor
      Serial.println("Motor stopped");
      stepper.setCurrentPosition(0); // Reset the position
    }
  }

  if (motorRunning) {
    // Set the target speed
    float targetSpeed = 40; // Desired speed after acceleration

    // Gradual acceleration
    if (stepper.speed() < targetSpeed) {
      stepper.setSpeed(stepper.speed() + 1); // Gradually increase speed
    }

    // Run the motor at the current speed
    stepper.runSpeed();
  }
}


