# Asynchronizer
**Asynchronizer** is javascript like non blocking delay for Arduino.

**Asynchronizer** contains 2 types of delays:

## ***Delay* (equivalent to setTimeout in JS)**
```
int taskId = Asynchronizer::Delay([](){
  Serial.println("This text will be printed in 10 seconds");
}, 10000);
```
> Delay: Creates an Delay and returns the delayId

```
bool hasBeenUpdated = Asynchronizer::UpdateDelay(taskId, [](){
   Serial.println("Now this text will be printed in 5 seconds");
}, 5000);
```
> UpdateDelay: Updates an Delay and returns true if the Delay has been updated or false if it has not been updated

```
taskId = Asynchronizer::CreateOrUpdateDelay(taskId, [](){
  Serial.println("Now this text will be printed in 4 seconds");
}, 4000);
```
> CreateOrUpdateDelay: Create a new Delay if the taskId does not exists, or updates the current one

## ***Interval* (equivalent to setInterval in JS)**
```
int taskId = Asynchronizer::Interval([](){
  Serial.println("This text will be printed every 10 seconds");
}, 10000);
```
> Creates an Interval and returns the intervalId

```
bool hasBeenUpdated = Asynchronizer::UpdateInterval(taskId, [](){
   Serial.println("Now this text will be printed every 5 seconds");
}, 5000);
```
> Updates an Interval and returns true if the Interval has been updated or false if it has not been updated

```
taskId = Asynchronizer::CreateOrUpdateInterval(taskId, [](){
  Serial.println("Now this text will be printed every 4 seconds");
}, 4000);
```
> Create a new Interval if the taskId does not exists, or updates the current one

## **Canceling a Delay or Timeout**
To cancel a Timeout or Delay you can use the *CancelById* method
```
Asynchronizer::CancelById(taskId);
```
  Or if you want to cancel all Delays or Timeouts you can use the *CancelAll* method
```
Asynchronizer::CancelAll();
```

## **Check if a Delay or Timeout is running**
To check if a Delay or Timeout is running you can use the *IsRunning* method
```
bool isRunning = Asynchronizer::IsRunning(taskId);
```

# **Using Asynchronizer**
To use **Asynchronizer**, you will need to use the *Check* method
```
Asynchronizer::Check();
```
> The *Check* method basically check if a delay or timeout has ended, its recommended to put in the *loop()* method

**Example**
```
void loop() 
{   
  Asynchronizer::Check();
}
```
