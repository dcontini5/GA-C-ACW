#pragma once
#include <thread>
#include <vector>
#include <map>

typedef std::map<uint32_t, std::thread> ThreadMap;


class ThreadManager {

	//Private Structors
private:
	ThreadManager() = default;
	ThreadManager(const ThreadManager&) = delete;
	ThreadManager &operator=(const ThreadManager&) = delete;

	//Public Structors
public:
	~ThreadManager();

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
	

	template<class Function, class Args>
	int AddThread(Function&& pFunction, Args&& pArgs) {

		mThreads.insert(std::pair<uint32_t, std::thread>(mID, std::thread(pFunction, pArgs)));
		return mID++;

	}

	
	//template<class Function, class Args>
	//int AddThread1(Function&& pFunction) {
	//
	//	mThreads.insert(std::pair<uint32_t, std::thread>(mID, std::thread(pFunction)));
	//
	//	return mID++;
	//
	//}
	

	void TeminateThread(uint32_t pThreadID);
	void Finish();
	
	// Private Functions
private:

	//Data:
private:
	static ThreadManager* mInstance;
	static int mID;
	ThreadMap mThreads;
	
};


