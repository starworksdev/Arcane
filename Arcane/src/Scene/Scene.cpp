#include "Scene.h"

#include "Components.h"
#include "Core/Console.h"
#include "Entity.h"
#include "Math/Geometry.h"

Arcane::Scene::Scene() :
   m_running(false),
   m_paused(false)
{
}

Arcane::Scene::~Scene()
{
}

Arcane::Entity Arcane::Scene::CreateEntity(const std::string& name /*= std::string()*/)
{
   return CreateEntity(UUID(), name);
}

Arcane::Entity Arcane::Scene::CreateEntity(UUID uuid, const std::string& name /*= std::string()*/)
{
   Entity entity = { m_registry.create(), this };
   
   entity.AddComponent<Components::ID>(uuid);
   static const std::string defaultName = "Entity";
   entity.AddComponent<Components::Tag>(name.empty() ? defaultName : name);
   entity.AddComponent<Components::Transform>();
   
   m_entityMap[uuid] = entity;

   return entity;
}

void Arcane::Scene::DestroyEntity(Entity entity)
{
   m_entityMap.erase(entity.GetComponent<Components::ID>());
   m_registry.destroy(entity);
}

Arcane::Entity Arcane::Scene::FindEntity(const std::string& name)
{
   auto view = m_registry.view<Components::Tag>();
   for (auto entity : view)
   {
      const auto& tag = view.get<Components::Tag>(entity);
      if (tag == name)
         return Entity{ entity, this };
   }

   return Entity{};
}

Arcane::Entity Arcane::Scene::GetEntity(UUID uuid)
{
   auto entity = m_entityMap.find(uuid);
   if (entity != m_entityMap.end())
      return Entity{ entity->second, this };

   return Entity{};
}

void Arcane::Scene::OnStart()
{
   m_running = true;
}

void Arcane::Scene::OnStop()
{
   m_running = false;
}

void Arcane::Scene::Update(float32_t deltaTime)
{
   if (m_running && !m_paused)
   {
      for (const auto& system : m_updateSystems)
      {
         system(shared_from_this(), deltaTime);
      }
   }
}

void Arcane::Scene::FixedUpdate(float32_t timeStep)
{
   if (m_running && !m_paused)
   {
      for (auto& system : m_fixedUpdateSystems)
      {
         system(shared_from_this(), timeStep);
      }
   }
}

void Arcane::Scene::Render()
{
   if (m_running)
   {
      for (auto& system : m_renderSystems)
      {
         system(shared_from_this());
      }
   }
}

template <typename T>
void Arcane::Scene::OnComponentAdded(Entity entity, T& component)
{
   static_assert(sizeof(T) == 0);
}

template <>
void Arcane::Scene::OnComponentAdded<Arcane::Components::ID>(Entity entity, Components::ID& component)
{
}

template <>
void Arcane::Scene::OnComponentAdded<Arcane::Components::Tag>(Entity entity, Components::Tag& component)
{
}

template <>
void Arcane::Scene::OnComponentAdded<Arcane::Components::Transform>(Entity entity, Components::Transform& component)
{
}
