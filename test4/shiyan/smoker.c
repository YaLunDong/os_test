#include "ipc.h"

int main(int argc,char*argv[]){

	//共享内存使用的变量
    buff_key = 101;//缓冲区任给的键值 
    buff_num = 2;//缓冲区任给的长度 
    shm_flg = IPC_CREAT | 0644;//共享内存读写权限 
    
    //获取缓冲区使用的共享内存，buff_ptr指向缓冲区首地址 
    buff_ptr = (char *)set_shm(buff_key,buff_num,shm_flg); 
    
    //信号量使用的变量 
    prod_key = 201;//提供者同步信号灯键值 
    pmtx_key = 202;//提供者互斥信号灯键值 
    cons_key = 301;//抽烟者同步信号灯键值 
    cmtx_key = 302;//抽烟者互斥信号灯键值 
    sem_flg = IPC_CREAT | 0644; 
    
    //提供者同步信号灯
    sem_val = 1;
    //获取提供者同步信号灯
    prod_sem = set_sem(prod_key,sem_val,sem_flg); 
    
    //抽烟者同步信号灯 
    sem_val = 0;     
    //获取抽烟者同步信号灯，引用标识存 prod_sem 
    cons_sem = set_sem(cons_key,sem_val,sem_flg);
    
    //抽烟者互斥信号灯 
    sem_val = 1;     
    //获取抽烟者互斥信号灯，引用标识存 cons_sem 
    cmtx_sem = set_sem(cmtx_key,sem_val,sem_flg);
    
    if((pid[0]=fork())==0){//第一个抽烟者进程；
    	char ch = 't';
   		while(1){
   			//如果缓冲区为空，等待！
   			down(cons_sem);
   
  			if(!(ch!=buff_ptr[0]&&ch!=buff_ptr[1])){
   				up(cons_sem);
   				continue;
   			}
   		
   			printf("有烟草的抽烟者，获得胶水和纸，进行抽烟！\n");
   			sleep(1);
  
  			//唤醒阻塞的提供者
   			up(prod_sem);
   		 		
   		}
    }else{
    	if((pid[1]=fork())==0){//第二个抽烟者进程
    		char ch = 'p';
   			while(1){
   				//如果缓冲区为空，等待！
   				down(cons_sem);
   		
   				if(!(ch!=buff_ptr[0]&&ch!=buff_ptr[1])){
   					up(cons_sem);
		   			continue;
		   		}
   		
   				printf("有纸的抽烟者，获得烟草和胶水，进行抽烟！\n");
   				sleep(1);
   		
  				//唤醒阻塞的提供者
   				up(prod_sem);
   		 		
   			}
    	}else{//第三个抽烟者进程
			char ch = 'g';
		   	while(1){
   				//如果缓冲区为空，等待！
   				down(cons_sem);
   		
   				if(!(ch!=buff_ptr[0]&&ch!=buff_ptr[1])){
   					up(cons_sem);
   					continue;
   				}
   			
   				printf("有胶水的抽烟者，获得纸和烟草，进行抽烟！\n");
   				sleep(1);
   				
  				//唤醒阻塞的提供者
   				up(prod_sem);
   		 		
   			}
    	}
    }
}
