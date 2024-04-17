#include <Arduino.h>

class Task {
    public:
        Task(){};
        Task(int id, unsigned long ms, std::function<void()> callbackFunction)
        {
            taskId = id;
            timeMs = ms;
            callback = callbackFunction;
            afterFire = NULL;
        };
        Task(int id, unsigned long ms, std::function<void()> callbackFunction, std::function<void()> afterFireFunction)
        {
            taskId = id;
            timeMs = ms;
            callback = callbackFunction;
            afterFire = afterFireFunction;
        };
        int taskId;
        unsigned long timeMs;
        std::function<void()> callback;
        std::function<void()> afterFire;
};