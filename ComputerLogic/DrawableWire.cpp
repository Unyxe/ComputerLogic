#include "DrawableWire.h"

#include "DrawingHelper.h"

DrawableWire::DrawableWire(WireRenderData data)
{
	wireId = data.wireId;
	state = data.wireState;
	wireActiveColor = sf::Color::Green;
	wireInactiveColor = sf::Color::Red;
	width = data.width;
}

void DrawableWire::Draw(sf::RenderWindow& window) const
{
	//draw wire with width and color
	/*sf::VertexArray line(sf::PrimitiveType::Lines, 2);
	line[0].position = position1;
	line[0].color = state ? wireActiveColor : wireInactiveColor;
	line[1].position = position2;
	line[1].color = state ? wireActiveColor : wireInactiveColor;
	window.draw(line);*/



	std::vector<sf::Vector2f> points = {
		position1,
		{(position1.x + position2.x) / 2, position1.y},
		{(position1.x + position2.x) / 2, position2.y},
		position2
	};
	auto c = DrawingHelper::GenerateCircleTurnsCurves(points, 30);
	DrawingHelper::DrawWire(window, c , 3, state ? wireActiveColor : wireInactiveColor);
}
