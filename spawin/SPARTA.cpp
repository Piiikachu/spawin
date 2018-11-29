#include "stdafx.h"
#include "SPARTA.h"
#include <mpi.h>
#include <string.h>
#include "Universe.h"
#include "Memory.h"
#include "Error.h"
#include "Output.h"
#include "Input.h"

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
	if (universe->me > 0) {
		if (screenflag == 0) universe->uscreen = stdout;
		else universe->uscreen = NULL;
		universe->ulogfile = NULL;
	}
	// make universe and single world the same, since no partition switch
	// world inherits settings from universe
	// set world screen, logfile, communicator, infile
	// open input script if from file

	if (universe->existflag == 0) {
		screen = universe->uscreen;
		logfile = universe->ulogfile;
		world = universe->uworld;
		infile = NULL;

		if (universe->me == 0) {
			if (inflag == 0) infile = stdin;
			else infile = fopen(arg[inflag], "r");
			if (infile == NULL) {
				char str[128];
				sprintf(str, "Cannot open input script %s", arg[inflag]);
				error->one(FLERR, str);
			}
		}

		if (universe->me == 0) {
			if (screen) fprintf(screen, "SPARTA (%s)\n", universe->version);
			if (logfile) fprintf(logfile, "SPARTA (%s)\n", universe->version);
		}

		// universe is one or more worlds, as setup by partition switch
		// split universe communicator into separate world communicators
		// set world screen, logfile, communicator, infile
		// open input script

	}
	else {
		int me;
		MPI_Comm_split(universe->uworld, universe->iworld, 0, &world);
		MPI_Comm_rank(world, &me);

		if (me == 0)
			if (partscreenflag == 0)
				if (screenflag == 0) {
					char str[32];
					sprintf(str, "screen.%d", universe->iworld);
					screen = fopen(str, "w");
					if (screen == NULL) error->one(FLERR, "Cannot open screen file");
				}
				else if (strcmp(arg[screenflag], "none") == 0)
					screen = NULL;
				else {
					char str[128];
					sprintf(str, "%s.%d", arg[screenflag], universe->iworld);
					screen = fopen(str, "w");
					if (screen == NULL) error->one(FLERR, "Cannot open screen file");
				}
			else if (strcmp(arg[partscreenflag], "none") == 0)
				screen = NULL;
			else {
				char str[128];
				sprintf(str, "%s.%d", arg[partscreenflag], universe->iworld);
				screen = fopen(str, "w");
				if (screen == NULL) error->one(FLERR, "Cannot open screen file");
			}
		else screen = NULL;

		if (me == 0)
			if (partlogflag == 0)
				if (logflag == 0) {
					char str[32];
					sprintf(str, "log.sparta.%d", universe->iworld);
					logfile = fopen(str, "w");
					if (logfile == NULL) error->one(FLERR, "Cannot open logfile");
				}
				else if (strcmp(arg[logflag], "none") == 0)
					logfile = NULL;
				else {
					char str[128];
					sprintf(str, "%s.%d", arg[logflag], universe->iworld);
					logfile = fopen(str, "w");
					if (logfile == NULL) error->one(FLERR, "Cannot open logfile");
				}
			else if (strcmp(arg[partlogflag], "none") == 0)
				logfile = NULL;
			else {
				char str[128];
				sprintf(str, "%s.%d", arg[partlogflag], universe->iworld);
				logfile = fopen(str, "w");
				if (logfile == NULL) error->one(FLERR, "Cannot open logfile");
			}
		else logfile = NULL;

		if (me == 0) {
			infile = fopen(arg[inflag], "r");
			if (infile == NULL) {
				char str[128];
				sprintf(str, "Cannot open input script %s", arg[inflag]);
				error->one(FLERR, str);
			}
		}
		else infile = NULL;

		// screen and logfile messages for universe and world

		if (universe->me == 0) {
			if (universe->uscreen) {
				fprintf(universe->uscreen, "SPARTA (%s)\n", universe->version);
				fprintf(universe->uscreen, "Running on %d partitions of processors\n",
					universe->nworlds);
			}
			if (universe->ulogfile) {
				fprintf(universe->ulogfile, "SPARTA (%s)\n", universe->version);
				fprintf(universe->ulogfile, "Running on %d partitions of processors\n",
					universe->nworlds);
			}
		}

		if (me == 0) {
			if (screen) {
				fprintf(screen, "SPARTA (%s)\n", universe->version);
				fprintf(screen, "Processor partition = %d\n", universe->iworld);
			}
			if (logfile) {
				fprintf(logfile, "SPARTA (%s)\n", universe->version);
				fprintf(logfile, "Processor partition = %d\n", universe->iworld);
			}
		}
	}
	// check datatype settings in spatype.h

	if (sizeof(smallint) != sizeof(int))
		error->all(FLERR, "Smallint setting in spatype.h is invalid");
	if (sizeof(bigint) < sizeof(smallint))
		error->all(FLERR, "Bigint setting in spatype.h is invalid");

	int mpisize;
	MPI_Type_size(MPI_SPARTA_BIGINT, &mpisize);
	if (mpisize != sizeof(bigint))
		error->all(FLERR,
			"MPI_SPARTA_BIGINT and bigint in spatype.h "
			"are not compatible");

	if (sizeof(smallint) != 4 || sizeof(bigint) != 8)
		error->all(FLERR, "Small,big integers are not sized correctly");




	input = new Input(this, narg, arg);


}


SPARTA::~SPARTA()
{
}
