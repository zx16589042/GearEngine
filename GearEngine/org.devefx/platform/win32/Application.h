#ifndef __APPLICATION_H__
#define __APPLICATION_H__

class Application
{
public:

	Application();

	virtual ~Application();

	int run();

	static Application* getInstance();

private:


	static Application * sm_pSharedApplication;
};

#endif