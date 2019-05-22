// Workshop <Milestone 05>
// Name: <Sooyong Lee>
// Student #: <146074174>
// Course: OOP244 Winter 2019
// File: <ErrorState.h>
#include <iostream>

#ifndef ERRORSTATE_H
#define ERRORSTATE_H

namespace ama {
	class ErrorState {
		char * errorMessage;
	public:
		explicit ErrorState(const char* errorMessage = nullptr);
		ErrorState(const ErrorState& other) = delete;
		ErrorState& operator=(const ErrorState& other) = delete;
		~ErrorState();
		operator bool() const;
		ErrorState& operator=(const char* pText);
		void message(const char* pText);
		const char* message() const;
		bool isEmpty() const;
	};

	std::ostream& operator<<(std::ostream& os, const ErrorState& es);
}

#endif