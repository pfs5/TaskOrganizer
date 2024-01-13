#pragma once

template <typename T>
struct AABB
{
	sf::Vector2<T> Min;
	sf::Vector2<T> Max;

	AABB() = default;
	AABB(const sf::Vector2<T>& min, const sf::Vector2<T>& max) :
		Min{ min },
		Max{ max }
	{

	}

	bool IsPointInside(T x, T y)
	{
		return x >= Min.x && x <= Max.x &&
			y >= Min.y && y <= Max.y;
	}
};