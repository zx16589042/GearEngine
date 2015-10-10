#include "Application.h"

Application * Application::sm_pSharedApplication = 0;

Application::Application()
{

}

Application::~Application()
{
	sm_pSharedApplication = nullptr;
}

int Application::run()
{







	return 0;
}

Application* Application::getInstance()
{
	return sm_pSharedApplication;
}
