#pragma once
#ifndef SPARTA_ERROR_H
#define SPARTA_ERROR_H

#include "Pointers.h"

namespace SPARTA_NS {
	class Error :
		public Pointers
	{
	public:
		Error(class SPARTA *);
		~Error();
		void universe_all(const char *, int, const char *);
		void universe_one(const char *, int, const char *);

		void all(const char *, int, const char *);
		void one(const char *, int, const char *);
		void warning(const char *, int, const char *, int = 1);
		void message(const char *, int, const char *, int = 1);
		void done();
	};


}
#endif // !SPARTA_ERROR_H


