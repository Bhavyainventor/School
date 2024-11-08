import tkinter as tk
import serial
import serial.tools.list_ports
import threading
import time

# Set up the serial connection (update 'COM12' to your Arduino port)
ports = list(serial.tools.list_ports.comports())
for port in ports:
    if 'Arduino' in port.description:
        ser = serial.Serial(port.device, 9600)
        print(f'Connected to Arduino on port {port.device}')
        break
# Initialize variables a to l
a = b = c = d = e = f = g = h = i = j = k = l = "0"

# Function to read serial data and update variables
def read_serial_and_update():
    global a, b, c, d, e, f, g, h, i, j, k, l
    while True:
        # Initialize a list to store the values
        values = []
        while ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').rstrip()
            print("Received line:", line)  # Debugging statement
            # Split the received line into individual values
            values.extend(line.split())

        # Check if we have enough values (12 expected values)
        if len(values) >= 12:
            # Assign values to variables a to l
            a, b, c, d, e, f, g, h, i, j, k, l = values[:12]
            #print(f"Updated values:\na: {a}, b: {b}, c: {c}, d: {d}, e: {e}, f: {f}, g: {g}, h: {h}, i: {i}, j: {j}, k: {k}, l: {l}")
            update_gui()  # Call the function to update the GUI
        
        time.sleep(3)  # Wait for 3 seconds before the next read

# Function to update the GUI with the current values of a to l
def update_gui():
    label_a.config(text=f"Candidate 1: {a}")
    label_b.config(text=f"Candidate 2: {b}")
    label_c.config(text=f"Candidate 3: {c}")
    label_d.config(text=f"Candidate 1: {d}")
    label_e.config(text=f"Candidate 2: {e}")
    label_f.config(text=f"Candidate 3: {f}")
    label_g.config(text=f"Candidate 1: {g}")
    label_h.config(text=f"Candidate 2: {h}")
    label_i.config(text=f"Candidate 3: {i}")
    label_j.config(text=f"Candidate 1: {j}")
    label_k.config(text=f"Candidate 2: {k}")
    label_l.config(text=f"Candidate 3: {l}")

# Function to run the serial reading in a separate thread
def start_serial_reading():
    threading.Thread(target=read_serial_and_update, daemon=True).start()

def save_results():
    with open("results.txt", "w") as file:
        file.write("Boy's Captain:\n")
        file.write(f"Candidate 1: {a}\n")
        file.write(f"Candidate 2: {b}\n")
        file.write(f"Candidate 3: {c}\n")
        file.write("\nGirl's Captain:\n")
        file.write(f"Candidate 1: {d}\n")
        file.write(f"Candidate 2: {e}\n")
        file.write(f"Candidate 3: {f}\n")
        file.write("\nBoy's Vice Captain:\n")
        file.write(f"Candidate 1: {g}\n")
        file.write(f"Candidate 2: {h}\n")
        file.write(f"Candidate 3: {i}\n")
        file.write("\nGirl's Vice Captain:\n")
        file.write(f"Candidate 1: {j}\n")
        file.write(f"Candidate 2: {k}\n")
        file.write(f"Candidate 3: {l}\n")

def on_closing(root):
    global ser
    save_results()
    root.destroy()

# Set up the GUI
new_root = tk.Tk()
new_root.title("Election Control")

# Create frames for each post
frame_boys_captain = tk.Frame(new_root, bd=2, relief=tk.SUNKEN)
frame_girls_captain = tk.Frame(new_root, bd=2, relief=tk.SUNKEN)
frame_boys_vice_captain = tk.Frame(new_root, bd=2, relief=tk.SUNKEN)
frame_girls_vice_captain = tk.Frame(new_root, bd=2, relief=tk.SUNKEN)

# Add headers for each post
tk.Label(frame_boys_captain, text="Boy's Captain", font=("Ink Free", 40, "bold")).pack(pady=5)
tk.Label(frame_girls_captain, text="Girl's Captain", font=("Ink Free", 40, "bold")).pack(pady=5)
tk.Label(frame_boys_vice_captain, text="Boy's Vice Captain", font=("Ink Free", 40, "bold")).pack(pady=5)
tk.Label(frame_girls_vice_captain, text="Girl's Vice Captain", font=("Ink Free", 40, "bold")).pack(pady=5)

# Labels to display the values
label_a = tk.Label(frame_boys_captain, text="Candidate 1: 0", font=("Time New Roman", 25))
label_b = tk.Label(frame_boys_captain, text="Candidate 2: 0", font=("Time New Roman", 25))
label_c = tk.Label(frame_boys_captain, text="Candidate 3: 0", font=("Time New Roman", 25))

label_d = tk.Label(frame_girls_captain, text="Candidate 1: 0", font=("Time New Roman", 25))
label_e = tk.Label(frame_girls_captain, text="Candidate 2: 0", font=("Time New Roman", 25))
label_f = tk.Label(frame_girls_captain, text="Candidate 3: 0", font=("Time New Roman", 25))

label_g = tk.Label(frame_boys_vice_captain, text="Candidate 1: 0", font=("Time New Roman", 25))
label_h = tk.Label(frame_boys_vice_captain, text="Candidate 2: 0", font=("Time New Roman", 25))
label_i = tk.Label(frame_boys_vice_captain, text="Candidate 3: 0", font=("Time New Roman", 25))

label_j = tk.Label(frame_girls_vice_captain, text="Candidate 1: 0", font=("Time New Roman", 25))
label_k = tk.Label(frame_girls_vice_captain, text="Candidate 2: 0", font=("Time New Roman", 25))
label_l = tk.Label(frame_girls_vice_captain, text="Candidate 3: 0", font=("Time New Roman", 25))

# Pack labels in frames
label_a.pack(pady=20)
label_b.pack(pady=20)
label_c.pack(pady=20)
label_d.pack(pady=20)
label_e.pack(pady=20)
label_f.pack(pady=20)
label_g.pack(pady=20)
label_h.pack(pady=20)
label_i.pack(pady=20)
label_j.pack(pady=20)
label_k.pack(pady=20)
label_l.pack(pady=20)

# Layout frames in the GUI
frame_boys_captain.grid(row=0, column=0, padx=20, pady=10, sticky=tk.NSEW)
frame_girls_captain.grid(row=0, column=1, padx=20, pady=10, sticky=tk.NSEW)
frame_boys_vice_captain.grid(row=1, column=0, padx=20, pady=10, sticky=tk.NSEW)
frame_girls_vice_captain.grid(row=1, column=1, padx=20, pady=10, sticky=tk.NSEW)
# Configure the columns and rows of new_root to expand equally
new_root.grid_rowconfigure(0, weight=1)
new_root.grid_rowconfigure(1, weight=1)
new_root.grid_columnconfigure(0, weight=1)
new_root.grid_columnconfigure(1, weight=1)


start_serial_reading()

# Run the GUI main loop
new_root.protocol("WM_DELETE_WINDOW", lambda: on_closing(new_root))
new_root.mainloop()

# Close the serial connection when the program ends

ser.close()
