#pragma once
#include <thread>
#include <vector>
#include <map>
#include <condition_variable>
#include <mutex>
#include <shared_mutex>



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
	std::mutex& GetMutex() const { return mMutex; }
	std::condition_variable& GetConditionVariable() const { return mConditionVariable; }
	std::shared_mutex& GetSharedMutex() const { return mSharedMutex; }
	bool IsPhysicsDone() const { return mPhysicsDone; }
	void SetPhysicsDone(const bool& pNewValue) { mPhysicsDone = pNewValue; }
	//Mutators
public:

	// Public Functions
public:
	

	template<class Function, class Args>
	int AddThread(Function&& pFunction, Args&& pArgs) {
	
		mThreads.insert(std::pair<uint32_t, std::thread>(mID,
			std::thread(pFunction , pArgs)));
		return mID++;
	
	}
	
	//template<class Function, class... Args>
	//int AddThread(Function&& pFunction, Args&&... pArgs) {
	//
	//	mThreads.insert(std::pair<uint32_t, std::thread>(mID,
	//		std::thread(std::forward<Function>(pFunction) , std::forward<Args>(pArgs)...)));
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


	mutable std::condition_variable mConditionVariable;
	mutable std::mutex mMutex;
	mutable std::shared_mutex mSharedMutex;

	static bool mPhysicsDone;
	bool mCollisionDone;
	
};


