//
// Input.cpp
//
#include "Input.hpp"

#include <unordered_set>
using std::unordered_set;


class InputImpl {
private:
	friend class Input;

	// KEY is in set if it is currently down.
	std::unordered_set<KEY> keyDownSet;
};

InputImpl * Input::impl = new InputImpl();


//---------------------------------------------------------------------------------------
bool Input::keyDown(KEY key)
{
	return impl->keyDownSet.count(key) == 1;
}


//---------------------------------------------------------------------------------------
void Input::setKeyDown(KEY key)
{
	impl->keyDownSet.insert(key);
}

//---------------------------------------------------------------------------------------
void Input::setKey(KEY key, bool isDown)
{
	if (isDown) {
		setKeyDown(key);
	}
	else {
		setKeyUp(key);
	}
}

//---------------------------------------------------------------------------------------
void Input::setKeyUp(KEY key)
{
	impl->keyDownSet.erase(key);
}

