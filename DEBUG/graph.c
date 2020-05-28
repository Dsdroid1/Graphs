#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define MAX_NO_OF_VERTICES 10
#define INF INT_MAX
//Using Adjacency List

typedef enum {FALSE,TRUE} Bool;
typedef enum {FAILURE,SUCCESS} status_code;
typedef enum {DIRECTED,UNDIRECTED} graph_type;


typedef struct GraphNode
{
    int NodeNumber;
    struct GraphNode *next;
    int weight;
}GraphNode;

typedef struct Graph
{
    int N;//No.of Vertices/Nodes
    struct GraphNode *EdgeList[MAX_NO_OF_VERTICES];
    //int UserVertices[MAX_NO_OF_VERTICES];
    graph_type type;
}Graph;

//BAsic Structure definitions end here-----------------------

//Definition for queue---------------------------------------
typedef struct Q_element
{
    int data;
    struct Q_element *next;
}Q_element;

typedef struct Queue
{
    Q_element *front;
    Q_element *rear;
}Queue;



void InitQueue(Queue *Qptr)
{
    Qptr->front=Qptr->rear=NULL;
}

status_code InsertQ(Queue *Qptr,int data)
{
    status_code sc=SUCCESS;
    if(Qptr->front==NULL)
    {
        //Insert in empty queue
        Q_element *ptr=NULL;
        ptr=(Q_element *)malloc(sizeof(Q_element));
        if(ptr!=NULL)
        {
            ptr->data=data;
            Qptr->front=Qptr->rear=ptr;
        }
        else
        {
            sc=FAILURE;
        }
    }
    else
    {
        Q_element *ptr=NULL;
        ptr=(Q_element *)malloc(sizeof(Q_element));
        if(ptr!=NULL)
        {
            ptr->data=data;
            Qptr->rear->next=ptr;
            Qptr->rear=ptr;    
        }
        else
        {
            sc=FAILURE;
        }
    }
    return sc;
}

status_code DeleteQ(Queue *Qptr,int *dptr)
{
    status_code sc=SUCCESS;
    if(Qptr->front==NULL)
    {
        sc=FAILURE;
    }
    else
    {
        if(Qptr->front==Qptr->rear)
        {
            *dptr=Qptr->front->data;
            Qptr->front=Qptr->rear=NULL;
            free(Qptr->front);
        }
        else
        {
            *dptr=Qptr->front->data;
            Q_element *tmp=Qptr->front;
            Qptr->front=Qptr->front->next;
            free(tmp);
        }
    }
    return sc;
}

Bool isQueueEmpty(Queue Q)
{
    Bool retval=FALSE;
    if(Q.front==NULL)
    {
        retval=TRUE;
    }
    return retval;
}
//Basic Functions--------------------------------------------

void InitGraph(Graph *G)
{
    if(G!=NULL)
    {
        G->N=0;
        int i=0;
        for(i=0;i<MAX_NO_OF_VERTICES;i++)
        {
            (G->EdgeList)[i]=NULL;
        }
    }
}

status_code AddNode(Graph *G)
{
    //The added node will be predefined in terms of NodeNumber,i.e. curr largest NodeNumber +1
    status_code sc=SUCCESS;
    if(G->N < MAX_NO_OF_VERTICES - 1 )
    {
        //Insertion is possible ,i.e one more element in the array will become 'valid'
        G->N=(G->N)+1;
        printf("\nThe newly added node has NodeNumber %d",G->N-1);
    }
    else
    {
        //Error,Such node number cannot exist
        sc=FAILURE;
    }
    return sc;
}

