
#include "StateManager.h"
#include "Button.h"

StateManager::StateManager() {
  SetState(IDLE_STATE);
}

void StateManager::SetState(int state) {
  m_currentState = state;

  if(state == IDLE_STATE) {
    InitIdleState();
  }

  else if(state == RUNNING_STATE) {
    InitRunningState();
  }
}

void StateManager::InitIdleState() {} 

void StateManager::InitRunningState() {
  m_reset = false;
} 

void StateManager::Update(float dt) {
  if(m_currentState == IDLE_STATE) {
    UpdateIdleState(dt);
  }

  else if(m_currentState == RUNNING_STATE) {
    UpdateRunningState(dt);
  }
}

void StateManager::UpdateIdleState(float dt) {}

void StateManager::UpdateRunningState(float dt) {
  m_time -= dt;

  if(m_time <= 0) { // program complete, notification?
    m_reset = true;
    m_time = m_set_time;

    SetState(IDLE_STATE);
  }
}

void StateManager::GetDisplayValues(int *rpm, int *time) {
  if(m_currentState == IDLE_STATE) {
    *rpm = m_set_rpm;
    *time = m_time;
  }

  else if(m_currentState == RUNNING_STATE) {
    *rpm = m_set_rpm; // will be measured rpm eventually
    *time = m_time;
  }
}

void StateManager::ButtonPressed(int button) {
  if(m_currentState == IDLE_STATE) {
    IdleButtonPressed(button);
  }

  else if(m_currentState == RUNNING_STATE) {
    RunningButtonPressed(button);
  }
}

void StateManager::IdleButtonPressed(int button) {
  if(button == START) {
    SetState(RUNNING_STATE);
  }

  else if(button == STOP) {
    if(m_reset) {
      m_set_time = DEFAULT_TIME;
      m_set_rpm = DEFAULT_RPM;
    }

    m_time = m_set_time;
    m_reset = true;
  }

  else if(button == TIME_UP) {
    m_time += TIME_INC;

    if(m_reset) {
      m_set_time += TIME_INC;
    }
  }

  else if(button == TIME_DOWN) {
    m_time -= TIME_INC;

    if(m_reset) {
      m_set_time -= TIME_INC;
    }
  }

  else if(button == RPM_UP) {
    m_set_rpm += RPM_INC;
  }

  else if(button == RPM_DOWN) {
    m_set_rpm -= RPM_INC;
  }
}

void StateManager::RunningButtonPressed(int button) {
  if(button == START) {}

  else if(button == STOP) {
    SetState(IDLE_STATE);
  }

  else if(button == TIME_UP) {
    m_time += TIME_INC;
  }

  else if(button == TIME_DOWN) {
    m_time -= TIME_INC;
  }

  else if(button == RPM_UP) {
    m_set_rpm += RPM_INC;
  }

  else if(button == RPM_DOWN) {
    m_set_rpm -= RPM_INC;
  }
}