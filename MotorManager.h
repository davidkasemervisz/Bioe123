
#include <PID_v1.h>

const double KP = 0.03;
const double KI = 0.03;
const double KD = 0.0;

class MotorManager {
  private:
    int m_counter;
    float m_timer;
    double m_currentRPM;
    double m_targetRPM;
    double m_calculatedPWM;

    PID m_pid = PID(&m_currentRPM, &m_calculatedPWM, &m_targetRPM, KP, KI, KD, DIRECT);

  public:
    void RegisterRotation();
    void Update(float dt, bool isRunning);
    int GetCurrentRPM();
    int GetPWM() { return (int)m_calculatedPWM; }
    void SetTargetRPM(int targetRPM) { m_targetRPM = targetRPM; }

    MotorManager(float targetRPM);
};
