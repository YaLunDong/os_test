#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
  int pid;
  int pipe1[2];
  int pipe2[2];
  int x;
  
  if(pipe(pipe1)<0){ printf("pipe not create"); exit(EXIT_FAILURE);}
  if(pipe(pipe2)<0){ printf("pipe not create"); exit(EXIT_FAILURE);}
  
  if((pid=fork())<0) {perror("process not create"); exit(EXIT_FAILURE);}
  else if(pid==0)
  {
   close(pipe1[1]); close(pipe2[0]);
   do{
    read(pipe1[0],&x,sizeof(int));
    printf("child %d read:%d\n",getpid(),x++);
    write(pipe2[1],&x,sizeof(int));
  }while(x<=9);
  close(pipe1[0]); close(pipe2[1]);
  exit(EXIT_SUCCESS);
  }
  else
  {
    close(pipe1[0]); close(pipe2[1]);
    x=1;
    do
    {
     write(pipe1[1],&x,sizeof(int));
     read(pipe2[0],&x,sizeof(int));
     printf("parent %d read:%d\n",getpid(),x++);
    }while(x<=9);
    close(pipe1[1]);
    close(pipe2[0]);
  }
  return EXIT_SUCCESS;
}
