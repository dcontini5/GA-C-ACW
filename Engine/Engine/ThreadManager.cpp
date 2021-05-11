//#include "pch.h"
#include "ThreadManager.h"
ThreadManager* ThreadManager::mInstance = nullptr;
int ThreadManager::mID = 0;
bool ThreadManager::mPhysicsDone = false;
bool ThreadManager::mCollisionsDone = false;
bool ThreadManager::mRenderPaused = true;
bool ThreadManager::mPhysicsPaused = false;
//bool ThreadManager::mCollisionDone = true;

ThreadManager::~ThreadManager(){


	delete mInstance;
	
}

void ThreadManager::TeminateThread(uint32_t pThreadID){

	auto thread = mThreads.find(pThreadID);

	if(thread != mThreads.end()){

		thread->second.join();
		mThreads.erase(thread);
		
	}
}

void ThreadManager::DetachThread(uint32_t pThreadID){

	auto thread = mThreads.find(pThreadID);

	if(thread != mThreads.end()){

		thread->second.detach();
		mThreads.erase(thread);
		
	}
}

void ThreadManager::Finish(){

	for (auto i = mThreads.begin(); i != mThreads.end(); ++i) {

		i->second.join();

	}

	mThreads.clear();
	
}
