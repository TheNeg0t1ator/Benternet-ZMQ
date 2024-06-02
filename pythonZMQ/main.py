import time
import json
from zmqServiceClass import ZMQ_service


print("starting")
messenger = ZMQ_service("tcp://benternet.pxl-ea-ict.be:24041", "tcp://benternet.pxl-ea-ict.be:24042")
print("messenger created")

primes = []
with open("primes.txt", "r") as file:
    for line in file:
        primes.append(int(line.strip()))

fibbo = []
with open("fibonacci_sequence.txt", "r") as file:
    for line in file:
        fibbo.append(int(line.strip()))

messenger.subscribe("kobe")  # Subscribe to all topics

print("receiving messages")

response = messenger.receive_message()
# if response is not None:
#     print("Received:", response)

while True:
    message = messenger.receive_message()
    
    if message is not None:
        print("Received:", message)
        message = message.replace("kobe?", "")
        print(message)
        NewMessage:str = "" 
        parsed_json = json.loads(message)
        numbertype = parsed_json['NumberType']
        response = {"output": 0}
        print("numbertype:", numbertype)
        if numbertype == "Prime":
            prompt = parsed_json['Prompt']
            print("prompt:", prompt)
            prime_index = int(prompt)
            if prime_index < len(primes):
                prime_to_send = primes[prime_index+1]
                response = {"output": prime_to_send}
                # response = {"PrimeNumber": prime_to_send}
                #messenger.send_message(json.dumps(response))
            else:
                print("Invalid prime index:", prime_index)
                
                messenger.send_message("kobe?Invalid index")
        elif numbertype == "Fibonacci":
            prompt = parsed_json['Prompt']
            print("prompt:", prompt)
            fibbo_index = int(prompt)
            if fibbo_index < len(fibbo):
                fibbo_to_send = primes[fibbo_index+1]
                response = {"output": prime_to_send}
                # response = {"PrimeNumber": prime_to_send}
                #messenger.send_message(json.dumps(response))
            else:
                print("Invalid prime index:", fibbo_index)
                messenger.send_message("kobe?Invalid index")
            
                
        NewMessage = json.dumps(response)
        print(NewMessage)
        messenger.send_message(NewMessage)
        
    
