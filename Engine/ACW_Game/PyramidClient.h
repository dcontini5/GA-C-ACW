#pragma once
#include "Client.h"
#include "Game.h"
#include "PlayerUpdateInfo.h"
#include "PyramidGame.h"

//typedef std::unique_ptr<GameObject> GameObjectUPtr;



class PyramidClient : public Client {

	//Structors
public:
	PyramidClient():Client(), mGameState(PyramidGame::GetGameState()){}
	PyramidClient(const PyramidClient&);
	PyramidClient(PyramidClient&&); //exchange members here;
	~PyramidClient() = default;

	//Accessors
public:
	//PlayerUpdateInfo GetPlayerUpdateInfo()
	
	//Mutators
public:

	
	// Public Functions
public:

	void CreateMessage(std::string& pMessage, const std::shared_ptr<TransferSocket>& pTransferSocket) override;
	void ParseMessage(std::string& pMessage, const std::shared_ptr<TransferSocket>& pTransferSocket) override;
	
	// Private Functions
private:
	void UpdateScene(const std::shared_ptr<TransferSocket>& pTransferSocket);
	void UpdateGameObjects(std::string& pUpdate);
	void UpdatePlayer( std::string& pUpdate);
	//Operators
public:
	PyramidClient& operator=(const PyramidClient& pOther) = default;

	PyramidClient& operator=(const PyramidClient&& pOther){

		/*Swap Members Here*/
		return *this;
	}


	//Data:
private:

	std::vector<GameObjectPtr> mGameObjectsUpdated;
	std::shared_ptr<GameState> mGameState;
};


