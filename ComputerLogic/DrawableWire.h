#pragma once

#include "SFML/Graphics.hpp"

class DrawableWire
{
private:
	int wireId;
	bool state;

	sf::Color wireActiveColor;
	sf::Color wireInactiveColor;

	sf::Vector2f position1;
	sf::Vector2f position2;

	float width;

public:
	DrawableWire(int wireId, bool state);

	void Draw(sf::RenderWindow& window) const;

	const sf::Vector2f& GetPosition1() const { return position1; };
	const sf::Vector2f& GetPosition2() const { return position2; };
	float GetWidth() const { return width; };

	void SetState(bool state)
	{
		this->state = state;
	};
	void SetPosition(const sf::Vector2f& pos1, const sf::Vector2f& pos2)
	{
		position1.x = pos1.x;
		position1.y = pos1.y;
		position2.x = pos2.x;
		position2.y = pos2.y;
	};
};

