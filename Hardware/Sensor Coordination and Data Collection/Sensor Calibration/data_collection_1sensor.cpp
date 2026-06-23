// #include <Arduino.h>

// const int SENSOR_PIN = 32;
// const int HZ = 100;
// const int INTERVAL_MS = 1000 / HZ;
// const int UTTERANCE_MS = 2000; 
// const int TOTAL_UTTERANCES = 50; // Increased to 50

// void runFiftyUtterances();

// void setup() {
//   Serial.begin(115200);
//   analogReadResolution(12);
//   analogSetAttenuation(ADC_11db);
//   // System waits for 'S' from Python script
// }

// void loop() {
//   if (Serial.available() > 0) {
//     char cmd = Serial.read();
//     if (cmd == 'S') {
//       runFiftyUtterances();
//     }
//   }
// }

// void runFiftyUtterances() {
//   for (int i = 1; i <= TOTAL_UTTERANCES; i++) {
//     // 3-second countdown for the user to prepare
//     delay(3000); 
    
//     Serial.println("START_REC"); 
//     unsigned long startTime = millis();
    
//     while (millis() - startTime < UTTERANCE_MS) {
//       unsigned long loopStart = millis();
//       Serial.println(analogRead(SENSOR_PIN));
//       while (millis() - loopStart < INTERVAL_MS); 
//     }
    
//     Serial.println("STOP_REC"); 
//     // Small delay between utterances to allow muscle reset
//     delay(500); 
//   }
//   Serial.println("FINISHED_ALL");
// }