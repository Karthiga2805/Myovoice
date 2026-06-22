# import serial
# import time
# import os
# import sys

# PORT = 'COM5' # <--- Set your port
# BAUD = 115200

# try:
#     ser = serial.Serial(PORT, BAUD, timeout=1)
#     time.sleep(2)
#     ser.reset_input_buffer()
#     print(f"System Ready on {PORT}")
# except Exception as e:
#     print(f"Error: {e}")
#     sys.exit()

# def get_baseline():
#     print("Calculating baseline... stay still.")
#     ser.write(b'S') # Trigger a test run (we won't save this)
#     vals_w1 = []
#     vals_w2 = []
    
#     # Read for about 1 second to check noise
#     start = time.time()
#     while time.time() - start < 1.0:
#         line = ser.readline().decode('utf-8', errors='ignore').strip()
#         if "," in line:
#             parts = line.split(",")
#             if len(parts) == 3:
#                 vals_w1.append(int(parts[1]))
#                 vals_w2.append(int(parts[2]))
    
#     avg1 = sum(vals_w1)/len(vals_w1) if vals_w1 else 0
#     avg2 = sum(vals_w2)/len(vals_w2) if vals_w2 else 0
#     print(f"Baseline Noise -> Pin 34: {avg1:.1f} | Pin 32: {avg2:.1f}")
#     if avg1 > 3500 or avg2 > 3500:
#         print("!! WARNING: Clipping detected. Check gain/ground !!")

# def record_word():
#     word_name = input("\nEnter word (50x): ").strip().upper()
#     if not word_name: return

#     os.makedirs('myovoice_data', exist_ok=True)
#     file_path = f"myovoice_data/{word_name}.csv"

#     print(f"Ready for '{word_name}'. Press ENTER to start...")
#     input()
    
#     # Optional: run get_baseline() here if you want it every time
    
#     ser.write(b'S') 
#     count = 0
    
#     with open(file_path, "w") as f:
#         f.write("timestamp_ms,wire1_pin34,wire2_pin32\n")
        
#         while count < 50:
#             line = ser.readline().decode('utf-8', errors='ignore').strip()

#             if line == "START_REC":
#                 count += 1
#                 sys.stdout.write(f"\r[{count}/50] SPEAK! ")
#                 sys.stdout.flush()
            
#             elif line == "STOP_REC":
#                 sys.stdout.write(" DONE | Resting... ")
#                 sys.stdout.flush()
            
#             elif line == "FINISHED_ALL":
#                 print(f"\n\nSUCCESS: 50 utterances saved to {file_path}")
#                 break
                
#             elif "," in line:
#                 f.write(line + "\n")
#                 # Live display of raw values
#                 sys.stdout.write(f"\r[{count}/50] DATA: {line.ljust(20)}")
#                 sys.stdout.flush()

# if __name__ == "__main__":
#     while True:
#         record_word()
#         if input("\nNext word? (y/n): ").lower() != 'y':
#             break