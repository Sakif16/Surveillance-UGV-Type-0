# Surveillance-UGV-Type-0
## Intro
An extremely cost effective and recyclable autonomous surveillance UGV capable of patrolling, detecting motion, and following objects/threats in real-time — designed for surveillance and reconnaissance (and elimination if added a fun little tweak >_<) applications.

---

## Description
Surveillance-UGV-Type-0 is a robotics project that implements an autonomous Unmanned Ground Vehicle (UGV) with advanced obstacle avoidance and motion detection capabilities. The UGV autonomously patrols a designated area, detects motion using sensors, and can follow detected objects. It features intelligent navigation to avoid obstacles and maintain stable autonomous operation all while being extremely cost effective and made so that it can be dismantled and recycled very easily.

### Key Features:
- Autonomous patrolling and surveillance
- Real-time motion detection
- Object following capabilities
- Obstacle avoidance system
- Modular and upgradeable design

---

##  Video Showcase (Click!)

[![Watch the video](https://img.youtube.com/vi/xMGt-dS8Khw/maxresdefault.jpg)](https://youtu.be/xMGt-dS8Khw)

---

## Circuit Diagram
![UGV Circuit Diagram](public/ugv0.png)

The circuit diagram above shows the complete wiring and component layout for the Surveillance-UGV-Type-0, including motor connections, sensor integration, and power distribution.

---

## Components
- **Arduino** (microcontroller programming)
- **HC-SR04 Sensor** (Sonar, Distance measurement)
- **SG90 Servo** (Head rotation)
- **IR Sensor x2** (Object position determination)
- **HC-SR501 PIR Sensor** (Motion detection)
- **L298N H-Bridge Dual Motor Driver** (Motor driver)
- **6V Motor x4** (Mobility)
- **Breadboard** (Circuit hub)
- **3.7V Cell x3** (Motordriver power source)
- **3 Cell holder** (pretty self explainatory)
- **5V Powerbank** (Arduino power source)
- **Red LED** (Motion idication)
- **330Ohm Resistor** (LED safeguard)

- **Jumper Wires & Alligator Clips** (Primary connection)
- **Cardboard x2** (Chassis)
- **Double Sided Tape** (Recyclable hardware attachments)

## Tech Stack
- **Arduino** (microcontroller programming)
- **C/C++** (Arduino language)
- **Motor Control Libraries** (DC motor driving)
- **Sensor Integration** (motion detection, obstacle sensing, distance calculation)
- **Embedded Systems** (autonomous vehicle logic)

---

## ⚠️ Known Issues
- IR sensor adjusted for very short range, for demo.
- Motion detection may trigger false positives in changing lighting conditions
- Object following speed inconsistencies depending on battery power.
- Limited battery life during continuous operation.

---

## Future Development
- Improved sensor fusion for better obstacle detection
- GPS integration for autonomous waypoint navigation
- Live video streaming capability
- Enhanced motion detection algorithm with ML-based filtering
- Mobile app for remote control and monitoring
- Multi-robot coordination for group patrols
- Power management optimization for extended operation time
- Custom PCB design for compact integration

---

### Fun Fact
The UGV was intentionally stripped out of its original suicidal logic of attempting to crash into the detected anomaly (with immaginary explosive filler of course) in order to comply with "academic" guidelines/policies. 
