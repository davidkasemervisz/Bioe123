
#include "MotorManager.h"
#include "Button.h"

MotorManager::MotorManager(float targetRPM) {
  m_targetRPM = targetRPM;
  m_pid.SetMode(AUTOMATIC);
  m_pid.SetOutputLimits(0, 255);
}

void MotorManager::RegisterRotation() {
  m_counter++;
}

void MotorManager::Update(float dt, bool isRunning) {
  m_timer += dt;

  if(m_timer >= 1) {
    m_currentRPM = m_counter * 60 / 2; // registers twice per rotation
    m_counter = 0; 
    m_timer = 0;
  }

  if(isRunning) {
    m_pid.Compute();
  }
}

int MotorManager::GetCurrentRPM() {
  return m_currentRPM;
}
