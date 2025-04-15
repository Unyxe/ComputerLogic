#pragma once
#include "Gate.h"

class PrimitiveGate : public Gate
{
public:
	PrimitiveGate(int gateType);

	std::vector<bool> Evaluate(const std::vector<bool>& input) override;
};

