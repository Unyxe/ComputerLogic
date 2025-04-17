#include "RenderManager.h"

#include "StaticGateLibrary.h"

void RenderManager::pollEvents()
{
	if (const std::optional event = renderWindow.pollEvent()) {
		if (event->is<sf::Event::Closed>())
			renderWindow.close();
	}
}

void RenderManager::Draw(const CircuitManager& circuitManager)
{
	const std::vector<int>& gatesData = circuitManager.GetGatesData();
	const std::vector<int>& wiresData = circuitManager.GetWiresData();


	for (auto& wireData : SplitVector(wiresData, 4)) {
		DrawWire(wireData);
	}
	for (auto& gateData : SplitVector(gatesData, 4)) {
		DrawGate(gateData);
	}
}

const std::vector<std::vector<int>>& RenderManager::SplitVector(const std::vector<int>& vector, int subSize) const
{
	if (vector.size() % subSize != 0) throw std::invalid_argument("Vector size is not divisible by subSize.");
	std::vector<int> buffer;
	std::vector<std::vector<int>> result;

	for (int i = 0; i < (int)vector.size(); i++) {
		if (i % subSize == 0 && i != 0) {
			result.push_back(buffer);
			buffer.clear();
		}
		buffer.push_back(vector[i]);
	}
	if (!buffer.empty()) {
		result.push_back(buffer);
	}

	return result;
}

RenderManager::RenderManager()
{
	renderWindow = sf::RenderWindow(
		sf::VideoMode({ 800, 600 }),
		"Computer Logic Simulator"
	);
}

RenderManager::~RenderManager()
{
	renderWindow.close();
}

void RenderManager::StartDrawing(const CircuitManager& circuitManager)
{
	while (renderWindow.isOpen())
	{
		pollEvents();

		Draw(circuitManager);

		renderWindow.clear(sf::Color::Black);
	}
}
