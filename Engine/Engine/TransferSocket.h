#pragma once

#include "Socket.h"
#include "chrono"

class GameObject;
typedef std::shared_ptr<GameObject> GameObjectPtr;

class TransferSocket : public Socket {

	//Structors
public:
	TransferSocket() : Socket() {}
	explicit TransferSocket(SOCKET& pSocket) : Socket(pSocket) {}
	explicit TransferSocket(SOCKET& pSocket, std::string pClientAddress) : Socket(pSocket), mClientAddress(pClientAddress) {}
	TransferSocket(const TransferSocket& pOther) = default;
	TransferSocket(TransferSocket&& pOther) noexcept = default; //exchange members here;
	~TransferSocket() = default;

	//Accessors
public:

	GameObjectPtr GetPlayer() const { return mPlayer; }
	std::string GetClientAddress() const { return mClientAddress; }
	bool IsConnected() const { return mConnected; }
	int GetSendThreadID() const { return mSendThreadID; }
	int GetReceiveThreadID() const { return mReceiveThreadID; }
	bool IsResetted() const { return mResetted; }
	std::chrono::time_point<std::chrono::high_resolution_clock> GetLastSendTime() const { return mLastTimeSend; }
	std::chrono::time_point<std::chrono::high_resolution_clock> GetLastReceiveTime() const { return mLastTimeReceive; }
	float GetAverageSend() const { return mAverageSendPerSecond;}
	
	//Mutators
public:

	void SetClient(const GameObjectPtr& pPlayer) { mPlayer = pPlayer; }
	void SetClientAddress(const std::string& pClientAddress ) {  mClientAddress = pClientAddress; }
	void SetSocket(SOCKET& pSocket) override { mResetted = mConnected = true; Socket::SetSocket(pSocket); }
	void Disconnect() override { mConnected = false; Socket::Disconnect(); }
	void ResetDone() { mResetted = false; }
	void SetSendThreadID(const int& pID) {mSendThreadID = pID; }
	void SetReceiveThreadID(const int& pID) {mReceiveThreadID = pID; }
	void SetLastSendTime(const std::chrono::time_point<std::chrono::high_resolution_clock>& pNewTime) { mLastTimeSend = pNewTime; }
	void SetLastReceiveTime(const std::chrono::time_point<std::chrono::high_resolution_clock>& pNewTime) { mLastTimeReceive = pNewTime; }
	void SetAverageSend(const float& pNewValue) { mAverageSendPerSecond = pNewValue; }
	// Public Functions
public:
		
	void Connect(const Peer& pPeer);
	void Send();
	void Receive();
	//void Send(const std::string pMessage);
	//void Receive(std::string& pMessage);
	
	// Private Functions
private:

	//Operators
public:
	TransferSocket& operator=(const TransferSocket& pOther) = delete;

	TransferSocket& operator=(const TransferSocket&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
private:

	
	GameObjectPtr mPlayer;
	std::string mClientAddress;
	bool mResetted	{false};
	bool mConnected{ false };
	int mSendThreadID{-1};
	int mReceiveThreadID{-1};
	std::chrono::time_point<std::chrono::high_resolution_clock> mLastTimeSend;
	std::chrono::time_point<std::chrono::high_resolution_clock> mLastTimeReceive;
	float mAverageSendPerSecond{0.f};
	float mAverageReceivePerSecond{0.f};
	
};
