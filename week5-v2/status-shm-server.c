/*
 * Shared Memory Server Process as per D.A. Curry `Using C on the Unix System'
 * shm-server-test.c
 * Author: C. Kopp
 * (c) 2004, Monash University, SCCSE
 *
 * $Id: status-shm-server.c,v 1.2 2015/08/17 06:53:03 carlo Exp carlo $
 *
 */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "segment-lock.h"

int get_client_number(int num){
	int power = 0;
	while(num != 0){
		num /= 2;
		power++;
	}
	return power;
}

int main()
{
	char
		ident[] = "\n$Id: status-shm-server.c, Arvin Wiyono 16/08/2016";
	int
		up = 0, shmid;
	key_t
		mykey;
	void *
    	shmat(int shmid, const void *addr, int flag);
	int
		shmdt(const void *shmaddr);
	SEG_DATA
		*shm, *mydata;

	/*
	 * The shared memory segment is identified by SEGMENTID
	 */
	mykey = SEGMENTID;

	/*
	 * here we create the shared memory segment using the `shmget' system call.
     * - for debugging remove the IPC_EXCL flag - `IPC_CREAT | IPC_EXCL | 0666'
	 */

	if( (shmid = shmget( mykey, sizeof(SEG_DATA), IPC_CREAT | 0666)) < 0 )
		{
		perror("shmget: cannot create shared memory segment; exiting now");
		exit(1);
		}

	/*
	 * We must now map the segment into our process address space using the
	 * `shmat' [attach] system call.
	 */

	if( (shm = (SEG_DATA *)shmat( shmid, NULL, 0)) == ((SEG_DATA *)-1) )
		{
		perror("shmat: cannot attach shared memory segment; exiting now");
		exit(1);
		}

	int exit_status = 0;
	// Get exit status from sum of client IDs
	for(int i = 0; i < 4; i++){
		exit_status += clients[i];
	}

	/*
	 * Initialise values in segment
	 */
	mydata = (SEG_DATA *)shm;
	mydata->mylock = 0;
	mydata->exit = 0;
	mydata->rpm = 3500;
	mydata->crankangle = 0;
	mydata->throttle = 70;
	mydata->fuelflow = 50;
	mydata->temp = 80;
	mydata->fanspeed = 30;
	mydata->oilpres = 70;
	printf("%s\n", ident);
	while( mydata->exit != exit_status ){
		if ( up == 1 && mydata->rpm > 6500 ) up = 0; /* cycle values */
		if ( up == 0 && mydata->rpm < 500 ) up = 1;
		if ( up == 1 ){
			mydata->rpm += 100;
			mydata->crankangle += 1;
			mydata->crankangle %= 360;
			mydata->throttle += 1;
			mydata->throttle %= 100;
			mydata->fuelflow += 1;
			mydata->fuelflow %= 100;
			mydata->temp += 1;
			mydata->temp %= 100;
			mydata->fanspeed += 1;
			mydata->fanspeed %= 100;
			mydata->oilpres += 1;
			mydata->oilpres %= 100;
		} else {
			mydata->rpm -= 100;
			mydata->crankangle -= 1;
			mydata->crankangle %= 360;
			mydata->throttle -= 1;
			mydata->throttle %= 100;
			mydata->fuelflow -= 1;
			mydata->fuelflow %= 100;
			mydata->temp -= 1;
			mydata->temp %= 100;
			mydata->fanspeed -= 1;
			mydata->fanspeed %= 100;
			mydata->oilpres -= 1;
			mydata->oilpres %= 100;
		}
		sleep(1);
		fprintf(stdout, "\nSTATUS DUMP\n");
		fprintf(stdout, "Lock             = %d\n", mydata->mylock );
		fprintf(stdout, "Present          = %d\n", mydata->present );
		fprintf(stdout, "UP Status        = %d\n", up );
		fprintf(stdout, "Exit Status      = %d\n", mydata->exit );
		fprintf(stdout, "RPM              = %d\n", mydata->rpm );
		fprintf(stdout, "Crank Angle      = %d\n", mydata->crankangle );
		fprintf(stdout, "Throttle Setting = %d\n", mydata->throttle );
		fprintf(stdout, "Fuel Flow        = %d\n", mydata->fuelflow );
		fprintf(stdout, "Engine Temp      = %d\n", mydata->temp );
		fprintf(stdout, "Fan Speed        = %d\n", mydata->fanspeed );
		fprintf(stdout, "Oil Pressure     = %d\n", mydata->oilpres );
		if(mydata->mylock > 0){
			fprintf(stdout, "Getting locked by CLIENT #%d\n", get_client_number(mydata->mylock));
		}
		else{
			fprintf(stdout, "Waiting for client\n");
		}
	}

	/*
	 * We must now unmap the segment into our process address space using the
	 * `shmdt' [detach] system call.
	 */

	if( (shmid = shmdt( shm )) == (-1) )
		{
		perror("shmdt: cannot detach shared memory segment; exiting now");
		exit(1);
		}

	fprintf(stdout, "Task completed\n");
	exit(0);

}
