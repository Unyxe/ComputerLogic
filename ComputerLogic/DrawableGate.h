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
	void Draw(sf::RenderWindow& window) const;
	
	const sf::Vector2f& GetPosition() const;
	const sf::Vector2f& GetSize() const;

};

