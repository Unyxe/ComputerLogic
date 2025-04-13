#pragma once

#include <map>
#include <random>

#include "Gate.h"
#include "StaticGateLibrary.h"

class GateStore
{
private:
	std::map<int, Gate> GateMap;

public:
	GateStore() = default;

	void EmplaceGate() {
		int gateTypeId = std::rand();
		GateMap[gateTypeId] = Gate::Deserialize(StaticGateLibrary::GetGateType(gateTypeId));
	}

	std::vector<bool> EvaluateGate(int gateTypeId, std::vector<bool> input) {
		if (GateMap.find(gateTypeId) == GateMap.end()) {
			throw std::invalid_argument("Gate type not found in store.");
		}
		return GateMap[gateTypeId].Evaluate(input);
	}
};

