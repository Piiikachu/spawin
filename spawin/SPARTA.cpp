#include "stdafx.h"
#include "SPARTA.h"
#include <mpi.h>

using namespace SPARTA_NS;

SPARTA::SPARTA(int narg, char **arg, MPI_Comm communicator)
{
	int myid, numprocs, namelen;
	char processor_name[MPI_MAX_PROCESSOR_NAME];

	MPI_Comm_rank(MPI_COMM_WORLD, &myid);  // get current process id
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);      // get number of processes
	MPI_Get_processor_name(processor_name, &namelen);

	if (myid == 0) printf("number of processes: %d\n...", numprocs);
	printf("%s: class sparta from process %d \n", processor_name, myid);
}


SPARTA::~SPARTA()
{
}
