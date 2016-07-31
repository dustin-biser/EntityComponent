//
// ScriptSystem.hpp
//

// Forward declare.
template <class T>
class ComponentPool;
class Script;


class ScriptSystem {
public:

	// Calls Script::init() on call active Script Components.
	static void init();

	// Calls Script::update() on call active Script Components.
	static void update();

private:
	static ComponentPool<Script> * m_scriptPool;
};
