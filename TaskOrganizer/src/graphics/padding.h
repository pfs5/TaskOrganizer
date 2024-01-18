#pragma once

template <typename T>
struct Padding
{
	T Left;
	T Right;
	T Top;
	T Bottom;

	Padding()
	{
		std::memset(this, 0x00, sizeof(Padding));
	}

	Padding& SetLeft(T value) { Left = value; return *this; }
	Padding& SetRight(T value) { Right = value; return *this; }
	Padding& SetTop(T value) { Top = value; return *this; }
	Padding& SetBottom(T value) { Bottom = value; return *this; }
};

using PaddingF = Padding<float>;