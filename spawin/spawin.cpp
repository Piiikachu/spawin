// spawin.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#include<time.h>
#include "SPARTA.h"
using namespace SPARTA_NS;

int main(int argc, char** argv)
{
	MPI_Init(&argc, &argv);        // starts MPI

	SPARTA *sparta = new SPARTA(argc, argv, MPI_COMM_WORLD);


	delete sparta;


	MPI_Finalize();

	return 0;
}

