#pragma once

#include "Common.h"
#include "entt/entt.hpp"
#include "Scene.h"

namespace Arcane
{
   class Entity
   {
   public:
      Entity() = default;
      Entity(entt::entity handle, Scene* scene);
      Entity(const Entity& other) = default;
      
      operator bool() const { return m_handle != entt::null; }
      operator entt::entity() const { return m_handle; }
      operator uint32_t() const { return (uint32_t)m_handle; }

      template <typename Component, typename... Args>
      Component& AddComponent(Args&&... args)
      {
         ARC_ASSERT(!HasComponent<Component>(), "Entity already has component!");
         Component& component = m_scene->m_registry.emplace<Component>(m_handle, std::forward<Args>(args)...);
         m_scene->OnComponentAdded<Component>(*this, component);
         return component;
      }

      template <typename Component>
      void AddComponent(Component& component)
      {
         ARC_ASSERT(!HasComponent<Component>(), "Entity already has component!");
         m_scene->m_registry.emplace<Component>(m_handle, component);
         m_scene->OnComponentAdded<Component>(*this, component);
      }

      template <typename Component, typename... Args>
      Component& AddOrReplaceComponent(Args&&... args)
      {
         Component& component = m_scene->m_registry.emplace_or_replace<Component>(m_handle, std::forward<Args>(args)...);
         m_scene->OnComponentAdded<Component>(*this, component);
         return component;
      }

      template <typename Component>
      [[nodiscard]] Component& GetComponent() { return m_scene->m_registry.get<Component>(m_handle); }

      template <typename Component>
      bool HasComponent() { return m_scene->m_registry.try_get<Component>(m_handle) != nullptr; }

      template <typename Component>
      void RemoveComponent() { m_scene->m_registry.remove<Component>(m_handle); }
      
   private:
      entt::entity m_handle;
      Scene* m_scene;
   };
} // namespace Arcane
