// #include <ArduinoBLE.h>

// const int WIRE_1 = 34; 
// const int WIRE_2 = 32; // Changed from 36 to 32
// const int HZ = 100;
// const int INTERVAL_MS = 1000 / HZ;
// const int UTTERANCE_MS = 2000; 
// const int TOTAL_UTTERANCES = 50;

// void runThreeSensorCycle(BLECharacteristic& dataChar);

// void setup() {
//   Serial.begin(115200);
//   analogReadResolution(12);
//   analogSetAttenuation(ADC_11db);

//   if (!BLE.begin()) {
//     while (1); 
//   }
//   BLE.scanForUuid("19b10000-e8f2-537e-4f6c-d104768a1214");
// }

// void loop() {
//   BLEDevice peripheral = BLE.available();
//   if (peripheral && peripheral.localName() == "MYOWARE1") {
//     BLE.stopScan();
//     if (peripheral.connect()) {
//       peripheral.discoverAttributes();
//       BLECharacteristic dataChar = peripheral.characteristic("19b10001-e8f2-537e-4f6c-d104768a1214");
//       dataChar.subscribe();

//       while (true) {
//         if (Serial.available() > 0 && Serial.read() == 'S') {
//           runThreeSensorCycle(dataChar);
//           break; 
//         }
//       }
//     }
//     BLE.scanForUuid("19b10000-e8f2-537e-4f6c-d104768a1214");
//   }
// }

// void runThreeSensorCycle(BLECharacteristic& dataChar) {
//   int bleVal = 0;
//   for (int i = 1; i <= TOTAL_UTTERANCES; i++) {
//     delay(3000); 
//     Serial.println("START_REC");
    
//     unsigned long startTime = millis();
//     while (millis() - startTime < UTTERANCE_MS) {
//       unsigned long loopStart = millis();
      
//       if (dataChar.valueUpdated()) {
//         byte b;
//         dataChar.readValue(b);
//         bleVal = b;
//       }

//       int w1 = analogRead(WIRE_1);
//       int w2 = analogRead(WIRE_2);

//       Serial.print(w1); Serial.print(",");
//       Serial.print(w2); Serial.print(",");
//       Serial.println(bleVal);

//       while (millis() - loopStart < INTERVAL_MS);
//     }
//     Serial.println("STOP_REC");
//   }
//   Serial.println("FINISHED_ALL");
// }