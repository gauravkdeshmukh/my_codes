/*	    C PROGRAM
*@author : Gaurav Deshmukh
*          The University of Texas at Tyler
*          Computer Science 
* Assignment No: 4 
* Operating Systems COSC 5330-01 
* Implementation of Bankers Algorithm
* Assume a system with n (n =10 maximum) processes and m (m = 5, maximum) resources.     
  Write Banker’s algorithm to test whether the system in the safe state. 
  If it is in the safe state, show the sequence for executing the processes
*/
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
 
int main() {
	/*curr_alloc-> Current Allocation Matrix
	  need		-> Need Matrix
	  max		-> Maximum Matrix
	  avl		-> Available Vector 
	  max_res	-> Maximum Resources Vector */
    int curr_alloc[10][10],need[10][10];
    int max[10][10];
    int avl[10];
    int alloc[10] = {0};
    int max_res[10];
	int sequence[10];
    int running[10];
	int n = -1;
	char ch;
 
	/*exec -> flag to indicate process in execution
	  safe -> boolean flag to denote system state ie. safe or u safe*/
    int i, j, exec, no_res, no_proc;
    int count = 0;
    bool safe = false;

	/*Enter number of resources -> no_res*/
    printf("\nEnter the number of resources: ");
    scanf_s("%d", &no_res);

	/*Enter number of processes -> no_res*/
    printf("\nEnter the number of processes: ");
    scanf_s("%d", &no_proc);
    for (i = 0; i < no_proc; i++) {
        running[i] = 1;
        count++;
    }
 
	/*Enter vector of exixting resources*/
    printf("\nEnter Exisiting Resources Vector (E): ");
    for (i = 0; i < no_res; i++)
        scanf_s("%d", &max_res[i]);
 
	/*Enter Allocation matrix A*/
    printf("\nEnter Allocation Matrix: ");
    for (i = 0; i < no_proc; i++) {
        for (j = 0; j < no_res; j++)
            scanf_s("%d", &curr_alloc[i][j]);
    }
 
    printf("\nEnter Need Matrix: ");
    for (i = 0; i < no_proc; i++) {
        for (j = 0; j < no_res; j++)
			scanf_s("%d", &need[i][j]);
    }

	for (i = 0; i < no_proc; i++) {
        for (j = 0; j < no_res; j++)
			max[i][j] = need[i][j] + curr_alloc[i][j];
    }

 
    printf("\nThe Exisiting Resources Vector is: ");
    for (i = 0; i < no_res; i++)
        printf("%d ", max_res[i]);
 
    printf("\nThe Allocation Matrix:\n");
    for (i = 0; i < no_proc; i++) {
        for (j = 0; j < no_res; j++)
            printf("\t%d", curr_alloc[i][j]);
        printf("\n");
    }
 
    printf("\nThe Maximum Matrix:\n");
    for (i = 0; i < no_proc; i++) {
        for (j = 0; j < no_res; j++)
            printf("\t%d", max[i][j]);
        printf("\n");
    }
 
    for (i = 0; i < no_proc; i++)
        for (j = 0; j < no_res; j++)
            alloc[j] += curr_alloc[i][j];
 
    printf("\nAllocated resources: ");
    for (i = 0; i < no_res; i++)
        printf("%d ", alloc[i]);
    for (i = 0; i < no_res; i++)
        avl[i] = max_res[i] - alloc[i];
 
    printf("\nAvailable resources: ");
    for (i = 0; i < no_res; i++)
        printf("%d ", avl[i]);
    printf("\n");
 
	/*Bankers Algorithm*/
    while (count != 0) {
        safe = false;
        for (i = 0; i < no_proc; i++) {
            if (running[i]) {
                exec = 1;
 /*condition that checks if current allocation fits the available matrix */
                for (j = 0; j < no_res; j++) {
                    if (max[i][j] - curr_alloc[i][j] > avl[j]) {
						exec = 0;
                        break;
                    }
                }
 
                if (exec) {
                    printf("\nProcess%d is executed.", i + 1);
					sequence[++n] = i+1;
					running[i]=0;
                    count--;
                    safe = true;
                    for (j = 0; j < no_res; j++)
                        avl[j] += curr_alloc[i][j];
                    break;
                }
            }
        }
 
        if (!safe) {
            printf("\nThe System is in unsafe state.");
            break;
        }
 
        if (safe)
            printf("\nThe System is in safe state.");
		
        printf("\nAvailable vector: ");
        for (i = 0; i < no_res; i++)
		{
            printf("%d ", avl[i]);
		}
		printf("\n");
    }

	printf("\n Execution Sequence:\n");
        for (i = 0; i < no_proc; i++)
		{
			printf(" P%d ", sequence[i]);
			if(i<no_proc-1)
				printf("->");
 		}
	ch = getchar();
	ch = getchar();
    return 0;
}
