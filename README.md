# Benternet-ZMQ# Benternet-ZMQ



This is how the basics work 

```mermaid
sequenceDiagram
    participant Service
    participant User

    activate User
    activate Service
    User-->>+Service: Negotiator? (JSON with prompt and options)
    Service-->>+User: Negotiator! (Photo in base64 format)
```

this works with the following flowchart

```mermaid
flowchart LR
    INPUT(User</br> input)
    JSON{Extract </br>JSON}
    OUTPUT(Output image </br>to zmq)
    USER_OUTPUT(user)
    IMAGE(PhotoGenic)
    NUMBER(NumberGenic)
    PRIMES(Prime Numbers)
    SIMPLES(Simple Numbers)
    NUMBER_OUT(Output number </br>to ZMQ)

    INPUT-->JSON
    JSON-->IMAGE
    JSON-->NUMBER

    NUMBER-->PRIMES & SIMPLES

    PRIMES & SIMPLES --> NUMBER_OUT
    NUMBER_OUT --> USER_OUTPUT
    

    IMGUR(imgur api)
    OPENAI(openai</br>image api)
    SEPPE(Seppe's Image </br>editing api)

    IMAGE--Search-->IMGUR
    IMAGE--Generate-->OPENAI
    IMAGE--Edit-->SEPPE


    IMGUR & OPENAI & SEPPE --Base 64 -->OUTPUT
    OUTPUT-->USER_OUTPUT
```

The Json has this structure

```json
{
    "RequestType": "Image",
    "ImageType": "Generate",
    "Prompt": "A penguin in a suit",
    "Resolution": "512x512",
    "Spellcheck": "True"
}
```

or you could ask for a prime number, simple number or other by changing the json

```json
{
    "RequestType": "Number",
    "NumberType": "Prime",
    "CheckNumber": "false",// if checknumber is true, it checks if prompt is of number type
    "Prompt": "5", // in this case it gives the fifth prime number
}
```

failsafes,

als niet geldig altijd een respons sturen

