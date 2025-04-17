#include "RenderManager.h"

#include "StaticGateLibrary.h"

void RenderManager::pollEvents()
{
	if (const std::optional event = renderWindow.pollEvent()) {
		if (event->is<sf::Event::Closed>())
			renderWindow.close();
	}
}

void RenderManager::Draw()
{

}

const std::vector<std::vector<int>> RenderManager::SplitVector(const std::vector<int>& vector, int subSize) const
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

void RenderManager::PopulateDrawables()
{
	outputPositions.clear();
	inputPositions.clear();

	for (int i = 0; i < currentRenderData.GetNumberOfInputs(); i++) {
		inputPositions.push_back({ (float)(i * 100 + 50), 50.0f });
	}
	for (int i = 0; i < currentRenderData.GetNumberOfOutputs(); i++) {
		outputPositions.push_back({ (float)(i * 100 + 50), 550.0f });
	}

	for (const auto& gateData : SplitVector(currentRenderData.GetSequentialGateData(), 6))
	{
		int gateId = gateData[0];
		int gateTypeId = gateData[1];
		int numberOfInputs = gateData[2];
		int numberOfOutputs = gateData[3];
		int x = gateData[4];
		int y = gateData[5];
		drawableGateMap[gateId] = std::make_unique<DrawableGate>(gateId, gateTypeId, numberOfInputs, numberOfOutputs);
		drawableGateMap[gateId]->SetPosition({ (float)x, (float)y });
	}
	for (const auto& wireData : SplitVector(currentRenderData.GetSequentialWireData(), 6))
	{
		int wireId = wireData[0];
		int wireState = wireData[1];
		int startGateId = wireData[2];
		int endGateId = wireData[3];
		int startGateIndex = wireData[4];
		int endGateIndex = wireData[5];
		drawableWireMap[wireId] = std::make_unique<DrawableWire>(wireId, wireState);

		sf::Vector2f pos1;
		sf::Vector2f pos2;

		if (startGateId == currentRenderData.GetInputId()) {
			pos1 = inputPositions[startGateIndex];
		}
		else {
			pos1 = drawableGateMap[startGateId]->GetOutputPosition(startGateIndex);
		}

		if (endGateId == currentRenderData.GetOutputId()) {
			pos2 = outputPositions[endGateIndex];
		}
		else {
			pos2 = drawableGateMap[endGateId]->GetInputPosition(endGateIndex);
		}

		drawableWireMap[wireId]->SetPosition(
			pos1,pos2
		);
	}
}

RenderManager::RenderManager(const CircuitRenderData& initialData)
{
	currentRenderData = initialData;
	renderWindow = sf::RenderWindow(
		sf::VideoMode({ 800, 600 }),
		"Computer Logic Simulator"
	);

	PopulateDrawables();
}

RenderManager::~RenderManager()
{
	renderWindow.close();
}

void RenderManager::StartDrawing()
{
	while (renderWindow.isOpen())
	{
		pollEvents();

		Draw();

		renderWindow.clear(sf::Color::Black);
	}
}
