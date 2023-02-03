#include "Adafruit_LiquidCrystal.h"

const int rs = 10, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
Adafruit_LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define ThermistorPin A0
int Vo;
float R1 = 10000;
float R2, myRoomTemp;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

void setup() {
    // Begin serial communication at a baud rate of 9600.
    Serial.begin(9600);

    // Initialize the LCD.
    lcd.begin(16, 2);
}

void loop() {
    // Read the voltage from the thermistor.
    Vo = analogRead(ThermistorPin);

    // Calculate the resistance of the thermistor.
    R2 = R1 * (1023.0 / (float)Vo - 1.0);

    // Calculate the temperature in degrees Celsius.
    myRoomTemp = (1.0 / (c1 + (c2 * log(R2)) + (c3 * log(R2) * log(R2) * log(R2)))) - 273.15;

    // If `myRoomTemp` is not a number, there's no room temperature.
    // Print an error message to the serial monitor and try again immediately.
    if (myRoomTemp == -273.15) {
        Serial.println("No data.");
    } else {
        // Print the value of `myRoomTemp` to the serial monitor.
        Serial.println(myRoomTemp);

        // Print the value of `myRoomTemp` to the LCD.
        lcd.setCursor(0, 0);
        lcd.print("Temp: ");
        lcd.print(myRoomTemp);
        lcd.print("\337C");
    }

    // Wait 1 second before we read the next value from the sensor.
    delay(1000);

    // Clear the LCD.
    lcd.clear();
}
