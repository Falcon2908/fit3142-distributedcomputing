all: exc1 exc2 spike

exc1: exc1.c
	mpicc -o exc1 exc1.c

exc2: exc2.c
	mpicc -o exc2 exc2.c

spike: spike.c
	mpicc -o spike spike.c

clean:
	rm -f exc1 exc2 spike
