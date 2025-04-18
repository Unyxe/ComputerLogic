#include "ApplicationManager.h"

#include <thread>

const CircuitRenderData ApplicationManager::GetCircuitRenderData()
{
	CircuitRenderData circuitRenderData;
	circuitRenderData.gateData = circuitManager->GetGatesData();
	circuitRenderData.wireData = circuitManager->GetWiresData();
	circuitRenderData.numberOfInputs = circuitManager->GetInputStates().size();
	circuitRenderData.numberOfOutputs = circuitManager->GetOutputStates().size();
	circuitRenderData.inputId = circuitManager->GetInputsID();
	circuitRenderData.outputId = circuitManager->GetOutputsID();
	return circuitRenderData;
}

void ApplicationManager::CircuitThread()
{
	while (true) {
		circuitManager->Update();
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		std::cout << "Circuit updated" << std::endl;
	}
}

ApplicationManager::ApplicationManager()
{
	StaticGateLibrary::InitializeGateMap();
	circuitManager = std::make_unique<CircuitManager>(2, 2);
	circuitManager->LoadCircuit(StaticGateLibrary::GetGateType(666));
	renderManager = std::make_unique<RenderManager>(GetCircuitRenderData());
}

void ApplicationManager::TestCLI()
{
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

	circuitManager.GenerateTruthTable();

	std::cout << "Serialized Gate: " << circuitManager.SerializeGate() << std::endl;

	CircuitManager circuitManager2(2, 2);
	circuitManager2.EmplaceGate(100, 666);

	circuitManager2.EmplaceWire(circuitManager2.GetInputsID(), 100, 0, 0);
	circuitManager2.EmplaceWire(circuitManager2.GetInputsID(), 100, 1, 1);
	circuitManager2.EmplaceWire(100, circuitManager2.GetOutputsID(), 0, 0);
	circuitManager2.EmplaceWire(100, circuitManager2.GetOutputsID(), 1, 1);

	circuitManager2.GenerateTruthTable();

	std::cout << "Serialized Gate: " << circuitManager2.SerializeGate() << std::endl;
}

void ApplicationManager::StartApp()
{
	std::thread circuitThread(&ApplicationManager::CircuitThread, this);

	renderManager->StartDrawing();

	circuitThread.join();
}
