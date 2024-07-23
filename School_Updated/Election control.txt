import tkinter as tk
import serial
import time
import serial.tools.list_ports
import threading

name_status = False

# Set up serial communication with Arduino
ports = list(serial.tools.list_ports.comports())
for port in ports:
    if 'Arduino' in port.description:
        arduino = serial.Serial(port.device, 9600)
        print(f'Connected to Arduino on port {port.device}')
        break

time.sleep(2)  # Wait for the connection to establish

# Function to send data to Arduino
def send_to_arduino():
    names = {
        "boy_captain1": entries_boy_captain[0].get(),
        "boy_captain2": entries_boy_captain[1].get(),
        "boy_captain3": entries_boy_captain[2].get(),
        "girl_captain1": entries_girl_captain[0].get(),
        "girl_captain2": entries_girl_captain[1].get(),
        "girl_captain3": entries_girl_captain[2].get(),
        "boy_vicecaptain1": entries_boy_vicecaptain[0].get(),
        "boy_vicecaptain2": entries_boy_vicecaptain[1].get(),
        "boy_vicecaptain3": entries_boy_vicecaptain[2].get(),
        "girl_vicecaptain1": entries_girl_vicecaptain[0].get(),
        "girl_vicecaptain2": entries_girl_vicecaptain[1].get(),
        "girl_vicecaptain3": entries_girl_vicecaptain[2].get()
    }

    for key, value in names.items():
        arduino.write((key + ':' + value + '\n').encode())
        time.sleep(0.1)
    
    print(f'Sent to Arduino: {names}')

def flaging():
    send_to_arduino()
    global name_status
    name_status = True
    send_button.pack_forget() # Hide the button when names are sent
    root.destroy()

# Set up the GUI
root = tk.Tk()
root.title("Arduino Name Sender")
root.geometry("1500x1000")
root.configure(bg="#2c3e50")

# Function to create label and entry pairs
def create_entry_label_pair(frame, label_text):
    label = tk.Label(frame, text=label_text, font=("Helvetica", 14), bg="#34495e", fg="#ecf0f1", width=15, anchor=tk.W)
    label.pack(pady=50, padx=60 ,side=tk.LEFT)
    entry = tk.Entry(frame, font=("Helvetica", 12), width=20)
    entry.pack(pady=5, padx=0, side=tk.LEFT)
    return entry

# Frame for Boy's Captain
frame_boy_captain = tk.Frame(root, bg="#34495e", bd=2, relief=tk.GROOVE)
frame_boy_captain.pack(pady=10, padx=20, fill=tk.BOTH)

tk.Label(frame_boy_captain, text="Boy's Captain", font=("Helvetica", 16, "bold"), bg="#34495e", fg="#ecf0f1").pack(pady=5)

entries_boy_captain = []
for i in range(3):
    entry = create_entry_label_pair(frame_boy_captain, f"Candidate {i+1}:")
    entries_boy_captain.append(entry)

# Frame for Girl's Captain
frame_girl_captain = tk.Frame(root, bg="#34495e", bd=2, relief=tk.GROOVE)
frame_girl_captain.pack(pady=10, padx=20, fill=tk.BOTH)

tk.Label(frame_girl_captain, text="Girl's Captain", font=("Helvetica", 16, "bold"), bg="#34495e", fg="#ecf0f1").pack(pady=5)

entries_girl_captain = []
for i in range(3):
    entry = create_entry_label_pair(frame_girl_captain, f"Candidate {i+1}:")
    entries_girl_captain.append(entry)

# Frame for Boy's Vice Captain
frame_boy_vicecaptain = tk.Frame(root, bg="#34495e", bd=2, relief=tk.GROOVE)
frame_boy_vicecaptain.pack(pady=10, padx=20, fill=tk.BOTH)

tk.Label(frame_boy_vicecaptain, text="Boy's Vice Captain", font=("Helvetica", 16, "bold"), bg="#34495e", fg="#ecf0f1").pack(pady=5)

entries_boy_vicecaptain = []
for i in range(3):
    entry = create_entry_label_pair(frame_boy_vicecaptain, f"Candidate {i+1}:")
    entries_boy_vicecaptain.append(entry)

# Frame for Girl's Vice Captain
frame_girl_vicecaptain = tk.Frame(root, bg="#34495e", bd=2, relief=tk.GROOVE)
frame_girl_vicecaptain.pack(pady=10, padx=20, fill=tk.BOTH)

tk.Label(frame_girl_vicecaptain, text="Girl's Vice Captain", font=("Helvetica", 16, "bold"), bg="#34495e", fg="#ecf0f1").pack(pady=5)

entries_girl_vicecaptain = []
for i in range(3):
    entry = create_entry_label_pair(frame_girl_vicecaptain, f"Candidate {i+1}:")
    entries_girl_vicecaptain.append(entry)

# Button to send names to Arduino
send_button = tk.Button(root, text="Send to Arduino", command=flaging, font=("Helvetica", 14), bg="#27ae60", fg="#ecf0f1")
send_button.pack(pady=20)

root.mainloop()

# -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

# Initialize variables a to l
a = b = c = d = e = f = g = h = i = j = k = l = "0"

# Function to read serial data and update variables
def read_serial_and_update():
    global a, b, c, d, e, f, g, h, i, j, k, l
    while True:
        # Initialize a list to store the values
        values = []
        while arduino.in_waiting > 0:
            line = arduino.readline().decode('utf-8').rstrip()
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

# Set up the GUI
new_root = tk.Tk()
new_root.title("Arduino Values Display")

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


# Start the serial reading in a separate thread
start_serial_reading()

# Run the GUI main loop
new_root.mainloop()

# Close the serial connection when the program ends creat text file

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

arduino.close()
print(name_status)

