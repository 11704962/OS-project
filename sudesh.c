
#include<stdio.h>
#include<windows.h>

int n, fc=0, sc=0, jc=0;
int quantum;

struct query
{
	
	
	int qid;//process id
	int priid;//priority id
	int at;//arrival time
	int bt;//burst tije
	int cmpt;//completion time
	int rbt;

}fac[100], stu[100], m[100];



void roundRobin()

{

	//time = complete[0].atime is used for initializing the time with the first arrived process's arrival time
    int time = m[0].at, cc=0, i, j, check;

    //while the total time is less than 120 minutes and
    //all the processes are not processed we'll run the loop
	while(time!=120 && cc!=jc){
    //iterate through the processes
		for(i=0; i<jc; i++){
		    //when arrival time is less than the starting time
            if(m[i].at<=time ){
            //when burst time is grater than time quantum
			if(m[i].rbt > quantum){
				time += quantum;
				m[i].rbt -= quantum;
			}
            //when burst time is less than time quantum
			else if(m[i].rbt <=quantum && m[i].rbt!=0){
				time += m[i].rbt;
				m[i].rbt =0;
				m[i].cmpt= time;
				cc++;
			}
            }
            //if arrival time is greater than the present time
            else{
                check=0;
                for(j=0;j<i;j++)
                {
                    //to check if any process above is yet to be completed
                    //if not then present time is set to arrival time of this process
                    if((m[j].at<m[i].at) && (m[j].rbt!=0))
                    {
                        check++;
                        break;
                    }
                }
                //if no process is present to execute int the current time
                //we increase the present time to the closest process's arrival time
                if(check==0)
                {
                    time=m[i].at;
                }
                continue;
            }
		}
	}
	//if  time limit exceeds then issue a warning because Sudesh can run the system
	//from 10am to 12pm only
	if(time>120)
        {
            printf("\nTime limit exceeded! Results will still show.\n");
        }
}

void join()

{
	int jsc=0, jfc= 0, min, flag;
	if( fc!=0  && sc!=0)
	{
		while(jsc<sc && jfc<fc)
		{
			if(fac[jfc].at == stu[jsc].at)
			{
				m[jc] = fac[jfc];
				jc++;
				jfc++;
				m[jc]= stu[jsc];
				jc++;
				jsc++;
			}
			else if(fac[jfc].at < stu[jsc].at)
			{
				m[jc]= fac[jfc];
				jc++;
				jfc++;
			}
			else if(fac[jfc].at > stu[jsc].at)
			{
				m[jc]= stu[jsc];
				jc++;
				jsc++;
			}
			else;
		}
		if(jc != (fc+sc))
		{
			if(fc!=jfc)
			{
				while(jfc!=fc)
				{
					m[jc]= fac[jfc];
					jc++;
					jfc++;
				}
			}
			else if(sc!=jsc)
			{
				while(jsc!=sc)
				{
					m[jc]= stu[jsc];
					jc++;
					jsc++;
				}
			}
		}
	}
	else if(fc==0)
	{
		while(jsc!=sc)
		{
			m[jc]= stu[jsc];
			jc++;
			jsc++;
		}
	}
	else if(sc==0)
	{
		while(jfc!=fc)
		{
			m[jc]= fac[jfc];
			jc++;
			jfc++;
		}
	}
	else 
	{
		printf("\n No valid Jobs available\n");
	}
}

void report()

{
	int i=0, total=0, sum=0;
	double avg;
	printf("\n\n\tDetails of processes executed\n");
	printf("\n\tMap\tQUERY ID\tARRIVAL TIME\tRESOLVING TIME\tCOMPLETION TIME\tTURN AROUND TIME\tWAITING TIME");

	for(i; i<jc; i++)
	
	
	{
		printf("\n\t%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d",
		m[i].priid,m[i].qid, (m[i].at+1000), m[i].bt, (m[i].cmpt+1000), (m[i].cmpt-m[i].at), ((m[i].cmpt-m[i].at)- m[i].bt));
		total= m[i].cmpt;
		sum+= (m[i].cmpt-m[i].at);
	}
	
	
	avg = sum/jc;
	printf("\n\n\tTotal time taken: %d", total);
	printf("\n\n\tAverage time: %lf", avg);
	printf("\n\n\tExecution Completed");


}

void processDetails()

{system("cls");
	int priority,  i, t;
	printf("\n\n\tEnter total no of queries: "); scanf("%d", &n);
	if(n==0) { printf("\n No queries to solve\n"); }
	else
	{
		printf("\n\tEnter time quantum for each Process: "); scanf("%d", &quantum);
		printf("\n\tEnter 1 for faculty and 2 for student\n");
		for(i=0; i<n; i++){
			printf("\n\t%d.Query type (Enter either 1 or 2): ",i+1); scanf("%d", &priority);
			if(priority==1)
			{
				printf("\n\tQuery Id: "); scanf("%d", &fac[fc].qid);
				fac[fc].priid=1;
				printf("\n\tArrival Time: "); scanf("%d", &t);
				if(t<1000 || t>1200){

					printf("\nEnter Correct time\n");
					processDetails();
				}
				else{fac[fc].at= t-1000;}
				printf("\n\tResolving Time: "); scanf("%d", &fac[fc].bt);	 fac[fc].rbt= fac[fc].bt;
				fc++;
			}
		
			else if(priority==2)
			{
				printf("\n\tQuery Id: "); scanf("%d", &stu[sc].qid);
				stu[sc].priid=2;
				printf("\n\tArrival Time: "); scanf("%d", &t);
				if(t<1000 || t>1200){
					printf("\n\n\tEnter Correct time\n");
					processDetails();
				}
				else {stu[sc].at= t-1000; }
				printf("\n\tResolving Time: "); scanf("%d", &stu[sc].bt);	 stu[sc].rbt= stu[sc].bt;
				sc++;
			}
			
			else
			{
			printf("\n\n\tInvalid Entry");
			processDetails();
			}
		}
	}
}

void display()

{
	printf("\n\n\tPLEASE FOLLOW THE BELOW INSTRUCTIONS FOR PROPER FUNCTIONING OF THE PROGRAM"
			"\n\n\n\t>Enter arrival time in 2400 hours format i.e 11:20 will be written as 1120"
			"\n\n\t>Query arrival times to be entered in real time i.e in ascending order\n"
			"\n\n\t>Query ID entered should be unique\n"
			"\n\n\tAll Time units are in minutes.(Resolving Time and Time quantums are to be entered in minutes) \n\n"
			"\n\n\t>PRESS ENTER TO CONTINUE.....\n"
			);
			getch();
}

 main()
 
 {
 	
	display();
	processDetails();
	join();
	roundRobin();
	report();

}
