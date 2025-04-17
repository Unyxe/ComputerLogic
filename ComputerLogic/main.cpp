#include <iostream>
#include "CircuitManager.h"
#include "StaticGateLibrary.h"





int main() {
	
	return 0;
}




















/*
StaticGateLibrary::InitializeGateMap();
	CircuitManager circuitManager(2, 2);

	int andGateID = circuitManager.EmplaceGate(0);
	int xorGateID = circuitManager.EmplaceGate(5);

	int wire1ID = circuitManager.EmplaceWire(
		circuitManager.GetInputsID(),
		xorGateID,
		0,
		0
	);

	int wire2ID = circuitManager.EmplaceWire(
		circuitManager.GetInputsID(),
		xorGateID,
		1,
		1
	);

	int wire3ID = circuitManager.EmplaceWire(
		circuitManager.GetInputsID(),
		andGateID,
		0,
		0
	);

	int wire4ID = circuitManager.EmplaceWire(
		circuitManager.GetInputsID(),
		andGateID,
		1,
		1
	);

	int wire5ID = circuitManager.EmplaceWire(
		xorGateID,
		circuitManager.GetOutputsID(),
		0,
		0
	);

	int wire6ID = circuitManager.EmplaceWire(
		andGateID,
		circuitManager.GetOutputsID(),
		0,
		1
	);

	GenerateTruthTable(circuitManager);

	std::cout << "Serialized Gate: " << circuitManager.SerializeGate() << std::endl;

	CircuitManager circuitManager2(2, 2);
	circuitManager2.EmplaceGate(428467,100);

	circuitManager2.EmplaceWire(circuitManager2.GetInputsID(), 100, 0, 0);
	circuitManager2.EmplaceWire(circuitManager2.GetInputsID(), 100, 1, 1);
	circuitManager2.EmplaceWire(100, circuitManager2.GetOutputsID(), 0, 0);
	circuitManager2.EmplaceWire(100, circuitManager2.GetOutputsID(), 1, 1);

	GenerateTruthTable(circuitManager2);

	std::cout << "Serialized Gate: " << circuitManager2.SerializeGate() << std::endl;
*/