#include "DrawableWire.h"

DrawableWire::DrawableWire(int wireId, bool state)
{
	this->wireId = wireId;
	this->state = state;

	wireActiveColor = sf::Color::Green;
	wireInactiveColor = sf::Color::Red;
	width = 5.0f; // Default width
	position1 = { 0.0f, 0.0f };
	position2 = { 0.0f, 0.0f };
}

void DrawableWire::Draw(sf::RenderWindow& window) const
{
	//draw wire with width and color
	sf::VertexArray line(sf::PrimitiveType::Lines, 2);
	line[0].position = position1;
	line[0].color = state ? wireActiveColor : wireInactiveColor;
	line[1].position = position2;
	line[1].color = state ? wireActiveColor : wireInactiveColor;
	window.draw(line);
}
