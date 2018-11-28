#pragma once
#ifndef SPARTA_UNIVERSE_H
#define SPARTA_UNIVERSE_H

#include "Pointers.h"

namespace SPARTA_NS {
	class Universe :
		public Pointers
	{
	public:
		//char *version;          // SPARTA version string = date

		MPI_Comm uworld;        // communicator for entire universe
		int me, nprocs;          // my place in universe

		//FILE *uscreen;          // universe screen output
		//FILE *ulogfile;         // universe logfile

		int existflag;          // 1 if universe exists due to -partition flag
		//int nworlds;            // # of worlds in universe
		//int iworld;             // which world I am in
		//int *procs_per_world;   // # of procs in each world
		//int *root_proc;         // root proc in each world

		MPI_Comm uorig;         // original communicator passed to SPARTA instance
		int *uni2orig;          // proc I in universe uworld is 
								// proc uni2orig[I] in original communicator
		Universe(class SPARTA *,MPI_Comm);
		~Universe();
	};
}

#endif // !SPARTA_UNIVERSE_H



