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
   auto* app = new Arcane::Application(hInstance, nCmdShow);

   app->SetUpdateCallback(Update);
   app->SetFixedUpdateCallback(FixedUpdate);
   app->SetRenderCallback(Render);

   app->Run();
   delete app;
}
