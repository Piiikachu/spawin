#pragma once
#ifndef SPARTA_POINTERS_H
#define SPARTA_POINTERS_H
#include "SPARTA.h"
#include "spatype.h"

namespace SPARTA_NS {

	// universal defines inside namespace

#define FLERR __FILE__,__LINE__

#define MIN(A,B) ((A) < (B) ? (A) : (B))
#define MAX(A,B) ((A) > (B) ? (A) : (B))

	// roundup a char ptr to 8-byte boundary
	// roundup an int to multiple of 8

#define ROUNDUP(A) (char *) (((uint64_t) (A) + 7) & ~7);
#define IROUNDUP(A) ((((int) (A) + 7) / 8) * 8);

	class Pointers {
	public:
		Pointers(SPARTA *ptr):
			sparta(ptr),
			memory(ptr->memory),
			error(ptr->error),
			output(ptr->output),
			world(ptr->world),
			infile(ptr->infile),
			screen(ptr->screen),
			logfile(ptr->logfile),
			input(ptr->input),
			universe(ptr->universe){}
			
		virtual ~Pointers(){}

	protected:
		SPARTA *sparta;
		Memory *&memory;
		Universe *&universe;
		Error *&error;
		Output *&output;
		Input *&input;


		MPI_Comm &world;
		FILE *&infile;
		FILE *&screen;
		FILE *&logfile;

	};




}


#endif // !SPARTA_POINTERS_H
