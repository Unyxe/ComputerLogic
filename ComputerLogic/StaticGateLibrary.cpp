#include "StaticGateLibrary.h"

#include <string>
#include <sstream>

std::unordered_map<int, std::string_view> StaticGateLibrary::SerializedGateMap;
std::unordered_map<std::string, int> StaticGateLibrary::GateNames;
std::unordered_map<int, std::string> StaticGateLibrary::GateMapReverse;

std::string StaticGateLibrary::SerializeIntVector(const std::vector<int>& vec, char separator)
{
	std::string serialized;
	for (size_t i = 0; i < vec.size(); ++i) {
		serialized += std::to_string(vec[i]);
		if (i < vec.size() - 1) {
			serialized += separator;
		}
	}
	return serialized;
}

const std::vector<int> StaticGateLibrary::DeserializeIntVector(std::string_view str, char separator)
{
	std::vector<int> vec;
	std::string chunk;
	std::istringstream stream(str.data());
	while (std::getline(stream, chunk, separator)) {
		vec.push_back(std::stoi(chunk));
	}
	return vec;
}
