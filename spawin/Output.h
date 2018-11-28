#pragma once
#ifndef SPARTA_OUTPUT_H
#define SPARTA_OUTPUT_H
#include "Pointers.h"

namespace SPARTA_NS {
	class Output :
		public Pointers
	{
	public:
		Output(class SPARTA *);
		~Output();
	};

}
#endif // !SPARTA_OUTPUT_H


