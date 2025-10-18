#include <stdio.h>
#include <stdlib.h>
#define max 1000

typedef struct
{
    int fila;
    int columna;
} Ship;

typedef struct
{
    Ship **ships;
    int size;
} ShipsArray;

typedef struct
{
    int *results;
    int numberOfResults;
} IntegerArray;

Ship *createShip();
ShipsArray *createShipsArray(int numberOfShips);
int calculateDistance(ShipsArray *ships);
IntegerArray *saveResults(IntegerArray *results, int result);
void freeShipMemory(ShipsArray *ships);
void freeResultsMemory(IntegerArray *results);

int main(int argc, char *argv[])
{
    int i, numberOfShips;
    IntegerArray *results = NULL;

    while (scanf("%d", &numberOfShips) && numberOfShips != 0)
    {
        if (numberOfShips < 2 || numberOfShips > max)
        {
            printf("Número de barcos no válido\n");
            continue;
        }

        ShipsArray *ships = createShipsArray(numberOfShips);

        for (i = 0; i < numberOfShips; i++)
            ships->ships[i] = createShip();

        results = saveResults(results, calculateDistance(ships));
        freeShipMemory(ships);
    }

    if (results != NULL)
    {
        for (i = 0; i < results->numberOfResults; i++)
            printf("%d\n", results->results[i]);

        freeResultsMemory(results);
    }

    return 0;
}

Ship *createShip()
{
    Ship *newShip = malloc(sizeof(Ship));
    if (newShip == NULL)
    {
        printf("Error al asignar memoria\n");
        exit(1);
    }
    if (scanf("%d %d", &newShip->fila, &newShip->columna) != 2)
    {
        printf("Error de lectura de datos\n");
        free(newShip);
        exit(1);
    }
    return newShip;
}

ShipsArray *createShipsArray(int numberOfShips)
{
    ShipsArray *ships = malloc(sizeof(ShipsArray));
    if (ships == NULL)
    {
        printf("Error al asignar memoria\n");
        exit(1);
    }
    ships->ships = malloc(numberOfShips * sizeof(Ship *));
    if (ships->ships == NULL)
    {
        printf("Error al asignar memoria\n");
        free(ships);
        exit(1);
    }
    ships->size = numberOfShips;
    return ships;
}

int calculateDistance(ShipsArray *ships)
{
    int i, j, distance = 0;

    for (i = 0; i < ships->size; i++)
    {
        for (j = i + 1; j < ships->size; j++)
        {
            int fs = ships->ships[i]->fila - ships->ships[j]->fila;
            if (fs < 0)
                fs = fs * -1;

            int cs = ships->ships[i]->columna - ships->ships[j]->columna;
            if (cs < 0)
                cs = cs * -1;

            int st = fs + cs;
            if (distance < st)
                distance = st;
        }
    }
    return distance;
}

IntegerArray *saveResults(IntegerArray *results, int result)
{
    if (results == NULL)
    {
        results = malloc(sizeof(IntegerArray));
        if (results == NULL)
        {
            printf("Error al asignar memoria\n");
            return NULL;
        }
        results->results = malloc(1 * sizeof(int));
        if (results->results == NULL)
        {
            free(results);
            return NULL;
        }
        results->results[0] = result;
        results->numberOfResults = 1;
    }
    else
    {
        int *temp = realloc(results->results, (results->numberOfResults + 1) * sizeof(int));
        if (temp == NULL)
        {
            printf("Error al asignar memoria\n");
            freeResultsMemory(results);
            return NULL;
        }
        results->results = temp;
        results->results[results->numberOfResults] = result;
        results->numberOfResults++;
    }
    return results;
}

void freeShipMemory(ShipsArray *ships)
{
    int i;
    for (i = 0; i < ships->size; i++)
    {
        free(ships->ships[i]);
    }
    free(ships);
}

void freeResultsMemory(IntegerArray *results)
{
    free(results->results);
    free(results);
}
