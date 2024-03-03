
enum States {
  IDLE_STATE,
  RUNNING_STATE,
  NUM_STATES
};

class StateManager {
  private:
    const int TIME_INC = 15;
    const int RPM_INC = 50;

    int m_currentState = IDLE_STATE;

    const int DEFAULT_RPM = 2500;
    const int DEFAULT_TIME = 600; // 10 minutes

    float m_set_rpm = DEFAULT_RPM;
    float m_set_time = DEFAULT_TIME;
    float m_time = DEFAULT_TIME;

    bool m_reset = true;

    void UpdateIdleState(float dt);
    void UpdateRunningState(float dt);
    void InitIdleState();
    void InitRunningState();
    void IdleButtonPressed(int button);
    void RunningButtonPressed(int button);

  public:
    StateManager();

    void SetState(int state);
    void Update(float dt);
    void GetDisplayValues(int* rpm, int* time);
    void ButtonPressed(int button);

    int GetState() { return m_currentState; }
    int GetTargetRPM() { return m_set_rpm; }
};
