#include "Arcane.h"

void Update(float dt)
{
}

void FixedUpdate(float ts)
{
}

void Render()
{
}

ARC_API void EntryPoint(HINSTANCE hInstance, int nCmdShow)
{
   auto app = Arcane::Application::Create(hInstance, nCmdShow);

   app->RegisterUpdateCallback(Update);
   app->RegisterFixedUpdateCallback(FixedUpdate);
   app->RegisterRenderCallback(Render);

   app->Run();
}