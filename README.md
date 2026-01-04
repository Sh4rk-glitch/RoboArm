# RoboArm

### Description: 
RoboArm is a fully 3D‑printed, Arduino‑powered robotic arm controlled through a wireless gesture‑tracking glove. The system uses dual microcontrollers (Arduino Nano + Arduino Uno), MPU6050 IMUs for gesture detection, and a PCA9685 servo driver to control multiple joints with smooth, precise motion.
This repository contains all firmware, CAD files, and documentation needed to build, modify, and expand the project.

### Features
- Wireless gesture control using MPU6050 sensors
- 6‑DOF robotic arm powered by MG996R servos
- PCA9685 servo driver for stable multi‑servo control
- Stepper‑motor base rotation
- Modular PlatformIO projects for both glove and arm
- Fully open‑source and customizable

### System Architecture
The project is split into two independent microcontroller systems:

1. Gesture Glove (Arduino Nano)
- Reads orientation data from MPU6050 sensors
- Processes gestures into discrete commands
- Sends commands over serial/Bluetooth to the arm

2. Robotic Arm (Arduino Uno)
- Receives gesture commands
- Controls servos via PCA9685
- Drives stepper motor for base rotation
- Executes smooth, incremental joint movements

# Pictures

### Breadboard:
<img width="1835" height="2000" alt="image" src="https://github.com/user-attachments/assets/3258f934-a6e9-4ef2-bb97-50791083342f" />
<img width="2000" height="989" alt="image" src="https://github.com/user-attachments/assets/af8c9d22-e2f7-4005-ab40-33dee54d5d8a" />
<img width="1424" height="2000" alt="image" src="https://github.com/user-attachments/assets/f8de1bea-baa3-4955-bd10-189e7eeb0a89" />
<img width="814" height="2000" alt="image" src="https://github.com/user-attachments/assets/33412234-5c47-4a38-a300-679cc3a39185" />

## CAD Pics and renders: 
### RoboGlove
The wrist connector:
<img width="627" height="464" alt="image" src="https://github.com/user-attachments/assets/0c49fef0-f662-4ae5-b22f-659e9221c425" />


The index finger:
<img width="530" height="468" alt="image" src="https://github.com/user-attachments/assets/04661e67-63f3-40d6-9c18-f824fee521a8" />


The pinky finger:
<img width="601" height="395" alt="image" src="https://github.com/user-attachments/assets/90f28e0b-0def-4da9-916d-c3300d5fd30e" />


The Thumb:
<img width="545" height="516" alt="image" src="https://github.com/user-attachments/assets/e5cf54b5-b0a0-4776-bb27-89cc9eb4e2ba" />


The right hand connector (this is where the arduino nano will sit on along side the breadboard and everthing):
<img width="675" height="537" alt="image" src="https://github.com/user-attachments/assets/d13a6f31-52ce-433b-a8f3-5fda27d2f1c7" />


And finally something I added for more movement alongside the wrist:
<img width="613" height="520" alt="image" src="https://github.com/user-attachments/assets/33129f1a-b862-4621-ae33-a4163a719866" />

### RoboArm
The claw (this is how it'll be put together, I have all the individual stl files which ill print and then put together to make the claw):
<img width="425" height="799" alt="image" src="https://github.com/user-attachments/assets/9815f09c-b92d-40d8-8de7-a881d5371bd2" />


<img width="907" height="836" alt="image" src="https://github.com/user-attachments/assets/1298a482-959f-433a-b36b-94324baa5c44" />


The Base with motor:
<img width="424" height="1018" alt="image" src="https://github.com/user-attachments/assets/6f76f1b3-1ecc-4fc5-a398-c665c70d7f3c" />


<img width="1024" height="887" alt="image" src="https://github.com/user-attachments/assets/3f28f494-70d5-4b1c-81ad-66cc55852ed8" />


And finally the Arm:
<img width="1022" height="874" alt="image" src="https://github.com/user-attachments/assets/6580c636-a6f9-4aca-82ad-e87b8efdc30d" />

<img width="893" height="687" alt="image" src="https://github.com/user-attachments/assets/b2a16ce7-c301-43f1-b8cc-59b399fa23d0" />

<img width="1024" height="858" alt="image" src="https://github.com/user-attachments/assets/8901d2ef-aecf-467d-97dc-1b611d363335" />

And the whole thing together:
<img width="1024" height="678" alt="image" src="https://github.com/user-attachments/assets/d7d1512d-c0b3-4705-a323-0eaec2ae28ae" />
