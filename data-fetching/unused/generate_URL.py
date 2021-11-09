import requests
import secrets


code_verifier = open('code_verifier.txt','r').read()

clientinfo = open('client_id.txt','r').read().splitlines()

clientid = clientinfo[0]
clientsecret = clientinfo[1]
clientredirect = clientinfo[2]

url = 'https://www.reddit.com/api/v1/authorize?'
url +='client_id=' + clientid +'&'
url += 'response_type=code&'
url += 'state=' + code_verifier + '&'
url += 'redirect_uri=' + clientredirect+ '&duration=permanent&scope=read'

print(url)

