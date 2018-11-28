#include "stdafx.h"
#include "SPARTA.h"
#include <mpi.h>
#include <string.h>
#include "Universe.h"
#include "Memory.h"
#include "Error.h"
#include "Output.h"

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
	

	output = NULL;

	screen = NULL;
	logfile = NULL;

	// parse input switches

	int inflag = 0;
	int screenflag = 0;
	int logflag = 0;
	int partscreenflag = 0;
	int partlogflag = 0;
	int kokkosflag = 0;
	int helpflag = 0;

	//suffix = NULL;
	//suffix_enable = 0;
	//packargs = NULL;
	//num_package = 0;
	//int kkfirst, kklast;

	int npack = 0;
	int *pfirst = NULL;
	int *plast = NULL;


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
	if (universe->existflag==0)
	{
		universe->add_world(NULL);
	}
	//if (!universe->consistent())
	//	error->universe_all(FLERR, "Processor partitions are inconsistent");

	// universe cannot use stdin for input file

	//if (universe->existflag && inflag == 0)
	//	error->universe_all(FLERR, "Must use -in switch with multiple partitions");

	// if no partition command-line switch, cannot use -pscreen option

	//if (universe->existflag == 0 && partscreenflag)
	//	error->universe_all(FLERR, "Can only use -pscreen with multiple partitions");

	// if no partition command-line switch, cannot use -plog option

	//if (universe->existflag == 0 && partlogflag)
	//	error->universe_all(FLERR, "Can only use -plog with multiple partitions");

	// set universe screen and logfile

	if (universe->me == 0) {
		if (screenflag == 0)
			universe->uscreen = stdout;
		else if (strcmp(arg[screenflag], "none") == 0)
			universe->uscreen = NULL;
		else {
			universe->uscreen = fopen(arg[screenflag], "w");
			if (universe->uscreen == NULL)
				error->universe_one(FLERR, "Cannot open universe screen file");
		}
		if (logflag == 0) {
			universe->ulogfile = fopen("log.sparta", "w");
			if (universe->ulogfile == NULL)
				error->universe_one(FLERR, "Cannot open log.sparta");
		}
		else if (strcmp(arg[logflag], "none") == 0)
			universe->ulogfile = NULL;
		else {
			universe->ulogfile = fopen(arg[logflag], "w");
			if (universe->ulogfile == NULL)
				error->universe_one(FLERR, "Cannot open universe log file");
		}
	}

}


SPARTA::~SPARTA()
{
}
