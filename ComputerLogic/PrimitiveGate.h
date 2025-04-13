#pragma once
#include "Gate.h"
class PrimitiveGate :
    public Gate
{
private:
	int gateTypeId;
public:
	PrimitiveGate(int gateType);

	std::vector<bool> Evaluate(std::vector<bool> input) override;
};

