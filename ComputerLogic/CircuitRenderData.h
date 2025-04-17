#pragma once

#include <vector>

class CircuitRenderData
{
private:
	std::vector<int> sequentialGateData;
	std::vector<int> sequentialWireData;

	int numberOfInputs = 0;
	int numberOfOutputs = 0;

	int inputId = 0;
	int outputId = 0;

public:
	CircuitRenderData() = default;
	CircuitRenderData(const std::vector<int>& sequentialGateData, const std::vector<int>& sequentialWireData, int numberOfInputs, int numberOfOutputs, int inputId, int outputId) : sequentialGateData(sequentialGateData), sequentialWireData(sequentialWireData), numberOfInputs(numberOfInputs), numberOfOutputs(numberOfOutputs), inputId(inputId), outputId(outputId) {};

	const std::vector<int>& GetSequentialGateData() const { return sequentialGateData; };
	const std::vector<int>& GetSequentialWireData() const { return sequentialWireData; };
	int GetNumberOfInputs() const { return numberOfInputs; };
	int GetNumberOfOutputs() const { return numberOfOutputs; };
	int GetInputId() const { return inputId; };
	int GetOutputId() const { return outputId; };
};