status_code AddEdge(Graph *G,int start_vertex,int end_vertex,int weight)
{
    //Node is from start_vertex - - - - > end_vertex
    //Considering DiGraphs currently
    status_code sc=SUCCESS;
    if(start_vertex < G->N && end_vertex < G->N)
    {
        GraphNode *Vertex,*Connection;
        Vertex=(GraphNode *)malloc(sizeof(GraphNode));
        if(Vertex!=NULL)
        {
            Vertex->NodeNumber=end_vertex;
            Vertex->next=NULL;
            Vertex->weight=weight;
            //Vertex->jump=G->EdgeList[end_vertex];
            Connection=G->EdgeList[start_vertex];
            if(Connection!=NULL)//It was neighbour to someone else
            {
                //We can check if such an edge already exists
                GraphNode *trav;
                trav=Connection;
                while(trav!=NULL && sc==SUCCESS)
                {
                    if(trav->NodeNumber == end_vertex)
                    {
                        //Already exists
                        sc=FAILURE;
                    }
                    else
                    {
                        trav=trav->next;
                    }
                }
                if(sc==SUCCESS)
                {
                    Vertex->next=Connection;
                    G->EdgeList[start_vertex]=Vertex;
                }
            }
            else
            {
                G->EdgeList[start_vertex]=Vertex;
            }
            if(sc==SUCCESS)
            {
                Connection=Vertex;
            }
        }
        else
        {
            sc=FAILURE;
        }
    }
    else
    {
        sc=FAILURE;
    }
    return sc;
}

status_code DeleteEdge(Graph *G,int start_vertex,int end_vertex)
{
    status_code sc=SUCCESS;
    if(start_vertex < G->N && end_vertex < G->N)
    {
        GraphNode *Connection,*prev;
        Connection=G->EdgeList[start_vertex];
        prev=NULL;
        int found=0;
        while(Connection!=NULL && found==0)
        {
            if(Connection->NodeNumber == end_vertex)
            {
                found=1;
                //This is the node to be deleted
                if(prev==NULL)
                {
                    G->EdgeList[start_vertex]=Connection->next;
                }
                free(Connection);
            }
            else
            {
                prev=Connection;
                Connection=Connection->next;
            }
        }
        if(found==0)
        {
            //Such edge doesnt exist
            sc=FAILURE;
        }
    }
    else
    {
        sc=FAILURE;
    }
    return sc;
}

status_code DeleteNode(Graph *G)//The latest added node can only be deleted
{
    GraphNode *Connection,*prev;
    int i=0,found=0;
    status_code sc=SUCCESS;
    if(G->N > 0)
    {
        for(i=0;i < G->N - 1 ;i++)
        {
            Connection=G->EdgeList[i];
            prev=NULL;
            found=0;
            while(Connection!=NULL && found==0)
            {
                if(Connection->NodeNumber == G->N - 1)
                {
                    if(prev==NULL)
                    {
                        G->EdgeList[i]=Connection->next;
                    }
                    prev=Connection;
                    Connection=Connection->next;
                    free(prev);
                    found=1;
                }
                else
                {
                    prev=Connection;
                    Connection=Connection->next;
                }
            }
        }
        G->N=G->N - 1;
        Connection=G->EdgeList[G->N - 1];
        while(Connection!=NULL)
        {
            prev=Connection;
            Connection=Connection->next;
            free(prev);
        }
    }
    else
    {
        sc=FAILURE;

        
    }
    return sc;
}

status_code ReadGraph(Graph *G,char *filename)
{
    //The file should be in a given format
    /*
        First Line-No.of nodes TypeOfGraph(0-Directed,1-Undirected)
        Consequent Lines-Edge vertex pairs like 1 2 if edge from 1 to 2
    */
    status_code sc=SUCCESS;
    graph_type Gtype;
    int type;
    FILE *fp;
    if(G->N == 0)//Basically not to overwrite an existing graph
    {
        fp=fopen(filename,"r");
        if(fp!=NULL)
        {
            int num_nodes=0;
            fscanf(fp,"%d %d",&num_nodes,&type);
            if(type==0||type==1)
            {
                Gtype=type;
            }
            else
            {
                Gtype=0;
            }
            G->type=Gtype;
            for(int i=0;i<num_nodes && sc==SUCCESS;i++)
            {
                sc=AddNode(G);
            }
            if(sc==SUCCESS)
            {
                //Continue edge addition
                int start_vertex,end_vertex,weight;
                while(fscanf(fp,"%d%d%d",&start_vertex,&end_vertex,&weight)!=EOF && sc==SUCCESS)
                {
                    sc=AddEdge(G,start_vertex,end_vertex,weight);
                    if(G->type==UNDIRECTED)
                    {
                        sc=AddEdge(G,end_vertex,start_vertex,weight);
                    }
                }
                if(sc==SUCCESS)
                {
                    printf("\nSuccessfully Read the Graph");
                }
                else
                {
                    //Some error in adding edges
                }
            }
            else
            {
                //Some error in adding nodes
            }
        }
        else
        {
            sc=FAILURE;
        }
        fclose(fp);
    }
    else
    {
        sc=FAILURE;
    }
    
    return sc;
}

