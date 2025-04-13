#pragma once

#include <map>
#include <vector>
#include <stdexcept>

#include "Wire.h"

class WireStore
{
private:
	std::map<int, Wire> wireMap;
public:
	WireStore() = default;

	void EmplaceWire(int objId1, int objId2) {
		int wireId = std::hash<int>()(objId1) ^ std::hash<int>()(objId2);
		wireMap[wireId] = Wire(objId1, objId2);
	}
	void RemoveWire(int objId1, int objId2) {
		int wireId = std::hash<int>()(objId1) ^ std::hash<int>()(objId2);
		if (wireMap.find(wireId) != wireMap.end()) {
			wireMap.erase(wireId);
		}
		else {
			throw std::invalid_argument("Wire ID not found in store.");
		}
	}

	bool GetWiresCombinedStateByOutput(int outputObjectID) {
		for (const auto& wire : wireMap) {
			if (wire.second.GetObjId2() == outputObjectID && wire.second.GetState()) {
				return true;
			}
		}
		return false;
	}
	void SetWiresStateByInput(int inputObjectID, bool state) {
		for (auto& wire : wireMap) {
			if (wire.second.GetObjId1() == inputObjectID) {
				wire.second.SetState(state);
			}
		}
	}

};

