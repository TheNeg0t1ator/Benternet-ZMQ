import json



def JsonParse(inputdata: str = "")->str:
    inputdata = inputdata.lstrip("kobe!>")
    parsed_data = json.loads(inputdata)
    output = parsed_data["output"]
    return output
        
    