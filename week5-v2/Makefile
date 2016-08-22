#
# Makefile for Prac 2
# (c) 2004, Carlo Kopp, Monash University, SCSSE
#
# $Id: Makefile,v 1.6 2004/03/21 17:45:56 carlo Exp $
#

CC = gcc
AS = as
LD = $(CC)

#
CFLAGS = -g -Wall
# -Wall
LDFLAGS = -g -lm -Wall
INCLUDES = .

#rules
.c.s:
	$(CC) -c -$(CFLAGS) -I $(INCLUDES) $<

.c.o:
	$(CC) -c $(CFLAGS) -I $(INCLUDES) $<


#
# Student files
#
MYSERVER = status-server
MYCLIENT = 24282588-client
MYCOBJS = 24282588-shm-client-writing-lock.o
MYSOBJS = status-shm-server.o
MYSRC = 24282588-shm-client-writing-lock.c status-shm-server.c

student: $(MYSOBJS) $(MYCOBJS) $(MYUTILOBJS)
	$(LD) $(LDFLAGS) -o $(MYSERVER) $(MYSOBJS)
	$(LD) $(LDFLAGS) -o $(MYCLIENT) $(MYCOBJS)

myserver: $(MYSOBJS)
	$(LD) $(LDFLAGS) -o $(MYSERVER) $(MYSOBJS)

24282588-shm-client.o:  24282588-shm-client-writing-lock.c
status-shm-server.o:	status-shm-server.c

checkin:
	echo "check in files ..."
	ci -l  \
	$(SRC) $(MYSRC) $(INCS) Makefile

clean:
	echo "cleaning up ..."
	rm -f *core
	rm -f $(MYSERVER) $(MYSOBJS) $(MYCLIENT) $(MYCOBJS)
