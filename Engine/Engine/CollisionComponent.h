#pragma once

class CollisionComponent {

	//Structors
public:
	CollisionComponent();
	CollisionComponent(const CollisionComponent&);
	CollisionComponent(CollisionComponent&&); //exchange members here;
	~CollisionComponent();

	//Accessors
public:

	//Mutators
public:

	// Public Functions
public:

	// Private Functions
private:

	//Operators
public:
	CollisionComponent& operator=(const CollisionComponent& pOther){ return *this = CollisionComponent(pOther); }

	CollisionComponent& operator=(const CollisionComponent&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
private:

	bool mIsTrigger = false;
	
};
