#pragma once

#include <unordered_map>
#include <memory>
#include <random>
#include <vector>

#include "Gate.h"

class GateStore
{
private:
	std::unordered_map<int, std::unique_ptr<Gate>> GateMap;

public:
	GateStore() = default;
	~GateStore();

	int EmplaceGate(int gateTypeId);
	int EmplaceGate(int gateTypeId, int gateId);
	void RemoveGate(int gateId);

	std::vector<int> GetAllGateIds() const;

	std::vector<bool> EvaluateGate(int gateId, const std::vector<bool>& input);
	std::vector<bool> GetLastOutput(int gateId) const;
	int GetNumberOfInputs(int gateId) const;

	std::string SerializeGates() const;
};

