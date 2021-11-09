import requests
import json

#Read token
f = open('token.json','r')
token = json.load(f)
access_token = token["access_token"]

#Input: subreddit name
#Output: a list of 100 newest post id in that subreddit
def postlist(subred): 
    #Get some newest post on a subreddit (r/uiuc)
    subredditurl = 'https://oauth.reddit.com/r/' + subred + '/new'
    subresponse = requests.get(subredditurl, headers = {
        'User-Agent': 'Graphing/0.0.1',
        'Authorization': f'Bearer {access_token}'
        },
        params={
            'limit' :'100'
        })
    subresponse.raise_for_status()
    subredditjson = subresponse.json()
    subresponse.close()
    # with open('testsubreddit.json', 'w') as file:
    #     json.dump(subredditjson, file, indent = 4)
    #Turn into post id
    if not ("data" in subredditjson):
        return[]
    if not ("children" in subredditjson["data"]):
        return[]
    li = subredditjson["data"]["children"]
    postlist = []
    for i in li:
        s = i["data"]["name"]
        s = s[3 : : ]
        postlist.append(s)
    return postlist


#Input: a json comment tree
#Output: a list of users that commented on that root
def treetochildren(root):
    try:
        userlist = []
        a = root['data']['author_fullname']
        userlist.append(a)
        if root['data']['replies'] == "":
            return userlist
        for i in root['data']['replies']['data']['children']:
            k = treetochildren(i)
            for o in k:
                userlist.append(o)
        return userlist
    except:
        return []



#Input: post id and subreddit name
#Output: a list of users that commented on that post
def userinpostlist(post, subred):
    #Get commenters
    subredditurl = 'https://oauth.reddit.com/r/' + subred + '/comments/' + post
    subresponse = requests.get(subredditurl, headers = {
        'User-Agent': 'Graphing/0.0.1',
        'Authorization': f'Bearer {access_token}'
        },
        params={
        })

    subresponse.raise_for_status()
    subredditjson = subresponse.json()
    subresponse.close()
    # with open('testpost' + post + '.json', 'w') as file:
    #     json.dump(subredditjson, file, indent = 4)
    
    author_name = subredditjson[0]['data']['children'][0]['data']['author_fullname']
    userlist = []
    userlist.append(author_name)
    
    for i in subredditjson[1]['data']['children']:
        k = treetochildren(i)
        for o in k:
            userlist.append(o)

    return userlist

alluserslist = []
pl = postlist('uiuc')
for i in pl:
    ul = userinpostlist(i, 'uiuc')
    for u in ul:
        alluserslist.append(u)
for u in alluserslist:
    print(u)
print(len(alluserslist))