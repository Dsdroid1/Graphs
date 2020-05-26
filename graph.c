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
    //graph_type type;
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
        First Line-No.of nodes
        Consequent Lines-Edge vertex pairs like 1 2 if edge from 1 to 2
    */
    status_code sc=SUCCESS;
    FILE *fp;
    if(G->N == 0)//Basically not to overwrite an existing graph
    {
        fp=fopen(filename,"r");
        if(fp!=NULL)
        {
            int num_nodes=0;
            fscanf(fp,"%d",&num_nodes);
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
//


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
    return retval;
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
        
        sc=TopologicalSort(G);
        if(sc==FAILURE)
        {
            printf("\nTerminating function,cycle detected");
        }
       
        Bool b=isGraphConnected(G);
        if(b==TRUE)
        {
            printf("\nYes,connected \n");
        }
        else
        {
            printf("\nNo, not connected\n");
        }

        b=isCycleInGraph(G);
        if(b==TRUE)
        {
            printf("\nNo cycle exists\n");
        }
        else
        {
            printf("\nYes, atleast one cycle is present\n");
        }
        */
        int pathcost[MAX_NO_OF_VERTICES],path[MAX_NO_OF_VERTICES];
        int vertex,i=0,j=0;
        vertex=1;
        sc=DijkstraShortestPath(G,vertex,pathcost,path);
        if(sc==SUCCESS)
        {
            printf("\n");
            PrintPathCalculatedViaDijkstra(G,vertex,pathcost,path);
        }
    }
    
}


