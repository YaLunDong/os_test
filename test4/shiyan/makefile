hdrs = ipc.h 
opts = -g -c 
src = smoker.c ipc.c   
obj = smoker.o ipc.o 
p_src = provider.c ipc.c   
p_obj = provider.o ipc.o 

all:    provider smoker
 
smoker:  $(obj) 
	gcc $(obj) -o smoker   
smoker.o:  $(rc) $(hdrs) 
	gcc $(opts) $(src)     	
provider: $(p_obj) 
	gcc $(p_obj) -o provider   
provider.o:  $(p_src) $(hdrs) 
	gcc $(opts) $(p_src)   
	
clean: 
	rm smoker provider *.o
