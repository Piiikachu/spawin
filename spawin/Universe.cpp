#include "stdafx.h"
#include "Universe.h"
#include "Memory.h"

using namespace SPARTA_NS;



Universe::Universe(SPARTA *sparta,MPI_Comm communicator):Pointers(sparta)
{
	printf("Universe initialised\n");

	uworld = uorig = communicator;
	MPI_Comm_rank(uworld, &me);
	MPI_Comm_size(uworld, &nprocs);

	existflag = 0;
	memory->create(uni2orig, nprocs, "universe:uni2orig");
	for (int i = 0; i < nprocs; i++)
	{
		uni2orig[i] = i;
	}
}


Universe::~Universe()
{
	if (uworld != uorig) MPI_Comm_free(&uworld);
	/*memory->destroy(procs_per_world);
	memory->destroy(root_proc);*/
	memory->destroy(uni2orig);
}
