#pragma once

template <typename T>
struct Bounds2
{
	sf::Vector2<T> Min;
	sf::Vector2<T> Max;

	Bounds2() = default;
	Bounds2(sf::Vector2<T> min, sf::Vector2<T> max) :
		Min{ min },
		Max{ max }
	{

	}

	sf::Vector2<T> GetSize() const { return Max - Min; }
	T GetSizeX() const { return Max.x - Min.x; }
	T GetSizeY() const { return Max.y - Min.y; }

	sf::Vector2<T> GetCenter() const { return sf::Vector2<T>{ (T)((Min.x + Max.x) * 0.5f), (T)((Min.y + Max.y) * 0.5f) }; }

	Bounds2& operator+=(sf::Vector2<T> vector)
	{
		Min += vector;
		Max += vector;
		return *this;
	}
	Bounds2& operator-=(sf::Vector2<T> vector)
	{
		Min -= vector;
		Max -= vector;
		return *this;
	}

};

using Bounds2f = Bounds2<float>;
using Bounds2u = Bounds2<uint32_t>;