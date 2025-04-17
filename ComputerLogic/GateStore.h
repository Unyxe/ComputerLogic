#pragma once

#include <unordered_map>
#include <memory>
#include <random>
#include <vector>

#include "Gate.h"
#include "GateMetaData.h"

class GateStore
{
private:
	std::unordered_map<int, std::unique_ptr<Gate>> gateMap;
	std::unordered_map<int, std::unique_ptr<GateMetaData>> gateMetaDataMap;

public:
	GateStore() = default;
	~GateStore();

	int EmplaceGate(int gateTypeId, const GateMetaData& metaData);
	int EmplaceGate(int gateTypeId, int gateId, const GateMetaData& metaData);
	void RemoveGate(int gateId);

	const std::vector<int> GetAllGateIds() const;

	std::vector<bool> EvaluateGate(int gateId, const std::vector<bool>& input);
	std::vector<bool> GetLastOutput(int gateId) const;
	int GetNumberOfInputs(int gateId) const;

	std::string SerializeGates() const;

	int OverwriteGatesByParsed(std::vector<int> data, int start);

	const std::vector<int> GetGatesData() const;
};

