#ifndef __GEVIEW_H__
#define __GEVIEW_H__

#include <string>

class GEView
{
public:
	GEView();

	virtual ~GEView();

	virtual void setViewName(const std::string& viewname);

	const std::string& getViewName() const;

protected:
	std::string _viewName;
};

#endif