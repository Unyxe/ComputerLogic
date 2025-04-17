#include "GateStore.h"

#include <sstream>

#include "StaticGateLibrary.h"
#include "Gate.h"
#include "PrimitiveGate.h"

GateStore::~GateStore() = default;

int GateStore::EmplaceGate(int gateTypeId, const GateMetaData& metaData)
{
	int gateId = std::rand() * 10000 + rand();
	return EmplaceGate(gateId, gateTypeId, metaData);
}

int GateStore::EmplaceGate(int gateId, int gateTypeId, const GateMetaData& metaData)
{
	std::string_view serializedGate = StaticGateLibrary::GetGateType(gateTypeId);
	if (StaticGateLibrary::isPrimitive(serializedGate)) {
		gateMap[gateId] = std::make_unique<PrimitiveGate>(gateTypeId);
	}
	else {
		gateMap[gateId] = std::make_unique<Gate>(serializedGate);
	}
	gateMetaDataMap[gateId] = std::make_unique<GateMetaData>(metaData);
	return gateId;
}

void GateStore::RemoveGate(int gateId)
{
	if (gateMap.find(gateId) != gateMap.end()) {
		gateMap.erase(gateId);
		gateMetaDataMap.erase(gateId);
	}
	else {
		throw std::invalid_argument("Gate ID not found in store.");
	}
}

const std::vector<int> GateStore::GetAllGateIds() const
{
	std::vector<int> gateIds;
	for (const auto& pair : gateMap) {
		gateIds.push_back(pair.first);
	}
	return gateIds;
}

std::vector<bool> GateStore::EvaluateGate(int gateId, const std::vector<bool>& input)
{
	if (gateMap.find(gateId) == gateMap.end()) {
		throw std::invalid_argument("Gate ID not found in store.");
	}
	return gateMap[gateId]->Evaluate(input);
}

std::vector<bool> GateStore::GetLastOutput(int gateId) const
{
	if (gateMap.find(gateId) != gateMap.end()) {
		return gateMap.at(gateId)->GetLastOutput();
	}
	else {
		throw std::invalid_argument("Gate ID not found in store.");
	}
}

int GateStore::GetNumberOfInputs(int gateId) const
{
	if (gateMap.find(gateId) != gateMap.end()) {
		return gateMap.at(gateId)->GetNumberOfInputs();
	}
	else {
		throw std::invalid_argument("Gate ID not found in store.");
	}
}

std::string GateStore::SerializeGates() const
{
	std::vector<int> data;

	data.push_back(static_cast<int>(gateMap.size()));
	data.push_back(2); // Assuming 2 is the number of attributes for each gate

	for (const auto& pair : gateMap) {
		int gateId = pair.first;
		int gateTypeId = pair.second->GetTypeID();
		data.push_back(gateId);
		data.push_back(gateTypeId);

		std::vector<int> metaData = gateMetaDataMap.at(gateId)->GetData();
		data.push_back(static_cast<int>(metaData.size()));
		data.insert(data.end(), metaData.begin(), metaData.end());
	}

	return StaticGateLibrary::SerializeIntVector(data);
}

int GateStore::OverwriteGatesByParsed(std::vector<int> data, int start)
{
	for (auto& pair : gateMap) {
		pair.second.reset();
	}
	gateMap.clear();

	for (auto& pair : gateMetaDataMap) {
		pair.second.reset();
	}
	gateMetaDataMap.clear();
	int numberOfGates = data[start++];
	int numberOfAttributes = data[start++];
	for (int i = 0; i < numberOfGates; i++) {
		int gateId = data[start++];
		int gateTypeId = data[start++];
		
		GateMetaData tempMetaData;
		start = tempMetaData.UpdateFromData(data, start);

		EmplaceGate(gateId, gateTypeId, tempMetaData);
	}
	return start;
}

const std::vector<int> GateStore::GetGatesData() const
{
	std::vector<int> sequentialData;
	for (const auto& pair : gateMap) {
		sequentialData.push_back(pair.first);
		sequentialData.push_back(pair.second->GetTypeID());
		sequentialData.push_back(pair.second->GetNumberOfInputs());
		sequentialData.push_back((int)pair.second->GetLastOutput().size());
		auto& metaData = gateMetaDataMap.at(pair.first)->GetData();
		sequentialData.push_back(metaData[0]);
		sequentialData.push_back(metaData[1]);
	}
	return sequentialData;
}
