#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct process{
	int burstTime,arrivalTime, priority;
	float waitingTime, turnArroundTime;
	struct process *next;
}*proc=NULL;

int LISTSIZE=0;
char *method=NULL;
char *inputFile = NULL;
char *outputFile = NULL;

//Functions prototypes
struct process* new_process(int,int,int);
struct process * insertFront(struct process *, int, int ,int);
struct process * insertBack(struct process *, int , int , int );

int get_nth_process_burstTime(struct process *,int );
int get_nth_process_arrivalTime(struct process*, int);
int get_nth_process_priority(struct process*,int);
int get_nth_process_waitingTime(struct process*,int);
void set_nth_process_waitingTime(struct process *, int , float);

void buubleSortArrivalTime(void);
void bubbleSortBurstTime(void);
void bubbleSortPriority(void);

void displayProcesses(void);
void showResult(void);
void printResult();

void fcfs();
void sJFNp();
void priorityNp(void);
//End of Functions prototypes




int main (int argc, char **argv)
{

struct process*temp=NULL;
FILE *fp=NULL;
int i, j, k, c,z, index, errorOpening=1;
char str[256];


  opterr = 0;


  while ((c = getopt (argc, argv, "f:o:")) != -1)

    switch (c)
      {

      case 'f':
        inputFile=optarg;
        errorOpening=0;
        break;
      case 'o':
         outputFile=optarg;
        break;
        //Checking for missusage of arguments
        case '?':
        if (optopt == 'f' || optopt=='o')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
        return 1;
        //Ed of arguments check

      default:

        abort ();

      }

 /* printf ("input = %s, output = %s\n",
          inputFile, outputFile);*/

  for (index = optind; index < argc; index++)
    printf ("Non-option argument %s\n", argv[index]);



if(!errorOpening)
fp = fopen(inputFile, "r");

if(!fp) {
   printf("Warning: you didn't select any file for input.\n");
}

if(!errorOpening){

while(fgets(str, sizeof str, fp)) {
   char *p = strchr(str, '\n');
   if (p) *p = 0; // remove the trailing newline, if

   if( sscanf(str, "%d:%d:%d", &i, &j, &k) == 3) {
      proc=insertBack(proc, i, j, k);
      LISTSIZE++;

   }
   }
}




do{
printf(" --------------------CPU Scheduler Simulator--------------------\n");
printf(" | 1) First come, first served scheduling.                     |\n");
printf(" | 2) Shortest-Job-First scheduling.                           |\n");
printf(" | 3) Priority Scheduling.                                     |\n");
printf(" | 4) Round Robin Scheduling.                                  |\n");
printf(" | 5) Show Result.                                             |\n");
printf(" | 6) Terminate.                                               |\n");
printf(" ---------------------------------------------------------------\n");
printf("Please enter your option: ");
scanf("%d", &z);


switch(z){

    case 1:
    /*struct process *p1= new_process(1,2,3);
    printf("%d %d %d\n", p1->burstTime, p1->arrivalTime, p1->priority);
    printf("%s", inputFile);*/
    fcfs();
    break;

    case 2:
    sJFNp();
    break;

    case 3:
    priorityNp();
    break;

    case 4:
    printf("Hello4\n");
    break;

    case 5:
    showResult();
    break;

    case 6:
    printResult();
    return 0;

    default:
    printf("Please enter a valid choice!\n");
    getchar();
    break;
    }

    }while(z!=6);


return 0;

}








//Linked List Functions
void displayProcesses(){

 struct process *temp;
 printf("you have %d processes\n",LISTSIZE);
    printf("Burst Time   Arrival Time   Priority\n");
	for(temp=proc; temp!=NULL; temp=temp->next)
        printf("    %d            %d              %d\n", temp->burstTime, temp->arrivalTime, temp->priority);



}

int is_empty(struct process *header)
{
    if(header==NULL)
       return 1;
    else
       return 0;
}

struct process * new_process(int a, int b, int c)
{
	struct process * temp;
	temp=(struct process *)malloc(sizeof(struct process));
	temp->burstTime=a;
	temp->arrivalTime=b;
	temp->priority=c;
	return temp;
}

struct process * insertFront(struct process *header, int a, int b, int c)
{
	struct process *temp;
    temp=new_process(a,b,c);
	temp->next=header;
	header=temp;
	return header;
}



struct process * insertBack(struct process *header, int a, int b, int c)
{
	struct process *temp, *headertemp;
	temp=new_process(a,b,c);
	if(header==NULL)
	{
		header=temp;
		return header;
	}
	headertemp=header;
	while(headertemp->next!=NULL)
		headertemp=headertemp->next;
	headertemp->next=temp;
	return header;
}

