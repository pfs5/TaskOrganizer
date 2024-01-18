#pragma once

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstdint>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <random>
#include <regex>
#include <string>
#include <vector>

#include "SFML/Graphics/Color.hpp"
#include "SFML/System/Vector2.hpp"

#include "math/bounds.h"
#include "util/asserts.h"
#include "util/tostring.h"

#define USE_DEBUG \
	!defined(_RELEASE)