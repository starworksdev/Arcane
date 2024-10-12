#pragma once

#include <memory>

#include "Common.h"

namespace Arcane
{
   class Scene;

   class System
   {
   public:
      int32_t priority = 0;

      bool operator<(const System& other) const { return priority < other.priority; }
   };

   struct UpdateSystem : public System
   {
      std::function<void(std::shared_ptr<Scene>, float32_t)> system;

      void operator()(std::shared_ptr<Scene> scene, float32_t deltaTime) { system(scene, deltaTime); }
      void operator()(std::shared_ptr<Scene> scene, float32_t deltaTime) const { system(scene, deltaTime); }
   };

   struct RenderSystem : public System
   {
      std::function<void(std::shared_ptr<Scene>)> system;

      void operator()(std::shared_ptr<Scene> scene) { system(scene); }
      void operator()(std::shared_ptr<Scene> scene) const { system(scene); }
   };
} // namespace Arcane
