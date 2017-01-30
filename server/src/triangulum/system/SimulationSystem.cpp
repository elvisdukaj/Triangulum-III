#include "triangulum/system/SimulationSystem.h"

using namespace entityx;

namespace triangulum {
namespace system {

SimulationSystem::SimulationSystem(b2World& world)
: m_world(world)
, m_velocityIterations(8)  // how strongly to correct velocity
, m_positionIterations(3)  // how strongly to correct position
{  
  world.SetContactListener(this);
}

void SimulationSystem::update(EntityManager& entities, EventManager& events,
                              TimeDelta dt)
{
  m_world.Step(dt, m_velocityIterations, m_positionIterations);
}

void SimulationSystem::BeginContact(b2Contact* contact) {
  std::cout << "BAM! Contact!" << std::endl;
  /*
  //check if fixture A was a ball
  void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
  if ( bodyUserData )
    static_cast<Ball*>( bodyUserData )->startContact();
  
  //check if fixture B was a ball
  bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
  if ( bodyUserData )
    static_cast<Ball*>( bodyUserData )->startContact();
  */
}
  
void SimulationSystem::EndContact(b2Contact* contact) {
    std::cout << "Bye bye! No more contact" << std::endl;
  /*
  //check if fixture A was a ball
  void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
  if ( bodyUserData )
  static_cast<Ball*>( bodyUserData )->endContact();
  
  //check if fixture B was a ball
  bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
  if ( bodyUserData )
  static_cast<Ball*>( bodyUserData )->endContact();
  */
}

}  // namespace system
}  // namespace triangulum
