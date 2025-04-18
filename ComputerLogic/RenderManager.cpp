#include "RenderManager.h"

#include <iostream>

#include "StaticGateLibrary.h"
#include "DrawingHelper.h"

void RenderManager::pollEvents()
{
	if (const std::optional event = renderWindow.pollEvent()) {
		if (event->is<sf::Event::Closed>())
			renderWindow.close();
	}
}

void RenderManager::Draw()
{

	DrawBackground();

	for (auto& drawableWire : drawableWireMap) {
		drawableWire.second->Draw(renderWindow);
	}

	for (int i = 0; i < currentRenderData.numberOfInputs; i++) {
		DrawingHelper::DrawStateCircle(renderWindow, inputPositions[i], false);
	}

	for (int i = 0; i < currentRenderData.numberOfOutputs; i++) {
		DrawingHelper::DrawStateCircle(renderWindow, outputPositions[i], false);
	}

	for (auto& drawableGate : drawableGateMap) {
		drawableGate.second->Draw(renderWindow);
	}
}

void RenderManager::DrawBackground()
{
	//TODO
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


	int inputCount = currentRenderData.numberOfInputs;
	int outputCount = currentRenderData.numberOfOutputs;

	for (int i = 0; i < inputCount; i++) {
		inputPositions.push_back({ 50.f, 50.f + (WINDOW_HEIGHT-100.f)*(i+1)/(inputCount+1)});
	}
	for (int i = 0; i < outputCount; i++) {
		outputPositions.push_back({ WINDOW_WIDTH - 50.f, 50.f + (WINDOW_HEIGHT - 100.f) * (i+1) / (outputCount+1) });
	}

	for (const auto& gateData : currentRenderData.gateData)
	{
		drawableGateMap[gateData.gateId] = std::make_unique<DrawableGate>(gateData);
	}
	for (const auto& wireData : currentRenderData.wireData)
	{
		drawableWireMap[wireData.wireId] = std::make_unique<DrawableWire>(wireData);

		sf::Vector2f pos1;
		sf::Vector2f pos2;

		if (wireData.startGateId == currentRenderData.inputId) {
			pos1 = inputPositions[wireData.startGateIndex];
		}
		else {
			pos1 = drawableGateMap[wireData.startGateId]->GetOutputPosition(wireData.startGateIndex);
		}

		if (wireData.endGateId == currentRenderData.outputId) {
			pos2 = outputPositions[wireData.endGateIndex];
		}
		else {
			pos2 = drawableGateMap[wireData.endGateId]->GetInputPosition(wireData.endGateIndex);
		}

		drawableWireMap[wireData.wireId]->SetPosition(
			pos1,pos2
		);
	}
}

RenderManager::RenderManager(const CircuitRenderData& initialData)
{
	currentRenderData = initialData;

	sf::Vector2u size; 
	size.x = WINDOW_WIDTH;
	size.y = WINDOW_HEIGHT;

	renderWindow = sf::RenderWindow(
		sf::VideoMode(size),
		"Computer Logic Simulator",
		sf::Style::Titlebar | sf::Style::Close
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

		renderWindow.clear(sf::Color::Color(45,45,45));

		Draw();

		renderWindow.display();
	}
}
