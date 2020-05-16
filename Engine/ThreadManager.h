#pragma once
#include <map>
#include <thread>

typedef std::map<unsigned int, std::thread> ThreadMap;

static unsigned int NO_OF_THREADS = 0;

class ThreadManager {

	//Private Structors
private:
	ThreadManager() = default;

	//Public Structors
public:
	~ThreadManager() = default;

	static ThreadManager* Instance(){

		if (!mInstance){ mInstance = new ThreadManager(); }

		return mInstance;
	}

	//Accessors
public:

	//Mutators
public:

	// Public Functions
public:

	// Private Functions
private:

	//Data:
private:
	static ThreadManager* mInstance;
	ThreadMap mThreads;
};
