#include <stdio.h>

int main()
{
    int i=0;
    float sum=0;
    for(i=1;i<1000;i++)
    {
      if(i%3==0 || i%5==0)
      {
      printf("%d ",i);
      sum += i;
      }
      
    }
    printf("Sum = %0.2f",sum);
    return 0;
}
