#pragma once

#include <vector>

class GateRenderData
{
public:
	GateRenderData() = default;
	int gateId;
	int gateTypeId;
	int numberOfInputs;
	int numberOfOutputs;
	int x;
	int y;
	std::vector<bool> inputStates;
	std::vector<bool> outputStates;
};

