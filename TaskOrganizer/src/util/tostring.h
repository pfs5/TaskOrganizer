#pragma once

template<typename ... Args>
std::string StringFormat(const char* format, Args... args)
{
	const int size_s = std::snprintf(nullptr, 0, format, args ...) + 1; // Extra space for '\0'
	const size_t size = static_cast<size_t>(size_s);
	std::unique_ptr<char[]> buf(new char[size]);
	std::snprintf(buf.get(), size, format, args ...);
	return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

inline std::string ToString(const sf::Vector2<float>& v)
{
	return StringFormat("{%.2f, %.2f}", v.x, v.y);
}

template <typename Int/*, std::enable_if_t<std::is_integral<Int>::value, bool> = true*/>
inline std::string ToString(const sf::Vector2<Int>& v)
{
	return StringFormat("{%d, %d}", v.x, v.y);
}

inline std::string ToString(bool value)
{
	return value ? "true" : "false";
}

template<typename T>
std::string ToString(const T& value)
{
	return "Please define a ToString specialization";
}