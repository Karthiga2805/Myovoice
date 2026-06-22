/* ==========================================================================
   ESP32 DEBUG MODE - SINGLE SENSOR TEST
   ========================================================================== */

// ⚠️ REPLACE THIS with your actual library name
#include <sagar1609-project-1_inferencing.h> 

const int PIN_SENSOR_1 = 34; 
const unsigned long TIME_BETWEEN_SAMPLES_US = 1666; 
float features[EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE]; 

void setup() {
    Serial.begin(115200);
    while (!Serial);
    
    // CHECKPOINT 1
    Serial.println("------------------------------------");
    Serial.println("1. SYSTEM STARTUP: COMPLETE");
    Serial.print("2. Memory Allocated for Window Size: ");
    Serial.println(EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE);
    Serial.println("------------------------------------");
}

void loop() {
    // CHECKPOINT 3: Start Loop
    // Serial.println("3. Loop Started. Listening for data..."); 

    for (size_t ix = 0; ix < EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE; ix += 2) {
        unsigned long start_time = micros();

        // READ
        int raw_val = analogRead(PIN_SENSOR_1);

        // DUPLICATE
        features[ix + 0] = (float)raw_val; 
        features[ix + 1] = (float)raw_val; 

        // TIMING
        while (micros() - start_time < TIME_BETWEEN_SAMPLES_US);
    }
    
    // CHECKPOINT 4: Buffer Full
    // Serial.println("4. Buffer Full. Creating Signal...");

    ei_impulse_result_t result = { 0 };
    signal_t signal;
    int err = numpy::signal_from_buffer(features, EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE, &signal);
    
    if (err != 0) {
        Serial.print("❌ ERROR: Signal creation failed code: ");
        Serial.println(err);
        return;
    }

    // CHECKPOINT 5: Running AI
    // Serial.println("5. Running Classifier (MFCC + TFLite)...");

    err = run_classifier(&signal, &result, false); // false = hide internal debug
    
    if (err != EI_IMPULSE_OK) {
        Serial.print("❌ ERROR: Classifier failed code: ");
        Serial.println(err);
        return;
    }

    // CHECKPOINT 6: Success - Printing Top Result
    // Serial.println("6. Inference Done. Checking Results...");

    int best_idx = -1;
    float best_score = -1.0;
    
    for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
        if (result.classification[ix].value > best_score) {
            best_score = result.classification[ix].value;
            best_idx = ix;
        }
    }
    
    String label = result.classification[best_idx].label;
    
    // Only print if confident
    if (best_score > 0.50) {
        Serial.print("🟢 DETECTED: ");
        Serial.print(label);
        Serial.print(" (");
        Serial.print(best_score * 100);
        Serial.println("%)");
    } else {
        // Optional: Print faint detection to prove it's running
        // Serial.println("... (No strong detection) ...");
    }
}