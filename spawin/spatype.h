#pragma once
#ifndef SPARTA_SPTYPE_H
#define SPARTA_SPTYPE_H

#define __STDC_LIMIT_MACROS
#define __STDC_FORMAT_MACROS

#include "limits.h"
#include "stdint.h"
#include "inttypes.h"

// grrr - IBM Power6 does not provide this def in their system header files

#ifndef PRId64
#define PRId64 "ld"
#endif

namespace SPARTA_NS {

	// enum used for KOKKOS host/device flags

	enum ExecutionSpace { Host, Device };

	// default settings: 32-bit smallint, 64-bit bigint, 32-bit cellint

#if !defined(SPARTA_SMALL) && !defined(SPARTA_BIG) && !defined(SPARTA_BIGBIG)
#define SPARTA_BIG
#endif

	// allow user override of LONGLONG to LONG, necessary for some machines/MPI

#ifdef SPARTA_LONGLONG_TO_LONG
#define MPI_LL MPI_LONG
#define ATOLL atoll
#else
#define MPI_LL MPI_LONG_LONG
#define ATOLL atol
#endif

	// default, sufficient for problems with up to 2B grid cells
	// 32-bit smallint, 64-bit bigint, 32-bit cellint

#ifdef SPARTA_BIG

	typedef int smallint;
	typedef int cellint;
	typedef int64_t bigint;

#define MAXSMALLINT INT_MAX
#define MAXBIGINT INT64_MAX
#define MPI_SPARTA_BIGINT MPI_LL
#define CELLINT_FORMAT "%d"
#define BIGINT_FORMAT "%" PRId64
#define ATOCELLINT atoi
#define ATOBIGINT ATOLL

#endif

	// for problems with more than 2B grid cells
	// 32-bit smallint, 64-bit bigint, 64-bit cellint

#ifdef SPARTA_BIGBIG

	typedef int smallint;
	typedef int64_t cellint;
	typedef int64_t bigint;

#define MAXSMALLINT INT_MAX
#define MAXBIGINT INT64_MAX
#define MPI_SPARTA_BIGINT MPI_LL
#define CELLINT_FORMAT "%" PRId64
#define BIGINT_FORMAT "%" PRId64
#define ATOCELLINT ATOLL
#define ATOBIGINT ATOLL

#endif

	// for machines that do not support 64-bit ints
	// 32-bit smallint and bigint and cellint

#ifdef SPARTA_SMALL

	typedef int smallint;
	typedef int cellint;
	typedef int bigint;

#define MAXSMALLINT INT_MAX
#define MAXBIGINT INT_MAX
#define MPI_SPARTA_BIGINT MPI_INT
#define CELLINT_FORMAT "%d"
#define BIGINT_FORMAT "%d"
#define ATOCELLINT atoi
#define ATOBIGINT atoi

#endif

}

// settings to enable SPARTA to build under Windows

#endif