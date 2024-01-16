#include <stdio.h>

struct Process
{
    int processNumber;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnAroundTime;
    int waitingTime;
};

void calculateAverageWaitingTime(struct Process processes[], int n);

int main()
{
    struct Process processes[3]; // Assuming there are 3 processes

    // Input process details
    for (int i = 0; i < 3; ++i)
    {
        printf("Enter details for Process %d:\n", i + 1);

        processes[i].processNumber = i + 1;

        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrivalTime);

        printf("Burst Time: ");
        scanf("%d", &processes[i].burstTime);

        printf("\n");
    }

    // FCFS Algorithm
    for (int i = 0; i < 3 - 1; ++i)
    {
        for (int j = 0; j < 3 - i - 1; ++j)
        {
            if (processes[j].arrivalTime > processes[j + 1].arrivalTime)
            {
                // Swap processes
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    int completionTime = processes[0].arrivalTime;
    int turnAroundTime;
    int waitingTime;

    for (int i = 0; i < 3; ++i)
    {
        // Calculate completion time
        completionTime += processes[i].burstTime;

        // Calculate turn around time and waiting time
        processes[i].turnAroundTime = completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnAroundTime - processes[i].burstTime;

        printf("Process %d:\n", processes[i].processNumber);
        printf("Completion Time: %d\n", completionTime);
        printf("Turn Around Time: %d\n", processes[i].turnAroundTime);
        printf("Waiting Time: %d\n\n", processes[i].waitingTime);
    }

    // Calculate and print the average waiting time
    calculateAverageWaitingTime(processes, 3);

    return 0;
}

void calculateAverageWaitingTime(struct Process processes[], int n)
{
    int totalWaitingTime = 0;

    for (int i = 0; i < n; ++i)
    {
        totalWaitingTime += processes[i].waitingTime;
    }

    double averageWaitingTime = (double)totalWaitingTime / n;

    printf("Average Waiting Time: %.2f\n", averageWaitingTime);
}
