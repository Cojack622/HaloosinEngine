#pragma once

#include "../Core/World.h"
#include "../Core/Procedure.h"

#include <vector>


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