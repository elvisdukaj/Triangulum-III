#include "triangulum/system/WorldSystem.h"
#include "triangulum/EntityFactory.h"

using namespace entityx;

namespace triangulum {
namespace system {


  WorldSystem::WorldSystem(EntityFactory &entity_factory, entityx::EntityManager& entities, entityx::EventManager& eventManager)
: m_entity_factory(entity_factory)
, m_entity_manager(entities)
, m_eventManager(eventManager)
{
  createNewWorld(50, 50);
}

void WorldSystem::createNewWorld(int sizeX, int sizeY)
{
  std::cout << "CREATES NEW WORLD!" << std::endl;

  // creates border walls
  m_entity_factory.create_border_block(m_entity_manager.create(), b2Vec2(20, 0), 10, 2);

  // creates asteroids
  for(int i = 0; i < 50; ++i)  {
    // should check for overlaps as well...
    auto entity = m_entity_manager.create();
    float x = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / sizeX));
    float y = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / sizeY));
    float r = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 360));
    float s = 0.5 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX));

    m_entity_factory.create_simple_asteroid(entity, b2Vec2(x, y), s, r);
  }
}

void WorldSystem::update(entityx::EntityManager& entities,
                          entityx::EventManager& events,
                          entityx::TimeDelta dt)
{
}

void WorldSystem::configure(entityx::EventManager &event_manager)
{
  event_manager.subscribe<CreateWorldEvent>(*this);
}

void WorldSystem::receive(const CreateWorldEvent &createWorld)
{
  createNewWorld(createWorld.sizeX, createWorld.sizeY);
}


}  // namespace system
}  // namespace triangulum
