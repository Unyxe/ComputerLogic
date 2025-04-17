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
		SaveGateType("00", 0, "AND");
		SaveGateType("O1", 1, "OR");
		SaveGateType("02", 2, "NOT");
		SaveGateType("03", 3, "NAND");
		SaveGateType("04", 4, "NOR");
		SaveGateType("05", 5, "XOR");
		SaveGateType("428467,2,2,63366500,191705724,2,2,114809358,0,2,0,0,99610491,5,2,0,0,6,5,-1293370643,63366500,114809358,1,1,1429161250,63366500,99610491,0,0,-1412065012,63366500,99610491,1,1,-2079024991,63366500,114809358,0,0,-896307708,99610491,191705724,0,0,-242046070,114809358,191705724,0,1", 666,
			"Half-Adder");
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

	static std::string SerializeIntVector(const std::vector<int>& vec, char separator = ',');
	static const std::vector<int> DeserializeIntVector(std::string_view str, char separator = ',');
};

