import math

THAI_ALPHABET = (
    "กขฃคฅฆงจฉชซโซฑฒณดตถทธนบปผฝพฟภมยรลวศษสหฬอฮ"
    "ะาำิีึืุูเแโใไั็่้๊๋"
)
PADDING_CHAR = "="

def thai_base64_encode(data: bytes) -> str:
    """
    Arg:
        data: bytes
    Ret:
        str
    """
    binary_string = ""
    
    for byte in data:
        binary_string += f"{byte:08b}"
    
    chunks = [binary_string[i:i+6] for i in range(0, len(binary_string), 6)]
    
    result = []
    for chunk in chunks:
        if len(chunk) < 6:
            padding_needed = 6 - len(chunk)
            chunk = chunk + ("0" * padding_needed)
            
        index = int(chunk, 2)
        result.append(THAI_ALPHABET[index])
    
    rem = len(data) % 3
    if rem == 1:
        result.append(PADDING_CHAR * 2)
    elif rem == 2:
        result.append(PADDING_CHAR)
        
    return "".join(result)

if __name__ == "__main__":
    test_bytes = b"HelloWorld!"
    encoded_text = thai_base64_encode(test_bytes)
    
    print(f"Original: {test_bytes.decode('utf-8')}")
    print(f"Thai Base64: {encoded_text}")