
/*
Ranges for RPM and time

*/

#include "StateManager.h"
#include "MotorManager.h"
#include "LiquidCrystalDisplay.h"
#include "ButtonManager.c"

const int location_motorRotationSignal = A5;
const int location_motorPWM = 5;
const int location_buttonSignal = A4;

StateManager stateManager = StateManager();
MotorManager motorManager = MotorManager(stateManager.GetTargetRPM());

long lastLoopTime;

void setup() {
  Serial.begin(9600);

  initDisplay();
  updateDisplay(0, 0);

  pinMode(location_motorRotationSignal, INPUT);
  pinMode(location_motorPWM, OUTPUT);
  pinMode(location_buttonSignal, OUTPUT);
}

const int MOTOR_ROTATION_THRESHOLD = 600;
bool lastAboveThreshold = false;

void checkForMotorRotation() {
  int input = analogRead(location_motorRotationSignal);
  bool aboveThreshold = input > MOTOR_ROTATION_THRESHOLD;

  if(aboveThreshold && !lastAboveThreshold) {
    motorManager.RegisterRotation();
  }

  lastAboveThreshold = aboveThreshold;
}

void updateMotorSpeed() {
  int targetRPM = stateManager.GetTargetRPM();
  motorManager.SetTargetRPM(targetRPM);
  int pwm = motorManager.GetPWM();
  analogWrite(location_motorPWM, pwm);
}

void updateButtonPress() {
  int input = analogRead(location_buttonSignal);
  int button = getButtonPressed(input);
  if(button != NO_BUTTON_PRESSED) {
    stateManager.ButtonPressed(button);
    if(button == BUTTON_NOT_RECOGNIZED) {
      Serial.print("Button Not Recognized! Input Value: ");
      Serial.println(input);
    }
  }
}

void loop() {
  float dt = (millis() - lastLoopTime) / 1000.0f;
  lastLoopTime = millis();

  stateManager.Update(dt);
  bool isRunning = stateManager.GetState() == RUNNING_STATE;
  motorManager.Update(dt, isRunning);

  updateButtonPress();
  checkForMotorRotation();

  if(isRunning) {
    updateMotorSpeed();
  } else {
    analogWrite(location_motorPWM, 0);
  }

  int rpm = 0;
  int time = 0;
  stateManager.GetDisplayValues(&rpm, &time);

  if(isRunning) {
    rpm = motorManager.GetCurrentRPM();
  }

  updateDisplay(rpm, time);
}
