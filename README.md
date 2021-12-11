# Reddit graph

### The location of all major code, data, and results
/InterFontCharacters : Font folder containing letters PNG

/cs225 : Contains cs225 stuffs that is used like PNG, testing, make

/data-fetching : Contains code used in fetching data
    /data-fetching/data : The result from the data fetching
    /data-fetching/data/converter.py : Convert .json files to .txt
    /data-fetching/data/fetch_data.py : Main data-fetching code
    /data-fetching/data/fetch_from_subreddit.py : Code that reads from one subreddit
    /data-fetching/data/fetch_from_user.py : Convert Code that reads from one user
    /data-fetching/data/get-token.py : Get the access token neccessary to fetch data from reddit

/data : Contains all the datasets, including the test data
    /data/data1/ : Fetched data containing about 900 nodes
    /data/data2/ : Fetched data containing about 60000 nodes
    /data/testConstructor : Test data to test the graph constructor
    /data/testDijkstra1 : Test data to test the Dijkstra algorithm

/documents : Contains all the documents
    /documents/meeting_records.md : Log of meeting records/DEVELOPMENT file
    /documents/project_proposal.md : Project proposal
    /documents/team_contract.md : Team contract
    
/tests : Contains all test suites used in testing

FileReader.cpp FileReader.h : File reader class, use to read from datasets
Graph.cpp Graph.h : The main graph class
GraphVisualization.cpp GraphVisualization.h : Class use to output visualization image
PhysicSimulation.cpp PhysicSimulation.h : Physics Simulation class use to output the final coordinates of all nodes to give to GraphVisualization for it to draw
PriorityQueue.cpp PriorityQueue.h : Pointer-based min heap for Dijkstra

### Building and running the executable


### Testing





