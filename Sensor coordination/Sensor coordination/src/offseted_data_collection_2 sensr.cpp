// #include <Arduino.h>

// const int WIRE_1 = 34; 
// const int WIRE_2 = 32; 
// const int HZ = 100;
// const int INTERVAL_MS = 1000 / HZ;
// const int UTTERANCE_MS = 2000; 
// const int TOTAL_UTTERANCES = 50;

// void runDualSensorCycle();

// void setup() {
//   Serial.begin(115200);
//   analogReadResolution(12); // 12-bit resolution (0-4095)
//   analogSetAttenuation(ADC_11db); // Range up to ~3.1V
//   pinMode(WIRE_2, INPUT); 
// }

// void loop() {
//   if (Serial.available() > 0) {
//     char cmd = Serial.read();
//     if (cmd == 'S') {
//       runDualSensorCycle();
//     }
//   }
// }

// void runDualSensorCycle() {
//   for (int i = 1; i <= TOTAL_UTTERANCES; i++) {
//     delay(3000); // Prep time
    
//     Serial.println("START_REC"); 
//     unsigned long startTime = millis();
    
//     while (millis() - startTime < UTTERANCE_MS) {
//       unsigned long loopStart = millis();
      
//       unsigned long timestamp = millis();
//       int w1 = analogRead(WIRE_1);
//       int w2 = analogRead(WIRE_2);

//       // Raw CSV: Time,W1,W2
//       Serial.print(timestamp);
//       Serial.print(",");
//       Serial.print(w1); 
//       Serial.print(",");
//       Serial.println(w2);

//       while (millis() - loopStart < INTERVAL_MS); 
//     }
    
//     Serial.println("STOP_REC"); 
//     delay(500); 
//   }
//   Serial.println("FINISHED_ALL");
// }