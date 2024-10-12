#pragma once

#include <algorithm>
#include <functional>
#include <map>
#include <memory>
#include <vector>

#include "Common.h"
#include "entt/entt.hpp"
#include "System.h"
#include "Util/UUID.h"

namespace Arcane
{
   template<typename SystemType>
   class SortedSystemList
   {
   public:
      SortedSystemList(size_t capacity = 32)
      {
         m_systems.reserve(capacity);
      }

      ~SortedSystemList() = default;

      void Insert(const SystemType& system)
      {
         auto it = std::lower_bound(m_systems.begin(), m_systems.end(), system,
            [](const SystemType& a, const SystemType& b) { return a.priority < b.priority; });
         m_systems.insert(it, system);
      }

      typename std::vector<SystemType>::const_iterator begin() const { return m_systems.begin(); }
      typename std::vector<SystemType>::const_iterator end() const { return m_systems.end(); }

   private:
      std::vector<SystemType> m_systems;
   };

   class Entity;

   class Scene : public std::enable_shared_from_this<Scene>
   {
   public:
      Scene();
      ~Scene();

      Entity CreateEntity(const std::string& name = std::string());
      Entity CreateEntity(UUID uuid, const std::string& name = std::string());
      void DestroyEntity(Entity entity);

      Entity FindEntity(const std::string& name);
      Entity GetEntity(UUID uuid);
		
      template <typename... Components>
		auto GetEntitiesWith() { return m_registry.view<Components...>(); }

      void OnStart();
      void OnStop();

      void Update(float32_t deltaTime);
      void FixedUpdate(float32_t timeStep);
      void Render();

      void AddUpdateSystem(const UpdateSystem& system) { m_updateSystems.Insert(system); }
      void AddFixedUpdateSystem(const UpdateSystem& system) { m_fixedUpdateSystems.Insert(system); }
      void AddRenderSystem(const RenderSystem& system) { m_renderSystems.Insert(system); }

      bool IsRunning() const { return m_running; }

   private:
      template <typename T>
      void OnComponentAdded(Entity entity, T& component);

      entt::registry m_registry;
      std::unordered_map<UUID, entt::entity> m_entityMap;

      SortedSystemList<UpdateSystem> m_updateSystems;
      SortedSystemList<UpdateSystem> m_fixedUpdateSystems;
      SortedSystemList<RenderSystem> m_renderSystems;

      bool m_running;
      bool m_paused;

      friend class Entity;
   };
} // namespace Arcane
