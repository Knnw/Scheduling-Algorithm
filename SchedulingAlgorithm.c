#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Constant variables
const int MIN_JOBS = 3;
const int MAX_JOBS = 10;

void SJN();
void PP();
int getJobNumber();
int getAlgoInput();
void showTable();

/**
    MAIN FUNCTION
*/
int main(){
    //Variables
    int jobNumber;
    bool loopEnd = false;
    char choice;
    //Creating Menu
    do {
        printf("- - -Scheduling Algorithm- - -\n");
        printf("A: Shortest Job Next\n");
        printf("B: Preemptive Priority\n");
        printf("C: Exit\n\n");
        printf("Enter Choice: ");
        scanf("%c", &choice);
        fflush(stdin);
        //Input Checker
        switch(toupper(choice)){
        case 'A': //Shortest Job Next
            printf("\n");
            SJN();
            break;
        case 'B': //Preemptive Priority
            printf("\n");
            PP();
            break;
        case 'C': //Exit loop and end code
            loopEnd = true;
            break;
        default: //Input Error
            printf("Input Unavailable\n");
        }
    } while (!loopEnd);
    //Exit Message
    printf("Thank You For Using The Program!\n");
    return 0;
}

/**
    Function Name: SJN
    Parameter: none
    Return Type: void
    Function:
        Do the Shortest Job Next algorithm for the data
        Display the output
*/
void SJN(){
    //variables
    int jobNumber = getJobNumber();
    int arrivalTime[jobNumber];
    int burstTime[jobNumber];
    int index[getAlgoInput(jobNumber, arrivalTime, burstTime, NULL)];

    //@Show Data Table
    showTable(jobNumber, arrivalTime, burstTime, NULL);
    
    //-----------------SJN Edit Fermin, Ogwo (DRAFT)---------------------------
    printf ("\n");
    //additional variables
    int totalTime=0;
    int LBT=99999; //least burst time

    //gets the total time
    for(int a=0;a<jobNumber;++a){
        totalTime+=burstTime[a];
    }

    //@show simulation
    for(int a=0;a<=totalTime; ++a){
        //variable for chosen next job
        int NextJob;
        //choosing next job to be printed
        for (int b=0; b<jobNumber; b++){
            if (arrivalTime[b]<=a && burstTime[b]<LBT){
                NextJob=b;
                LBT=burstTime[b];
            }
        }
        //prints the job accordingly
        printf ("J%d ", NextJob+1);
        for (int c=0; c<burstTime[NextJob]-1; ++c){
                printf ("-  ");
            if (a>9 && a<100){
            printf (" ");
        }
            if (a>100){
               printf (" ");
            }
        }
        //makes the counter start at the end of the present job
        a+=burstTime[NextJob];
        //prevents repetition of done jobs
        arrivalTime[NextJob]=totalTime+1;
        //resets LBT
        LBT=99999;
    }
    printf ("\n");
    //prints the time line
    for (int a=0;a<=totalTime-1; ++a){
        printf ("%d  ", a);

    }
    printf ("\n\n");

    //-----------------------------------------------------

}

/**
    Function Name: PP
    Parameter: none
    Return Type: none
    Function:
        Do the Preemptive Priority algorithm for the data
        Display the output
*/
void PP(){
    //variables
    int jobNumber = getJobNumber();
    int arrivalTime[jobNumber];
    int burstTime[jobNumber];
    int priority[jobNumber];
    int index[getAlgoInput(jobNumber, arrivalTime, burstTime, priority)];





    //@Show Data Table
    showTable(jobNumber, arrivalTime, burstTime, priority);
}

/**
    Function Name: getJobNumber
    Parameter: none
    Return Type: int
        return the number of jobs the algorithm will have
    Function:
        Let the user input the number of jobs the algorithm will use
*/
int getJobNumber(){
    int jobNumber;
    printf("(min: 3|max: 10)\n");
    do{
        printf("Enter number of Jobs: ");
        scanf("%d", &jobNumber);
        fflush(stdin);
        if(jobNumber < MIN_JOBS || jobNumber > MAX_JOBS){
            printf("Limit Error!\n");
        }
    } while(jobNumber < MIN_JOBS || jobNumber > MAX_JOBS);
    printf("\n");
    return jobNumber;
}

/**
    Function Name: getAlgoNumber
    Parameter: int, int[], int[], int[]
        - jobNumber - Number of Jobs
        - AT[] - Array for Arrival Time
        - BT[] - Array for Burst Time
        - Priority[] - Array for Priority of Job
    Return Type: int
        return the total of burst time for all jobs
    Function:
        Let the user input the data for the algorithm
        Return the sum of time of the jobs
*/
int getAlgoInput(int jobNumber, int AT[], int BT[], int priority[]){
    int jobTimeSum = 0;
    //Enter Data for Arrival Time Array
    printf("Arrival Time:\n");
    for(int i = 0; i < jobNumber; ++i){
        printf("Enter Arrival Time for J%d: ", (i + 1));
        scanf("%d", &AT[i]);
        fflush(stdin);
    }
    printf("\n");

    //Enter Data for Burst Time Array
    printf("Burst Time:\n");
    for(int i = 0; i < jobNumber; ++i){
        printf("Enter Burst Time for J%d: ", (i + 1));
        scanf("%d", &BT[i]);
        fflush(stdin);
        jobTimeSum += BT[i];
    }
    printf("\n");

    //Enter Data for Priority Array
    if(priority != NULL){
        printf("(1 - Highest Priority)\n");
        printf("Priority:\n");
        for(int i = 0; i < jobNumber; ++i){
            printf("Enter Priority for J%d: ", (i + 1));
            scanf("%d", &priority[i]);
            fflush(stdin);
        }
        printf("\n");
    }
    return jobTimeSum;
}

/**
    Function Name: showTable
    Parameter: int, int[], int[], int[]
        - jobNumber - Number of Jobs
        - AT[] - Array for Arrival Time
        - BT[] - Array for Burst Time
    Return Type: void
    Function:
        Show the Table:
            JOB     AT      BT      Priority(optional)
*/
void showTable(int jobNumber, int AT[], int BT[], int priority[]){
    if(priority == NULL){
        printf("Jobs\tArrival Time\tBurst Time\n");
        for(int i = 0; i < jobNumber; ++i){
            printf("J%d\t%d\t\t%d\t\t\n", (i + 1), AT[i], BT[i]);
        }
    }
    else{
        printf("Jobs\tArrival Time\tBurst Time\tPriority\n");
        for(int i = 0; i < jobNumber; ++i){
            printf("%d\t%d\t\t%d\t\t%d\n", (i + 1), AT[i], BT[i], priority[i]);
        }
    }
}
