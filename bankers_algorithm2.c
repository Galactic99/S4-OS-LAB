#include<stdio.h>

void main()
{
  int m,n,alloc[50][50],max[50][50],need[50][50],avail[50],
      work[50],finish[50],j,i;
   
  //number of processes and resources    
  printf("Enter number of processes:");
  scanf("%d",&m);
  printf("Enter number of unique resources:");
  scanf("%d",&n);
  
  //allocation table
  printf("Enter Allocation Matrix:\n");
  for(i=0;i<m;i++)
   {
     for(j=0;j<n;j++)
     {
        printf("Process %d Resource %d:",i,j+1);
        scanf("%d",&alloc[i][j]);
     }
   }    
  
  //max table
  printf("Enter Max Matrix\n");
  for(i=0;i<m;i++)
  {
     for(j=0;j<n;j++)
     {
        printf("Process %d Resource %d:",i,j+1);
        scanf("%d",&max[i][j]);
     }
  }
  
  printf("Enter available instance of each resources:");
  for(i=0;i<n;i++)
  {
     scanf("%d",&avail[i]);
  }
  
  //need table
  for(i=0;i<m;i++)
  {
     for(j=0;j<n;j++)
     {
        need[i][j]= max[i][j] - alloc[i][j];
     }
  }
  
  //variable to check if process has already been excuted
  for(i=0;i<m;i++)
  {
   finish[i]=0;
  }
  
  int count=0,found,k=0,flag,process[50];
  
  //Check for safe sequence
  while(count<m)
  {
     for(i=0;i<m;i++)
     {
        if(finish[i]==0)
        {
           flag=1;
           for(j=0;j<n;j++)
           {
              if(need[i][j]>avail[j])
              {
                 flag=0;
                 break;
              }
           }  
        
          if(flag)
          {
            for(j=0;j<n;j++)
            {
               avail[j]+=alloc[i][j];
            } 
            count++; 
            process[k]=i;
            finish[i]=1;
            k++;
          } 
       }
     }
  }
  
  //Print safe sequnce
  printf("Safe Sequence:");
  for(i=0;i<m;i++)
  {
     printf("P%d->",process[i]);
  }
  printf("\n");
  
}  
