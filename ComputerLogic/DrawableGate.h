#pragma once

#include <SFML/Graphics.hpp>

class DrawableGate
{
private:
	int gateId;
	int gateType;
	int gateInputCount;
	int gateOutputCount;

	sf::Color gateColor;
	
	sf::Vector2f position;
	sf::Vector2f size;
public:
	DrawableGate(int gateId, int gateTypeId, int gateInputCount, int gateOutputCount);

	void Draw(sf::RenderWindow& window) const;
	
	const sf::Vector2f& GetPosition() const { return position; };
	const sf::Vector2f& GetSize() const { return size; };

	void SetPosition(const sf::Vector2f& pos) { position.x = pos.x; position.y = pos.y; };

	sf::Vector2f GetInputPosition(int index);
	sf::Vector2f GetOutputPosition(int index);
};

