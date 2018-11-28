#include "stdafx.h"
#include "Universe.h"

using namespace SPARTA_NS;



Universe::Universe(SPARTA *sparta,MPI_Comm communicator):Pointers(sparta)
{
	printf("Universe initialised\n");
}


Universe::~Universe()
{
}