//Traversal Functions----------------------------------------------

//***********************FOR Depth First Traversal*****************
void Traverse(int curr_vertex,Graph G,int Visited[MAX_NO_OF_VERTICES])
{
    GraphNode *Connection;
    if(Visited[curr_vertex]==0)
    {
        printf("%d ",curr_vertex);
        Visited[curr_vertex]=1;
    }
    Connection=G.EdgeList[curr_vertex];
    while(Connection!=NULL)
    {
        if(Visited[Connection->NodeNumber]==0)
        {
            Traverse(Connection->NodeNumber,G,Visited);
        }
        Connection=Connection->next;
    }        
}

void DFT(Graph G)
{
    int Visited[MAX_NO_OF_VERTICES]={0};
    int curr_vertex=0;//Lets say
    int i;
    GraphNode *Connection=NULL;
    printf("\n\nDepth First traversal of this graph:\n");
    for(i=0;i<G.N;i++)
    {
        curr_vertex=i;
        if(Visited[curr_vertex]==0)
        {
            Traverse(curr_vertex,G,Visited);
        }
    }
}

//************************BREADTH FIRST TRAVERSAL*******************************
//Queue data structure required-------------------------------------------------
void BFT(Graph G)
{
    Queue Q;
    InitQueue(&Q);
    int Visited[MAX_NO_OF_VERTICES]={0};
    status_code sc=SUCCESS;
    int i=0,curr_vertex=0;
    printf("\n\nBreadth First traversal of this graph:\n");
    for(i=0;i<G.N;i++)
    {
        if(Visited[i]==0)
        {
            //then visit this node and add remaining to the queue
            sc=InsertQ(&Q,i);
            if(sc==SUCCESS)
            {
                while(isQueueEmpty(Q)==FALSE)
                {
                    sc=DeleteQ(&Q,&curr_vertex);
                    if(sc=SUCCESS)
                    {
                        if(Visited[curr_vertex]==0)
                        {
                            printf("%d ",curr_vertex);
                            Visited[curr_vertex]=1;
                            GraphNode *Connection=G.EdgeList[curr_vertex];
                            while(Connection!=NULL)
                            {
                                if(Visited[Connection->NodeNumber]==0)
                                {
                                    InsertQ(&Q,Connection->NodeNumber);
                                }
                                Connection=Connection->next;
                            }
                        }
                    }
                }   
            }
        }
    }
}
//**---------------END OF TRAVERSE FUNCTIONS------------------------------------

