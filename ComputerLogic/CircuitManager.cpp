#include "CircuitManager.h"

#include <sstream>
#include <iostream>

#include <random>

CircuitManager::CircuitManager(int numberOfInputs, int numberOfOutputs)
{
	typeID = rand() * 10000 + rand();
	wireStore = std::make_unique<WireStore>();
	gateStore = std::make_unique<GateStore>();
	inputsID = rand() * 10000 + rand();
	outputsID = rand() * 10000 + rand();
	for (int i = 0; i < numberOfInputs; i++) {
		inputStates.push_back(false);
	}
	for (int i = 0; i < numberOfOutputs; i++) {
		outputStates.push_back(false);
	}
}

void CircuitManager::Update()
{
	std::vector<int> gateIds = gateStore->GetAllGateIds();

	for (int i = 0; i < (int)inputStates.size(); i++) {
		wireStore->SetWiresStateByInput(inputsID, i, inputStates[i]);
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
}

int CircuitManager::EmplaceGate(int gateTypeId)
{
	int gateId = gateStore->EmplaceGate(gateTypeId);
	return gateId;
}

int CircuitManager::EmplaceGate(int gateTypeId, int gateId)
{
	gateStore->EmplaceGate(gateTypeId, gateId);
	return gateId;
}

void CircuitManager::RemoveGate(int gateId)
{
	gateStore->RemoveGate(gateId);
	wireStore->RemoveWireCascade(gateId);
}

int CircuitManager::EmplaceWire(int objId1, int objId2, int index1, int index2)
{
	int wireId = wireStore->EmplaceWire(objId1, objId2, index1, index2);
	return wireId;
}

void CircuitManager::RemoveWire(int objId1, int objId2, int index1, int index2)
{
	wireStore->RemoveWire(objId1, objId2, index1, index2);
}

const std::vector<int>& CircuitManager::GetGatesData() const
{
	return gateStore->GetGatesData();
}

const std::vector<int>& CircuitManager::GetWiresData() const
{
	return wireStore->GetWiresData();
}

void CircuitManager::ClearCircuit(int numberOfInputs, int numberOfOutputs)
{
	inputStates.clear();
	outputStates.clear();
	typeID = rand() * 10000 + rand();
	wireStore = std::make_unique<WireStore>();
	gateStore = std::make_unique<GateStore>();
	inputsID = rand() * 10000 + rand();
	outputsID = rand() * 10000 + rand();
	for (int i = 0; i < numberOfInputs; i++) {
		inputStates.push_back(false);
	}
	for (int i = 0; i < numberOfOutputs; i++) {
		outputStates.push_back(false);
	}
}

void CircuitManager::LoadCircuit(std::string_view serializedCircuit)
{
	ClearCircuit(0, 0);

	std::string chunk = "";
	std::vector<std::string> chunks;
	bool flagOpen = false;
	for (int i = 1; i < (int)serializedCircuit.size(); i++) {
		char c = serializedCircuit[i];
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
			else {
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
					for (int i = 0; i < data[0]; i++) {
						inputStates.push_back(false);
					}
				}
				else {
					for (int i = 0; i < data[0]; i++) {
						outputStates.push_back(false);
					}
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
}

void CircuitManager::GenerateTruthTable(int substepCount)
{
	{
		int numOfInputs = static_cast<int>(GetInputStates().size());
		for (auto& e : GenerateInputCombinations(numOfInputs)) {
			for (int i = 0; i < numOfInputs; i++) {
				SetInputState(i, e[i]);
			}
			for (int i = 0; i < substepCount; i++) {
				Update();
			}
			std::cout << "Inputs: ";
			for (int i = 0; i < numOfInputs; i++) {
				std::cout << GetInputStates()[i] << " ";
			}
			std::cout << " | Outputs: ";
			for (int i = 0; i < GetOutputStates().size(); i++) {
				std::cout << GetOutputStates()[i] << " ";
			}
			std::cout << std::endl;
		}
	}
}

std::string CircuitManager::SerializeGate()
{  
  std::stringstream serializedGate;

  serializedGate << "1[{" << typeID << ",}][{"<<inputStates.size()<<",}{"<<outputStates.size()<< ",}][{" << inputsID << ",}{" << outputsID << ",}]";
  serializedGate << gateStore->SerializeGates();
  serializedGate << wireStore->SerializeWires();

  return serializedGate.str();
}
