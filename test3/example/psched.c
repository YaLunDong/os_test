#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
int main(int argc, char *argv[])
{
int i,j,status;
int pid[3]; //存放进程号
struct sched_param p[3]; //设置调度策略时使用的数据结构
//for(i=1;i<=6;i++) printf("++++++++++++++++%s\n",argv[i]);
for(i=0; i<3;i++){
//循环创建 3 个子进程
if((pid[i]=fork()) >0){
//取进程优先数放在调度策略数据结构中
p[i].sched_priority = (argv[i+1] != NULL) ? atoi(argv[i+1]):10;
//printf("%dprocess youxianshu:%d\n",getpid(),p[i].sched_priority);
//父进程设置子进程的调度策略.如果命令行第 4,5,6 参数指定了 3 个策略第二部分
sched_setscheduler(pid[i],(argv[i+4] != NULL) ? atoi(argv[i+4]) : SCHED_OTHER,&p[i]);
//printf("%dprocess diaoducelue:%d\n",pid[i],sched_getscheduler(pid[i]));
//父进程设置子进程的优先数,如果命令行第 1,2,3 参数指定了 3 个优先数
setpriority(PRIO_PROCESS,pid[i],(argv[i+1] != NULL) ? atoi(argv[i+1]):10);
//printf("%dprocess youxianshu:%d\n",pid[i],getpriority(PRIO_PROCESS,pid[i]));
}
//各子进程循环报告其优先数和调度策略
else{
sleep(2);
//每隔 1 妙报告一次进程号和优先级
for(i=0; i<10; i++){
printf("Child PID = %d priority =%d\n",getpid(),getpriority(PRIO_PROCESS,0));
sleep(1);
}
exit( EXIT_SUCCESS);
}
}
//父进程报告子进程调度策略后先行退出
printf("My child %d policy is %d\n",pid[0],sched_getscheduler(pid[0]));
printf("My child %d policy is %d\n",pid[1],sched_getscheduler(pid[1]));
printf("My child %d policy is %d\n",pid[2],sched_getscheduler(pid[2]));
return EXIT_SUCCESS;
}