status_code TopologicalSort(Graph G)
{
    status_code sc=SUCCESS;
    int Visited[MAX_NO_OF_VERTICES]={0};
    int parent_edges[MAX_NO_OF_VERTICES]={0};
    GraphNode *Connection;
    int i=0,done=0,number_unlocked_in_this_iter=0,found=0;
    printf("\n\nTopological Sort:\n");
    //Tabulate the data
    for(i=0;i<G.N;i++)
    {
        Connection=G.EdgeList[i];
        while(Connection!=NULL)
        {
            parent_edges[Connection->NodeNumber]++;
            Connection=Connection->next;
        }
    }
    //We now have the data correponding to initial state
    while(sc==SUCCESS && done==0)
    {
        //Search for any nodes with 0 parent edges
        number_unlocked_in_this_iter=0;
        for(i=0;i<G.N;i++)
        {
            if(parent_edges[i]==0)
            {
                if(Visited[i]==0)
                {
                    number_unlocked_in_this_iter++;
                    printf("%d ",i);
                    Visited[i]=1;
                    //Delete all parent of outgoing from this node after printing it
                    Connection=G.EdgeList[i];
                    while(Connection!=NULL)
                    {
                        parent_edges[Connection->NodeNumber]--;
                        Connection=Connection->next;
                    }
                }
                
            }
        }
        if(number_unlocked_in_this_iter==0)
        {
            for(i=0;i<G.N && found==0;i++)
            {
                if(parent_edges[i]!=0)
                {
                    found=1;
                    sc=FAILURE;
                    //Some cycle existed
                }
            }
            if(found==0)
            {
                done=1;//All nodes have been visited
            }
        }
    }
    return sc;
}
//------------------------END of TOPOLOGICAL SORT-----------------
Bool isGraphConnected(Graph G)
{
    //For DiGraphs Acyclic ..DAGs
    Bool retval=TRUE;
    int update=0,done=0;
    int Reachability[MAX_NO_OF_VERTICES][MAX_NO_OF_VERTICES]={0};
    GraphNode *Connection=NULL;
    int i=0,j=0,k=0;
    for(i=0;i<G.N;i++)
    {
        Connection=G.EdgeList[i];
        while(Connection!=NULL)
        {
            Reachability[i][Connection->NodeNumber]=1;
            Connection=Connection->next;
        }
    }
    //Initialisation phase ends
    //Adding an optim.
    int found=0,not_connected=0;
    for(i=0;i<G.N && not_connected==0;i++)
    {
        found=0;
        for(j=0;j<G.N && found==0;j++)
        {
            if(i!=j)
            {
                if(Reachability[i][j]!=0)
                {
                    found=1;
                }
            }
        }
        if(found==0)
        {
            not_connected=1;
        }
    }
    if(not_connected==0)
    {
        while(done==0)
        {
            update=0;
            for(i=0;i<G.N;i++)
            {
                for(j=0;j<G.N;j++)
                {
                    if(i!=j)
                    {
                        if(Reachability[i][j]==1)
                        {
                            //Use this to update the reachability matrix
                            for(k=0;k<G.N;k++)
                            {
                                if(k!=i)
                                {
                                    if(Reachability[i][k]==0 && Reachability[j][k]==1)
                                    {
                                        Reachability[i][k]=1;
                                        update=1;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if(update==0)
            {
                done=1;
            }
        }
        for(i=0;i<G.N && retval==TRUE;i++)
        {
            for(j=0;j<G.N && retval==TRUE;j++)
            {
                if(i!=j)
                {
                    if(Reachability[i][j]!=1)
                    {
                        retval=FALSE;
                    }
                }
            }
        }
    }
    else
    {
        retval=FALSE;
    }
    return retval;
}
//Above code to detect connected graph
//----------------------------------------------------------------
//Dijkstra's Shortest Path Algorithm
status_code DijkstraShortestPath(Graph G,int Vertex,int pathcost[MAX_NO_OF_VERTICES],int path[MAX_NO_OF_VERTICES])//Will only work for positive edges 
{
    int CostMatrix[MAX_NO_OF_VERTICES][MAX_NO_OF_VERTICES]={0};
    status_code sc=SUCCESS;
    //Populate the cost matrix
    int i=0,j=0,k=0;
    GraphNode *Connection=NULL;
    for(i=0;i<G.N;i++)
    {
        Connection=G.EdgeList[i];
        while(Connection!=NULL && sc==SUCCESS)
        {
            if(Connection->weight > 0)
            {
                CostMatrix[i][Connection->NodeNumber]=Connection->weight;
            }
            else
            {
                sc=FAILURE;
            }
            Connection=Connection->next;
        }
    }
    for(i=0;i<G.N;i++)
    {
        for(j=0;j<G.N;j++)
        {
            if(i!=j)
            {
                if(CostMatrix[i][j]==0)
                {
                    CostMatrix[i][j]=INF;//No edge exists 
                }
            }
        }
    }
    //Now the algorithm


    if(sc==SUCCESS)
    {
        int gotshortestpath[MAX_NO_OF_VERTICES]={0};
        int min=INF,min_vertex=-1;
        
        for(i=0;i<G.N;i++)
        {
            pathcost[i]=CostMatrix[Vertex][i];
            path[i]=-1;//Indicating direct route
        }
        //Some initialisations
        
        for(i=0;i<G.N-1;i++)
        {
            min=INF;
            min_vertex=-1;
            //get the least cost path till now
            for(j=0;j<G.N;j++)
            {
                if(CostMatrix[Vertex][j] < min)
                {
                    if(gotshortestpath[j]==0)
                    {
                        min=CostMatrix[Vertex][j];
                        min_vertex=j;
                    }
                }
            }
            //After this loop we get the current not finalised min
            if(min_vertex!=-1)
            {
                gotshortestpath[min_vertex]=1;
                //Store this path length in the array to return
                pathcost[min_vertex]=min;
            }
            
            

            //Now ,use this min to try to update any other existing pathlength
            if(min!=INF)
            {
                for(k=0;k<G.N;k++)
                {
                    //Check if it improves any other path
                    if(gotshortestpath[k]==0)
                    {
                        if(CostMatrix[min_vertex][k]!=INF)
                        {
                            if(CostMatrix[Vertex][k] > CostMatrix[Vertex][min_vertex]+CostMatrix[min_vertex][k])
                            {
                                CostMatrix[Vertex][k]=CostMatrix[Vertex][min_vertex]+CostMatrix[min_vertex][k];
                                path[k]=min_vertex;//To go to 'k' we need to go via 'min_vertex'
                            }
                        }
                    }
                }
            }
            
            
        }
        int done=0;
        for(i=0;i<G.N && done==0 ;i++)
        {
            if(gotshortestpath[i]==0)
            {
                pathcost[i]=CostMatrix[Vertex][i];
                done=1;
            }
        }

    }
    
    return sc;
}

//----------To help prin the results of DijkstraShortestPath------
void PrintPathCalculatedViaDijkstra(Graph G,int vertex,int pathcost[MAX_NO_OF_VERTICES],int path[MAX_NO_OF_VERTICES])
{
    int i=0,j=0,k=0;
    int displaypath[MAX_NO_OF_VERTICES];
    printf("\n\nResults of Dijkstra's Shortest Path Algorithm:");
    for(i=0;i<G.N;i++)
    {
        if(pathcost[i]!=INF)
        {
            printf("\nThe shortest path from %d to %d costs:%d",vertex,i,pathcost[i]);
            printf("\nThe path is:");
            if(i==vertex)
            {
                printf("Trivial to itself");
            }
            else
            {
                k=0;
                j=i;
                displaypath[k]=j;
                k++;
                while(path[j]!=-1)
                {
                    displaypath[k]=path[j];
                    j=path[j];
                    k++;
                }
                displaypath[k]=vertex;
                for(j=k;j>=0;j--)
                {
                    printf("%d ",displaypath[j]);
                }
            }
        }
        else
        {
            printf("\nThe shortest path from %d to %d costs:INF",vertex,i);
            printf("\nThe path is:Does Not Exist");
        }
    }

}
//End of Dijkstra's Shortest Path algorithm
//----------------------------------------------------------------
//All Pair Shortest Path Algorithm
void PrintPathCalculatedViaAPSP(Graph G,int CostMatrix[MAX_NO_OF_VERTICES][MAX_NO_OF_VERTICES],int Path[MAX_NO_OF_VERTICES][MAX_NO_OF_VERTICES]);
void AllPairShortestPath(Graph G,int Path[MAX_NO_OF_VERTICES][MAX_NO_OF_VERTICES])
{
    //Currently the path storing/displaying method is wrong....  
    int CostMatrix[MAX_NO_OF_VERTICES][MAX_NO_OF_VERTICES]={0};
    int i=0,j=0,k=0;
    GraphNode *Connection;
    for(i=0;i<G.N;i++)
    {
        Connection=G.EdgeList[i];
        while(Connection!=NULL)
        {
            CostMatrix[i][Connection->NodeNumber]=Connection->weight;
            Connection=Connection->next;
        }
    }
    for(i=0;i<G.N;i++)
    {
        for(j=0;j<G.N;j++)
        {
            Path[i][j]=-1;
            if(i!=j)
            {
                if(CostMatrix[i][j]==0)
                {
                    CostMatrix[i][j]=INF;
                }
            }
        }
    }
    //Initialising Cost matrix complete
    //This matrix is the -1 th matrix.....from this we will derive ,0th,1th,2th...(G.N-1)th matrix

    for(k=0;k<G.N;k++)//k will signify which matrix is being made
    {
        for(i=0;i<G.N;i++)
        {
            for(j=0;j<G.N;j++)
            {
                if(i!=j)
                {
                    if(CostMatrix[i][k]!=INF && CostMatrix[k][j]!=INF)
                    {
                        if(CostMatrix[i][j] > CostMatrix[i][k]+CostMatrix[k][j])
                        {
                            CostMatrix[i][j]=CostMatrix[i][k]+CostMatrix[k][j];
                            //Update the path
                            //***********Stuff needs to be done
                            if(Path[k][j]==-1)
                            {
                                //-1 will imply direct edge from k to j
                                Path[i][j]=k;
                            }
                            else
                            {
                                int m=Path[k][j];
                                //Now the path is k,m then m,j
                                while(Path[m][j]!=-1)
                                {
                                    m=Path[m][j];
                                }
                                Path[i][j]=m;
                            }
                            //Path[i][j]=k;//Path 'i' will signify the array for going to any vertex from 'i'
                            //Path i,j signifies the previous element that is to j in the path from i to j
                        }
                    }
                }
            }
        }
    }
    PrintPathCalculatedViaAPSP(G,CostMatrix,Path);
}

void PrintPathCalculatedViaAPSP(Graph G,int CostMatrix[MAX_NO_OF_VERTICES][MAX_NO_OF_VERTICES],int Path[MAX_NO_OF_VERTICES][MAX_NO_OF_VERTICES])
{
    int displaypath[MAX_NO_OF_VERTICES]={0};
    int i=0,j=0,k=0,l=0;
    printf("\n**********************************");
    printf("\n\nThe Data calculated by APSP is:");
    for(i=0;i<G.N;i++)
    {
        for(j=0;j<G.N;j++)
        {
            printf("\n");
            if(i==j)
            {
                printf("\nThe Path from %d to %d has Cost:0",i,j);
                printf("\nThe path is:Trivial to itself");
            }
            else
            {
                if(CostMatrix[i][j]==INF)
                {
                    printf("\nThe Path from %d to %d has Cost:INF",i,j);
                    printf("\nThe path is:Does not exist");
                }
                else
                {
                    printf("\nThe Path from %d to %d has Cost:%d",i,j,CostMatrix[i][j]);
                    printf("\nThe path is:");
                    k=0;
                    l=j;
                    //displaypath[k]=l;
                    //k++;
                    int m=l;
                   // m=Path[i][j];
                    while(Path[i][m]!=-1)
                    {
                        displaypath[k]=m;
                        k++;
                        m=Path[i][m];
                    }
                    displaypath[k]=m;
                    k++;
                    displaypath[k]=i;
                    for(l=k;l>=0;l--)
                    {
                        printf("%d ",displaypath[l]);
                    }
                }
            }
        }
    }
}
//End of APSP------------------------------------------------------

//To calculate the Minimum Spanning Tree***************************
int MST(Graph G)
{
    //Based on Prim's Algorithm
    //The calculated tree will be stored in MST.txt in same directory 
    int includedInGraph[MAX_NO_OF_VERTICES]={0};
    int cost=0;
    int min,i=0,j=0,done=0;
    int from=-1,to=-1;
    GraphNode *Connection;
    includedInGraph[0]=1;
    FILE *fp;
    fp=fopen("MST.txt","w");
    fprintf(fp,"%d %d",G.N,G.type);
    //Assuming that the 0 vertex is already present in the set 
    //Find the minimum wt edge such that the vertex is contains is not included in the set... 
    for(j=0;j<G.N-1;j++)//To select N-1 more vertex
    {   
        min=INF;
        from=-1;
        to=-1;
        for(i=0;i<G.N;i++)
        {
            if(includedInGraph[i]==1)
            {
                //Then only check to update minimum
                Connection=G.EdgeList[i];
                while(Connection!=NULL)
                {
                    if(includedInGraph[Connection->NodeNumber]==0)//FInd a new edge of min cost
                    {
                        if(Connection->weight < min)
                        {
                            min=Connection->weight;
                            from=i;
                            to=Connection->NodeNumber;
                        }
                    }
                    Connection=Connection->next;
                }
            }
        }
        if(min==INF)
        {
            //No edge is existing ,MST cant be found
            cost=-1;
            done=1;
        }
        else
        {
            includedInGraph[to]=1;
            fprintf(fp,"\n%d %d %d",from,to,min);
            cost+=min;
        }
    }
    fclose(fp);
    return cost;
}


//-----------------------------------------------------------------
Bool isCycleInGraph(Graph G)//This one works only for Digraphs
{
    //based on similar approach of the topological sort
    Bool retval=TRUE;
    int Visited[MAX_NO_OF_VERTICES]={0};
    int parent_edges[MAX_NO_OF_VERTICES]={0};
    GraphNode *Connection;
    int i=0,done=0,number_unlocked_in_this_iter=0,found=0;
    
    //Tabulate the data
    for(i=0;i<G.N;i++)
    {
        Connection=G.EdgeList[i];
        while(Connection!=NULL)
        {
            parent_edges[Connection->NodeNumber]++;
            Connection=Connection->next;
        }
    }
    //We now have the data correponding to initial state
    while(done==0)
    {
        //Search for any nodes with 0 parent edges
        number_unlocked_in_this_iter=0;
        for(i=0;i<G.N;i++)
        {
            if(parent_edges[i]==0)
            {
                if(Visited[i]==0)
                {
                    number_unlocked_in_this_iter++;
                    Visited[i]=1;
                    //Delete all parent of outgoing from this node
                    Connection=G.EdgeList[i];
                    while(Connection!=NULL)
                    {
                        parent_edges[Connection->NodeNumber]--;
                        Connection=Connection->next;
                    }
                }
                
            }
        }
        if(number_unlocked_in_this_iter==0)
        {
            for(i=0;i<G.N && found==0;i++)
            {
                if(parent_edges[i]!=0)
                {
                    found=1;
                    retval=FALSE;
                    done=1;
                    //Some cycle existed
                }
            }
            if(found==0)
            {
                done=1;//All nodes have been visited
            }
        }
    }
    //Invert coz of meaning
    if(retval==FALSE)
    {
        retval=TRUE;
    }
    else
    {
        retval=FALSE;
    }
    return retval;
}

Bool isCycleInGraphVer2(Graph G)//I was trying to make for undirected,this will not work on directed
{
    ///TO BE TESTED**************************************************
    int AdjacencyMatrix[MAX_NO_OF_VERTICES][MAX_NO_OF_VERTICES]={0},temp[MAX_NO_OF_VERTICES][MAX_NO_OF_VERTICES]={1};
    int result[MAX_NO_OF_VERTICES][MAX_NO_OF_VERTICES]={0};
    int i=0,j=0,k=0,a=0,b=0,c=0;
    Bool retval=FALSE;
    GraphNode *Connection;
    for(i=0;i<G.N;i++)
    {
        Connection=G.EdgeList[i];
        while(Connection!=NULL)
        {
            AdjacencyMatrix[i][Connection->NodeNumber]++;
            Connection=Connection->next;
        }
    }
     //The above stuff readies the adjacnecy matrix
    for(k=0;k<G.N-1 && retval==FALSE;k++)
    {
        
        //Multiply Adjacency matrix with temp
        for(a=0;a<G.N && retval==FALSE;a++)
        {
            for(b=0;b<G.N && retval==FALSE;b++)
            {
                for(c=0;c<G.N;c++)
                {
                    result[a][b]+=AdjacencyMatrix[a][c]*temp[c][b];
                }
                if(result[a][b] >= 2)//More than one path to the same vertex
                {
                    retval=TRUE;
                }
            }
        }
        if(retval==FALSE)
        {
            for(a=0;a<G.N;a++)
            {
                for(b=0;b<G.N;b++)
                {
                    temp[a][b]=result[a][b];
                    result[a][b]=0;
                }
            }
        }

    }
    //
    return retval;
}
//-----------------------------------------------------------------
//Function to print all possible paths from vertex 'A' to 'B'
void FindPath(Graph G,int curr_vertex,int visited[MAX_NO_OF_VERTICES],int destination,int *pathlength,int path[MAX_NO_OF_VERTICES],Bool *atleastOnePath);
void PrintAllPossiblePaths(Graph G,int vertex_Start,int vertex_End)
{
    int i=0;
    int pathlength=0;
    int path[MAX_NO_OF_VERTICES];
    int visited[MAX_NO_OF_VERTICES]={0};
    Bool atleastOnePath=FALSE;
    if(vertex_Start < G.N && vertex_End < G.N)
    {
        path[pathlength]=vertex_Start;
        //pathlength++;
        visited[vertex_Start]=1;
        //Now we will try for a recursive solution to get all paths
        //kind of like a Depth First traversal
        GraphNode *Connection=G.EdgeList[vertex_Start];
        while(Connection!=NULL)
        {
            FindPath(G,Connection->NodeNumber,visited,vertex_End,&pathlength,path,&atleastOnePath);
            Connection=Connection->next;
        }
        if(atleastOnePath==FALSE)
        {
            printf("\n\nThere is no possible path between the given pair of vertices!\n");
        }
    }
    else
    {
        printf("\nInvalid Details of Vertices!!");
    }
}

void FindPath(Graph G,int curr_vertex,int visited[MAX_NO_OF_VERTICES],int destination,int *pathlength,int path[MAX_NO_OF_VERTICES],Bool *atleastOnePath)
{
    
    //Then use recursion to go to all other nodes connected to this node
    if(curr_vertex==destination)//Will happen only via call through Above fn
    {
        printf("\n\nOne of the Path(s) is:\n");
        printf("%d %d",path[*pathlength],destination);
        *atleastOnePath=TRUE;
    }
    else
    {
        *pathlength=(*pathlength)+1;
        path[*pathlength]=curr_vertex;
        visited[curr_vertex]=1;
        GraphNode *Connection;
        Connection=G.EdgeList[curr_vertex];
        while(Connection!=NULL)
        {
            if(Connection->NodeNumber==destination)
            {
                *pathlength=(*pathlength)+1;
                path[*pathlength]=destination;
                //Print this current path
                *atleastOnePath=TRUE;
                int i=0;
                printf("\n\nOne of the Path(s) is:\n");
                for(i=0;i<=*pathlength;i++)
                {
                    printf("%d ",path[i]);
                }
                *pathlength=(*pathlength)-1;
                //To normalise to search for next path...
            }
            else
            {
                if(visited[Connection->NodeNumber]==0)
                {
                    //*pathlength=(*pathlength)+1;
                    //path[*pathlength]=Connection->NodeNumber;
                    //visited[Connection->NodeNumber]=1;
                    FindPath(G,Connection->NodeNumber,visited,destination,pathlength,path,atleastOnePath);
                    //visited[Connection->NodeNumber]=0;
                    //*pathlength=(*pathlength)-1;
                }
            }
            Connection=Connection->next;
        }
        visited[curr_vertex]=0;
        *pathlength=(*pathlength)-1;
    }
    
}


///********************For testing purpose ONLY********************
void main()
{
    Graph G;
    InitGraph(&G);
    status_code sc;
    sc=ReadGraph(&G,"TestGraph.txt");
    if(sc==SUCCESS)
    {
        /*
        BFT(G);
        
        DFT(G);
        
        /*
        sc=TopologicalSort(G);
        if(sc==FAILURE)
        {
            printf("\nTerminating function,cycle detected");
        }
        
        /*
        Bool b=isGraphConnected(G);
        if(b==TRUE)
        {
            printf("\nYes,connected \n");
        }
        else
        {
            printf("\nNo, not connected\n");
        }
        
        /*
        Bool b=isCycleInGraph(G);
        if(b==FALSE)
        {
            printf("\nNo cycle exists\n");
        }
        else
        {
            printf("\nYes, atleast one cycle is present\n");
        }
        
        /*
        int pathcost[MAX_NO_OF_VERTICES],path[MAX_NO_OF_VERTICES];
        int vertex,i=0,j=0;
        vertex=1;
        sc=DijkstraShortestPath(G,vertex,pathcost,path);
        if(sc==SUCCESS)
        {
            printf("\n");
            PrintPathCalculatedViaDijkstra(G,vertex,pathcost,path);
        }
        
        /*
        int Path[MAX_NO_OF_VERTICES][MAX_NO_OF_VERTICES]={0};
        AllPairShortestPath(G,Path);
        
        */
        int cost;
        cost=MST(G);
        if(cost<0)
        {
            printf("\n\nMST does not exist");
        }
        else
        {
            printf("\n\nThe cost of this MST is :%d",cost);
            Graph Tree;
            InitGraph(&Tree);
            ReadGraph(&Tree,"MST.txt");

        }
        
	/*
        int vertex_Start,vertex_End;
        vertex_Start=1;
        vertex_End=2;
        PrintAllPossiblePaths(G,vertex_Start,vertex_End);
        */
    }
    
}


