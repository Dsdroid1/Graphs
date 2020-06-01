#include"graph.h"

status_code DeleteAndRename(Graph *G,int NodeNumber)
{
    status_code sc=SUCCESS;
    if(NodeNumber < G->N)
    {
        GraphNode *Connection,*prev=NULL;
        int i;
        for(i=0;i<G->N;i++)
        {
            Connection=G->EdgeList[i];
            prev=NULL;
            if(i!=NodeNumber)
            {
                while(Connection!=NULL)
                {
                    if(Connection->NodeNumber==NodeNumber)
                    {
                        if(prev==NULL)
                        {
                            G->EdgeList[i]=Connection->next;
                        }
                        else
                        {
                            prev->next=Connection->next;
                        }
                        
                        prev=Connection;
                        Connection=Connection->next;
                        free(prev);
                    }
                    else if(Connection->NodeNumber < NodeNumber)
                    {
                        prev=Connection;
                        Connection=Connection->next;
                    }
                    else
                    {
                        Connection->NodeNumber=(Connection->NodeNumber)-1;  
                        prev=Connection;
                        Connection=Connection->next; 
                    }
                }
            }
            else
            {
                while(Connection!=NULL)
                {
                    prev=Connection;
                    Connection=Connection->next;
                    free(prev);
                    G->EdgeList[i]=NULL;
                }
            }
        }  
        for(i=NodeNumber;i<G->N-1;i++)
        {
            G->EdgeList[i]=G->EdgeList[i+1];
            printf("\nNode %d has been renamed to %d",i+1,i);
        }
        G->EdgeList[G->N]=NULL;
        G->N=G->N - 1;
    }
    else
    {
        sc=FAILURE;
    }
    return sc;
}

void DisplayGraphInfo(Graph G)
{
    int i=0;
    GraphNode *Connection;
    printf("\nThis graph has the set of vertices:");
    printf("\n{");
    for(i=0;i<G.N;i++)
    {
        printf("%d ",i);
    }
    printf("}\n");
    if(G.type==DIRECTED)
    {
        printf("It is a Directed Graph");
    }
    else
    {
        printf("It is an Undirected Graph");
    }
    if(G.weighted==TRUE)
    {
        printf("\nIt is a Weighted Graph");
    }
    else
    {
        printf("\nIt is a Non-Weighted Graph");
    }
    printf("\nThe set of edges are:\n");
    for(i=0;i<G.N;i++)
    {
        Connection=G.EdgeList[i];
        while(Connection!=NULL)
        {
            printf("(%d, %d) ",i,Connection->NodeNumber);
            Connection=Connection->next;
        }
    }
    printf("\n\n");
}

status_code StoreGraphToFile(Graph G,char *filename)
{
    status_code sc=SUCCESS;
    FILE *fp;
    fp=fopen(filename,"w");
    if(fp!=NULL)
    {
        fprintf(fp,"%d %d",G.N,G.type);
        fprintf(fp,"\n%d",G.weighted);
        int i=0;
        GraphNode *Connection;
        for(i=0;i<G.N;i++)
        {
            Connection=G.EdgeList[i];
            while(Connection!=NULL)
            {
                fprintf(fp,"\n%d %d %d",i,Connection->NodeNumber,Connection->weight);
                Connection=Connection->next;
            }
        }
        fclose(fp);
    }
    else
    {
        sc=FAILURE;
    }
    return sc;
}

