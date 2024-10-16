#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NumOfProcesses 10
char Metrics[6][200];

// Structure to represent a process
typedef struct process
{
	char name[5];
	int burstTime;
	int arrivalTime;
	int priority;
	int waitTime, turnAround;
	int done;
} processes;
// bubble sort implementation used to sort an array of processes based on their arrival time.
void b_sort(processes temp[], int numOfProc)
{
	processes t;
	int i, j;
	for (i = 1; i < numOfProc; i++)
		for (j = 0; j < numOfProc - i; j++)
		{
			if (temp[j].arrivalTime > temp[j + 1].arrivalTime)
			{
				t = temp[j];
				temp[j] = temp[j + 1];
				temp[j + 1] = t;
			}
		}
}
//The function accept is used to accept process details from the user and store them in an array of processes structures
int accept(processes P[])
{
	int i, numOfProc;
	printf("\n Enter total no. of processes : ");
	scanf("%d", &numOfProc);
	for (i = 0; i < numOfProc; i++)
	{
		printf("\n PROCESS [%d]", i + 1);
		printf(" Enter process name : ");
		scanf("%s", &P[i].name);
		printf(" Enter burst time : ");
		scanf("%d", &P[i].burstTime);
		printf(" Enter arrival time : ");
		scanf("%d", &P[i].arrivalTime);
		printf(" Enter priority : ");
		scanf("%d", &P[i].priority);
		P[i].done = 0;
	}
	printf("\n PROCESS\tBURST TIME\tARRIVAL TIME\tPRIORITY");
	for (i = 0; i < numOfProc; i++)
		printf("\n %s\t\t%d\t\t%d\t\t%d", P[i].name, P[i].burstTime, P[i].arrivalTime, P[i].priority);
	return numOfProc;
}

// FCFS Algorithm
void FCFS(processes P[], int numOfProc)
{
	processes temp[NumOfProcesses];
	int sumWait = 0, sumTurnaround = 0;
	int x = 0;
	float avgWait = 0.0, avgTurnaround = 0.0;
	int i, j;
	for (i = 0; i < numOfProc; i++)
		temp[i] = P[i];

	b_sort(temp, numOfProc);

	printf("\n\n PROCESS\tBURST TIME\tARRIVAL TIME");
	for (i = 0; i < numOfProc; i++)
		printf("\n %s\t\t%d\t\t%d", temp[i].name, temp[i].burstTime, temp[i].arrivalTime);

	sumWait = temp[0].waitTime = 0;
	sumTurnaround = temp[0].turnAround = temp[0].burstTime - temp[0].arrivalTime;

	for (i = 1; i < numOfProc; i++)
	{
		temp[i].waitTime = (temp[i - 1].burstTime + temp[i - 1].arrivalTime + temp[i - 1].waitTime) - temp[i].arrivalTime;
		;
		temp[i].turnAround = (temp[i].waitTime + temp[i].burstTime);
		sumWait += temp[i].waitTime;
		sumTurnaround += temp[i].turnAround;
	}
	avgWait = (float)sumWait / numOfProc;
	avgTurnaround = (float)sumTurnaround / numOfProc;
	printf("\n\n PROCESS\tBURST TIME\tARRIVAL TIME\tWAITING TIME\tTURN-AROUND TIME");
	for (i = 0; i < numOfProc; i++)
		printf("\n %s\t\t%d\t\t%d\t\t%d\t\t%d", temp[i].name, temp[i].burstTime, temp[i].arrivalTime, temp[i].waitTime, temp[i].turnAround);

	printf("\n\n GANTT CHART\n |");
	for (i = 0; i < numOfProc; i++)
		printf("  %s  |", temp[i].name);
	printf("\n ");

	printf("0\t");
	for (i = 1; i <= numOfProc; i++)
	{
		x += temp[i - 1].burstTime;
		if (x < 10)
			printf("%d      ", x);
		else
			printf("%d     ", x);
	}
	sprintf(Metrics[0], "FCFS: \t\t\t\t      Average waiting time = %0.2f\t Average turn-around = %0.2f.\n", avgWait, avgTurnaround);
	printf("\n\n Average waiting time = %0.2f\n Average turn-around = %0.2f.", avgWait, avgTurnaround);
}

