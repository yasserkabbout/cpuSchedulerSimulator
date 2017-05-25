#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct process{
	int burstTime,arrivalTime, priority;
	float waitingTime, turnArroundTime;
	struct process *next;
};

struct process* new_process(int,int,int);
struct process * insertFront(struct process *, int, int ,int);
struct process * insertBack(struct process *, int , int , int );
int get_nth_process_burstTime(struct process *,int );
int get_nth_process_arrivalTime(struct process*, int);
int get_nth_process_priority(struct process*,int);
int get_nth_process_waitingTime(struct process*,int);
void set_nth_process_waitingTime(struct process *, int , float);


void fcfs(struct process*, int);


int main (int argc, char **argv)
{

struct process *proc= NULL;
struct process*temp=NULL;
FILE *fp=NULL;
char *inputFile = NULL;
char *outputFile = NULL;
int i, j, k, c,z, index, errorOpening=1,listSize=0;
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
      listSize++;

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

    printf("you have %d processes\n",listSize);

    /*struct process *p1= new_process(1,2,3);

    printf("%d %d %d\n", p1->burstTime, p1->arrivalTime, p1->priority);

    printf("%s", inputFile);*/
	for(temp=proc; temp!=NULL; temp=temp->next)
        printf("%d %d %d\n", temp->burstTime, temp->arrivalTime, temp->priority);

    fcfs(proc, listSize);
    for(temp=proc; temp!=NULL; temp=temp->next)
        printf("%lf\n", temp->waitingTime);


    break;

    case 2:
    printf("Hello2\n");
    break;

    case 3:
    printf("Hello3\n");
    break;

    case 4:
    printf("Hello4\n");
    break;

    case 5:
    printf("Hello5\n");
    break;

    case 6:
    return 0;

    default:
    printf("Please enter a valid choice!");
    getchar();
    break;
    }

    }while(z!=6);


return 0;

}








//Linked List Functions

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





//Sorting according to the arrival Time Function



//End of Sorting according to the arrival Time Function


//Scheduling Functions

void fcfs(struct process *header, int size){

int i=2;
set_nth_process_waitingTime(header, 1, 0);
for(i=2;i<=size;i++)
set_nth_process_waitingTime(header,i,(get_nth_process_burstTime(header,i-1))+(get_nth_process_waitingTime(header, i-1)));


}


