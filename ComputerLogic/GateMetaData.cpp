#include "GateMetaData.h"

#include <stdexcept>

GateMetaData::GateMetaData(const GateMetaData& other)
{
	gatePosX = other.gatePosX;
	gatePosY = other.gatePosY;
}

int GateMetaData::UpdateFromData(std::vector<int> data, int start)
{
	if (data[start++] <2) {
		throw std::out_of_range("Not enough data to update GateMetaData.");
	}
	gatePosX = static_cast<float>(data[start++]);
	gatePosY = static_cast<float>(data[start++]);
	return start;
}
