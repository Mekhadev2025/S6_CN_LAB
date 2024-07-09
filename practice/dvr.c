#include <stdio.h>
#include <stdlib.h>

struct router
{
    unsigned cost[20];
    unsigned from[20];
} routingTable[20];

int main()
{
    int routers;
    int costmatrix[20][20];
    printf("Enter the number of routers:");
    scanf("%d", &routers);
    printf("\n");

        printf("Enter the cost matrix:\n");
    for (int i = 0; i < routers; i++)
    {
        for (int j = 0; j < routers; j++)
        {
            scanf("%d", &costmatrix[i][j]);
            costmatrix[i][i] = 0;
            routingTable[i].cost[j] = costmatrix[i][j];
            routingTable[i].from[j] = j;
        }
    }
    const int INFINITY = 999;
    int shortestPath;
    do
    {
        shortestPath = 0;
        for (int i = 0; i < routers; i++)
        {
            for (int j = 0; j < routers; j++)
            {
                for (int k = 0; k < routers; k++)
                {
                    if (routingTable[i].cost[j] > costmatrix[i][k] + routingTable[k].cost[j])
                    {
                        routingTable[i].cost[j] = routingTable[i].cost[k] + routingTable[k].cost[j];
                        routingTable[i].from[j]=k;
                        shortestPath=1;
                    }
                }
            }
        }
    }while(shortestPath!=0);
    //pritn the routing table



    for(int i=0;i<routers;i++){
        for(int j=0;j<routers;j++){
            if(routingTable[i].cost[j]==INFINITY){
                printf("%d router via %d has distance infinity\n",j+1,routingTable[i].from[j]+1);

            }
            else{
                printf("%d router via %d has distance %d\n",j+1,routingTable[i].from[j]+1,routingTable[i].cost[j]);
                
            }
        }
        printf("\n");
    }
}