void insertAfter(struct process *afterNode, int a, int b, int c)
{
	struct process *temp;
	temp=new_process(a,b,c);
	temp->next=afterNode->next;
	afterNode->next=temp;
}


struct process * deleteBack(struct process *header)
{
	struct process *temp, *headertemp;
	if(header==NULL)
		return header;
	if(header->next==NULL)
	{
        free(header);
        header=NULL;
		return header;
    }
	headertemp=header;
	while(headertemp->next->next!=NULL)
		headertemp=headertemp->next;
	temp=headertemp->next;
	headertemp->next=NULL;
	free(temp);
	return header;
}


struct process * deleteFront(struct process *header)
{
	struct process *temp;
	if(header==NULL)
		return header;
	temp=header;
	header=header->next;
	free(temp);
	return header;
}

void deleteAfter(struct process *afterNode)
{
	struct process *temp;
	if(afterNode->next==NULL || afterNode==NULL)
		return;
	temp =afterNode->next;
	afterNode->next=temp->next;
	free(temp);
}

int get_nth_process_burstTime(struct process *header,int position)
{
    int i=1;
    struct process *temp;
    for (temp=header;temp!=NULL;temp=temp->next)
    {
        if(i==position)
           return temp->burstTime;
        i++;
    }
    return -1;
}



int get_nth_process_arrivalTime(struct process *header,int position)
{
    int i=1;
    struct process *temp;
    for (temp=header;temp!=NULL;temp=temp->next)
    {
        if(i==position)
           return temp->arrivalTime;
        i++;
    }
    return -1;
}

int get_nth_process_priority(struct process *header,int position)
{
    int i=1;
    struct process *temp;
    for (temp=header;temp!=NULL;temp=temp->next)
    {
        if(i==position)
           return temp->priority;
        i++;
    }
    return -1;
}

int get_nth_process_waitingTime(struct process *header, int position){

    int i=1;
    struct process *temp;
    for (temp=header;temp!=NULL;temp=temp->next)
    {
        if(i==position)
           return temp->waitingTime;
        i++;
    }
    return -1;

}

void set_nth_process_burstTime(struct process*header, int position, int value){

int i=1;
    struct process *temp;
    for (temp=header;temp!=NULL;temp=temp->next)
    {
        if(i==position)
            temp->burstTime= value;
        i++;
    }


}

void set_nth_process_waitingTime(struct process *header, int position, float value){

int i=1;
    struct process *temp;
    for (temp=header;temp!=NULL;temp=temp->next)
    {
        if(i==position)
            temp->waitingTime= value;
        i++;
    }


}
//End of Linked List functions



//Sorting Functions

//Sorting according to the arrival Time Function
void bubbleSortArrivalTime(){

struct process *temp1, *temp2, *temp3, *temp4, *temp5;

temp4=NULL;

while(temp4!=proc->next)
{
   temp3=temp1=proc;
   temp2=temp1->next;

   while(temp1!=temp4)
   {
      if(temp1->arrivalTime > temp2->arrivalTime)
      {
         if(temp1==proc)
         {
           temp5=temp2->next;
           temp2->next=temp1;
           temp1->next=temp5;
           proc=temp2;
           temp3=temp2;

         }
      else
      {
      temp5=temp2->next;
      temp2->next=temp1;
      temp1->next=temp5;
      temp3->next=temp2;
      temp3=temp2;



      }
      }
   else{
         temp3=temp1;
         temp1=temp1->next;
         }

         temp2=temp1->next;
         if(temp2==temp4)
         temp4=temp1;

   }


}



}
//End of Sorting according to the arrival Time Function

//Sorting according to the burst time

void bubbleSortBurstTime(){

struct process *temp1, *temp2, *temp3, *temp4, *temp5;

temp4=NULL;

while(temp4!=proc->next)
{
   temp3=temp1=proc;
   temp2=temp1->next;

   while(temp1!=temp4)
   {
      if(temp1->burstTime > temp2->burstTime)
      {
         if(temp1==proc)
         {
           temp5=temp2->next;
           temp2->next=temp1;
           temp1->next=temp5;
           proc=temp2;
           temp3=temp2;

         }
      else
      {
      temp5=temp2->next;
      temp2->next=temp1;
      temp1->next=temp5;
      temp3->next=temp2;
      temp3=temp2;



      }
      }
   else{
         temp3=temp1;
         temp1=temp1->next;
         }

         temp2=temp1->next;
         if(temp2==temp4)
         temp4=temp1;

   }


}



}
//End of sorting according to the burst time