// SJF Non Pre-emptive
void SJF_NonPreemptive(processes P[], int numOfProc)
{
	processes temp[NumOfProcesses];
	processes t;
	int sumWait = 0, sumTurnaround = 0;
	int x = 0;
	float avgWait = 0.0, avgTurnaround = 0.0;
	int i, j;

	for (i = 0; i < numOfProc; i++)
		temp[i] = P[i];

	b_sort(temp, numOfProc);

	for (i = 2; i < numOfProc; i++)
		for (j = 1; j < numOfProc - i + 1; j++)
		{
			if (temp[j].arrivalTime > temp[j + 1].arrivalTime)
			{
				t = temp[j];
				temp[j] = temp[j + 1];
				temp[j + 1] = t;
			}
		}

	printf("\n\n PROCESS\tBURST TIME\tARRIVAL TIME");
	for (i = 0; i < numOfProc; i++)
		printf("\n %s\t\t%d\t\t%d", temp[i].name, temp[i].burstTime, temp[i].arrivalTime);

	sumWait = temp[0].waitTime = 0;
	sumTurnaround = temp[0].turnAround = temp[0].burstTime - temp[0].arrivalTime;

	for (i = 1; i < numOfProc; i++)
	{
		temp[i].waitTime = (temp[i - 1].burstTime + temp[i - 1].arrivalTime + temp[i - 1].waitTime) - temp[i].arrivalTime;
		;
		temp[i].turnAround = (temp[i].waitTime + temp[i].burstTime);
		sumWait += temp[i].waitTime;
		sumTurnaround += temp[i].turnAround;
	}
	avgWait = (float)sumWait / numOfProc;
	avgTurnaround = (float)sumTurnaround / numOfProc;
	printf("\n\n PROCESS\tBURST TIME\tARRIVAL TIME\tWAITING TIME\tTURN-AROUND TIME");
	for (i = 0; i < numOfProc; i++)
		printf("\n %s\t\t%d\t\t%d\t\t%d\t\t%d", temp[i].name, temp[i].burstTime, temp[i].arrivalTime, temp[i].waitTime, temp[i].turnAround);

	printf("\n\n GANTT CHART\n |");
	for (i = 0; i < numOfProc; i++)
		printf("  %s  |", temp[i].name);
	printf("\n ");

	printf("0\t");
	for (i = 1; i <= numOfProc; i++)
	{
		x += temp[i - 1].burstTime;
		if (x < 10)
			printf("%d      ", x);
		else
			printf("%d     ", x);
	}
	sprintf(Metrics[2], "SJF (Non Preemptive): \t\t      Average waiting time = %0.2f\t Average turn-around = %0.2f.\n", avgWait, avgTurnaround);
	printf("\n\n Average waiting time = %0.2f\n Average turn-around = %0.2f.", avgWait, avgTurnaround);
}

// Priority Non Pre-emptive
void PrioritySched_NonPreemptive(processes P[], int numOfProc)
{
	processes temp[NumOfProcesses];
	processes t;
	int sumWait = 0, sumTurnaround = 0;
	float avgWait = 0.0, avgTurnaround = 0.0;
	int i, j;
	int x = 0;

	for (i = 0; i < numOfProc; i++)
		temp[i] = P[i];

	b_sort(temp, numOfProc);

	for (i = 2; i < numOfProc; i++)
		for (j = 1; j < numOfProc - i + 1; j++)
		{
			if (temp[j].priority > temp[j + 1].priority)
			{
				t = temp[j];
				temp[j] = temp[j + 1];
				temp[j + 1] = t;
			}
		}

	printf("\n\n PROCESS\tBURST TIME\tARRIVAL TIME\tPRIORITY");
	for (i = 0; i < numOfProc; i++)
		printf("\n %s\t\t%d\t\t%d\t\t%d", temp[i].name, temp[i].burstTime, temp[i].arrivalTime, temp[i].priority);

	sumWait = temp[0].waitTime = 0;
	sumTurnaround = temp[0].turnAround = temp[0].burstTime - temp[0].arrivalTime;

	for (i = 1; i < numOfProc; i++)
	{
		temp[i].waitTime = (temp[i - 1].burstTime + temp[i - 1].arrivalTime + temp[i - 1].waitTime) - temp[i].arrivalTime;
		;
		temp[i].turnAround = (temp[i].waitTime + temp[i].burstTime);
		sumWait += temp[i].waitTime;
		sumTurnaround += temp[i].turnAround;
	}
	avgWait = (float)sumWait / numOfProc;
	avgTurnaround = (float)sumTurnaround / numOfProc;
	printf("\n\n PROCESS\tBURST TIME\tARRIVAL TIME\tWAITING TIME\tTURN-AROUND TIME");
	for (i = 0; i < numOfProc; i++)
		printf("\n %s\t\t%d\t\t%d\t\t%d\t\t%d", temp[i].name, temp[i].burstTime, temp[i].arrivalTime, temp[i].waitTime, temp[i].turnAround);

	printf("\n\n GANTT CHART\n |");
	for (i = 0; i < numOfProc; i++)
		printf("  %s  |", temp[i].name);
	printf("\n ");

	printf("0\t");
	for (i = 1; i <= numOfProc; i++)
	{
		x += temp[i - 1].burstTime;
		if (x < 10)
			printf("%d      ", x);
		else
			printf("%d     ", x);
	}
	sprintf(Metrics[4], "Priority Scheduling (Non Preemptive): Average waiting time = %0.2f\t Average turn-around = %0.2f.\n", avgWait, avgTurnaround);
	printf("\n\n Average waiting time = %0.2f\n Average turn-around = %0.2f.", avgWait, avgTurnaround);
}

