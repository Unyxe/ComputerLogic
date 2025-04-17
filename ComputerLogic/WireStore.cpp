#include "WireStore.h"

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
	std::stringstream serializedWires;

	serializedWires << "[";
	for (const auto& wire : wireMap) {
		serializedWires << "{" << wire.second->GetObjId1() << "," << wire.second->GetObjId2() << "," << wire.second->GetIndex1() << "," << wire.second->GetIndex2() << ",}";
	}
	serializedWires << "]";

	return serializedWires.str();
}

const std::vector<int>& WireStore::GetWiresData() const
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
