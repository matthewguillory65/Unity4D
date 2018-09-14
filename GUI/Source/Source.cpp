#include "GUIApplication.h"


int main()
{
	MyApplication* app = new GUIApplication();
	app->run("guiboi", 800, 600, false);
}