#include "PrimitiveGate.h"

#include <stdexcept>

PrimitiveGate::PrimitiveGate(int gateType)
{
	if (gateType > 5 || gateType < 0) throw std::invalid_argument("Invalid primitive gate type. Must be between 0 and 5.");
	ChangeTypeID(gateType);
	numberOfOutputs = 1;
	if (gateType != 2) {
		numberOfInputs = 2;
	}
	else {
		numberOfInputs = 1;
	}

	for (int i = 0; i < numberOfOutputs; i++) {
		lastOutput.push_back(false);
	}
}

std::vector<bool> PrimitiveGate::Evaluate(const std::vector<bool>& input)
{
	if (input.size() != numberOfInputs) {
		throw std::invalid_argument("Input size does not match the number of inputs for this gate.");
	}
	std::vector<bool> output(numberOfOutputs, false);
	switch (GetTypeID()) {
		case 0: // AND
			output[0] = input[0] && input[1];
			break;
		case 1: // OR
			output[0] = input[0] || input[1];
			break;
		case 2: // NOT
			output[0] = !input[0];
			break;
		case 3: // NAND
			output[0] = !(input[0] && input[1]);
			break;
		case 4: // NOR
			output[0] = !(input[0] || input[1]);
			break;
		case 5: // XOR
			output[0] = input[0] ^ input[1];
			break;
	}

	lastOutput = output;
	return output;
}
