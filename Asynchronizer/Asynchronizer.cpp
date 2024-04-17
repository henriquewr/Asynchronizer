#include <Arduino.h>
#include <string>
#include "Asynchronizer.h"

static std::vector<Task*> tasks;

void Asynchronizer::Check() {
    unsigned long currentMillis = millis();

    for (size_t i = 0; i < tasks.size(); i++) {
        auto item = tasks[i];
        
        if (item->timeMs > currentMillis) {
            continue;
        }

        auto callback = item->callback;
        if(callback != NULL){
            callback();
        }

        if(item->afterFire != NULL){
            item->afterFire();
        }
        else{
            Asynchronizer::CancelById(item->taskId);
        }
    }
}

#pragma region Interval

int Asynchronizer::Interval(std::function<void()> callback, unsigned long timeMs) {
    auto task = Asynchronizer::CreateTask(callback, timeMs);

    task->afterFire = [task, timeMs](){
        task->timeMs = (millis() + timeMs);
    };

    return task->taskId;
}

bool Asynchronizer::UpdateInterval(int taskId, std::function<void()> callback, unsigned long timeMs) {
    auto task = Asynchronizer::GetTaskById(taskId);
    if(task == NULL){
        return false;
    }

    task->callback = callback;
    task->afterFire = [task, timeMs](){
        task->timeMs = (millis() + timeMs);
    };

    return true;
}

int Asynchronizer::CreateOrUpdateInterval(int taskId, std::function<void()> callback, unsigned long timeMs) {
    auto result = Asynchronizer::UpdateInterval(taskId, callback, timeMs);

    if(result == false){
        auto newTaskId = Asynchronizer::Interval(callback, timeMs);
        return newTaskId;
    }
    
    return taskId;
}

#pragma endregion Interval

#pragma region Delay

int Asynchronizer::Delay(std::function<void()> callback, unsigned long timeMs) {
    auto task = Asynchronizer::CreateTask(callback, timeMs);

    task->afterFire = [task](){
        CancelById(task->taskId);
    };

    return task->taskId;
}

bool Asynchronizer::UpdateDelay(int taskId, std::function<void()> callback, unsigned long timeMs) {
    auto task = Asynchronizer::GetTaskById(taskId);
    if(task == NULL){
        return false;
    }

    auto newTimeMs = millis() + timeMs;
    task->timeMs = newTimeMs;
    task->callback = callback;
    return true;
}

int Asynchronizer::CreateOrUpdateDelay(int taskId, std::function<void()> callback, unsigned long timeMs) {
    auto result = Asynchronizer::UpdateDelay(taskId, callback, timeMs);

    if(result == false){
        auto newTaskId = Asynchronizer::Delay(callback, timeMs);
        return newTaskId;
    }
    
    return taskId;
}

#pragma endregion Delay

void Asynchronizer::CancelById(int taskId) {
    tasks.erase(remove_if(tasks.begin(), tasks.end(), [taskId](auto item){
        return item->taskId == taskId;
    }), tasks.end());
}

void Asynchronizer::CancelAll() {
    tasks.clear();
}

bool Asynchronizer::IsRunning(int taskId) {
    bool isRunning = std::any_of(tasks.begin(), tasks.end(), [taskId](auto task) {
        return task->taskId == taskId;
    });
    return isRunning;
}

#pragma region PRIVATE

int Asynchronizer::GenerateId(){
    auto id = rand();

    if(id == 0 || Asynchronizer::IsRunning(id))
    {
        return Asynchronizer::GenerateId();
    }

    return id;
}

Task* Asynchronizer::GetTaskById(int taskId) {
    auto iterador = find_if(tasks.begin(), tasks.end(), [&](auto item) {
        return item->taskId == taskId;
    });

    if (iterador != tasks.end()) {
        return (*iterador);
    } else {
        return NULL;
    }
}

Task* Asynchronizer::CreateTask(std::function<void()> callback, unsigned long timeMs) {
    auto taskId = Asynchronizer::GenerateId();
    auto task = new Task(taskId, (millis() + timeMs), callback);
    tasks.push_back(task);
    return task;
}

#pragma endregion PRIVATE