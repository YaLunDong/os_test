#include<sched.h>
#include<sys/time.h>
#include<sys/resource.h>
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>

typedef void(*sighandler_t)(int);

void sigcat_1(){
     printf("sigint,add priority\n");
     setpriority(PRIO_PROCESS,getpid(),getpriority(PRIO_PROCESS,getpid())+1);
}

void sigcat_2(){
     printf("sigtstp,decrease the priority\n");
     setpriority(PRIO_PROCESS,getpid(),getpriority(PRIO_PROCESS,getpid())-1);    
}

int main(int argc,char *argv[])
{
   int i,j,pid;
   printf("crtl-c add the priority while crtl-z decrease the priority\n");
   if((pid=fork())==0)
   {
      signal(SIGINT,(sighandler_t)sigcat_1);
      signal(SIGTSTP,(sighandler_t)sigcat_2);
      for(i=0;i<20;i++){
           printf("the child process PID=%d,scheduler stratey=%d\n",getpid(),getpriority(PRIO_PROCESS,0),sched_getscheduler(getpid()));
          sleep(1);
       }
   }
   else{
   signal(SIGINT,(sighandler_t)sigcat_1);
   signal(SIGTSTP,(sighandler_t)sigcat_2);
   for(i=0;i<20;i++){
           printf("the parent process PID=%d,scheduler stratey=%d\n",getpid(),getpriority(PRIO_PROCESS,0),sched_getscheduler(getpid()));
           sleep(1);
    }
   }
  return EXIT_SUCCESS; 
}
