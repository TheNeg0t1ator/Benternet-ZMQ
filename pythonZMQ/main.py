import time
import json
from zmqServiceClass import ZMQ_service


print("starting")
messenger = ZMQ_service("tcp://benternet.pxl-ea-ict.be:24041", "tcp://benternet.pxl-ea-ict.be:24042")
print("messenger created")
with open("banana.json", 'r') as file:
    json_str = file.read()
print("parsed json")

messageTosend:str = "kobe?"+json_str
messenger.send_message(messageTosend)

messenger.subscribe("kobe")  # Subscribe to all topics



print("receiving messages")

response = messenger.receive_message()
if response is not None:
    print("Received:", response)

while True:
    #messenger.send_message(messageTosend)
    print("Sent:", messageTosend)
    message = messenger.receive_message()
    
    if response is not None:
        print("Received:", message)

