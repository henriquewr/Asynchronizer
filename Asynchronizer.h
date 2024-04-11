#include <Arduino.h>
#include <string>
#include "Task.h"

class Asynchronizer {
    public:
        static void Check();

        static int Timeout(std::function<void()> callback, unsigned long timeMs);
        static bool UpdateTimeout(int taskId, std::function<void()> callback, unsigned long timeMs);
        static int CreateOrUpdateTimeout(int taskId, std::function<void()> callback, unsigned long timeMs);

        static int Delay(std::function<void()> callback, unsigned long timeMs);
        static bool UpdateDelay(int taskId, std::function<void()> callback, unsigned long timeMs);
        static int CreateOrUpdateDelay(int taskId, std::function<void()> callback, unsigned long timeMs);

        static void CancelById(int taskId);
        static void CancelAll();

    private:
        static int GenerateId();
        static Task* GetTaskById(int taskId);
        static bool ContainsId(int taskId);
        static Task* CreateTask(std::function<void()> callback, unsigned long timeMs);
};