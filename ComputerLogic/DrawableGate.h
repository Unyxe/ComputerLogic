#pragma once

#include <SFML/Graphics.hpp>

#include "GateRenderData.h"

class DrawableGate
{
private:
	int gateId;
	int gateType;
	int gateInputCount;
	int gateOutputCount;

	std::vector<bool> inputStates;
	std::vector<bool> outputStates;

	sf::Color gateColor;
	
	sf::Vector2f position;
	sf::Vector2f size;
public:
	DrawableGate(GateRenderData data);

	void Draw(sf::RenderWindow& window) const;
	
	const sf::Vector2f& GetPosition() const { return position; };
	const sf::Vector2f& GetSize() const { return size; };

	void SetPosition(const sf::Vector2f& pos) { position.x = pos.x; position.y = pos.y; };

	sf::Vector2f GetInputPosition(int index);
	sf::Vector2f GetOutputPosition(int index);
};

