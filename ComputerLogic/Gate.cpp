#include "Gate.h"
#include "GateStore.h"
#include "PrimitiveGate.h"
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

	std::string chunk = "";
	std::vector<std::string> chunks;
	bool flagOpen= false;
	for (int i = 1; i < (int)serializedGate.size(); i++) {
		char c = serializedGate[i];
		if (c == '[') {
			flagOpen = true;
			continue;
		}
		else if (c == ']') {
			flagOpen = false;
			chunks.push_back(chunk);
			chunk = "";
			continue;
		}
		else {
			chunk += c;
		}
	}
	for (int i = 0; i < (int)chunks.size(); i++) {
		std::vector<std::string> subchunks;
		for (int j = 0; j < (int)chunks[i].size(); j++) {
			char c = chunks[i][j];
			if (c == '{') {
				flagOpen = true;
				continue;
			}
			else if (c == '}') {
				flagOpen = false;
				subchunks.push_back(chunk);
				chunk = "";
				continue;
			}
			else{
				chunk += c;
			}
		}
		for (int j = 0; j < (int)subchunks.size(); j++) {
			std::vector<int> data;
			for (int k = 0; k < (int)subchunks[j].size(); k++) {
				char c = subchunks[j][k];
				if (c == ',') {
					data.push_back(std::stoi(chunk));
					chunk = "";
					continue;
				}
				else {
					chunk += c;
				}
			}

			switch (i)
			{
			case 0:
				typeID = data[0];
				break;
			case 1:
				if (j == 0) {
					numberOfInputs = data[0];
				}
				else {
					numberOfOutputs = data[0];
				}
				break;
			case 2:
				if (j == 0) {
					inputsID = data[0];
				}
				else {
					outputsID = data[0];
				}
				break;
			case 3:
				gateStore->EmplaceGate(data[0], data[1]);
				break;
			case 4:
				wireStore->EmplaceWire(data[0], data[1], data[2], data[3]);
				break;
			}
		}
	}

	for (int i = 0; i < numberOfOutputs; i++) {
		lastOutput.push_back(false);
	}
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
