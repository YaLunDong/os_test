#include "ipc.h"

int main(int argc,char *argv[]){
	int i;
	int rate;
	int count = MAXVAL;
	Msg_buf msg_arg;
	struct msqid_ds msg_inf;

	buff_key=101;
	buff_num=STRSIZ+1;
	shm_flg=IPC_CREAT|0644;
	buff_ptr=(char *)set_shm(buff_key,buff_num,shm_flg);
	for(i=0;i<STRSIZ;i++) buff_ptr[i]='A';
	buff_ptr[i]='\0';

	quest_flg=IPC_CREAT|0644;
	quest_key=201;
	quest_id=set_msq(quest_key,quest_flg);

	respond_flg=IPC_CREAT|0644;
	respond_key=202;
	respond_id=set_msq(respond_key,respond_flg);

	printf("wait quest:\n");
	while(1){
		if(count >0){
			quest_flg=IPC_NOWAIT;
			if(msgrcv(quest_id,&msg_arg,sizeof(msg_arg),FINISHED,quest_flg)>=0){
				count++;
				printf("%d reader finshed\n",msg_arg.mid);
			}
			else if(msgrcv(quest_id,&msg_arg,sizeof(msg_arg),READERQUEST,quest_flg)>=0){
				count--;
				msg_arg.mtype=msg_arg.mid;
				msgsnd(respond_id,&msg_arg,sizeof(msg_arg),0);
				printf("%d quest read\n",msg_arg.mid);
			}
			else if(msgrcv(quest_id,&msg_arg,sizeof(msg_arg),WRITERQUEST,quest_flg)>=0){
				count-=MAXVAL;
				msg_arg.mtype=msg_arg.mid;
				msgsnd(respond_id,&msg_arg,sizeof(msg_arg),0);
				printf("%d quest write\n",msg_arg.mid);
			}
		}
		if(count==0){
			msgrcv(quest_id,&msg_arg,sizeof(msg_arg),FINISHED,0);
			count=MAXVAL;
			printf("%d write finished\n",msg_arg.mid);
			if(msgrcv(quest_id,&msg_arg,sizeof(msg_arg),READERQUEST,quest_flg)>=0){
				count--;
				msg_arg.mtype=msg_arg.mid;
				msgsnd(respond_id,&msg_arg,sizeof(msg_arg),0);
				printf("%d quest read\n",msg_arg.mid);
			}
		}
		while(count<0){
			msgrcv(quest_id,&msg_arg,sizeof(msg_arg),FINISHED,0);
			count++;
			printf("%d reader finished\n",msg_arg.mid);
		}
	}
	return EXIT_SUCCESS;
}
