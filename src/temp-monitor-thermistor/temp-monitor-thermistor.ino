#define ThermistorPin A0
int Vo;
float R1 = 10000;
float R2, myRoomTemp;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

void setup() {
   // Begin serial communication at a baud rate of 9600.
   Serial.begin(9600);
}

void loop() {
   // Read the voltage from the thermistor.
   Vo = analogRead(ThermistorPin);

   // Calculate the resistance of the thermistor.
   R2 = R1 * (1023.0 / (float)Vo - 1.0);

   // Calculate the temperature in degrees Celsius.
   myRoomTemp = (1.0 / (c1 + (c2 * log(R2)) + (c3 * log(R2) * log(R2) * log(R2)))) - 273.15;

   // Print the value of `myRoomTemp` to the serial monitor.
   Serial.println(myRoomTemp);

   // If `myRoomTemp` is not a number, there's no room temperature.
   // Print an error message to the serial monitor and try again immediately.
   if (isnan(myRoomTemp)) {
      Serial.println("No room temperature data.");
      return;
   }

   // Wait 1 second before we read the next value from the sensor.
   delay(1000);
}

