
import secrets

def generateCode() -> str:
    token = secrets.token_urlsafe(100)
    return token[:128]

code_verifier = generateCode()
print(len(code_verifier))
print(code_verifier)
f = open('code_verifier.txt','w')
f.write(code_verifier)