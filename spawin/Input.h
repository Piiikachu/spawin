#pragma once
#ifndef SPARTA_INPUT_H
#define SPARTA_INPUT_H
#include "Pointers.h"
namespace SPARTA_NS {
	class Input :
		public Pointers
	{
	public:
		Input(class SPARTA *, int, char **);
		~Input();
	};
}


#endif // !SPARTA_INPUT_H



