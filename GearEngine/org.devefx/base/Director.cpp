#include "Director.h"

static Director *s_SharedDirector = nullptr;

Director::Director()
{
}

Director::~Director()
{
	delete _renderer;

	_renderer = nullptr;
}

Director* Director::getInstance()
{
	if (!s_SharedDirector)
	{
		s_SharedDirector = new (std::nothrow) Director;
		s_SharedDirector->init();
	}
	return s_SharedDirector;
}

bool Director::init()
{

	_renderer = new (std::nothrow) Renderer;

	return true;
}
