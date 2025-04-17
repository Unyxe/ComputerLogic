#pragma once

#include <string>
#include <vector>

class GateMetaData
{
private:
	float gatePosX;
	float gatePosY;
public:
	GateMetaData() : gatePosX(0.0f), gatePosY(0.0f) {};
	GateMetaData(float x, float y) : gatePosX(x), gatePosY(y) {};
	explicit GateMetaData(const GateMetaData& other);
	~GateMetaData() = default;
	float GetX() const { return gatePosX; }
	float GetY() const { return gatePosY; }

	int UpdateFromData(std::vector<int> data, int start);

	const std::vector<int> GetData() const
	{
		return std::vector<int>{ static_cast<int>(gatePosX), static_cast<int>(gatePosY) };
	}
};

