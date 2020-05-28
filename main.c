#include"graph.h"

void EditUIGraph(Graph *G)
{
    int done=0,choice;
    int from,to,wt;
    status_code sc;
    while(done==0)
    {
        printf("\nWhat do you want to do:");
        printf("\n1.Add a Node");
        printf("\n2.Add an Edge");
        printf("\n3.Delete an Edge");
        printf("\n4.Delete a node[To be developed]");
        printf("\n5.Store graph details in GraphDetails.txt[To be developed]");
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
                    sc=AddEdge(G,from,to,wt);
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
                    break;

            case 5:
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
    sc=ReadGraph(&G,"TestGraph.txt");
    if(sc==SUCCESS)
    {
        printf("\nSuccessfully read the graph from file!");
        
        int done=0,choice;
        Bool isConnected,isCyclic;

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
                        break;

                case 7:
                        ;
                        int Path[MAX_NO_OF_VERTICES][MAX_NO_OF_VERTICES]={0};
                        AllPairShortestPath(G,Path);//Does not detect negative cycle
                        break;

                case 8:
                        //To be implemented....
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