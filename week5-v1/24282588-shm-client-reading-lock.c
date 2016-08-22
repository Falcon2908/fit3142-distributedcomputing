/*
 * Shared Memory Client Process as per D.A. Curry `Using C on the Unix System'
 * shm-clinet-test.c
 * Author: Arvin Wiyono
 * 16/08/2016
 */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "segment-lock.h"

int main()
{
	int
		myexit,
		shmid;
	key_t
		mykey;
	void *
    	shmat(int shmid, const void *addr, int flag);
	int
		shmdt(const void *shmaddr);
	SEG_DATA
		*shm, *mydata;

	int client_number;
	fprintf(stdout, "Enter client number: ");
	scanf("%d", &client_number);
	if(client_number > 4 || client_number < 1){
		fprintf(stdout, "Client number is invalid. Only accept a number between 1 to 4!\n");
		exit(1);
	}

	int client_id = clients[client_number-1];

	/*
	 * The shared memory segment is identified by SEGMENTID
	 */
	mykey = SEGMENTID;

	/*
	 * Here we create the shared memory segment using the `shmget' system call.
	 */
	if( ( shmid = shmget( mykey, sizeof(SEG_DATA), 0666 ) ) < 0){
		perror("shmget: cannot find shared memory segment; exiting now");
		exit(1);
	}
	fprintf(stdout, "shmget: %d\n", shmid);
	/*
	 * We must now map the segment into our process address space using the
	 * `shmat' [attach] system call.
	 */
	 if((shm = (SEG_DATA*) shmat(shmid, NULL, 0)) == ((SEG_DATA*)-1)){
		 perror("shmat: cannot attach shared memory segment; exiting now");
		 exit(1);
	 }
	 fprintf(stdout, "shmat: attaching shared memory segement successful\n");
	/*
	 * Test Code - read from segment
	 */

	 mydata = shm;

	 // Toggle the present bit
	 if((mydata->present & client_id) == 0){
		 mydata->present ^= client_id;
	 }

	 fprintf(stdout, "Reading from Server Process SHM\n");
	 myexit = 0;
	 while(!(myexit == 1)){

		 while(mydata->mylock > 0){
			 fprintf(stdout, "Waiting for resource...\n");
			 sleep(1);
		 }
		 // Set lock
		 mydata->mylock ^= client_id;

		 // Print all properties of SEG_DATA
		 fprintf(stdout, "\nCLIENT #%d - STATUS DUMP\n", client_number);
		 fprintf(stdout, "Lock             = %d\n", mydata->mylock );
 		 fprintf(stdout, "Present          = %d\n", mydata->present );
		 fprintf(stdout, "Exit Status      = %d\n", mydata->exit );
		 fprintf(stdout, "RPM              = %d\n", mydata->rpm );
		 fprintf(stdout, "Crank Angle      = %d\n", mydata->crankangle );
		 fprintf(stdout, "Throttle Setting = %d\n", mydata->throttle );
		 fprintf(stdout, "Fuel Flow        = %d\n", mydata->fuelflow );
		 fprintf(stdout, "Engine Temp      = %d\n", mydata->temp );
		 fprintf(stdout, "Fan Speed        = %d\n", mydata->fanspeed );
		 fprintf(stdout, "Oil Pressure     = %d\n", mydata->oilpres );
		 // Sleep is added to give a real feel of utilizing resource
		 sleep(3);

		 // Unlock resource
		 fprintf(stdout, "Unlocking resource\n");
		 mydata->mylock ^= client_id;

		 myexit = 1000;
		 while(!(myexit > -1 && myexit < 2)){

			 // Get user input
			 printf("\nEnter (1) to exit OR (0) to continue: ");
			 scanf("%d", &myexit);
		 }
	 }

	 // Set present bit to 0
	 mydata->present ^= client_id;

	 // Toggling exit status to 1
	 if((mydata->exit & client_id) != 1)
	 	mydata->exit ^= client_id;

	/*
	 * We must now unmap the segment into our process address space using the
	 * `shmdt' [detach] system call.
	 */
	 if( (shmid = shmdt( shm )) == (-1) ){
 		perror("shmdt: cannot detach shared memory segment; exiting now");
 		exit(1);
	 }

	fprintf(stdout, "Task completed\n");
	exit(0);

}
