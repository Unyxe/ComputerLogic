#pragma once
class WireRenderData
{
public:
	WireRenderData() = default;

	int wireId;
	int wireState;
	int width = 5;
	int startGateId;
	int endGateId;
	int startGateIndex;
	int endGateIndex;
};

