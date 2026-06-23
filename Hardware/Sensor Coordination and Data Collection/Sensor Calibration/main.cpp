// #include <ArduinoBLE.h>

// // Define pins for the local wired sensors
// const int SENSOR_PIN_1 = 34; 
// const int SENSOR_PIN_2 = 32; 



// void setup() 
// {
//   Serial.begin(115200);
//   while (!Serial); 
//   Serial.println("MyoWare Triple Sensor Setup - BLE Central + 2 Local");

//   // Configure ADC resolution for ESP32 (0-4095)
//   analogReadResolution(12);

// }
// void loop() 
// {
// // Oversampling for stability
// long sum1 = 0;
// long sum2 = 0;
// for(int i = 0; i < 10; i++) {
//     sum1 += analogRead(SENSOR_PIN_1);
//     sum2 += analogRead(SENSOR_PIN_2);
// }
// int localVal1 = sum1 / 10;
// int localVal2 = sum2 / 10;

// Serial.print(localVal1);
// Serial.print(",");
// Serial.println(localVal2);

// delay(100); 
// }