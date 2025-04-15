#include "StaticGateLibrary.h"

std::unordered_map<int, std::string_view> StaticGateLibrary::SerializedGateMap;
std::unordered_map<std::string, int> StaticGateLibrary::GateNames;
std::unordered_map<int, std::string> StaticGateLibrary::GateMapReverse;
