#pragma once

#include <list>

#include "World.h"
#include "Procedure.h"

class SystemManager {

	std::vector<Procedure*> Systems;

public:
	void AddSystem(Procedure* procedure) {
		Systems.push_back(procedure);
	}

	void UpdateSystems(World& world) {
		for (auto system : Systems) {
			system->Update(world);
		}
	}
};