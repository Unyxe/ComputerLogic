#include "Gate.h"
#include "GateMetaData.h"
#include "GateStore.h"
#include "PrimitiveGate.h"
#include "StaticGateLibrary.h"
#include <string>

Gate::Gate()
{
	inputsID = rand() * 10000 + rand();
	outputsID = rand() * 10000 + rand();
	typeID = rand() * 10000 + rand();
	gateStore = std::make_unique<GateStore>();
    wireStore = std::make_unique<WireStore>();

	for (int i = 0; i < numberOfOutputs; i++) {
		lastOutput.push_back(false);
	}
}

Gate::Gate(std::string_view serializedGate)
{
	gateStore = std::make_unique<GateStore>();
	wireStore = std::make_unique<WireStore>();

	std::vector<int> data = StaticGateLibrary::DeserializeIntVector(serializedGate);

	typeID = data[0];
	numberOfInputs = data[1];
	numberOfOutputs = data[2];
	inputsID = data[3];
	outputsID = data[4];

	for (int i = 0; i < numberOfOutputs; i++) {
		lastOutput.push_back(false);
	}

	int index = gateStore->OverwriteGatesByParsed(data, 5);
	wireStore->OverwriteWiresByParsed(data, index);
}

Gate::~Gate() = default;


std::vector<bool> Gate::Evaluate(const std::vector<bool>& input)
{
	if (input.size() != numberOfInputs) {
		throw std::invalid_argument("Input size does not match the number of inputs for this gate.");
	}

	std::vector<bool> outputStates(numberOfOutputs, false);

	std::vector<int> gateIds = gateStore->GetAllGateIds();

	for (int i = 0; i < (int)input.size(); i++) {
		wireStore->SetWiresStateByInput(inputsID, i, input[i]);
	}

	for (int i = 0; i < (int)gateIds.size(); i++) {
		std::vector<bool> outputStates = gateStore->GetLastOutput(gateIds[i]);
		for (int j = 0; j < (int)outputStates.size(); j++) {
			wireStore->SetWiresStateByInput(gateIds[i], j, outputStates[j]);
		}
	}

	for (int i = 0; i < (int)gateIds.size(); i++) {
		int numberOfInputs = gateStore->GetNumberOfInputs(gateIds[i]);
		std::vector<bool> inputStates;
		for (int j = 0; j < numberOfInputs; j++) {
			inputStates.push_back(wireStore->GetWiresCombinedStateByOutput(gateIds[i], j));
		}
		gateStore->EvaluateGate(gateIds[i], inputStates);
	}
	for (int i = 0; i < (int)outputStates.size(); i++) {
		outputStates[i] = wireStore->GetWiresCombinedStateByOutput(outputsID, i);
	}

	lastOutput = outputStates;

	return outputStates;
}