void EditUIGraph(Graph *G)
{
    int done=0,choice;
    int from,to,wt,vertex;
    status_code sc;
    while(done==0)
    {
        printf("\nWhat do you want to do:");
        printf("\n1.Add a Node");
        printf("\n2.Add an Edge");
        printf("\n3.Delete an Edge");
        printf("\n4.Delete a node(Will result in renaming vertices)");
        printf("\n5.Store graph details in GraphDetails.txt");
        printf("\n6.Display All info regarding this graph");
        printf("\n7.Any other number to go back");
        printf("\nYour Choice:");
        scanf("%d",&choice);
        printf("\n");
        switch(choice)
        {
            case 1:
                    sc=AddNode(G);
                    if(sc==SUCCESS)
                    {
                        printf("\nSuccessfull Operation");
                    }
                    else
                    {
                        printf("\nSome error occured");
                    }
                    break;

            case 2:
                    
                    //Make some bool in graph structure for weighted and do stuff of wts algos only if true
                    
                    printf("\nEnter the originating point(from):");
                    scanf("%d",&from);
                    printf("\nEnter the terminating point(to):");
                    scanf("%d",&to);
                    printf("\nEnter the edge weight(0 if unweighted graph):");
                    scanf("%d",&wt);
                    if(G->weighted==FALSE)
                    {
                        wt=0;
                    }
                    sc=AddEdge(G,from,to,wt);
                    if(G->type==UNDIRECTED)
                    {
                        sc=AddEdge(G,to,from,wt);
                    }
                    if(sc==SUCCESS)
                    {
                        printf("\nSuccessfull Operation");
                    }
                    else
                    {
                        printf("\nSome error occured");
                    }
                    break;

            case 3:
                    
                    printf("\nEnter the originating point(from):");
                    scanf("%d",&from);
                    printf("\nEnter the terminating point(to):");
                    scanf("%d",&to);
                    sc=DeleteEdge(G,from,to);
                    if(G->type==UNDIRECTED)
                    {
                        sc=DeleteEdge(G,to,from);
                    }
                    if(sc==SUCCESS)
                    {
                        printf("\nSuccessfull Operation");
                    }
                    else
                    {
                        printf("\nSome error occured");
                    }
                    break;

            case 4:
                    printf("\nWhich Node is to be deleted:");
                    scanf("%d",&vertex);
                    sc=DeleteAndRename(G,vertex);
                    if(sc==SUCCESS)
                    {
                        printf("\nSuccessfull Operation");
                    }
                    else
                    {
                        printf("\nSome error occured");
                    }
                    break;

            case 5:
                    sc=StoreGraphToFile(*G,"GraphDetails.txt");
                    if(sc==SUCCESS)
                    {
                        printf("\nSuccessfull Operation");
                    }
                    else
                    {
                        printf("\nSome error occured");
                    }
                    break;

            case 6:
                    DisplayGraphInfo(*G);
                    break;

            default:
                    done=1;
                    break;

        }
    }
}

