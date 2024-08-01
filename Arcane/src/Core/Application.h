#pragma once

#include <functional>

#include "Window.h"

namespace Arcane
{
   class Application
   {
   public:
      static constexpr uint32_t TARGET_UPDATES_PER_SECOND = 60U;
      static constexpr uint32_t MAX_ACCUMULATED_UPDATES = 5U;

      Application(HINSTANCE hInstance, int nCmdShow);
      ~Application();

      void Run();

      void SetUpdateCallback(std::function<void(float)> callback)       { m_updateCallback = callback; }
      void SetFixedUpdateCallback(std::function<void(float)> callback)  { m_fixedUpdateCallback = callback; }
      void SetRenderCallback(std::function<void()> callback)            { m_renderCallback = callback; }

   private:
      bool Initialize(HINSTANCE hInstance, int nCmdShow);

      void Update(float deltaTime);
      void FixedUpdate(float timeStep);
      void Render();

      void Cleanup();

      Window* m_window;

      uint32_t m_framesPerSecond;
      uint32_t m_updatesPerSecond;
      uint32_t m_fixedUpdatesPerSecond;

      std::function<void(float)> m_updateCallback;
      std::function<void(float)> m_fixedUpdateCallback;
      std::function<void()> m_renderCallback;

   };
}