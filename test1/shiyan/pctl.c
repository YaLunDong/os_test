#include "pctl.h"

int main()
{
  int pid_1,pid_2;
  int status_1,status_2;
  while(1)
  {
    pid_1=fork();
    printf("pid_1=%d\n",pid_1);
    if(pid_1<0)
   {  
      printf("process#1 create fail\n");
      exit(EXIT_FAILURE);
   }
    if(pid_1==0)
    {

        printf("%d child will running:\n",getpid());
        char *argv[]={"0",NULL};
        status_1=execve("/bin/ls",argv,NULL);
    }
    else
    {
     printf("i am parent process %d\n",getpid());
     printf("wait for the ls-child end %d\n",pid_1);
     waitpid(pid_1,&status_1,0);
     printf("child end,sleep...\n");
     sleep(3);
    }
}
return EXIT_SUCCESS;
}

