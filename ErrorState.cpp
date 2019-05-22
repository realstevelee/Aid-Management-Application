// Workshop <Milestone 05>
// Name: <Sooyong Lee>
// Student #: <146074174>
// Course: OOP244 Winter 2019
// File: <ErrorState.cpp>
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include "ErrorState.h"

namespace ama {
	ErrorState::ErrorState(const char* _errorMessage) {
		if (_errorMessage == nullptr) {
			errorMessage = nullptr;
		}
		else if (_errorMessage[0] == '\0')
			errorMessage = nullptr;
		else {
			errorMessage = new char[strlen(_errorMessage) + 1];
			strcpy(errorMessage, _errorMessage);
		}
	}

	ErrorState::~ErrorState() {
		delete errorMessage;
	}

	ErrorState::operator bool() const{
		bool valid;
		if (isEmpty())
			valid = false;
		else
			valid = true;

		return valid;
	}

	ErrorState& ErrorState::operator=(const char* pText) {
		if (pText == nullptr || pText[0] == '\0')
			errorMessage = nullptr;
		else {
			delete errorMessage;
			errorMessage = new char[strlen(pText) + 1];
			message(pText);
		}
		return *this;
	}

	void ErrorState::message(const char* pText) {
		if (pText == nullptr || pText[0] == '\0') {
			errorMessage = nullptr;
		}
		else {
			delete errorMessage;
			errorMessage = new char[strlen(pText) + 1];
			strcpy(errorMessage, pText);
		}
	}

	const char* ErrorState::message() const {
		return errorMessage;
	}

	bool ErrorState::isEmpty() const {
		bool valid;

		if (errorMessage == nullptr || errorMessage[0] == '\0')
			valid = true;
		else
			valid = false;

		return valid;
	}

	std::ostream& operator<<(std::ostream& os, const ErrorState& es) {
		if (!es.isEmpty())
			os << es.message();
		return os;
	}

}