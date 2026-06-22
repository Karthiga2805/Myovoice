/* ==========================================================================
   ESP32 SILENT SPEECH - WORD DECODER
   (Translates Phonetic Sequences into English Words)
   ========================================================================== */

// ⚠️ YOUR LIBRARY NAME HERE
#include <sagar1609-project-1_inferencing.h> 

// ---------------- HARDWARE SETTINGS ----------------
const int PIN_SENSOR_1 = 34; 
//const int PIN_SENSOR_2 = 35; 
const unsigned long TIME_BETWEEN_SAMPLES_US = 1666; 

float features[EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE]; 

// ---------------- DICTIONARY SETTINGS ----------------
// We store the last few detected classes to find patterns
String history[5]; // Remember last 5 sounds
int historyIndex = 0;
unsigned long lastPrintTime = 0;

void setup() {
    Serial.begin(115200);
    // while (!Serial); // Commented out to prevent hanging
    Serial.println("ESP32 Word Decoder: ONLINE");
}

void loop() {
    // 1. GATHER DATA
    for (size_t ix = 0; ix < EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE; ix += 2) {
        unsigned long start_time = micros();
        int raw1 = analogRead(PIN_SENSOR_1);
        int raw2 = analogRead(PIN_SENSOR_1); // Duplicate raw1 if single sensor
        
        // Single Sensor Mode Fix (Duplicate signal if sensor 2 is missing)
        // features[ix + 0] = (float)raw1;
        // features[ix + 1] = (float)raw1; 
        
        // Dual Sensor Mode (Normal)
        features[ix + 0] = (float)raw1;
        features[ix + 1] = (float)raw2;

        while (micros() - start_time < TIME_BETWEEN_SAMPLES_US);
    }

    // 2. RUN INFERENCE
    ei_impulse_result_t result = { 0 };
    signal_t signal;
    numpy::signal_from_buffer(features, EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE, &signal);
    run_classifier(&signal, &result, false);

    // 3. GET BEST PREDICTION
    int best_idx = -1;
    float best_score = -1.0;
    for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
        if (result.classification[ix].value > best_score) {
            best_score = result.classification[ix].value;
            best_idx = ix;
        }
    }
    
    String currentPhoneme = result.classification[best_idx].label;

    // 4. SMART DECODER LOGIC
    // Only process if confidence is high (> 60%) and not Silent
    if (best_score > 0.60 && currentPhoneme != "SIL" && currentPhoneme != "4") {
        
        // Add to history buffer (Debounce: only if different from last one)
        // This prevents "VOWEL VOWEL VOWEL" from filling the buffer instantly
        if (history[historyIndex] != currentPhoneme) {
            historyIndex = (historyIndex + 1) % 5; // Circular buffer
            history[historyIndex] = currentPhoneme;
            
            // Debug: Show raw stream
            Serial.print("Stream: "); Serial.println(currentPhoneme);
            
            checkDictionary();
        }
    }
    
    delay(50); // Small delay to pace detections
}

// ---------------- THE MINI-DICTIONARY ----------------
void checkDictionary() {
    // We look at the sequence in our 'history' array to find words.
    // Example: NASAL -> VOWEL -> NASAL = "MOM"
    
    // Construct a signature from the last 3 items
    // (Note: This is a simple logic for demonstration)
    
    String last3 = getSeq(2) + " " + getSeq(1) + " " + getSeq(0);
    String last2 = getSeq(1) + " " + getSeq(0);

    // --- WORD DEFINITIONS ---
    
    // "MOM" or "MAMA" (Nasal - Vowel - Nasal)
    if (last3 == "NASAL VOWEL NASAL") {
        printWord("MOM");
    }
    
    // "YES" (Approx/Fric - Vowel - Fric)
    // Note: 'Y' is an Approximant, 'S' is a Fricative
    else if (last3 == "APPROX VOWEL FRIC") {
        printWord("YES");
    }
    
    // "NO" (Nasal - Vowel)
    else if (last2 == "NASAL VOWEL") {
        printWord("NO");
    }
    
    // "POP" or "BAT" (Stop - Vowel - Stop)
    else if (last3 == "STOP VOWEL STOP") {
        printWord("POP / STOP");
    }
    
    // "HELLO" (Fricative/H - Vowel - Approx/L - Vowel)
    // Simplified to: FRIC VOWEL APPROX
    else if (last3 == "FRIC VOWEL APPROX") {
        printWord("HELLO");
    }
}

// Helper to get history safely
String getSeq(int lookback) {
    int idx = historyIndex - lookback;
    if (idx < 0) idx += 5;
    return history[idx];
}

void printWord(String word) {
    // Don't print the same word twice in 1 second
    if (millis() - lastPrintTime > 1000) {
        Serial.println("\n========================");
        Serial.print("📢 WORD DETECTED: ");
        Serial.println(word);
        Serial.println("========================\n");
        lastPrintTime = millis();
        
        // Clear history so we don't re-trigger
        for(int i=0; i<5; i++) history[i] = "";
    }
}