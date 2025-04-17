#include "DrawableGate.h"
DrawableGate::DrawableGate(int gateId, int gateTypeId, int gateInputCount, int gateOutputCount)
{
	this->gateId = gateId;
	this->gateType = gateTypeId;
	this->gateInputCount = gateInputCount;
	this->gateOutputCount = gateOutputCount;


	// Set default size and color
	size = { 50.0f, 50.0f };
	gateColor = sf::Color::White;
	// Set default position
	position = { 0.0f, 0.0f };
}

void DrawableGate::Draw(sf::RenderWindow& window) const
{
}

sf::Vector2f DrawableGate::GetInputPosition(int index)
{
	return { position.x + (size.x / (gateInputCount + 1)) * (index + 1), position.y };
}

sf::Vector2f DrawableGate::GetOutputPosition(int index)
{
	return { position.x + (size.x / (gateOutputCount + 1)) * (index + 1), position.y + size.y };
}
