
class MotorManager {
  private:
    int m_counter;
    float m_timer;
    int m_currentRPM;

  public:
    void RegisterRotation();
    void Update(float dt);
    int GetCurrentRPM();
};
