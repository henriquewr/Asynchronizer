#include <Arduino.h>
#include <string>
#include "Task.h"

class Asynchronizer {
    public:
        static void Check();

        static int Interval(std::function<void()> callback, unsigned long timeMs);
        static bool UpdateInterval(int taskId, std::function<void()> callback, unsigned long timeMs);
        static int CreateOrUpdateInterval(int taskId, std::function<void()> callback, unsigned long timeMs);

        static int Delay(std::function<void()> callback, unsigned long timeMs);
        static bool UpdateDelay(int taskId, std::function<void()> callback, unsigned long timeMs);
        static int CreateOrUpdateDelay(int taskId, std::function<void()> callback, unsigned long timeMs);

        static void CancelById(int taskId);
        static void CancelAll();
        static bool IsRunning(int taskId);

    private:
        static int GenerateId();
        static Task* GetTaskById(int taskId);
        static Task* CreateTask(std::function<void()> callback, unsigned long timeMs);
};