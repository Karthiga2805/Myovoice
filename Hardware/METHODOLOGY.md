# MyoVoice — Methodology Summary

Two parallel pipelines were developed and evaluated.

---

## Pipeline 1: Hardware (ESP32) — `01_hardware_esp32_pipeline.ipynb`

**Goal:** Real-time word classification from a custom wearable device.

### Data
- Recorded directly from an **ESP32 microcontroller** with 2-channel surface EMG sensors
- One CSV file per word, columns: `timestamp_ms`, `wire1_pin34`, `wire2_pin32`
- 11 target words: START, STOP, TROUBLE, HELP, FALL, UP, ON, NO, DOWN, OFF, YES
- ~18,648 windowed samples total

### Preprocessing
1. Load raw ADC values from CSV
2. **Mean-center** each channel: `signal -= mean(signal)`
3. **Max-normalize**: `signal /= max(|signal|)`
4. **Silence gating**: reject windows where `sum(|signal|) < 1.0`

### Feature Extraction — TD6 (Time-Domain, 6 features)
Applied per 25-sample sliding window (step = 5):

| Feature | Formula | Meaning |
|---|---|---|
| RMS | √(mean(x²)) | Signal power |
| Waveform Length | Σ\|x[i+1] - x[i]\| | Signal complexity |
| Slope Sign Changes | count(sign changes in diff) | Oscillation roughness |
| Max | max(x) | Peak amplitude |
| Min | min(x) | Trough amplitude |
| StdDev | std(x) | Amplitude spread |

Both channels processed → concatenated → **12-dim feature vector per window**

### Model
- **Gradient Boosting Classifier** (scikit-learn)
  - n_estimators = 300
  - learning_rate = 0.1
  - max_depth = 5
- 80/20 train-test split (stratified)

### Results
| Metric | Value |
|---|---|
| **Test Accuracy** | **88.87%** |
| All 11 words | ✅ PASS (96–99% confidence per word in sliding-window voting) |

---

## Pipeline 2: Corpus (EMG-UKA) — `02_corpus_emguka_pipeline.ipynb`

**Goal:** Phoneme-level recognition from a research corpus, with speaker adaptation for laryngectomy patients.

### Data
- **EMG-UKA Trial Corpus** (public): 6-channel sEMG @ 600 Hz
- Audible speech mode (used for training/evaluation)
- Binary `.adc` files (16-bit signed integers, 7 columns: 6 EMG + 1 sync)
- Frame-aligned phoneme labels from `Alignments/` directory

### Preprocessing
1. **Load raw signal**: reshape to (N, 7), keep first 6 channels
2. **Trim** to speech segment using `offset/` files
3. **Highpass filter** (1 Hz, 4th-order Butterworth) — removes baseline drift
4. **Frame** the signal: 20 ms windows, 10 ms hop

### Feature Extraction — TD5 (3 × 6 channels = 18 features/frame)
Per 20 ms frame across all 6 EMG channels:

| Feature | Formula |
|---|---|
| MAV | mean(\|x\|) per channel |
| Power | mean(x²) per channel |
| ZCR | sign-change count / (2×win) per channel |

### Context Stacking
- Each frame stacks its ±15 neighbors: **18 × 31 = 558 dims**
- Edge padding for boundary frames

### Dimensionality Reduction
- **StandardScaler** (fit on training set)
- **Linear Discriminant Analysis (LDA)** → 32 components
- Maximizes between-class separation for phoneme classes

### Model — GMMHMM
- **Gaussian Mixture Hidden Markov Model** (hmmlearn)
  - n_components = number of phonemes (~40+)
  - n_mix = 2 (Gaussian mixtures per state)
  - covariance_type = 'diag'
  - n_iter = 10 (training), 5 (adaptation)
- **Teacher–Student Adaptation**: 20% of test session used as calibration data, HMM adapted to specific speaker

### Evaluation
- **Phoneme Error Rate (PER)** = Levenshtein distance(pred, true) / len(true)
- Consecutive duplicate states collapsed before scoring (CTC-style)

---

## Key Design Decisions

| Decision | Rationale |
|---|---|
| Single-channel focus (TD5) | Reduces overfitting for sparse corpus |
| LDA over PCA | Supervised; maximizes class separability |
| Context stacking | Captures temporal dynamics around each frame |
| GMMHMM over deep model | More stable with limited labeled data |
| Teacher–Student adaptation | Mimics clinical setup: train on healthy speakers, adapt to patient |
| Gradient Boosting for hardware | Fast inference, robust to small per-class N |
| Silence gating | Removes flat/noise windows without a separate VAD model |
