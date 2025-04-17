#pragma once

#include "CircuitRenderData.h"
#include "DrawableWire.h"
#include "DrawableGate.h"

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

class RenderManager
{
private:
	sf::RenderWindow renderWindow;

	CircuitRenderData currentRenderData;

	std::unordered_map<int, std::unique_ptr<DrawableGate>> drawableGateMap;
	std::unordered_map<int, std::unique_ptr<DrawableWire>> drawableWireMap;

	std::vector<sf::Vector2f> inputPositions;
	std::vector<sf::Vector2f> outputPositions;


	void pollEvents();
	void Draw();

	const std::vector<std::vector<int>> SplitVector(const std::vector<int>& vector, int subSize) const;

	void PopulateDrawables();

public:
	RenderManager(const CircuitRenderData& initialData);
	~RenderManager();

	void UpdateRenderData(const CircuitRenderData& newData) { currentRenderData = newData; };

	void StartDrawing();
};

