//
// Input.hpp
//
#pragma once

#include <vector>

// Forward declare.
class InputImpl;
enum class KEY;

class Input {
public:

	static bool keyDown(KEY key);

	static void setKeyDown(KEY key);

	static void setKey(KEY key, bool isDown);

	static void setKeyUp(KEY key);
	

private:
	static InputImpl * impl;
};

enum class KEY {
	LEFT,
	UP,
	RIGHT,
	DOWN,
	SPACE
};

