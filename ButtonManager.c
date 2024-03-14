
#include "Button.h"
#include <stdbool.h>

const int l_START = 100;
const int u_START = 115;
const int l_STOP = 70;
const int u_STOP = 80;
const int l_TIME_UP = 50;
const int u_TIME_UP = 69;
const int l_TIME_DOWN = 35;
const int u_TIME_DOWN = 45;
const int l_RPM_UP = 190;
const int u_RPM_UP = 400;
const int l_RPM_DOWN = 500;
const int u_RPM_DOWN = 1000;

const int NO_BUTTON_PRESSED = -1;
const int BUTTON_NOT_RECOGNIZED = -10;

int inputInButtonRange(int lower, int upper, int input) {
  return input >= lower && input <= upper;
}

int determineButtonPressed(int input) {
  if(inputInButtonRange(l_START, u_START, input)) { return START; }
  else if(inputInButtonRange(l_STOP, u_STOP, input)) { return STOP; }
  else if(inputInButtonRange(l_TIME_UP, u_TIME_UP, input)) { return TIME_UP; }
  else if(inputInButtonRange(l_TIME_DOWN, u_TIME_DOWN, input)) { return TIME_DOWN; }
  else if(inputInButtonRange(l_RPM_UP, u_RPM_UP, input)) { return RPM_UP; }
  else if(inputInButtonRange(l_RPM_DOWN, u_RPM_DOWN, input)) { return RPM_DOWN; }
  else { return BUTTON_NOT_RECOGNIZED; }
}

int lastInput;
const int THRESHOLD = 20;

int getButtonPressed(int input) {
  if(input > THRESHOLD && lastInput <= THRESHOLD) {
    lastInput = input;
    return determineButtonPressed(input);
  }

  else {
    lastInput = input;
    return NO_BUTTON_PRESSED;
  }
}
