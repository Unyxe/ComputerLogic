#pragma once

#include <iostream>

#include "RenderManager.h"
#include "CircuitManager.h"
#include "StaticGateLibrary.h"

class ApplicationManager
{
private:
	std::unique_ptr<CircuitManager> circuitManager;
	std::unique_ptr<RenderManager> renderManager;


	const CircuitRenderData GetCircuitRenderData();

	void CircuitThread();
public:
	ApplicationManager();

	void TestCLI();

	void StartApp();
};

