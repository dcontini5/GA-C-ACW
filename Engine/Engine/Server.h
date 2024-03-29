﻿#pragma once
#include <unordered_map>

#include "ListenSocket.h"
#include "TransferSocket.h"
#include "NetworkingSystem.h"

#include <vector>


//struct custcom {
//
//	bool operator()(const std::string &s1, const std::string &s2) const{
//
//		return s1.back() < s2.back();
//		
//	}
//	
//};

class Server :public NetworkingSystem{

	//Structors
public:
	Server();
	~Server() { WSACleanup(); }

	//Accessors
public:

	//Mutators
public:

	// Public Functions
public:
	void Init() override;
	void Start() override;
	void Listen();
	//void AddObject(GameObjectPtr& pGameObject) override;
	//void Receive(TransferSocket& pClient)
	
	void Echo(std::string& pMessage);
	// Private Functions
private:

	//Operators
public:
	
	//Data:
private:

	typedef std::shared_ptr<TransferSocket> TransferSocketPtr;
	typedef std::map<std::string, TransferSocketPtr> ClientList;
	
	ClientList                  mClients;
	ListenSocket				mListenSocket;
	TransferSocket				mTransferSocket;
	
};
