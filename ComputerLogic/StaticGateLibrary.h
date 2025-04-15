#pragma once

#include <unordered_map>
#include <random>
#include <string_view>

class StaticGateLibrary
{
private:
	static std::unordered_map<int, std::string_view> SerializedGateMap;
	static std::unordered_map<std::string, int> GateNames;
	static std::unordered_map<int, std::string> GateMapReverse;
public:
	static void InitializeGateMap()
	{
		SerializedGateMap[0] = "00"; //AND
		SerializedGateMap[1] = "O1"; //OR
		SerializedGateMap[2] = "02"; //NOT
		SerializedGateMap[3] = "03"; //NAND
		SerializedGateMap[4] = "04"; //NOR
		SerializedGateMap[5] = "05"; //XOR
		SerializedGateMap[428467] = "1[{428467,}][{2,}{2,}][{63366500,}{191705724,}][{0,114809358,}{5,99610491,}][{63366500,114809358,1,1,}{63366500,99610491,0,0,}{63366500,99610491,1,1,}{63366500,114809358,0,0,}{99610491,191705724,0,0,}{114809358,191705724,0,1,}]"; //Half-Adder

		GateNames["AND"] = 0;
		GateNames["OR"] = 1;
		GateNames["NOT"] = 2;
		GateNames["NAND"] = 3;
		GateNames["NOR"] = 4;
		GateNames["XOR"] = 5;
		GateNames["Half-Adder"] = 428467;
	}
	static std::string_view GetGateType(int gateTypeId)
	{
		if (SerializedGateMap.find(gateTypeId) == SerializedGateMap.end()) {
			throw std::invalid_argument("Gate type ID not found in library.");
		}
		return SerializedGateMap[gateTypeId];
	}
    static void SaveGateType(std::string_view serializedGate, int gateTypeID, std::string gateName)  
    {  
       if (SerializedGateMap.find(gateTypeID) != SerializedGateMap.end()) {  
           auto reverseGateName = GateMapReverse[gateTypeID];  
           GateNames.erase(reverseGateName);  
       }  
       SerializedGateMap[gateTypeID] = serializedGate;  
       GateNames[gateName] = gateTypeID;  
       GateMapReverse[gateTypeID] = gateName;  
    }
	static bool isPrimitive(std::string_view serializedGate)
	{
		return serializedGate[0] == '0';
	}
};

