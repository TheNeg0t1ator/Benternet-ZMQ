# Benternet-ZMQ# Benternet-ZMQ





```mermaid
sequenceDiagram
    participant PhotoGenic
    participant User

    activate User
    activate PhotoGenic
    User-->>+PhotoGenic: Negotiator? (JSON with prompt and options)
    PhotoGenic-->>+User: Negotiator! (Photo in base64 format)
```

this works with the following flowchart

```mermaid
flowchart LR
    INPUT(User</br> input)
    JSON{Extract </br>JSON}
    OUTPUT(Output image </br>to zmq)
    USER_OUTPUT(Convert base 64</br>to jpg)
    INPUT-->JSON
    IMGUR(imgur api)
    OPENAI(openai</br>image api)
    SEPPE(Seppe's Image </br>editing api)
    JSON--Search-->IMGUR
    JSON--Generate-->OPENAI
    JSON--Edit-->SEPPE
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