
#include "StateManager.h"
#include "MotorManager.h"
#include "LiquidCrystalDisplay.h"
#include "Button.h"

const int location_buttonInterruptSignal = 7;
const int location_motorInterruptSignal = 0;
const int location_startButton = A0;
const int location_stopButton = A1;
const int location_timeUpButton = A2;
const int location_timeDownButton = A3;
const int location_rpmUpButton = A4;
const int location_rpmDownButton = A5;
const int location_motorPWM = 5;

StateManager stateManager = StateManager();
MotorManager motorManager = MotorManager();

long lastLoopTime;

void setup() {
  Serial.begin(9600);

  initDisplay();
  updateDisplay(0, 0);

  pinMode(location_startButton, INPUT);
  pinMode(location_stopButton, INPUT);
  pinMode(location_timeUpButton, INPUT);
  pinMode(location_timeDownButton, INPUT);
  pinMode(location_rpmUpButton, INPUT);
  pinMode(location_rpmDownButton, INPUT);
  pinMode(location_buttonInterruptSignal, INPUT);
  pinMode(location_motorInterruptSignal, INPUT);
  attachInterrupt(digitalPinToInterrupt(location_buttonInterruptSignal), buttonPressed, RISING);
  attachInterrupt(digitalPinToInterrupt(location_motorInterruptSignal), motorRotated, RISING);
  pinMode(location_motorPWM, OUTPUT);

  updateDisplay(0, 0);
}

void motorRotated() {
  motorManager.RegisterRotation();
}

void buttonPressed() {
  return;

  int button = -1;

  int signal_start = analogRead(location_startButton);
  int signal_stop = analogRead(location_stopButton);
  int signal_timeUp = analogRead(location_timeUpButton);
  int signal_timeDown = analogRead(location_timeDownButton);
  int signal_rpmUp = analogRead(location_rpmUpButton);
  int signal_rpmDown = analogRead(location_rpmDownButton);

  int maxSignal = max(signal_start, max(signal_stop, max(signal_timeUp, max(signal_timeDown, max(signal_rpmUp, signal_rpmDown)))));

  if(signal_start == maxSignal) { button = START; }
  else if(signal_stop == maxSignal) { button = STOP; }
  else if(signal_timeUp == maxSignal) { button = TIME_UP; }
  else if(signal_timeDown == maxSignal) { button = TIME_DOWN; }
  else if(signal_rpmUp == maxSignal) { button = RPM_UP; }
  else if(signal_rpmDown == maxSignal) { button = RPM_DOWN; }

  stateManager.ButtonPressed(button);
}

void loop() {
  float dt = (millis() - lastLoopTime) / 1000.0f;
  lastLoopTime = millis();
  
  analogWrite(location_motorPWM, 255);

  stateManager.Update(dt);
  motorManager.Update(dt);
  
  int rpm = 0;
  int time = 0;
  stateManager.GetDisplayValues(&rpm, &time);

  //if(stateManager.GetState() == RUNNING_STATE) {
    rpm = motorManager.GetCurrentRPM();
  //}

  updateDisplay(rpm, time);
}
