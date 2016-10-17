all: exc1 exc2 timing

exc1: exc1.c
	mpicc -o exc1 exc1.c

exc2: exc2.c
	mpicc -o exc2 exc2.c

timing: timing.c
	gcc -o timing timing.c

clean:
	rm -f exc1 exc2 timing
