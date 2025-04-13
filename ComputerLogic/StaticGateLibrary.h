#pragma once

class StaticGateLibrary
{
private:
	static std::map<int, std::string_view> SerializedGateMap;
public:
	static void InitializeGateMap()
	{
		SerializedGateMap[0] = "00"; //AND
		SerializedGateMap[1] = "O1"; //OR
		SerializedGateMap[2] = "02"; //NOT
		SerializedGateMap[3] = "03"; //NAND
		SerializedGateMap[4] = "04"; //NOR
		SerializedGateMap[5] = "05"; //XOR
	}
	static std::string_view GetGateType(int gateTypeId)
	{
		return SerializedGateMap[gateTypeId];
	}
};

