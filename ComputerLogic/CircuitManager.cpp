#include "CircuitManager.h"

#include "GateMetaData.h"
#include "StaticGateLibrary.h"

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
	GateMetaData metaData(0.0f, 0.0f); // Placeholder for gate position
	int gateId = gateStore->EmplaceGate(gateTypeId, metaData);
	return gateId;
}

int CircuitManager::EmplaceGate(int gateTypeId, int gateId)
{
	GateMetaData metaData(0.0f, 0.0f); // Placeholder for gate position
	gateStore->EmplaceGate(gateTypeId, gateId, metaData);
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

const std::vector<GateRenderData> CircuitManager::GetGatesData() const
{
	return gateStore->GetGatesData();
}

const std::vector<WireRenderData> CircuitManager::GetWiresData() const
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

	std::vector<int> data = StaticGateLibrary::DeserializeIntVector(serializedCircuit);

	typeID = data[0];
	int numberOfInputs = data[1];
	int numberOfOutputs = data[2];
	inputsID = data[3];
	outputsID = data[4];
	for (int i = 0; i < numberOfInputs; i++) {
		inputStates.push_back(false);
	}
	for (int i = 0; i < numberOfOutputs; i++) {
		outputStates.push_back(false);
	}

	int index = gateStore->OverwriteGatesByParsed(data, 5);
	wireStore->OverwriteWiresByParsed(data, index);
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

	std::vector<int> data;

	data.push_back(typeID);
	data.push_back(static_cast<int>(inputStates.size()));
	data.push_back(static_cast<int>(outputStates.size()));
	data.push_back(inputsID);
	data.push_back(outputsID);

	std::string serializedData = StaticGateLibrary::SerializeIntVector(data);

	std::string serializedGate = serializedData +"," + gateStore->SerializeGates()+"," + wireStore->SerializeWires();
	return serializedGate;
}
