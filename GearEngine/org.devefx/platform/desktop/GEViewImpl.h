#ifndef __GEVIEWIMPL_H__
#define __GEVIEWIMPL_H__

#include <windows.h>

#include "../GEView.h"
#include "../../math/Geometry.h"

class GEViewImpl : public GEView
{
public:
	static GEViewImpl* create(const std::string viewName);
	static GEViewImpl* create(const std::string viewName, Size size);

	void setViewName(const std::string& viewname);
protected:
	GEViewImpl();
	virtual ~GEViewImpl();

	bool initWithRect(const std::string viewName, Size size);

private:
	HWND hwnd;
};

#endif