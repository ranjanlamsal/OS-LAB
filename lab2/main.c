#include <stdio.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

void enterData(int max_resource[], int available[], int max[][MAX_RESOURCES], int alloc[][MAX_RESOURCES], int need[][MAX_RESOURCES]);
void display(int max_resource[], int available[], int max[][MAX_RESOURCES], int alloc[][MAX_RESOURCES], int need[][MAX_RESOURCES]);
int checkSafety(int available[], int max[][MAX_RESOURCES], int alloc[][MAX_RESOURCES], int need[][MAX_RESOURCES]);

int main()
{
    int max_resource[MAX_RESOURCES];
    int available[MAX_RESOURCES];
    int max[MAX_PROCESSES][MAX_RESOURCES];
    int alloc[MAX_PROCESSES][MAX_RESOURCES];
    int need[MAX_PROCESSES][MAX_RESOURCES];

    enterData(max_resource, available, max, alloc, need);
    display(max_resource, available, max, alloc, need);
    checkSafety(available, max, alloc, need);
}

void enterData(int max_resource[], int available[], int max[][MAX_RESOURCES], int alloc[][MAX_RESOURCES], int need[][MAX_RESOURCES])
{
    printf("Enter the number of instances for each resource:\n");
    for (int i = 0; i < MAX_RESOURCES; ++i)
    {
        printf("Resource %d: ", i + 1);
        scanf("%d", &max_resource[i]);
    }

    printf("\nEnter the maximum requirement of each process:\n");
    for (int i = 0; i < MAX_PROCESSES; ++i)
    {
        printf("For Process %d:\n", i + 1);
        for (int j = 0; j < MAX_RESOURCES; ++j)
        {
            printf("Resource %d: ", j + 1);
            scanf("%d", &max[i][j]);
        }
    }

    printf("\nEnter the current allocation for each process:\n");
    for (int i = 0; i < MAX_PROCESSES; ++i)
    {
        printf("For Process %d:\n", i + 1);
        for (int j = 0; j < MAX_RESOURCES; ++j)
        {
            printf("Resource %d: ", j + 1);
            scanf("%d", &alloc[i][j]);
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
    printf("Enter the number of available instances for each resource after allocation:\n");
    for (int i = 0; i < MAX_RESOURCES; ++i)
    {
        printf("Resource %d: ", i + 1);
        scanf("%d", &available[i]);
    }
}

void display(int max_resource[], int available[], int max[][MAX_RESOURCES], int alloc[][MAX_RESOURCES], int need[][MAX_RESOURCES])
{
    printf("\n Max Instances of resources:\n");
    for (int i = 0; i < MAX_RESOURCES; ++i)
    {
        printf("Resource %d: %d\n", i + 1, max_resource[i]);
    }

    printf("\nMaximum requirement of each process:\n");
    for (int i = 0; i < MAX_PROCESSES; ++i)
    {
        printf("For Process %d:", i + 1);
        for (int j = 0; j < MAX_RESOURCES; ++j)
        {
            printf(" Resource %d: %d", j + 1, max[i][j]);
        }
        printf("\n");
    }

    printf("\nCurrent allocation for each process:\n");
    for (int i = 0; i < MAX_PROCESSES; ++i)
    {
        printf("For Process %d:", i + 1);
        for (int j = 0; j < MAX_RESOURCES; ++j)
        {
            printf(" Resource %d: %d", j + 1, alloc[i][j]);
        }
        printf("\n");
    }

    printf("\nNeed matrix:\n");
    for (int i = 0; i < MAX_PROCESSES; ++i)
    {
        printf("For Process %d:", i + 1);
        for (int j = 0; j < MAX_RESOURCES; ++j)
        {
            printf(" Resource %d: %d", j + 1, need[i][j]);
        }
        printf("\n");
    }
    printf("\nAvailable Instances of resources:\n");
    for (int i = 0; i < MAX_RESOURCES; ++i)
    {
        printf("Resource %d: %d\n", i + 1, available[i]);
    }
}

int checkSafety(int available[], int max[][MAX_RESOURCES], int alloc[][MAX_RESOURCES], int need[][MAX_RESOURCES])
{
    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES] = {0};
    int safeSequence[MAX_PROCESSES];
    int count = 0;

    for (int i = 0; i < MAX_RESOURCES; ++i)
    {
        work[i] = available[i];
    }

    while (count < MAX_PROCESSES)
    {
        int found = 0;
        for (int i = 0; i < MAX_PROCESSES; ++i)
        {
            if (finish[i] == 0)
            {
                int j;
                for (j = 0; j < MAX_RESOURCES; ++j)
                {
                    if (need[i][j] > work[j])
                        break;
                }

                if (j == MAX_RESOURCES)
                {
                    for (int k = 0; k < MAX_RESOURCES; ++k)
                    {
                        work[k] += alloc[i][k];
                    }

                    safeSequence[count++] = i;
                    finish[i] = 1;
                    found = 1;

                    printf("Safe sequence: ");
                    for (int k = 0; k < count; ++k)
                    {
                        printf("P%d ", safeSequence[k]);
                    }
                    printf("\n");
                }
            }
        }

        if (found == 0)
        {
            printf("\nSystem is in unsafe state. No safe sequence exists.\n");
            return 0;
        }
    }

    return 1;
}