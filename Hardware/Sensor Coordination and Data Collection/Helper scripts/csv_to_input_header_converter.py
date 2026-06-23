import csv

# Configuration
input_csv = 'NOW.csv'       # Ensure this matches your file name
output_header = 'test_data_now.h'

print(f"🔄 Reading {input_csv}...")

try:
    with open(input_csv, 'r') as f:
        reader = csv.DictReader(f)
        data = []
        for row in reader:
            # Extract data columns (ignoring timestamp to rely on ESP32 timing)
            s1 = int(row['wire1_pin34'])
            s2 = int(row['wire2_pin32'])
            data.append((s1, s2))

    print(f"✅ Found {len(data)} data points.")
    print(f"✍️  Writing to {output_header}...")

    with open(output_header, 'w') as f:
        f.write("#ifndef TEST_DATA_H\n")
        f.write("#define TEST_DATA_H\n\n")
        f.write("#include <Arduino.h>\n\n")
        f.write(f"// Data from {input_csv}\n")
        f.write(f"const int test_data_len = {len(data)};\n")
        f.write("const int16_t test_data[][2] = {\n")
        
        for s1, s2 in data:
            f.write(f"    {{ {s1}, {s2} }},\n")
            
        f.write("};\n\n")
        f.write("#endif // TEST_DATA_H\n")

    print("🎉 Done! Move 'test_data.h' to your project's 'src' or 'include' folder.")

except FileNotFoundError:
    print(f"❌ Error: Could not find {input_csv}. Make sure it is in the same folder as this script.")
except KeyError as e:
    print(f"❌ Error: Column not found {e}. Check your CSV headers.")