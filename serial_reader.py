import serial
import csv
import time

# Adjust port name based on your system
SERIAL_PORT = "/dev/cu.usbmodem1101"  # Change this for Windows (e.g., "COM3")
BAUD_RATE = 9600
OUTPUT_FILE = "PID_tuning_run1_new.csv"

ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
time.sleep(2)  # Allow time for connection

with open(OUTPUT_FILE, mode="w", newline="") as file:
    writer = csv.writer(file)
    
    # Read and write the CSV header from Arduino
    header = ser.readline().decode("utf-8").strip().split(",")
    writer.writerow(header)
    
    print("Logging data... Press CTRL+C to stop.")
    
    try:
        while True:
            line = ser.readline().decode("utf-8").strip()
            if line:
                print(line)
                writer.writerow(line.split(","))
    except KeyboardInterrupt:
        print("\nData logging stopped.")

ser.close()
