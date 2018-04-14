#include <cmath>
#include <vector>

#include <SFML/System/Vector2.hpp>

#include "../../include/Utils/Math.h"

namespace ae
{
	const float Math::PI = 3.14159265359f;

	float Math::toDegrees(float radians)
	{
		return radians * 180.f / PI;
	}

	float Math::toRadians(float degrees)
	{
		return degrees * PI / 180.f;
	}

	sf::Vector2f Math::normalize(const sf::Vector2f& vec)
	{
		return vec / std::hypot(vec.x, vec.y);
	}

	sf::Vector2f Math::normalize(const sf::Vector2f& vec1, const sf::Vector2f& vec2)
	{
		const sf::Vector2f SEGMENT(vec1.y - vec2.y, vec2.x - vec1.x);
		const float LENGTH = std::hypot(SEGMENT.x, SEGMENT.y);

		// Returns the normalized segment if it's dividable by 0
		return LENGTH != 0.f ? SEGMENT / LENGTH : SEGMENT;
	}

	float Math::dotProduct(const sf::Vector2f& vec1, const sf::Vector2f& vec2)
	{
		return vec1.x * vec2.x + vec1.y * vec2.y;
	}

	std::vector<int> Math::pascalTriangle(int n)
	{
		std::vector<int> row(n + 1);
		row[0] = 1;
		for (int i = 1; i < n / 2 + 1; i++)
			row[i] = row[i - 1] * (n - i + 1) / i;

		for (int i = n / 2 + 1; i <= n; i++)
			row[i] = row[n - i];

		return row;
	}
}