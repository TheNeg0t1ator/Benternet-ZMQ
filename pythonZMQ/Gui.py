import customtkinter as ctk
import zmqServiceClass as zsc
import threading

class NumberData:
    prompt:str
    numberType:str
    def __init__(self, prompt:str = "", numberType:str = ""	):
        self.prompt = prompt
        self.numberType = numberType
    def __str__(self):
        return f'{{"RequestType": "Number", "NumberType": "{self.numberType}", "CheckNumber": "false", "Prompt": "{self.prompt}"}}'

messenger = zsc.ZMQ_service("tcp://benternet.pxl-ea-ict.be:24041", "tcp://benternet.pxl-ea-ict.be:24042")
messenger.subscribe("kobe!>")
def receive_response():
    while True:
        response = messenger.receive_message(timeout=1000)
        if response is not None:
            box.configure(state="normal")
            box.delete("1.0", "end")
            box.insert("end", response)
            box.configure(state="disabled")

response_thread = threading.Thread(target=receive_response)
response_thread.daemon = True
response_thread.start()
        
        
        
ctk.set_appearance_mode("dark")
ctk.set_default_color_theme("dark-blue")

root = ctk.CTk()
# root.geometry("800x400")
root.title("Hi bart :)")
root.resizable(False, False)

data:NumberData = NumberData()




def send_prompt():
    data.prompt = entry.get()
    data.numberType = dropdown.get()
    print(data)
    messenger.send_message("kobe?"+str(data))
   

frame = ctk.CTkFrame(master=root)
frame.pack(pady=10, padx=10, fill="both", expand=True)

label = ctk.CTkLabel(master=frame, text="Send Prompt", font=("Arial", 20))
label.pack(pady=10, padx=10)

def validate_input(char):
    if entry.get() == "Enter a number":
        entry.delete(0, "end")
    if char.isdigit() or char == '\b' or char == '\x7f':
        return True
    return False


options = ["Prime", "Fibonacci"]
dropdown = ctk.CTkComboBox(master=frame, values=options, state="readonly", width=300)
dropdown.pack(pady=10, padx=10)

entry = ctk.CTkEntry(master=frame, placeholder_text="Enter a number", width=300, validate="key")
entry.pack(pady=10, padx=10)



entry.configure(validatecommand=(entry.register(validate_input), '%S'))
entry.pack(pady=10, padx=10)

button = ctk.CTkButton(master=frame, text="Send prompt", command=send_prompt, width=300)
button.pack(pady=10, padx=10)

box = ctk.CTkTextbox(master=frame, width=300, height=150, state="disabled")
box.pack(pady=10, padx=10)

root.mainloop()



