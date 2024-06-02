import json
from enum import Enum

class ErrorMessage(Enum):
    io_NoError = 0
    io_parseError = 1
    io_promptError = 2
    io_resolutionError = 3
    io_requestTypeError = 4
    io_numberTypeError = 5
    io_numberError = 6
    io_outputError = 7

def JsonParse(inputdata: str = "")->str:
    inputdata = inputdata.lstrip("kobe!>")
    parsed_data = json.loads(inputdata)
    if parsed_data["errorType"] != ErrorMessage.io_NoError.value:
        
        errormessage:str = str("an error occured: " + str(parsed_data["errorType"]))
        if parsed_data["errorType"] == ErrorMessage.io_outputError.value:
            errormessage = "An error occured: value out of range"
        
        return errormessage
    output = parsed_data["output"]
    return output
        
    