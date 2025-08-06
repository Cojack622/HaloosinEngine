#pragma once

#include "../Core/World.h"

class Procedure {
public:
	inline static int count;
	int id;

	Procedure() {
		id = count;
		Procedure::count = id + 1;
	}


	virtual void Start() {

	}


	virtual void Stop() {

	}

	virtual void Update(World& reg) = 0;

	virtual void Free() {

	}

};