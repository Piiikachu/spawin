#include "stdafx.h"
#include "Universe.h"
#include "Memory.h"
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#include "version.h"

using namespace SPARTA_NS;



Universe::Universe(SPARTA *sparta,MPI_Comm communicator):Pointers(sparta)
{
	printf("Universe initialised\n");

	version = (char *)SPARTA_VERSION;

	uworld = uorig = communicator;
	MPI_Comm_rank(uworld, &me);
	MPI_Comm_size(uworld, &nprocs);

	uscreen = stdout;
	ulogfile = NULL;

	existflag = 0;
	nworlds = 0;
	procs_per_world = NULL;
	root_proc = NULL;


	memory->create(uni2orig, nprocs, "universe:uni2orig");
	for (int i = 0; i < nprocs; i++)
	{
		uni2orig[i] = i;
	}
}


Universe::~Universe()
{
	if (uworld != uorig) MPI_Comm_free(&uworld);
	memory->destroy(procs_per_world);
	memory->destroy(root_proc);
	memory->destroy(uni2orig);
}

void Universe::add_world(char *str)
{
	int n, nper;
	char *ptr;

	if (str == NULL) {
		n = 1;
		nper = nprocs;
	}
	else if ((ptr = strchr(str, 'x')) != NULL) {
		*ptr = '\0';
		n = atoi(str);
		nper = atoi(ptr + 1);
	}
	else {
		n = 1;
		nper = atoi(str);
	}

	memory->grow(procs_per_world, nworlds + n, "universe:procs_per_world");
	memory->grow(root_proc, (nworlds + n), "universe:root_proc");

	for (int i = 0; i < n; i++) {
		procs_per_world[nworlds] = nper;
		if (nworlds == 0) root_proc[nworlds] = 0;
		else
			root_proc[nworlds] = root_proc[nworlds - 1] + procs_per_world[nworlds - 1];
		if (me >= root_proc[nworlds]) iworld = nworlds;
		nworlds++;
	}
}


/* ----------------------------------------------------------------------
check if total procs in all worlds = procs in universe
------------------------------------------------------------------------- */

int Universe::consistent()
{
	int n = 0;
	for (int i = 0; i < nworlds; i++) n += procs_per_world[i];
	if (n == nprocs) return 1;
	else return 0;
}