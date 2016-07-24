//
// EntityGenerator.inl
//

#ifndef _ENTITY_GENERATOR_INL_
#define _ENTITY_GENERATOR_INL_

#include "EntityGenerator.hpp"

template <class T>
class EntityGeneratorImpl {
private:
	template <class T>
	friend class EntityGenerator;

	EntityGeneratorImpl(
		T * prototype
	);

	T * prototype;
	//EntityPool<T> & entityPool;
};

//---------------------------------------------------------------------------------------
template <class T>
EntityGeneratorImpl<T>::EntityGeneratorImpl(
	T * prototype
)
	: prototype(prototype)
{

}

//---------------------------------------------------------------------------------------
template <class T>
EntityGenerator<T>::EntityGenerator(
	T * prototype
)
{
	impl = new EntityGeneratorImpl<T>(prototype);
}

//---------------------------------------------------------------------------------------
template <class T>
EntityGenerator<T>::~EntityGenerator()
{
	delete impl;
	impl = nullptr;
}

#endif // _ENTITY_GENERATOR_INL_ 
