在
if(kill(pid,SIGINT)>=0).....
之前加
sleep(1)
大神解释信号太快了，需要暂停一下
