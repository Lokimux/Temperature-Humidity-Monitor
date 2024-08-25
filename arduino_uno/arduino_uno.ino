#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// Define DHT22 sensor pin
#define DHTPIN 2

// Define DHT type
#define DHTTYPE DHT22  // Change to DHT22

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
