//
// EntityGenerator.hpp
//
#pragma once

// Forward declare.
template <class T>
class EntityGeneratorImpl;


// Class for generating copies of a prototype entity.
// All newly created T objects will be allocated in the entityPool provided.
template <class T>
class EntityGenerator {
public:
	EntityGenerator(T * prototype);
	~EntityGenerator();

	T * setPrototype(T * prototype);


private:
	EntityGeneratorImpl<T> * impl;

};


#include "EntityGenerator.inl"

