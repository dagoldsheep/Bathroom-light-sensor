# Bathroom Light Sensor 

An ESP32‑powered presence‑activated bathroom light system that automatically turns lights on at night, keeps them off during the day, and uses a distance sensor to detect movement smoothly and reliably.

This project replaces manual switches with smart automation using:
- ESP32
- Analog distance sensor
- Relay module
- NTP time syncing
- Presence smoothing logic

---

##  Features

- **Night Mode (8 PM → 9 AM)**  
  Lights turn on automatically when presence is detected.

- **Daytime Off Mode (9 AM → 8 PM)**  
  Lights stay off 

- **Presence Smoothing**  
  Reduces false triggers by averaging sensor readings.

- **Auto‑Off Timer**  
  Turns lights off 5 seconds after no presence is detected.

- **NTP Time Sync**  
  Ensures accurate time windows without an RTC module.

---

##  How It Works

The ESP32 reads an analog distance sensor and converts the value into a smoothed distance estimate.  
If the smoothed distance is below a threshold, presence is detected.

Depending on the current hour (via NTP), the system chooses one of three modes:
- **Night** → Lights ON with presence  
- **Morning** → Lights ON with presence  
- **Daytime** → Lights always OFF  

A relay module controls the actual light strip.

---

##  Hardware Used

- ESP32 Dev Board  
- Analog distance sensor (e.g., VL53L0X, IR sensor, or similar)  
- 5V relay module  
- LED strip or bathroom light  
- Jumper wires  
- Power supply  

---

##  Code Overview

The main logic lives in `loop()`:
- Reads sensor  
- Smooths distance  
- Determines presence  
- Checks time window  
- Controls relay accordingly  

The relay defaults to **OFF** at startup and only turns **ON** when presence is detected in allowed time windows.

---

## Getting Started

1. Flash the `.ino` file to your ESP32  
2. Connect your sensor to pin **34**  
3. Connect your relay to pin **5**  
4. Add your WiFi credentials in the code  
5. Power the system and watch it run automatically  

---


Feel free to modify, improve, and share it.