// Round Robin Scheduling
void RoundRobin(processes P[], int numOfProc)
{
	int pflag = 0, t, tcurr = 0, k, i, Q = 0;
	int sumWait = 0, sumTurnaround = 0;
	float avgWait = 0.0, avgTurnaround = 0.0;
	processes temp1[NumOfProcesses], temp2[NumOfProcesses];

	for (i = 0; i < numOfProc; i++)
		temp1[i] = P[i];

	b_sort(temp1, numOfProc);

	for (i = 0; i < numOfProc; i++)
		temp2[i] = temp1[i];

	printf("\n Enter quantum time : ");
	scanf("%d", &Q);

	char name[500];
	char time[500];

	printf("\n PROCESS\tBURST TIME\tARRIVAL TIME");
	for (i = 0; i < numOfProc; i++)
		printf("\n %s\t\t%d\t\t%d", temp1[i].name, temp1[i].burstTime, temp1[i].arrivalTime);

	for (k = 0;; k++)
	{
		if (k > numOfProc - 1)
			k = 0;
		if (temp1[k].burstTime > 0)
		{
			char strTemp[NumOfProcesses], timeTemp[NumOfProcesses];
			sprintf(strTemp, "  %s  |", temp1[k].name);
			if (tcurr < 10)
				sprintf(timeTemp, "%d      ", tcurr);
			else
				sprintf(timeTemp, "%d     ", tcurr);
			strcat(name, strTemp);
			strcat(time, timeTemp);
		}
		t = 0;
		while (t < Q && temp1[k].burstTime > 0)
		{
			t++;
			tcurr++;
			temp1[k].burstTime--;
		}
		if (temp1[k].burstTime <= 0 && temp1[k].done != 1)
		{
			temp1[k].waitTime = tcurr - temp2[k].burstTime - temp1[k].arrivalTime;
			temp1[k].turnAround = tcurr - temp1[k].arrivalTime;
			pflag++;
			temp1[k].done = 1;
			sumWait += temp1[k].waitTime;
			sumTurnaround += temp1[k].turnAround;
		}
		if (pflag == numOfProc)
			break;
	}

	printf("\n\n PROCESS\tBURST TIME\tARRIVAL TIME\tWAITING TIME\tTURN-AROUND TIME");
	for (i = 0; i < numOfProc; i++)
		printf("\n %s\t\t%d\t\t%d\t\t%d\t\t%d", temp1[i].name, temp2[i].burstTime, temp1[i].arrivalTime, temp1[i].waitTime, temp1[i].turnAround);

	printf("\n\n GANTT CHART\n");
	printf("|%s\n%s", name, time);
	printf("%d", tcurr);

	avgWait = (float)sumWait / numOfProc;
	avgTurnaround = (float)sumTurnaround / numOfProc;
	sprintf(Metrics[5], "Round Robin: \t\t\t      Average waiting time = %0.2f\t Average turn-around = %0.2f.\n", avgWait, avgTurnaround);
	printf("\n\n Average waiting time = %0.2f\n Average turn-around = %0.2f.", avgWait, avgTurnaround);
}

