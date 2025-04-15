#pragma once
#include <memory>

#include "GateStore.h"
#include "WireStore.h"

class CircuitManager
{
private:
	std::unique_ptr<GateStore> gateStore;
	std::unique_ptr<WireStore> wireStore;

	std::vector<bool> inputStates;
	int inputsID;

	std::vector<bool> outputStates;
	int outputsID;

	int typeID;



	std::vector<std::vector<bool>> GenerateInputCombinations(int numInputs) const{
		std::vector<std::vector<bool>> combinations;
		for (int i = 0; i < (1 << numInputs); ++i) {
			std::vector<bool> combination;
			for (int j = 0; j < numInputs; ++j) {
				combination.push_back((i >> j) & 1);
			}
			combinations.push_back(combination);
		}
		return combinations;
	}

public:
	CircuitManager(int numberOfInputs, int numberOfOutputs);
	void Update();

	int EmplaceGate(int gateTypeId);
	int EmplaceGate(int gateTypeId, int gateId);
	void RemoveGate(int gateId);

	int EmplaceWire(int objId1, int objId2, int index1, int index2);
	void RemoveWire(int objId1, int objId2, int index1, int index2);

	void SetInputState(int index, bool state) { inputStates[index] = state; }

	const std::vector<bool>& GetInputStates() const { return inputStates; }
	const std::vector<bool>& GetOutputStates() const { return outputStates; }
	int GetInputsID() const { return inputsID; }
	int GetOutputsID() const { return outputsID; }


	void ClearCircuit(int numberOfInputs, int numberofOutputs);
	void LoadCircuit(std::string_view serializedCircuit);


	void GenerateTruthTable(int substepCount = 1000);


	std::string SerializeGate();
};

