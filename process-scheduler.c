/*	    C++ PROGRAM
*@author : Gaurav Deshmukh
*          The University of Texas at Tyler
*          Computer Science 
* Assignment No: 2 
* Operating Systems COSC 5330-01 
* Simulation of Process Scheduling
*/

#include <iostream>


using namespace std;

float total=0;

class jobs{
public:
	int time;
	int priority;
	char pid;
	int avgptime;
	int ctime;
	jobs(){
		pid ='\0';
		time = 0;
		priority =0;
		avgptime=0;
		ctime =0;
	};

	void sjf (jobs[],int);
	void prior (jobs p[],int n);
	void fcfs (jobs p[],int n);
	void roundrobin (jobs p[],int n);
	~jobs(){};


};

int main()
{
	char ch;
	int i,n;

	jobs process[10];

	cout << "\nThe Job Scheduling Program";
	cout << "\nEnter the number of processes:";
	cin >> n;

		for (i = 0; i < n ; i++)
		{
		cout << "\nEnter the value for process";
		cout << "\n Process id:";
		cin >> process[i].pid;
		cout << "\n Time for Process "<<process[i].pid<<":";
		cin >> process[i].time;
		cout << "\n Priority for Process "<<process[i].pid<<":";
		cin >> process[i].priority;
		}
			
		cout << "\nChoose from the list the Scheduling algorithm";
		cout << "\n\t1.Round Robin";
		cout << "\n\t2.Priority";
		cout << "\n\t3.Shortest job First";
		cout << "\n\t4.First Come First Serve";
		cout << "\nPlease Enter your choice OR Press Q to exit :";
		cin >> ch;

			switch(ch)
			{
				case '1':	process[n].roundrobin(process,n);
							break;

				case '2':   process[n].prior(process,n);
							break;

				case '3':	process[n].sjf(process,n);
							break;

				case '4':	process[n].fcfs(process,n);
							break;

				default: cout << "\nWrong Entry ... Exiting Program!!!";
						 return -1;
						 break;
			}

	getchar();
	return 0;

}

void jobs :: prior (jobs p[],int n)
{
	jobs temp;
	total = 0;
	int i,j;
	for(j = 0; j < n ; j++)
	{
		for(i = 0; i < n; i++)
		{
			if(p[i+1].priority > p[i].priority)
			{
				temp = p[i+1];
				p[i+1] = p[i];
				p[i] = temp;
			}
		}
	}
	
	i=0;
	while(i!=(n+1))
	{
		if(i==0)
		{
			p[i].avgptime = p[i].time;
			i++;
		}
		else
		{
			p[i].avgptime = p[i-1].avgptime + p[i].time;
			i++;
		}
	}

	float avgrt=0;
	cout << "\nProcess";
	cout << " Time";
	cout << "  Priority";
	cout << "   AvgTime";
	for (i = 0; i < n; i++)
	{
		total += p[i].avgptime;
		cout <<"\n"<< p[i].pid; 
		cout <<"\t"<<p[i].time;
		cout <<"\t  "<<p[i].priority;
		cout <<"\t     "<<p[i].avgptime;
	}

	avgrt = total / n;

	cout <<"\nTotal of Average times for "<<n<<" process using Priority Scheduling:"<<total<<endl;
	cout<<"Average round Time ="<<avgrt<<endl;

	getchar();
	getchar();

}

void jobs :: sjf (jobs p[],int n)
{
	jobs temp;
	total = 0;
	int i,j;

	for(j = 0; j < n ; j++)
	{
		for(i = 0; i < n; i++)
		{
			if(p[i].time > p[i+1].time)
			{
				temp = p[i+1];
				p[i+1] = p[i];
				p[i] = temp;
			}
		}
	}
	
	p[0].avgptime = p[0].time;

	for(i = 1 ; i <= n ; i++)
	{
		p[i].avgptime = p[i-1].avgptime + p[i].time;
	}

	float avgrt=0;
	cout << "\nProcess";
	cout << " Time";
	cout << "  Priority";
	cout << "   AvgTime";
	for (i = 1; i <= n; i++)
	{
		total += p[i].avgptime;
		cout <<"\n"<< p[i].pid; 
		cout <<"\t"<<p[i].time;
		cout <<"\t  "<<p[i].priority;
		cout <<"\t     "<<p[i].avgptime;
	}

	avgrt = total / n;

	cout <<"\nTotal of Average times for "<<n<<" process using SJF:"<<total<<endl;
	cout<<"Average round Time ="<<avgrt<<endl;

	getchar();
	getchar();
}


void jobs :: fcfs (jobs p[],int n)
{
	total = 0;
	int i;

	p[0].avgptime = p[0].time;

	for(i = 1 ; i <= n ; i++)
	{
		p[i].avgptime = p[i-1].avgptime + p[i].time;
	}

	float avgrt=0;
	cout << "\nProcess";
	cout << " Time";
	cout << "  Priority";
	cout << "   AvgTime";
	for (i = 0; i < n; i++)
	{
		total += p[i].avgptime;
		cout <<"\n"<< p[i].pid; 
		cout <<"\t"<<p[i].time;
		cout <<"\t  "<<p[i].priority;
		cout <<"\t     "<<p[i].avgptime;
	}

	avgrt = total / n;

	cout <<"\nTotal of Average times for "<<n<<" process using FCFS:"<<total<<endl;
	cout<<"Average round Time ="<<avgrt<<endl;

	getchar();
	getchar();
}

void jobs :: roundrobin (jobs p[],int n)
{
	jobs temp;
	total = 0;
	int i,j,k,tn,timeslice=0,time[10]={0};
	tn=n;

		 for(i = 0 ; i < tn ; i++)
		{
			for(j=0 ; j < tn ; j++)
			{
				if(p[j].time > p[j+1].time)
				{
					temp = p[j+1];
					p[j+1] = p[j];
					p[j] = temp;
				}
			}
		}

		 for(i = 1; i <= n; i++)
		 {
			 time[i] = p[i].time;
			 //cout <<"| " << time[i];
		 }
		 k=tn;
		 for( i = 1; i <= tn; i++ )
		 {
			 timeslice = time[i];
			 //cout <<" " << timeslice;
			 p[i].ctime = timeslice;
			 p[i].avgptime = timeslice*k;			 
			 
			 j=i;
			 while(time[j]!=0)
			 {
				 time[j]-=timeslice;
				 j++;
			 }

			 k--;
		 }
		
		 for(i = 1 ; i <= n ; i++)
		{
			p[i+1].avgptime = p[i].avgptime + p[i+1].avgptime;
		}
		
	float avgrt=0;
	cout << "\nProcess";
	cout << " Time";
	cout << "  Priority";
	cout << "     Timeslice";
	cout << "       AvgTime";

	for (i = 1; i <= n; i++)
	{
		total += p[i].avgptime;
		cout <<"\n"<< p[i].pid; 
		cout <<"\t"<<p[i].time;
		cout <<"\t  "<<p[i].priority;
		cout <<"\t     "<<p[i].ctime;
		cout <<"\t\t"<<p[i].avgptime;
	}

	avgrt = total / n;

	cout <<"\nTotal of Average times for "<<n<<" process using Round Robin Scheduling:"<<total<<endl;
	cout<<"Average round Time ="<<avgrt<<endl;

	getchar();
	getchar();
}
