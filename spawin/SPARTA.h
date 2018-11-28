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

		SPARTA(int, char **,MPI_Comm);
		~SPARTA();
	};

}


#endif // !SPARTA_SPARTA_H


