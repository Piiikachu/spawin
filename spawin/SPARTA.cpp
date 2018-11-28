#include "stdafx.h"
#include "SPARTA.h"
#include <mpi.h>
#include <string.h>
#include "Universe.h"
#include "Memory.h"

using namespace SPARTA_NS;

SPARTA::SPARTA(int narg, char **arg, MPI_Comm communicator)
{
#pragma region Output
	int myid, numprocs, namelen;
	char processor_name[MPI_MAX_PROCESSOR_NAME];

	MPI_Comm_rank(MPI_COMM_WORLD, &myid);  // get current process id
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);      // get number of processes
	MPI_Get_processor_name(processor_name, &namelen);

	if (myid == 0) printf("number of processes: %d\n...\n", numprocs);
	printf("%s: class sparta from process %d \n", processor_name, myid);
#pragma endregion

	memory = new Memory(this); 
	universe = new Universe(this, communicator);
	

	int inflag = 0;


	int iarg = 1;
	while (iarg<narg)
	{
		if (strcmp(arg[iarg], "-in") == 0 ||
			strcmp(arg[iarg], "-i") == 0) {
			if (iarg + 2 > narg)
				//error->universe_all(FLERR, "Invalid command-line argument");
				printf("Invalid command-line argument\n");
			inflag = iarg + 1;
			iarg += 2;
		}
	}





}


SPARTA::~SPARTA()
{
}
