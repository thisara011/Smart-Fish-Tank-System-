                                                                                                                                          #define BLYNK_TEMPLATE_ID "TMPL6O_bpf5Cd"
#define BLYNK_TEMPLATE_NAME "Smart Fish Tank System"

#define BLYNK_PRINT Serial  // Enable Blynk Debugging

#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP32Servo.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

#define SENSOR_PIN  19          // DS18B20 Temperature Sensor pin
#define SERVO_PIN   18          // Servo Motor pin
#define WATER_LEVEL_PIN 32      // Water Level Sensor pin
#define RELAY_PIN 4             // Relay for Automatic Pump Control
#define RELAY_PIN_Pump 5        // Relay for Manual Water Pump Control

// WiFi & Blynk credentials
char auth[] = "6KbVmW9zrdP1lQ2qyYAIVOg2zOdaExZq"; 
char ssid[] = "saman";    
char pass[] = "741640074";  

OneWire oneWire(SENSOR_PIN);
DallasTemperature DS18B20(&oneWire);
Servo servo;
BlynkTimer timer;

float tempC;
float waterLevelPercentage;
bool isPumpOn = false;
bool isManualPump = false;  // New flag for manual pump mode
bool isAutoControl = false;
int servoTimer1, servoTimer2;

void setup() {
  Serial.begin(9600);
  DS18B20.begin();
  servo.attach(SERVO_PIN);
  
  pinMode(WATER_LEVEL_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(RELAY_PIN_Pump, OUTPUT);  // ✅ FIXED: Ensure manual pump pin is set as OUTPUT
  
  digitalWrite(RELAY_PIN, LOW);     // Ensure pumps are OFF at startup
  digitalWrite(RELAY_PIN_Pump, LOW); 

  WiFi.begin(ssid, pass);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi!");

  Blynk.begin(auth, ssid, pass);
}

// Manual Servo Control (V0)
BLYNK_WRITE(V0) {
  int switchState = param.asInt();
  servo.write(switchState ? 180 : 0);
}

// Automatic Servo Control (V1)
// Automatic Servo Control (Modified)
BLYNK_WRITE(V1) {
  int switchState = param.asInt();
  if (switchState == 1) {
    isAutoControl = true;
    servoTimer1 = timer.setInterval(8000L, []() { // Total cycle: 3s ON + 5s OFF
      servo.write(180); // Rotate servo to 180 degrees
      timer.setTimeout(3000L, []() { 
        servo.write(0); // Rotate back to 0 degrees after 3 seconds
      });
    });
  } else {
    isAutoControl = false;
    timer.deleteTimer(servoTimer1);
    servo.write(0); // Ensure servo is off when manual mode is activated
  }
}


// Manual Remove Control (V4) - Drains Water
BLYNK_WRITE(V4) {
  int state = param.asInt();
  Serial.print("V4 Button Pressed: ");
  Serial.println(state);

  if (state == 1) {
    Serial.println("Manual Mode: Removing Water...");
    digitalWrite(RELAY_PIN, HIGH);
    isPumpOn = true;
    isManualPump = true;
  } else {
    Serial.println("Manual Mode: Stopping Water Removal...");
    digitalWrite(RELAY_PIN, LOW);
    isPumpOn = false;
    isManualPump = false;
  }
  Blynk.virtualWrite(V6, isPumpOn ? "ON" : "OFF"); 
}

// Manual Pump Control (V5) - Adds Water
BLYNK_WRITE(V5) {
  int state = param.asInt();
  Serial.print("V5 Button Pressed: ");
  Serial.println(state);

  if (state == 1) {
    Serial.println("Turning ON Manual Pump...");
    digitalWrite(RELAY_PIN_Pump, HIGH);
    isPumpOn = true;
    isManualPump = true;
  } else {
    Serial.println("Turning OFF Manual Pump...");
    digitalWrite(RELAY_PIN_Pump, LOW);
    isPumpOn = false;
    isManualPump = false;
  }
  Blynk.virtualWrite(V6, isPumpOn ? "ON" : "OFF");  
}

// Read Temperature & Water Level
void checkSystem() {
  DS18B20.requestTemperatures();
  tempC = DS18B20.getTempCByIndex(0);

  int sensorValue = analogRead(WATER_LEVEL_PIN);
  waterLevelPercentage = ((float)sensorValue / 4095) * 100;

  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.println("°C");

  Serial.print("Water Level: ");
  Serial.print(waterLevelPercentage, 2);
  Serial.println("%");

  Blynk.virtualWrite(V2, tempC);
  Blynk.virtualWrite(V3, waterLevelPercentage);

  // Automatic Pump Logic (Only if Manual Mode is OFF)
  if (!isManualPump) {
    if (tempC > 35.0) {
      Serial.println("Temperature high! Pump ON.");
      digitalWrite(RELAY_PIN, HIGH);
      isPumpOn = true;
    } 
    
    if (isPumpOn && waterLevelPercentage <= 50.0) {
      Serial.println("Water level sufficient! Pump OFF.");
      digitalWrite(RELAY_PIN, LOW);
      isPumpOn = false;
    }
  }

   // Automatic Pump Logic (Only if Manual Mode is OFF)
  if (!isManualPump) {
    if (tempC > 35.0) {
      Serial.println("Temperature high! Pump ON.");
      digitalWrite(RELAY_PIN_Pump, HIGH);
      isPumpOn = true;
    } 
    
    if (isPumpOn && waterLevelPercentage >= 80.0) {
      Serial.println("Water level sufficient! Pump OFF.");
      digitalWrite(RELAY_PIN_Pump, LOW);
      isPumpOn = false;
    }
  }


  Blynk.virtualWrite(V6, isPumpOn ? "ON" : "OFF");
}

void loop() {
  Blynk.run();
  timer.run();
  checkSystem();
  delay(1000); 
}
