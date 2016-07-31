//
// CannonScript.hpp
//
#include "Script/Script.hpp"

class CannonScript : public Script {
public:

	virtual void init();

	virtual void update();

private:
	GameObject * m_cannon;
};