// Shortest Job First - Pre-emptive
void SJF_Preemptive(processes P[], int numOfProc)
{
	int i, t_total = 0, tcurr, b[NumOfProcesses], min_at, j, x, min_bt;
	int sumWait = 0, sumTurnaround = 0;
	float avgWait = 0.0, avgTurnaround = 0.0;
	processes temp[NumOfProcesses], t;

	for (i = 0; i < numOfProc; i++)
	{
		temp[i] = P[i];
		t_total += P[i].burstTime;
	}

	b_sort(temp, numOfProc);

	for (i = 0; i < numOfProc; i++)
		b[i] = temp[i].burstTime;

	printf("\n PROCESS\tBURST TIME\tARRIVAL TIME");
	for (i = 0; i < numOfProc; i++)
		printf("\n %s\t\t%d\t\t%d", temp[i].name, temp[i].burstTime, temp[i].arrivalTime);

	i = j = 0;
	char name[500];
	char time[500];
	sprintf(name, "|  %s  |", temp[i].name);
	sprintf(time, "%d      ", i);
	for (tcurr = 0; tcurr < t_total; tcurr++)
	{

		if (b[i] > 0 && temp[i].arrivalTime <= tcurr)
			b[i]--;

		if (i != j)
		{
			char strTemp[NumOfProcesses], timeTemp[NumOfProcesses];
			sprintf(strTemp, "  %s  |", temp[i].name);
			if (tcurr < 10)
				sprintf(timeTemp, "%d      ", tcurr);
			else
				sprintf(timeTemp, "%d     ", tcurr);
			strcat(name, strTemp);
			strcat(time, timeTemp);
		}

		if (b[i] <= 0 && temp[i].done != 1)
		{

			temp[i].done = 1;
			temp[i].waitTime = (tcurr + 1) - temp[i].burstTime - temp[i].arrivalTime;
			temp[i].turnAround = (tcurr + 1) - temp[i].arrivalTime;
			sumWait += temp[i].waitTime;
			sumTurnaround += temp[i].turnAround;
		}
		j = i;
		min_bt = 999;
		for (x = 0; x < numOfProc; x++)
		{

			if (temp[x].arrivalTime <= (tcurr + 1) && temp[x].done != 1)
			{

				if (min_bt != b[x] && min_bt > b[x])
				{
					min_bt = b[x];
					i = x;
				}
			}
		}
	}

	printf("\n\n PROCESS\tBURST TIME\tARRIVAL TIME\tWAITING TIME\tTURN-AROUND TIME");
	for (i = 0; i < numOfProc; i++)
		printf("\n %s\t\t%d\t\t%d\t\t%d\t\t%d", temp[i].name, temp[i].burstTime, temp[i].arrivalTime, temp[i].waitTime, temp[i].turnAround);

	printf("\n GANTT CHART\n");
	printf("%s\n%s", name, time);
	printf("%d", tcurr);

	avgWait = (float)sumWait / numOfProc;
	avgTurnaround = (float)sumTurnaround / numOfProc;
	sprintf(Metrics[1], "SJF (Preemptive): \t\t      Average waiting time = %0.2f\t Average turn-around = %0.2f.\n", avgWait, avgTurnaround);
	printf("\n\n Average waiting time = %0.2f\n Average turn-around = %0.2f.", avgWait, avgTurnaround);
}

