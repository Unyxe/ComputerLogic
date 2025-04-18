#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class DrawingHelper
{

public:
	static void DrawStateCircle(sf::RenderWindow& window, const sf::Vector2f& position, bool state)
	{
		sf::CircleShape outline(12);
		outline.setFillColor(sf::Color::Black);
		outline.setPosition(position - sf::Vector2f(12, 12));
		window.draw(outline);

		sf::CircleShape circle(10);
		circle.setFillColor(state ? sf::Color::Red : sf::Color::Color(52,24,26));
		circle.setPosition(position - sf::Vector2f(10, 10));
		window.draw(circle);
	};

	static void DrawRoundedRectangle(sf::RenderWindow& window, const sf::Vector2f& position, const sf::Vector2f& size, float radius, const sf::Color& color)
	{
		std::vector<sf::Vertex> vertices;

		int circlePointCount = 32;

		for (int i = 0; i < circlePointCount; i++) {
			float angle = (float)i / (float)circlePointCount * 3.14159f * 2.0f;
			float x = radius * cos(angle);
			float y = radius * sin(angle);
			sf::Vertex vertex;
			vertex.position = sf::Vector2f(x, y) + position;

			if (i < circlePointCount / 4) {
				vertex.position.x += size.x/2-radius;
				vertex.position.y += size.y/2-radius;
			}
			else if (i < circlePointCount / 2) {
				vertex.position.x -= size.x/2-radius;
				vertex.position.y += size.y/2-radius;
			}
			else if (i < 3 * circlePointCount / 4) {
				vertex.position.x -= size.x/2 - radius;
				vertex.position.y -= size.y/2 - radius;
			}
			else {
				vertex.position.x += size.x/2-radius;
				vertex.position.y -= size.y/2-radius;
			}

			vertex.color = color;
			vertices.push_back(vertex);
		}

		window.draw(&vertices[0], vertices.size(), sf::PrimitiveType::TriangleFan);
	};

	static void DrawRoundedWithOutline(sf::RenderWindow& window, const sf::Vector2f& position, const sf::Vector2f& size, float radius, float outlineWidth ,const sf::Color& color, const sf::Color& outlineColor)
	{
		DrawRoundedRectangle(window, position, size + sf::Vector2f(outlineWidth*2, outlineWidth*2), radius + outlineWidth, outlineColor);
		DrawRoundedRectangle(window, position, size, radius, color);
	};

	static void DrawWire(sf::RenderWindow& window, const std::vector<sf::Vector2f> points, float wireThickness, const sf::Color& wireColor) {
		sf::VertexArray wire(sf::PrimitiveType::TriangleStrip , points.size() * 4 - 4);
		for (size_t i = 1; i < points.size(); ++i) {
			auto vecA = points[i]-points[i-1];
			auto vecN = sf::Vector2f(-vecA.y*wireThickness/sqrt(vecA.y*vecA.y + vecA.x*vecA.x), vecA.x * wireThickness / sqrt(vecA.y * vecA.y + vecA.x * vecA.x));
			wire[4*i-4] = sf::Vertex{ points[i-1] + vecN, wireColor };
			wire[4 * i - 3] = sf::Vertex{ points[i - 1] - vecN, wireColor };
			wire[4 * i - 2] = sf::Vertex{ points[i] + vecN, wireColor };
			wire[4*i-1] = sf::Vertex{ points[i] - vecN, wireColor };
		}
		window.draw(wire);
	};


	static std::vector<sf::Vector2f> GenerateBezierCurve(const sf::Vector2f& start, const sf::Vector2f& end, const sf::Vector2f& control1, const sf::Vector2f& control2, int numPoints)
	{
		std::vector<sf::Vector2f> points;
		points.reserve(numPoints);
		for (int i = 0; i <= numPoints; ++i) {
			float t = static_cast<float>(i) / static_cast<float>(numPoints);
			float u = 1 - t;
			sf::Vector2f point = u * u * u * start +
				3 * u * u * t * control1 +
				3 * u * t * t * control2 +
				t * t * t * end;
			points.push_back(point);
		}
		return points;
	};

	static std::vector<sf::Vector2f> GenerateCircleTurnsCurves(const std::vector<sf::Vector2f> points, float radius) {
		std::vector<sf::Vector2f> curves;
		for (size_t i = 0; i < points.size(); ++i) {
			
		}
		return curves;
	}
};

