// Include the libraries.
#include <DHT.h>

// Set DHT pin.
// This is the pin where the DHT's `DATA` pin is connected to.
// The `DATA` should be connected to a ANALOG pin.
#define DHTPIN A0

// Set DHT type.
// You can use the following types: DHT11, DHT21 or DHT22.
#define DHTTYPE DHT11

// Initialize DHT sensor for normal 16mhz Arduino.
DHT dht = DHT(DHTPIN, DHTTYPE);

void setup() {
   // Begin serial communication at a baud rate of 9600.
   Serial.begin(9600);

   // Double check whether the `dht` object was initialized
   // and began communication with the sensor.
   if (dht.begin()) {
      Serial.println("DHT sensor started.");
   } else {
      Serial.println("DHT sensor failed to start.");
   }
}

void loop() {
   // Calls a function on our dht opbject taht will return the
   // temperature in degrees celcius as a float value.
   // `myRoomTemp` holds the returned value.
   float myRoomTemp = dht.readTemperature();

   // Print the value of `myRoomTemp` to the serial monitor.
   Serial.println(myRoomTemp);

   // If `myRoomTemp` is not a number, there's no room temperature.
   // Print an error message to the serial monitor and try again immediately.
   if (isnan(myRoomTemp {
      Serial.println("No room temperature data.");
      return;
   }

   // Wait 1 second before we read the next value from the sensor.
   delay(1000);
}