//Sorting according to priority
void bubbleSortPriority(){

struct process *temp1, *temp2, *temp3, *temp4, *temp5;

temp4=NULL;

while(temp4!=proc->next)
{
   temp3=temp1=proc;
   temp2=temp1->next;

   while(temp1!=temp4)
   {
      if(temp1->priority > temp2->priority)
      {
         if(temp1==proc)
         {
           temp5=temp2->next;
           temp2->next=temp1;
           temp1->next=temp5;
           proc=temp2;
           temp3=temp2;

         }
      else
      {
      temp5=temp2->next;
      temp2->next=temp1;
      temp1->next=temp5;
      temp3->next=temp2;
      temp3=temp2;



      }
      }
   else{
         temp3=temp1;
         temp1=temp1->next;
         }

         temp2=temp1->next;
         if(temp2==temp4)
         temp4=temp1;

   }


}



}
//End of sorting according to priority


//End of Sorting Functions


//Scheduling Functions


//First come, First served
void fcfs(){

struct process *temp;
float average=0;
bubbleSortArrivalTime(); //to ensure that the arrival time is in correct order.
displayProcesses();
printf("Method selected: First come, first served\nSuccessfully performed!\n");
int i=2;
set_nth_process_waitingTime(proc, 1, 0);

for(i=2;i<=LISTSIZE;i++)
set_nth_process_waitingTime(proc,i,(get_nth_process_burstTime(proc,i-1))+(get_nth_process_waitingTime(proc, i-1)));



for(temp=proc; temp!=NULL; temp=temp->next)
average+=temp->waitingTime;

method="Method selected: First come, first served method";




}
//End of First come, First served


//Shortest Job First Non-Preemptive
void sJFNp(){

struct process *temp;
float average=0;
bubbleSortBurstTime(); //to ensure that the jobs are sorted according to the burst time.
displayProcesses();
printf("Method selected: Shortest Job First, Non-preemptive\nSuccessfully performed!\n");
int i=2;
set_nth_process_waitingTime(proc, 1, 0);

for(i=2;i<=LISTSIZE;i++)
set_nth_process_waitingTime(proc,i,(get_nth_process_burstTime(proc,i-1))+(get_nth_process_waitingTime(proc, i-1)));


for(temp=proc; temp!=NULL; temp=temp->next)
average+=temp->waitingTime;


method="Method selected: Shortest Job First, Non-preemptive";




}
//End of Shortest Job First, Non-preemptive


//Priority Scheduling, Non-Preemptive
void priorityNp(){

struct process *temp;
float average=0;
bubbleSortPriority(); //to ensure that the jobs are sorted according to the burst time.
displayProcesses();
printf("Method selected: Priority Scheduling, Non-preemptive\nSuccessfully Performed!\n");
int i=2;
set_nth_process_waitingTime(proc, 1, 0);
for(i=2;i<=LISTSIZE;i++)
set_nth_process_waitingTime(proc,i,(get_nth_process_burstTime(proc,i-1))+(get_nth_process_waitingTime(proc, i-1)));


for(temp=proc; temp!=NULL; temp=temp->next)
average+=temp->waitingTime;

method="Method selected: Priority Scheduling, Non-preemptive";

}
//End of priority scheduling non-preemptive

//End of scheduling Functions



//Showing result to screen function
void showResult(){

struct process *temp;
int i=0;
float average =0;

printf("%s\n", method);

 for(temp=proc; temp!=NULL; temp=temp->next){
        printf("Waiting Time for P[%d]= %lf ms\n",i+1 ,temp->waitingTime);
        i++;
        }

for(temp=proc; temp!=NULL; temp=temp->next)
average+=temp->waitingTime;


printf("The average waiting time is: %lf ms\n", average/LISTSIZE);

}
//End of showing result function



//Priting the Results to text file Function
void printResult(){

struct process *temp;
float average;
int i=0;

if(method==NULL)
printf("Nothing to save into an output file!\n");

else{

FILE *f = fopen(outputFile, "w");

if (f == NULL)
{
    printf("Error opening file! No output file was selected!\n");
    exit(1);
}


fprintf(f, "%s\n",method);

for(temp=proc; temp!=NULL; temp=temp->next){
        fprintf(f,"Waiting Time for P[%d]= %lf ms\n",i+1 ,temp->waitingTime);
        i++;
        }

for(temp=proc; temp!=NULL; temp=temp->next)
average+=temp->waitingTime;

fprintf(f,"The average waiting time is: %lf ms\n", average/LISTSIZE);

fclose(f);

printf("Results were printed into the specified text file\n.");

}
}
//End of priting the resutlts to text file

