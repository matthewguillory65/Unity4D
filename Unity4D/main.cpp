#include <iostream>
#include "MyApplication.h"

int main()
{
	MyApplication* theApp = new MyApplication();
	if (theApp->startUp() == true)
		while (theApp->Update() == true)
			theApp->Draw();

	return 0;
}