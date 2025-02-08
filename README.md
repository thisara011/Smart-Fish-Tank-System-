# Smart Fish Tank System 🐠💡

Welcome to the **Smart Fish Tank System** repository! This project automates and monitors essential aquarium conditions such as water temperature and water level while providing remote control via the **Blynk IoT** platform. The system ensures a healthy and safe environment for your fish with smart automation and manual override features.

## 🚀 Features

✅ **Real-time Temperature Monitoring**: Uses a DS18B20 sensor to measure water temperature and display it on the Blynk app.

✅ **Water Level Monitoring**: Reads water level percentage and sends live updates to the Blynk dashboard.

✅ **Automatic Water Pump Control**: Activates the pump when the temperature is too high or the water level is too low.

✅ **Manual Pump Override**: Enables manual water pump activation via the Blynk app.

✅ **Smart Servo Feeder**: Controls a servo motor to automate fish feeding, with both manual and scheduled modes.

✅ **WiFi Connectivity**: Uses an ESP32 module to communicate with Blynk via WiFi.

---

## 🛠️ Hardware Components

- ESP32 Development Board
- DS18B20 Temperature Sensor
- Water Level Sensor
- Servo Motor
- 2 x Relay Modules
- Submersible Water Pump
- Power Supply
- Jumper Wires & Breadboard

---

## 📲 Software & Libraries

This project is built using the following software tools:

- **Arduino IDE** (for programming ESP32)
- **Blynk IoT Platform** (for remote monitoring & control)
- **Libraries Used**:
  - `WiFi.h` (for ESP32 WiFi connectivity)
  - `BlynkSimpleEsp32.h` (for Blynk integration)
  - `OneWire.h` & `DallasTemperature.h` (for DS18B20 temperature sensor)
  - `ESP32Servo.h` (for servo motor control)

---

## 🔌 Wiring Diagram

| Component        | ESP32 Pin |
|-----------------|-----------|
| DS18B20 Temp Sensor | GPIO 19 |
| Water Level Sensor  | GPIO 32 |
| Servo Motor        | GPIO 18 |
| Relay (Auto Pump)  | GPIO 4  |
| Relay (Manual Pump)| GPIO 5  |

---

## 📜 Installation & Setup

1️⃣ **Clone this repository**:
```sh
   git clone https://github.com/yourusername/smart-fish-tank.git
   cd smart-fish-tank
```

2️⃣ **Install Required Libraries**:
   - Open Arduino IDE and install the required libraries via Library Manager.

3️⃣ **Edit WiFi & Blynk Credentials**:
   - Open `smart_fish_tank.ino` and update:
   ```cpp
   char auth[] = "Your_Blynk_Auth_Token";
   char ssid[] = "Your_WiFi_SSID";    
   char pass[] = "Your_WiFi_Password";  
   ```

4️⃣ **Upload Code**:
   - Select **ESP32** as the board and upload the code via USB.

5️⃣ **Configure Blynk Dashboard**:
   - Add virtual pins (V0-V6) for controls and monitoring.

---

## 🎯 How It Works

1️⃣ **Temperature & Water Level Monitoring**:
   - The system continuously reads temperature and water level and sends the data to Blynk.

2️⃣ **Automatic Water Pump**:
   - If the temperature exceeds **35°C**, the pump turns on.
   - If the water level is below **50%**, the pump turns on.
   - Once the water level reaches **80%**, the pump turns off.

3️⃣ **Manual Control via Blynk**:
   - Users can manually activate the **water pump** or **servo feeder** using buttons in the Blynk app.

4️⃣ **Automatic Fish Feeding**:
   - Users can enable automatic feeding where the servo rotates to release food at intervals.

---

## 🛠️ Future Improvements

🚀 Add a **pH Sensor** for monitoring water quality.  
🚀 Implement a **Mobile Notification System** for critical alerts.  
🚀 Integrate **AI-based Feeding Prediction** based on fish behavior.  
🚀 Create a **Web Dashboard** for monitoring without the Blynk app.  

---

## 🎉 Contributing

Feel free to contribute and improve this project! To contribute:

1. **Fork** the repository 🍴
2. **Create** a new branch (`feature-branch`) ✨
3. **Commit** your changes 📝
4. **Push** and submit a PR 🔥

---

## 🔗 Connect with Me
💼 LinkedIn:(https://www.linkedin.com/in/thisara-edirisingha-4b9515198?lipi=urn%3Ali%3Apage%3Ad_flagship3_messaging_conversation_detail%3B0JgJ2OK7RHSZPMaP6FHQkw%3D%3D))  
🐙 GitHub:(https://github.com/thisara011)  

---

## 📜 License

This project is **open-source** and available under the MIT License.

---

🚀 **Transform your aquarium into a smart, automated ecosystem today!** 🐟🌱

