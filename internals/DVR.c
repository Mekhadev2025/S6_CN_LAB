 #include <stdio.h>
struct router {
    unsigned cost[20];
    unsigned from[20];
} routingTable[10];

int main() {
    int costmat[20][20];
    int routers, i, j, k;

    printf("\nEnter the number of routers: ");
    scanf("%d", &routers);

    printf("\nEnter the cost matrix:\n");
    for (i = 0; i < routers; i++) {
        for (j = 0; j < routers; j++) {
            scanf("%d", &costmat[i][j]);
            costmat[i][i] = 0;  // Diagonal should be zero
            routingTable[i].cost[j] = costmat[i][j];
            routingTable[i].from[j] = j;
        }
    }

    // Initialize a large value for representing infinity
    const int INFINITY = 999;

    int otherShorterPathExists;
    do {
        otherShorterPathExists = 0;
        for (i = 0; i < routers; i++) {
            for (j = 0; j < routers; j++) {
                for (k = 0; k < routers; k++) {
                    if (routingTable[i].cost[j] > costmat[i][k] + routingTable[k].cost[j]) {
                        routingTable[i].cost[j] = routingTable[i].cost[k] + routingTable[k].cost[j];
                        routingTable[i].from[j] = k;
                        otherShorterPathExists = 1;
                    }
                }
            }
        }
    } while (otherShorterPathExists != 0);

    // Display routing table
    for (i = 0; i < routers; i++) {
        printf("\n\nFor Router %d\n", i + 1);
        for (j = 0; j < routers; j++) {
            if (routingTable[i].cost[j] == INFINITY) {
                printf("\tRouter %d via %d distance Infinity\n", j + 1, routingTable[i].from[j] + 1);
            } else {
                printf("\tRouter %d via %d distance %d\n", j + 1, routingTable[i].from[j] + 1, routingTable[i].cost[j]);
            }
        }
    }
    printf("\n\n");

    return 0;
}

