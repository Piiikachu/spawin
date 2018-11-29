#pragma once
#ifndef SPARTA_SPARTA_H
#define SPARTA_SPARTA_H
#include <mpi.h>

namespace SPARTA_NS {
	class SPARTA
	{
	public:
		class Universe *universe;
		class Memory *memory;
		class Error *error;
		class Input *input;


		class Output *output;

		MPI_Comm world;                // MPI communicator
		FILE *infile;                  // infile
		FILE *screen;                  // screen output
		FILE *logfile;                 // logfile

		SPARTA(int, char **,MPI_Comm);
		~SPARTA();
		void create();
		//void post_create();
		//void init();
		void destroy();

		void print_styles();
	};

}


#endif // !SPARTA_SPARTA_H


