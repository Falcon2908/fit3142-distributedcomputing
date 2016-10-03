all: helloworld exc2 exc3

helloworld: helloworld.c
	mpicc -o helloworld helloworld.c

exc2: exc2.c
	mpicc -o exc2 exc2.c

exc3: exc3.c
	mpicc -o exc3 exc3.c

clean:
	rm -f helloworld exc2 exc3 spike
