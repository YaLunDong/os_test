head=pctl.h
srcs=pctl.c
objs=pctl.o
opts=-g	-c
all:	pctl
pctrl:	$(objs)
	gcc	$(objs)	-o	pctl
pctrl.o:	$(srcs)	$(head)
	gcc	$(opts)	$(srcs)
clean:	rm	pctl	*.o
