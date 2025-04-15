#pragma once

#include <vector>
#include <memory>
#include <string_view>

class GateStore;
#include "WireStore.h"

class Gate
{
private:
	std::unique_ptr<GateStore> gateStore;
	std::unique_ptr<WireStore> wireStore;

	int inputsID;
	int outputsID;

	int typeID;
protected:
	int numberOfInputs = 0;
	int numberOfOutputs = 0;

	void ChangeTypeID(int newTypeID) { typeID = newTypeID; }
	
	std::vector<bool> lastOutput;
public:
	Gate();
	explicit Gate(std::string_view serializedGate);
	virtual ~Gate();
	virtual std::vector<bool> Evaluate(const std::vector<bool>& input);
	std::vector<bool> GetLastOutput() const { return lastOutput; }
	int GetNumberOfInputs() const { return numberOfInputs; }
	int GetTypeID() const { return typeID; }
};

