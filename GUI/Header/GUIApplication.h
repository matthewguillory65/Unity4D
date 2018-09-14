#pragma once
#include "../Unity4D/MyApplication.h"
class GUIApplication : public MyApplication
{
	// Inherited via MyApplication
	virtual void Startup() override;
	virtual void Shutdown() override;
	virtual void Update(float dt) override;
	virtual void Draw() override;
};

