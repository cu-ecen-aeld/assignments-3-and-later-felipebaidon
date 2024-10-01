
CROSS_COMPILE?=

.PHONY: default
default: threading 
threading: threading.h
	${CROSS_COMPILE}gcc -Wall -Werror -pthread threading.c -o threading

.PHONY: clean 
clean: 
	rm -f *.out *.o *.txt threading
