# Weather Display Station

## Overview

The **Weather Display Station** project uses an Arduino to interface with a DHT22 sensor and a 16x2 LCD display. The DHT22 sensor measures temperature and humidity, which are then displayed on the LCD. This project is useful for monitoring environmental conditions in real-time.

## Components Used

- **Arduino Uno** (or any compatible Arduino board)
- **DHT11 Sensor** (Temperature and Humidity Sensor)
- **16x2 LCD Display with I2C Interface**
- **Jumper Wires**
- **Breadboard** (optional)

## Circuit Diagram

<img src="https://github.com/Lokimux/Temp---Humidity-Monitor/blob/main/circuit.png" />

## Connections

### DHT22 Sensor to Arduino
- **VCC** -> Arduino 5V
- **GND** -> Arduino GND
- **DATA** -> Arduino Digital Pin 2
- **NC** -> Not Connected

### 16x2 LCD (I2C) to Arduino
- **VCC** -> Arduino 5V
- **GND** -> Arduino GND
- **SDA** -> Arduino SDA (A4 on UNO)
- **SCL** -> Arduino SCL (A5 on UNO)

## Code

```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// Define DHT11 sensor pin
#define DHTPIN 2

// Define DHT type
#define DHTTYPE DHT11  // Change to DHT11

// Initialize the DHT sensor
DHT dht(DHTPIN, DHTTYPE);

// Set the LCD address to 0x27 for a 16x2 display (change if necessary)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Start the LCD
  lcd.init();
  lcd.backlight();
  
  // Start the DHT sensor
  dht.begin();
  
  // Initial message
  lcd.setCursor(0, 0);
  lcd.print("Temp:    C");
  lcd.setCursor(0, 1);
  lcd.print("Hum:     %");
}

void loop() {
  // Read temperature as Celsius
  float temp = dht.readTemperature();
  
  // Read humidity
  float hum = dht.readHumidity();
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(temp) || isnan(hum)) {
    lcd.setCursor(0, 0);
    lcd.print("Error reading ");
    lcd.setCursor(0, 1);
    lcd.print("DHT22 sensor!");
    return;
  }

  // Display temperature on LCD
  lcd.setCursor(6, 0); // Set cursor to start of temp value
  lcd.print(temp);
  lcd.print(" ");
  
  // Display humidity on LCD
  lcd.setCursor(6, 1); // Set cursor to start of humidity value
  lcd.print(hum);
  lcd.print(" ");

  // Delay between readings
  delay(2000); // 2 seconds
}
