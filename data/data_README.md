# Data

Raw EMG data files are **not included** in this repository due to size and licensing constraints.

## EMG-UKA Trial Corpus

This project uses the **EMG-UKA Trial Corpus**, a publicly available dataset of surface electromyographic signals recorded during audible and silent speech.

**Citation:**
> Janke, M., & Diener, L. (2017). EMG-to-Speech: Direct Generation of Speech From Facial Electromyographic Signals. *IEEE/ACM Transactions on Audio, Speech, and Language Processing, 25*(12), 2375–2385.

**Download:**
The corpus is available from the original authors at:
https://www.informatik.uni-augsburg.de/en/chairs/hcm/resources/emg-uka/

**Setup:**
Once downloaded, place the data files in this `data/` directory. The notebooks expect the following structure:

```
data/
├── emg_uka/
│   ├── subject_01/
│   ├── subject_02/
│   └── ...
└── README.md   ← this file
```

## Kaggle Dataset

Additional experiments were run using a supplementary Kaggle dataset. See `docs/kaggle_notes.docx` for details and the source link.
