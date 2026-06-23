import serial
import time
import os
import sys

PORT = 'COM3' # <--- Change to your actual COM port
BAUD = 115200

try:
    # Adding a longer timeout and clearing buffer to prevent the Unicode error
    ser = serial.Serial(PORT, BAUD, timeout=1)
    time.sleep(2)
    ser.reset_input_buffer()
    print(f"Connected to {PORT} successfully.")
except Exception as e:
    print(f"Connection Error: {e}")
    sys.exit()

def record_word():
    word_name = input("\nEnter word (50x): ").strip().upper()
    if not word_name: return

    os.makedirs('myovoice_data', exist_ok=True)
    file_path = f"myovoice_data/{word_name}.csv"

    print(f"Ready. Press ENTER to start 50 utterances...")
    input()
    
    ser.write(b'S') 
    count = 0
    current_vals = "N/A"
    
    with open(file_path, "w") as f:
        # Header must have 3 columns to match the ESP32 output
        f.write("timestamp_ms,wire1_pin34,wire2_pin32\n")
        
        while count < 50:
            raw_line = ser.readline()
            try:
                # 'ignore' skips the 0xff junk bytes that cause crashes
                line = raw_line.decode('utf-8', errors='ignore').strip()
            except:
                continue

            if line == "START_REC":
                count += 1
                # Visual Feedback
                sys.stdout.write(f"\r[{count}/50] SPEAK! | ")
                sys.stdout.flush()
            
            elif line == "STOP_REC":
                sys.stdout.write(f" DONE | Resting... ")
                sys.stdout.flush()
            
            elif line == "FINISHED_ALL":
                print(f"\n\nSUCCESS: 50 utterances saved to {file_path}")
                break
                
            elif "," in line:
                # This stores the data to the file
                f.write(line + "\n")
                # This updates the terminal so you see the numbers live
                sys.stdout.write(f"\r[{count}/50] DATA: {line.ljust(20)}")
                sys.stdout.flush()

if __name__ == "__main__":
    while True:
        record_word()
        if input("\nRecord another word? (y/n): ").lower() != 'y':
            break