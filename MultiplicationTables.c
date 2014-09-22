#include<stdio.h>
#include<conio.h>

void main()
{
 int j=0,num=0,mul=0;
 char ch;
 clrscr();
 printf("\n\tHello! Amit , How are you today?");
 printf("\nNow Let us learn!!!!");
 getch();
 do
 {
 clrscr();
 printf("\n\t\t\t****MULTIPLICATION TABLES****");
 printf("\n\tEnter the Number whose table you want to print:");
 scanf("%d",&num);
 printf("\tMultiplication Table of :: %d",num);

	   for(j=1;j<=30;j++)
	  {
	    mul = num*j;
	    printf("\n");
	    printf("%d X %d= %d",num,j,mul);
	    getch();
	    if(j%10==0)
	    {
	     clrscr();
	    }
	  }
 printf("\n\t Enter (N) for NEXT table OR  press any key to exit!!!:\t");
 ch=getch();
 }while(ch=='n'|| ch=='N');
 printf("\n\t\t\t\Exiting .....");
 getch();
 }




