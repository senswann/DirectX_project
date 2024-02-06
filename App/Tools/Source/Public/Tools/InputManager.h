class InputManager {
private:
    float timer;
    bool* isRunning;

public:
    // Constructeur
    InputManager();

    // Destructeur
    ~InputManager();

    // Méthodes
    inline void Quit() { *(isRunning) = false; };

    // getter
    inline float getTimer() { return timer; };

    //setter
    inline void setRunning(bool* _isRuning) { isRunning = _isRuning; };
    inline void setTimer(float _timer) { timer=_timer; };
};