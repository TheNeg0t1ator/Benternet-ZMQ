import time
import json
from zmqServiceClass import ZMQ_service


print("starting")
messenger = ZMQ_service("tcp://benternet.pxl-ea-ict.be:24041", "tcp://benternet.pxl-ea-ict.be:24042")
print("messenger created")

messenger.subscribe("kobe!")  # Subscribe to all topics

with open("banana.json", "r") as file:
    messagetosend = file.read()

messagetosend = "kobe?" + messagetosend
print("receiving messages")

#while True:
print("Sending:", messagetosend)

messenger.send_message(messagetosend)
print("Message sent")
print("Waiting for message")
message = messenger.receive_message(timeout=1500)
#print("Message received:", message)
if message is not None:
    print("Received:", message)
    message = message[6:]
    with open("data.json", "w") as file:
        file.write(message)
    
        
    