void main()
{
    Graph G;
    InitGraph(&G);
    status_code sc;
    sc=ReadGraph(&G,"TestGraphUnweighted.txt");
    if(sc==SUCCESS)
    {
        printf("\nSuccessfully read the graph from file!");
        
        int done=0,choice,value;
        Bool isConnected,isCyclic,isValueInGraph;

        while(done==0)
        {
            printf("\n\nWhat operation do you want to perform:");
            printf("\n1.Edit the Graph");
            printf("\n2.Traverse the Graph via DFT");
            printf("\n3.Traverse the Graph via BFT");
            printf("\n4.Display the Topological Sort of the Graph");
            printf("\n5.Detect whether the graph is connected or disconnected");
            printf("\n6.Find the shortest path from a source vertex to all other vertices");
            printf("\n7.Find the shortest path for all pairs of the vertices");
            printf("\n8.Searching a value in the graph via BFS,DFS[Not yet implemented]");
            printf("\n9.Detect the presence of a cycle in the graph");
            printf("\n10.Calculate and store the MST of the Graph");
            printf("\n11.Display all possible paths between a pair of vertices");
            printf("\n12.Any other number to exit");
            printf("\nYour Choice:");
            scanf("%d",&choice);
            printf("\n\n");

            switch(choice)
            {
                case 1:
                        EditUIGraph(&G);
                        break;

                case 2:
                        DFT(G);
                        break;

                case 3:
                        BFT(G);
                        break;
                
                case 4:
                        sc=TopologicalSort(G);
                        if(sc==FAILURE)
                        {
                            printf("\nTerminating function,cycle detected");
                        }
                        break;

                case 5:
                        isConnected=isGraphConnected(G);
                        if(isConnected==TRUE)
                        {
                            printf("\nYes,connected \n");
                        }
                        else
                        {
                            printf("\nNo, not connected\n");
                        }
                        break;

                case 6:
                        ;
                        if(G.weighted==TRUE)
                        {
                            int pathcost[MAX_NO_OF_VERTICES],path[MAX_NO_OF_VERTICES];
                            int vertex;
                            printf("\nFrom which vertex do you want the paths:");
                            scanf("%d",&vertex);
                            sc=DijkstraShortestPath(G,vertex,pathcost,path);
                            if(sc==SUCCESS)
                            {
                                printf("\n");
                                PrintPathCalculatedViaDijkstra(G,vertex,pathcost,path);
                            }
                            else
                            {
                                printf("\nSome negative weight is present,use option 7 for APSP");
                            }
                        }
                        else
                        {
                            printf("\nIt is an unweighted graph!!");
                        }
                        
                        break;

                case 7:
                        ;
                        if(G.weighted==TRUE)
                        {
                            int Path[MAX_NO_OF_VERTICES][MAX_NO_OF_VERTICES]={0};
                            AllPairShortestPath(G,Path);//Does not detect negative cycle
                        }
                        else
                        {
                            printf("\nIt is an unweighted graph!!");
                        }
                        
                        break;

                case 8:
                        //To be implemented....
                        printf("\nEnter the value to be searched:");
                        scanf("%d",&value);
                        printf("\nSearching by DFS");
                        isValueInGraph=DFS(G,value);
                        if(isValueInGraph==TRUE)
                        {
                            printf("\nValue Found by DFS");
                        }
                        else
                        {
                            printf("\nThe value does not exist in the graph");
                        }
                        printf("\nSearching by BFS");
                        isValueInGraph=BFS(G,value);
                        if(isValueInGraph==TRUE)
                        {
                            printf("\nValue Found by BFS");
                        }
                        else
                        {
                            printf("\nThe value does not exist in the graph");
                        }
                        break;

                case 9:
                        //printf("%d",G.type);
                        if(G.type==DIRECTED)
                        {
                            isCyclic=isCycleInGraph(G);
                            if(isCyclic==FALSE)
                            {
                                printf("\nNo cycle exists\n");
                            }
                            else
                            {
                                printf("\nYes, atleast one cycle is present\n");
                            }
                        }
                        else
                        {
                            isCyclic==isCycleInGraphVer2(G);
                            if(isCyclic==FALSE)
                            {
                                printf("\nNo cycle exists\n");
                            }
                            else
                            {
                                printf("\nYes, atleast one cycle is present\n");
                            }
                        }
                        break;

                case 10:
                        //Needs to be changed in some display manner as well as non-existent
                        //Without -ve cost
                        ;
                        //Will give a directed/Undirected tree depending on the input
                        if(G.weighted==TRUE)
                        {
                            int cost;
                            cost=MST(G);
                            if(cost<0)
                            {
                                printf("\n\nMST does not exist");
                            }
                            else
                            {
                                printf("\n\nThe cost of this MST is :%d",cost);
                                printf("\nTne details of this tree are overwritten in MST.txt");
                            }
                        }
                        else
                        {
                            printf("\nIt is an unweighted graph!!");
                        }
                        break;

                case 11:
                        ;
                        int vertex_Start,vertex_End;
                        printf("\nEnter the source vertex:");
                        scanf("%d",&vertex_Start);
                        printf("\nEnter the destination vertex:");
                        scanf("%d",&vertex_End);
                        PrintAllPossiblePaths(G,vertex_Start,vertex_End);
                        break;

                default:
                        done=1;
                        break;
            
            }
        }
        
    }
    else
    {
        printf("\nError in reading the file");
    }
}