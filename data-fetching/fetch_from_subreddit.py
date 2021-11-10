import requests
import json

def fetch_from_subreddit(subr):

    #Read token
    f = open('token.json','r')
    token = json.load(f)
    access_token = token["access_token"]

    #Input: subreddit name
    #Output: a list of 100 post id in that subreddit
    def postlist(subred): 
        #Get some newest post on a subreddit
        subredditurl = 'https://oauth.reddit.com/r/' + subred
        subresponse = requests.get(subredditurl, headers = {
            'User-Agent': 'Graphing/0.0.1',
            'Authorization': f'Bearer {access_token}'
            },
            params={
                'limit' :'100'
            })
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
        userlist = []
        try: 
            #check for deleted author
            a = root['data']['author']
            if (a != '[deleted]' and a != '[removed]'):
                userlist.append(a)
        except:
            True
        try: 
            #check for end of comment when too many comments 
            #(json will only return 100 first comments and there will be a "more" in place)
            if root['data']['replies'] == "":
                return userlist
            for i in root['data']['replies']['data']['children']:
                k = treetochildren(i)
            for o in k:
                userlist.append(o)
        except:
            # with open('testposterror' + '.json', 'w') as file:
            #     json.dump(root, file, indent = 4)
            True
        return userlist


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
        subredditjson = subresponse.json()
        subresponse.close()
        # with open('testpost' + post + '.json', 'w') as file:
        #     json.dump(subredditjson, file, indent = 4)
        
        author_name = subredditjson[0]['data']['children'][0]['data']['author']
        userlist = []
        if (author_name != '[deleted]' and author_name != '[removed]'):
                userlist.append(author_name)
        
        for i in subredditjson[1]['data']['children']:
            k = treetochildren(i)
            for o in k:
                userlist.append(o)

        return userlist

    #Input: a list
    #Return: the list without duplicates
    def removeDups(li):
        existed = dict()
        newlist = []
        for i in li:
            if not (i in existed):
                newlist.append(i)
                existed[i] = True
        return newlist

    alluserslist = []
    pl = postlist(subr)
    for i in pl:
        ul = userinpostlist(i, subr)
        for u in ul:
            alluserslist.append(u)

    bef = len(alluserslist)
    alluserslist = removeDups(alluserslist)
    # for u in alluserslist:
    #     print(u)
    # print(bef)
    # print(len(alluserslist))
    return alluserslist