#include "GateStore.h"

#include <sstream>

#include "StaticGateLibrary.h"
#include "Gate.h"
#include "PrimitiveGate.h"

GateStore::~GateStore() = default;

int GateStore::EmplaceGate(int gateTypeId)
{
	int gateId = std::rand() * 10000 + rand();
	return EmplaceGate(gateTypeId, gateId);
}

int GateStore::EmplaceGate(int gateTypeId, int gateId)
{
	std::string_view serializedGate = StaticGateLibrary::GetGateType(gateTypeId);
	if (StaticGateLibrary::isPrimitive(serializedGate)) {
		GateMap[gateId] = std::make_unique<PrimitiveGate>(gateTypeId);
	}
	else {
		GateMap[gateId] = std::make_unique<Gate>(serializedGate);
	}
	return gateId;
}

void GateStore::RemoveGate(int gateId)
{
	if (GateMap.find(gateId) != GateMap.end()) {
		GateMap.erase(gateId);
	}
	else {
		throw std::invalid_argument("Gate ID not found in store.");
	}
}

std::vector<int> GateStore::GetAllGateIds() const
{
	std::vector<int> gateIds;
	for (const auto& pair : GateMap) {
		gateIds.push_back(pair.first);
	}
	return gateIds;
}

std::vector<bool> GateStore::EvaluateGate(int gateId, const std::vector<bool>& input)
{
	if (GateMap.find(gateId) == GateMap.end()) {
		throw std::invalid_argument("Gate ID not found in store.");
	}
	return GateMap[gateId]->Evaluate(input);
}

std::vector<bool> GateStore::GetLastOutput(int gateId) const
{
	if (GateMap.find(gateId) != GateMap.end()) {
		return GateMap.at(gateId)->GetLastOutput();
	}
	else {
		throw std::invalid_argument("Gate ID not found in store.");
	}
}

int GateStore::GetNumberOfInputs(int gateId) const
{
	if (GateMap.find(gateId) != GateMap.end()) {
		return GateMap.at(gateId)->GetNumberOfInputs();
	}
	else {
		throw std::invalid_argument("Gate ID not found in store.");
	}
}

std::string GateStore::SerializeGates() const
{
	std::stringstream serializedGates;

	serializedGates << "[";
	for (const auto& pair : GateMap) {
		int gateId = pair.first;
		int gateTypeId = pair.second->GetTypeID();
		serializedGates <<"{" << gateTypeId << "," << gateId << ",}";
	}
	serializedGates << "]";

	return serializedGates.str();
}
