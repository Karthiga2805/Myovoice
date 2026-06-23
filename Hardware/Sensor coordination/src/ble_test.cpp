// #include <BLEDevice.h>
// #include <BLEServer.h>
// #include <BLEUtils.h>
// #include <BLE2902.h>
// #include <Arduino.h>

// #define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
// #define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

// BLEServer* pServer = NULL;
// BLECharacteristic* pCharacteristic = NULL;
// bool deviceConnected = false;
// bool oldDeviceConnected = false;

// // --- YOUR CUSTOM DATA ---
// // We store these as an array of strings
// const char* validHexCodes[] = {
//   "01" // Social
// };

// // , "02", "03", "04", "05", // Emergency
// //   "06", "07", "08", "09", "0A", "0B", "0C", "0D", "0E", "0F", // Needs
// //   "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", // Medical
// //   "1A", "1B", "1C", "1D", "1E", "1F", "20", "21", "22", "23", // Control
// //   "24", "25", "26", "27", "28", "29", "2A", "2B", "2C", "2D", "2E", "2F", "30", "31", "32"

// // Calculate how many codes are in the list automatically
// const int numCodes = sizeof(validHexCodes) / sizeof(validHexCodes[0]);

// class MyServerCallbacks: public BLEServerCallbacks {
//     void onConnect(BLEServer* pServer) {
//       deviceConnected = true;
//     };

//     void onDisconnect(BLEServer* pServer) {
//       deviceConnected = false;
//     }
// };

// void setup() {
//   Serial.begin(115200);
//   Serial.println("Starting BLE Work!");

//   BLEDevice::init("ESP32_Command_Center");
//   pServer = BLEDevice::createServer();
//   pServer->setCallbacks(new MyServerCallbacks());

//   BLEService *pService = pServer->createService(SERVICE_UUID);

//   pCharacteristic = pService->createCharacteristic(
//                       CHARACTERISTIC_UUID,
//                       BLECharacteristic::PROPERTY_READ   |
//                       BLECharacteristic::PROPERTY_WRITE  |
//                       BLECharacteristic::PROPERTY_NOTIFY |
//                       BLECharacteristic::PROPERTY_INDICATE
//                     );

//   pCharacteristic->addDescriptor(new BLE2902());

//   pService->start();

//   BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
//   pAdvertising->addServiceUUID(SERVICE_UUID);
//   pAdvertising->setScanResponse(true);
//   pAdvertising->setMinPreferred(06); 
//   pAdvertising->setMinPreferred(12);
//   BLEDevice::startAdvertising();
//   Serial.println("Waiting for a client connection...");
// }

// void loop() {
//     if (deviceConnected) {
//         // 1. Pick a random index from 0 to (numCodes - 1)
//         int randomIndex = random(0, numCodes); 
        
//         // 2. Get the specific hex string at that index
//         const char* codeToSend = validHexCodes[randomIndex];

//         // 3. Send it
//         pCharacteristic->setValue(codeToSend);
//         pCharacteristic->notify();
        
//         Serial.print("Sent Command: ");
//         Serial.println(codeToSend);

//         delay(2000); 
//     }

//     // Disconnect/Reconnect handling
//     if (!deviceConnected && oldDeviceConnected) {
//         delay(500); 
//         pServer->startAdvertising(); 
//         Serial.println("Device disconnected. Restarting advertising...");
//         oldDeviceConnected = deviceConnected;
//     }
    
//     if (deviceConnected && !oldDeviceConnected) {
//         oldDeviceConnected = deviceConnected;
//     }
// }