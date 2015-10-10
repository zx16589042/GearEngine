#ifndef __DIRECTOR_H__
#define __DIRECTOR_H__

#include <stack>

#include "../renderer/Renderer.h"

class Director
{
public:
	static Director* getInstance();

	Director();
	virtual ~Director();
	virtual bool init();
private:
	Renderer *_renderer;
};

#endif