#include "DrawableGate.h"

#include "DrawingHelper.h"


DrawableGate::DrawableGate(int gateId, int gateTypeId, int gateInputCount, int gateOutputCount)
{
	this->gateId = gateId;
	this->gateType = gateTypeId;
	this->gateInputCount = gateInputCount;
	this->gateOutputCount = gateOutputCount;


	// Set default size and color
	size = { 125.0f, 80.0f };
	gateColor = sf::Color::Color(203, 107, 46);
	// Set default position
	position = { 0.0f, 0.0f };
}

void DrawableGate::Draw(sf::RenderWindow& window) const
{

	DrawingHelper::DrawRoundedWithOutline(window, position, size, 10.0f, 3.f,gateColor, sf::Color::Color(gateColor.r/2,gateColor.g/2,gateColor.b/2));



	for (int i = 0; i < gateInputCount; i++) {
		float x = position.x - size.x / 2;
		float y = position.y - size.y / 2 + (size.y / (gateInputCount + 1)) * (i + 1);

		DrawingHelper::DrawStateCircle(window, { x, y }, false);
	}

	for (int i = 0; i < gateOutputCount; i++) {
		float x = position.x + size.x / 2;
		float y = position.y - size.y / 2 + (size.y / (gateOutputCount + 1)) * (i + 1);

		DrawingHelper::DrawStateCircle(window, { x, y }, false);
	}
}

sf::Vector2f DrawableGate::GetInputPosition(int index)
{
	return { position.x - size.x/2, position.y - size.y / 2 + (size.y / (gateInputCount + 1)) * (index + 1)};
}

sf::Vector2f DrawableGate::GetOutputPosition(int index)
{
	return { position.x + size.x/2, position.y - size.y / 2 + (size.y / (gateOutputCount + 1)) * (index + 1) };
}
