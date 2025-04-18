#pragma once

#include <vector>

#include "GateRenderData.h"
#include "WireRenderData.h"

class CircuitRenderData
{
public:
	CircuitRenderData() = default;

	std::vector<GateRenderData> gateData;
	std::vector<WireRenderData> wireData;

	int numberOfInputs = 0;
	int numberOfOutputs = 0;

	std::vector<bool> inputStates;
	std::vector<bool> outputStates;

	int inputId = 0;
	int outputId = 0;
};

