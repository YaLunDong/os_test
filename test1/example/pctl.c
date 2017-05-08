#include "pctl.h"

int main(int argc,char *argv[])
{
  int i;
  int pid;//
  int status;
  char *args[]={"bin/ls","-a",NULL};
  signal(SIGINT,(sighandler_t)sigcat);
  pid=fork();
 // while(1){
  for(j=1;j<3;j++)
 {
  if(pid<0)
  {
     printf("Create Process failed!\n");
     exit(EXIT_FAILURE);
  }
  if(pid==0)
  {
    printf("i am Child process %d\nMy father is %d\n",getpid(),getppid());
  
   // printf("%d\n",i);//    pause(); 
    printf("%d Child will Running:",getpid());
    if(argv[1]!=NULL){
       for(i=1;i<=3;i++);
      // printf("###########");
       for(i=1;argv[i]!=NULL;i++) printf("%s",argv[i]);
       printf("\n");
       printf("########\n");
       status=execve(argv[1],&argv[1],NULL); 
   }
    else
    {
      for(i=0;args[i]!=NULL;i++) printf("%s",args[i]);
      printf("\n");
      status=execve(args[0],args,NULL);
    }
  }
  else
  {
    printf("\n i am Parent process %d\n",getpid());
    if(argv[1]!=NULL){
      printf("%d waiting for child done.\n\n");
     waitpid(pid,&status,0);
     printf("\n My child exit! status=%d\n\n",status);
      }
    else
    {
      if(kill(pid,SIGINT)>=0)
        printf("%d wakeup %d child.\n",getpid(),pid);
     printf("%d don't wait for child done.\n\n",getpid());
    }
  }
}
  return EXIT_SUCCESS;
}
