#include "ipc.h"

int main(int argc, char* argv[]){

	int count =0;
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
    //获取抽烟者同步信号灯，
    cons_sem = set_sem(cons_key,sem_val,sem_flg);
    
    srand((unsigned)time(NULL));
   
    while(1){
    	//如果缓冲区满，则提供者阻塞。
    	down(prod_sem);  	
    	
    	if(count==0){
    		buff_ptr[0]='t';
    		buff_ptr[1]='g';
    		printf("提供者提供烟草和胶水！\n");
    	}
    	if(count==1){
    		buff_ptr[0]='g';
    		buff_ptr[1]='p';
    		printf("提供者提供胶水和纸！\n");
    	}
    	if(count==2){
    		buff_ptr[0]='p';
    		buff_ptr[1]='t';
    		printf("提供者提供纸和烟草！\n");
    	}
    	 
    	 count++;
    	 count = count%3;
    	 
    	//唤醒阻塞的抽烟者，
    	up(cons_sem);
    }
    return EXIT_SUCCESS;
    
}

