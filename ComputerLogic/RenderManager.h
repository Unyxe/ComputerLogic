#pragma once

#include "CircuitManager.h"

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

class RenderManager
{
private:
	sf::RenderWindow renderWindow;

	void pollEvents();
	void Draw(const CircuitManager& circuitManager);

	void DrawGate(std::vector<int> gateData);
	void DrawWire(std::vector<int> wireData);

	const std::vector<std::vector<int>>& SplitVector(const std::vector<int>& vector, int subSize) const;

public:
	RenderManager();
	~RenderManager();

	void StartDrawing(const CircuitManager& circuitManager);
};

