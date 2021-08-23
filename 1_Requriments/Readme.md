# INTRODUCTION

This project is based on Simple Aurdino Home Automation with Gas and water level sensors.It is used to sense motion,temperature and light and Response according to it.It also used to detect  the leakage of gas and used to measure the water level.Gas leakage is a serious problem and nowadays it is observed in many places like residences,industries, and vehicles like Compressed Natural Gas (CNG), buses, cars, etc. It is noticed that due to gas leakage, dangerous accidents occur.


# RESEARCH

The aim of this project is to propose and discuss a design of a gas leakage detection system that can automatically detect, alert and control gas leakage. This proposed system also includes an alerting system for the users. The system is based on a sensor that easily detects a gas leakage. A gas leakage detector becomes vital and helps to protect people from the dangers of gas leakage. A number of research project have been published on gas leakage detection techniques.


# Defining Our System

In this project, we have focused on basic and important concept of allowing multiple sensors to perform simultaneously. The sensors installed are not directly connected to each other so the activity of an individual sensor remains unaffected which allows it to perform more effeciently and provide better results. The main obective is to prevent unnecessary hazards occuring from leakages along with the virtues of automated home control system. The defining fetures are
* Controlled switching of electrical appliances
* Gas leakage and water leavel treatment.    
* Door safety using numcode. 
* Switching fan via humidity and temperature values 


# SWOT ANALYSIS
![swot](https://user-images.githubusercontent.com/86046024/130255013-c012d295-4883-4b62-bb43-6c38c5a3d09c.png)


# 4W's and 1H
### WHO:
Can be used in houses.
### WHEN:
When a person wants to control his house in a smart way. It can also be used
as a safty measure.
### WHERE:
This system can be used all across the world. 
### WHAT:
This system is a smart automation system which makes life easy and secure.
### HOW:
The person can control the whole house smartly with the help of a smart
device.


# Detail Requirements

### High Level Requirements (HLR) 

| ID   | Description | Category| Status  |
| ------ | ------------| ---------- | -------- |
| HR_01| Signal Conversion and Switching| Technical |  Implemented|
| HR_02 | Gas Leakage Detection| Technical| Implemented |
| HR_03 | Water Level Indication | Technical | Implemented |
| HR_04 | Humidity and Temperature Detection | Tecnhical | Implemented |
| HR_05 | Door Lock | Technical | Implemented |
|HR_06| Simultaneous Functioning | Technical | Implemented|


### Low Level Requirements (LLR)

| ID | Description | Reference ID | Status |
| ---- |---- | ------ | ------ |
| LR_11 | Motion detector acts as an initiator to system | HR_01 | Implemented |
| LR_12 | Controlled switching of electrical appliances | HR_01 | Implemented |
| LR_13 | Valves for controlling/stopping leakages | HR_01 | Implemented |
| LR_21 | MQ sensors for detection of Gas | HR_02 | Implemented |
| LR_22 | Threshold value for gasshould not exceed  1000 ppm | HR_02 | Implemented |
| LR_23 | Disposing of gas ( via. exhaust fan)  | HR_02 | Implemented |
| LR_24 | Turning off the Gas leakage source | HR_02 | Implemented |
| LR_25 | Alertion about gas leakage | HR_02 | Implemented |
| LR_31 | Ultrasonic sensor for water level detection | HR_03 | Implemented |
| LR_32 | Water level indication on display | HR_03 | Implemented |
| LR_33 | Valve status indication via display | HR_03 | Implemented |
| LR_34 | Turning off the source once overflow is detected | HR_03 | Implemented |
| LR_41 | Switching fan depending on humidity and temperature ranges | HR_04 | Implemented |
| LR_42 | User defined minimum temperature values | HR_04 | Implemented |
| LR_51 | Number lock is required to unlock door | HR_05 | Implemented |
| LR_52 | Num Pad code is read by the system |  HR_05 | Implemented |
| LR_53 | Alerting owner after multiple incorrect tries | HR_05 | Not Implemented |
| LR_61 | System can perform multiple processes simultaneously| HR_06 | Implemented |
| LR_62 | Additional power source to maintain uninterrupted operation | HR_06 | Not implemented |
