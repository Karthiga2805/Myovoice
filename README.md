# MYOVOICE

> A wearable, low-power device that restores speech for laryngectomy patients by detecting silent articulation via surface electromyography (sEMG) sensors, classifying intended words/phrases using machine learning, and synthesizing natural voice output.

---

## Overview

Laryngectomy patients lose the ability to produce natural speech. **MyoVoice** aims to give them their voice back — without requiring surgery or implants. By placing sEMG sensors on the neck and jaw, the system captures the faint electrical signals produced during silent articulation, classifies the intended word using a trained ML model, and outputs synthesized speech in real time.

This repository covers the full stack: sensor hardware, firmware, data preprocessing, model training, and evaluation.

---

## Key Features

-  **Hardware** — ESP-32 based wearable with multi-channel sEMG sensor array
-  **Signal Processing** — Noise filtering, feature extraction from raw EMG signals
-  **ML Classification** — Random Forest and deep learning models trained on the EMG-UKA corpus
-  **Voice Synthesis** — Maps classified words to synthesized speech output
-  **Low Power** — Designed for real-world wearable constraints

---

## Repository Structure

```
MyoVoice/
├── hardware/
│   ├── esp32_firmware/          # Arduino/C++ firmware for the ESP-32 microcontroller
│   └── sensor_coordination/     # Sensor placement, calibration, and sync logic
│
├── notebooks/
│   ├── 01_emg_uka_trial.ipynb   # Initial exploration of the EMG-UKA corpus
│   ├── 02_random_forest.ipynb   # Baseline Random Forest classifier
│   ├── 03_myovoice_v2.ipynb     # Improved pipeline (v2)
│   ├── 04_myovoice_scratch.ipynb# Architecture experiments from scratch
│   ├── 05_try_elec.ipynb        # Electrode configuration experiments
│   └── 06_try_emg.ipynb         # Raw EMG signal analysis
│
├── docs/
│   ├── research_paper/          # Academic paper and references
│   ├── project_management.docx  # Project timeline and task breakdown
│   └── kaggle_notes.docx        # Notes from Kaggle dataset experiments
│
├── data/
│   └── README.md                # Instructions for obtaining the EMG-UKA corpus
│
├── models/                      # Saved model weights (see .gitignore for large files)
├── .gitignore
├── requirements.txt
└── README.md
```

---

## Getting Started

### Prerequisites

- Python 3.9+
- Arduino IDE (for ESP-32 firmware)
- The EMG-UKA corpus (see `data/README.md` for access instructions)

### Installation

```bash
git clone https://github.com/YOUR_USERNAME/MyoVoice.git
cd MyoVoice
pip install -r requirements.txt
```

### Running the notebooks

```bash
jupyter notebook notebooks/
```

Start with `01_emg_uka_trial.ipynb` for data exploration, then follow the numbered sequence to trace the full model development journey.

---

## Dataset

This project uses the **EMG-UKA Trial Corpus** — a publicly available dataset of surface EMG signals recorded during audible and silent speech.

> Janke, M., & Diener, L. (2017). EMG-to-Speech: Direct Generation of Speech From Facial Electromyographic Signals. *IEEE/ACM Transactions on Audio, Speech, and Language Processing.*

See `data/README.md` for download and setup instructions. Raw data files are excluded from this repository.

---

## Results

| Model | Accuracy | Notes |
|---|---|---|
| Random Forest (baseline) | ~XX% | EMG-UKA corpus, N-word vocab |
| MyoVoice v2 | ~XX% | Improved feature engineering |

*Fill in your actual numbers here — even preliminary results are worth including.*

---

## Hardware Setup

The wearable prototype uses an **ESP-32** microcontroller paired with surface EMG electrodes placed on the face and neck. Signal acquisition runs at [X] Hz with [N] channels.

See the `hardware/` directory for:
- Wiring diagrams and PCB layout
- Electrode placement guide
- Firmware flashing instructions

---

## Roadmap

- [x] EMG signal acquisition and preprocessing pipeline
- [x] Baseline Random Forest classifier
- [x] Improved feature engineering (v2)
- [x] Real-time inference on ESP-32
- [ ] Expand vocabulary beyond N words
- [ ] Text-to-speech voice synthesis integration
- [ ] User study with laryngectomy patients

---

## Team

This project was developed as part of the **Electronics Club 2025–26** .

| Name | Role |
|---|---|
| [Akshaiya, Karthiga] | Project Leads |
| [Sagar, Dinesh] | ML & Signal Processing |
| [Sabarish, Karnika] | Hardware & Firmware |


---

## Acknowledgements

- EMG-UKA corpus authors for the open dataset