void PrioritySched_Preemptive(processes P[], int numOfProc)
{
	int i, t_total = 0, tcurr, b[NumOfProcesses], j, x, min_pr;
	int sumWait = 0, sumTurnaround = 0;
	float avgWait = 0.0, avgTurnaround = 0.0;
	processes temp[NumOfProcesses], t;

	for (i = 0; i < numOfProc; i++)
	{
		temp[i] = P[i];
		t_total += P[i].burstTime;
	}

	b_sort(temp, numOfProc);

	for (i = 0; i < numOfProc; i++)
		b[i] = temp[i].burstTime;

	printf("\n PROCESS\tBURST TIME\tARRIVAL TIME\tPRIORITY");
	for (i = 0; i < numOfProc; i++)
		printf("\n %s\t\t%d\t\t%d\t\t%d", temp[i].name, temp[i].burstTime, temp[i].arrivalTime, temp[i].priority);

	i = j = 0;
	char name[500];
	char time[500];
	sprintf(name, "|  %s  |", temp[i].name);
	sprintf(time, "%d      ", i);
	for (tcurr = 0; tcurr < t_total; tcurr++)
	{

		if (b[i] > 0 && temp[i].arrivalTime <= tcurr)
			b[i]--;

		if (i != j)
		{
			char strTemp[NumOfProcesses], timeTemp[NumOfProcesses];
			sprintf(strTemp, "  %s  |", temp[i].name);
			if (tcurr < 10)
				sprintf(timeTemp, "%d      ", tcurr);
			else
				sprintf(timeTemp, "%d     ", tcurr);
			strcat(name, strTemp);
			strcat(time, timeTemp);
		}

		if (b[i] <= 0 && temp[i].done != 1)
		{
			temp[i].done = 1;
			temp[i].waitTime = (tcurr + 1) - temp[i].burstTime - temp[i].arrivalTime;
			temp[i].turnAround = (tcurr + 1) - temp[i].arrivalTime;
			sumWait += temp[i].waitTime;
			sumTurnaround += temp[i].turnAround;
		}
		j = i;
		min_pr = 999;
		for (x = 0; x < numOfProc; x++)
		{

			if (temp[x].arrivalTime <= (tcurr + 1) && temp[x].done != 1)
			{

				if (min_pr != temp[x].priority && min_pr > temp[x].priority)
				{
					min_pr = temp[x].priority;
					i = x;
				}
			}
		}
	}
	printf("\n\n PROCESS\tBURST TIME\tARRIVAL TIME\tWAITING TIME\tTURN-AROUND TIME");
	for (i = 0; i < numOfProc; i++)
		printf("\n %s\t\t%d\t\t%d\t\t%d\t\t%d", temp[i].name, temp[i].burstTime, temp[i].arrivalTime, temp[i].waitTime, temp[i].turnAround);

	printf("\n\n GANTT CHART\n");
	printf("%s\n%s", name, time);
	printf("%d", tcurr);

	avgWait = (float)sumWait / numOfProc;
	avgTurnaround = (float)sumTurnaround / numOfProc;
	sprintf(Metrics[3], "Priority Schedule (Preemptive):       Average waiting time = %0.2f\t Average turn-around = %0.2f.\n", avgWait, avgTurnaround);
	printf("\n\n Average waiting time = %0.2f\n Average turn-around = %0.2f.", avgWait, avgTurnaround);
}

void displayMetrics()
{
	printf("\nMetrics for the algorithms:\n");
	for (int i = 0; i < 6; i++)
		printf("%s", Metrics[i]);
}

int main()
{

	processes P[NumOfProcesses];
	int ch, numOfProc;
	do
	{
		printf("\n\n\n\t\t\t\t CPU SCHEDULING ALGORITHMS SIMULATION PROJECT");
		printf("\n Options:");
		printf("\n 0. Enter process data.");
		printf("\n 1. FCFS");
		printf("\n 2. SJF (Pre-emptive)");
		printf("\n 3. SJF (Non Pre-emptive)");
		printf("\n 4. Priority Scheduling (Pre-emptive)");
		printf("\n 5. Priority Scheduling (Non Pre-emptive)");
		printf("\n 6. Round Robin");
		printf("\n 7. Display metrics for each algorithm");
		printf("\n 8. Exit\n Select : ");
		scanf("%d", &ch);
		switch (ch)
		{
		case 0:
			numOfProc = accept(P);
			break;
		case 1:
			FCFS(P, numOfProc);
			break;
		case 2:
			SJF_Preemptive(P, numOfProc);
			break;
		case 3:
			SJF_NonPreemptive(P, numOfProc);
			break;
		case 4:
			PrioritySched_Preemptive(P, numOfProc);
			break;
		case 5:
			PrioritySched_NonPreemptive(P, numOfProc);
			break;
		case 6:
			RoundRobin(P, numOfProc);
			break;
		case 7:
			displayMetrics();
			break;
		case 8:
			exit(0);
		}
	} while (ch != 8);
	return 0;
}
