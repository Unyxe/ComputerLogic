#include "WireStore.h"

#include "StaticGateLibrary.h"

#include <sstream>

int WireStore::EmplaceWire(int objId1, int objId2, int index1, int index2)
{
	int wireId = static_cast<int>(std::hash<int>()(objId1 + index1) ^ std::hash<int>()(objId2 + index2));
	wireMap[wireId] = std::make_unique<Wire>(objId1, objId2, index1, index2);
	return wireId;
}

void WireStore::RemoveWire(int objId1, int objId2, int index1, int index2)
{
	int wireId = static_cast<int>(std::hash<int>()(objId1 + index1) ^ std::hash<int>()(objId2 + index2));
	if (wireMap.find(wireId) != wireMap.end()) {
		wireMap.erase(wireId);
	}
	else {
		throw std::invalid_argument("Wire ID not found in store.");
	}
}

void WireStore::RemoveWireCascade(int objId)
{
	for (auto& wire : wireMap) {
		if (wire.second->GetObjId1() == objId || wire.second->GetObjId2() == objId) {
			wireMap.erase(wire.first);
		}
	}
}

bool WireStore::GetWiresCombinedStateByOutput(int outputObjectID, int index)
{
	for (const auto& wire : wireMap) {
		if (wire.second->GetObjId2() == outputObjectID && wire.second->GetIndex2() == index && wire.second->GetState()) {
			return true;
		}
	}
	return false;
}

void WireStore::SetWiresStateByInput(int inputObjectID, int index, bool state)
{
	for (auto& wire : wireMap) {
		if (wire.second->GetObjId1() == inputObjectID && wire.second->GetIndex1() == index) {
			wire.second->SetState(state);
		}
	}
}

std::string WireStore::SerializeWires() const
{
	std::vector<int> data;

	data.push_back(static_cast<int>(wireMap.size()));
	data.push_back(5); // Assuming 6 is the number of attributes for each wire

	for (const auto& wire : wireMap) {
		data.push_back(wire.first);
		data.push_back(wire.second->GetObjId1());
		data.push_back(wire.second->GetObjId2());
		data.push_back(wire.second->GetIndex1());
		data.push_back(wire.second->GetIndex2());
	}

	return StaticGateLibrary::SerializeIntVector(data);
}

const std::vector<int> WireStore::GetWiresData() const
{
	std::vector<int> sequentialData;
	for (const auto& wire : wireMap) {
		sequentialData.push_back(wire.first);
		sequentialData.push_back(wire.second->GetState());
		sequentialData.push_back(wire.second->GetObjId1());
		sequentialData.push_back(wire.second->GetObjId2());
		sequentialData.push_back(wire.second->GetIndex1());
		sequentialData.push_back(wire.second->GetIndex2());
	}
	return sequentialData;
}

std::vector<int> WireStore::OverwriteWiresByParsed(std::vector<int> data, int start)
{
	wireMap.clear();
	int numberOfWires = data[start++];
	int numberOfAttributes = data[start++];
	for (int i = 0; i < numberOfWires; i++) {
		int wireId = data[start++];
		int objId1 = data[start++];
		int objId2 = data[start++];
		int index1 = data[start++];
		int index2 = data[start++];
		EmplaceWire(objId1, objId2, index1, index2);
	}
	return data;
}
