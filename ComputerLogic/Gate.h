#pragma once

#include <vector>
#include <memory>

#include "GateStore.h"

class Gate
{
private:
	GateStore gateStore;
protected:
	int numberOfInputs = 0;
	int numberOfOutputs = 0;
public:
	Gate() = default;
	virtual std::vector<bool> Evaluate(std::vector<bool> input);


	static Gate Deserialize(std::string_view serializedGate);
};

