//#include "pch.h"
#include "ThreadManager.h"
ThreadManager* ThreadManager::mInstance = nullptr;
int ThreadManager::mID = 0;


ThreadManager::~ThreadManager(){

	for(auto i = mThreads.begin(); i!=mThreads.end(); i++){

		i->second.join();
		
	}

	mThreads.clear();
	delete mInstance;
	
}

void ThreadManager::TeminateThread(uint32_t pThreadID){

	auto thread = mThreads.find(pThreadID);

	if(thread != mThreads.end()){

		thread->second.join();
		mThreads.erase(thread);
		
	}
}
