
#include "MotorManager.h"

void MotorManager::RegisterRotation() {
  m_counter++;
}

void MotorManager::Update(float dt) {
  m_timer += dt;

  if(m_timer > 1) {
    m_currentRPM = (int)(m_counter * 60 / m_timer);
    
    m_timer = 0;
    m_counter = 0;
  }
}

int MotorManager::GetCurrentRPM() {
  return m_currentRPM;
}
