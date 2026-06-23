import pandas as pd

# 1. Read your file
filename = 'OPEN.csv'
df = pd.read_csv(filename)

s1 = df['wire1_pin34'].values
s2 = df['wire2_pin32'].values

# 2. Create a C++ header file
output_file = "test_data_open.h"

with open(output_file, "w") as f:
    f.write(f"#ifndef TEST_DATA_OPEN_H\n#define TEST_DATA_OPEN_H\n\n")
    f.write(f"const int TEST_DATA_LENGTH = {len(s1)};\n\n")
    
    # Write Sensor 1 array
    f.write(f"const int16_t full_s1[{len(s1)}] = {{\n    ")
    f.write(", ".join(map(str, s1)))
    f.write("\n};\n\n")
    
    # Write Sensor 2 array
    f.write(f"const int16_t full_s2[{len(s2)}] = {{\n    ")
    f.write(", ".join(map(str, s2)))
    f.write("\n};\n\n")
    
    f.write(f"#endif\n")

print(f"✅ Success! All {len(s1)} data points saved to {output_file}")