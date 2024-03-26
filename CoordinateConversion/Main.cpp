#include "stdafx.h"
#include "include/Application.h"

//Hide Console in the background when running release build.
//////////////////#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

int main()
{
	Application app;
	app.appLoop();

	return 0;
}
