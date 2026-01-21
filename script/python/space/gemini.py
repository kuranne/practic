from google import genai
from google.genai import types

API_KEY = ""
client = genai.Client(api_key=API_KEY)
prompt = "(This is prompt to use in this conversation, Now I typing via terminal(80*24) so for terminal friendly use you must generate response for friendly to read in terminal) here is the input:"
while True:
    ctext = str(input("You: "))
    if ctext == "exit":
        break
    response = client.models.generate_content(
        model="gemini-2.5-flash",
        contents=prompt + ctext,
        config=types.GenerateContentConfig(
            thinking_config=types.ThinkingConfig(thinking_budget=0)
        ),
    )
    print(f"Gemini: {response.text}")
