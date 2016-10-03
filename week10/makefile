all: helloworld exc2 exc3 exc4 spike

helloworld: helloworld.c
	mpicc -o helloworld helloworld.c

exc2: exc2.c
	mpicc -o exc2 exc2.c

exc3: exc3.c
	mpicc -o exc3 exc3.c

exc4: exc4.c
	mpicc -o exc4 exc4.c

spike: spike.c
	mpicc -o spike spike.c

clean:
	rm -f helloworld exc2 exc3 exc4 spike
