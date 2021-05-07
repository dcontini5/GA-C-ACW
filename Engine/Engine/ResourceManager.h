#pragma once
#include <Windows.h>
#include <directxmath.h>
#include <vector>
#include <glm.hpp>
#include <map>
#include <memory>


class Mesh;
class Renderer;


typedef std::map<std::string, std::shared_ptr<Mesh>> MeshMap;

enum PrefabMeshes {

	SPHERE,
	PLANE,
	
};

struct SimpleVertex
{
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT4 color;
	DirectX::XMFLOAT3 normal;
	DirectX::XMFLOAT2 texCoord;
};

struct SettingList {

	std::string ServerAddress;
	std::string ClientAddress;
	int PyramidHeight;
	int Port;
	short Height;
	short Width;
	
};


class ResourceManager {

	//Private Structors
private:
	ResourceManager() = default;

	//Public Structors
public:
	~ResourceManager() = default;

	static ResourceManager* Instance(){

		if (!mInstance){
			mInstance = new ResourceManager();
		}

		return mInstance;
	}

	//Accessors
public:
	std::string GetServerAddress() const { return mSettings.ServerAddress; }
	std::string GetClientAddress() const { return mSettings.ClientAddress; }
	int GetPort() const { return mSettings.Port; }
	int GetPyramidHeight() const { return mSettings.PyramidHeight; }
	short GetWindowHeight() const { return mSettings.Height; }
	short GetWindowWidth() const { return mSettings.Width; }
	//Mutators
public:

	// Public Functions
public:

	void LoadSettings();
	void ParseMessage(std::string&);

	void LoadMesh(const PrefabMeshes& pMeshType, std::shared_ptr<Renderer>& pRenderer);
	std::shared_ptr<Mesh> GetMesh(const std::string& pName);
	void CreateSphereGeometry(std::vector<SimpleVertex>& vertices, std::vector<WORD>& indices, const int& sectorCount,
		const int& stackCount);
	
	std::vector<WORD> GenerateIndices();
	std::vector<SimpleVertex> GenerateVertices();
	int GetIndNo() const { return mIndicesNo; }
	// Private Functions
private:

	void ParseLine(std::string& line);
	

	//Data:
private:
	static ResourceManager* mInstance;
	int mIndicesNo = 0;
	MeshMap mMeshes;
	SettingList mSettings;
	//std::string  mParsedData = ""; //todo use it maybe?
	
};
