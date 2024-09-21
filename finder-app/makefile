
CROSS_COMPILE?=

.PHONY: default
default: writer.out
writer.out:
	chmod 777 writer.c
	${CROSS_COMPILE}gcc writer.c -o writer
	chmod 777 writer

.PHONY: clean 
clean: 
	rm -f *.out *.o *.txt writer
