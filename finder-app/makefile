
CROSS_COMPILE?=

.PHONY: default
default: writer.out
writer.out:
	${CROSS_COMPILE}gcc writer.c -o writer


.PHONY: clean 
clean: 
	rm -f *.out *.o *.txt writer
