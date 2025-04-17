#pragma once

#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <memory>

#include "Wire.h"

class WireStore
{
private:
	std::unordered_map<int, std::unique_ptr<Wire>> wireMap;
public:
	WireStore() = default;
	~WireStore() = default;

	int EmplaceWire(int objId1, int objId2, int index1, int index2);
	void RemoveWire(int objId1, int objId2, int index1, int index2);

	void RemoveWireCascade(int objId);

	bool GetWiresCombinedStateByOutput(int outputObjectID, int index);
	void SetWiresStateByInput(int inputObjectID, int index, bool state);

	std::string SerializeWires() const;

	const std::vector<int> GetWiresData() const;

	std::vector<int> OverwriteWiresByParsed(std::vector<int> data, int start);
};

