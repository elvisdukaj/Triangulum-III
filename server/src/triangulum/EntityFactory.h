#ifndef _ENTITY_FACTORY_H
#define _ENTITY_FACTORY_H

#include "entityx/Entity.h"

namespace triangulum {

namespace network {
class IConnection;
} // namesapce network

class EntityFactory
{
public:
   EntityFactory();

   ~EntityFactory();

   static void create_player(entityx::Entity entity,
                             const std::string& name,
                             const std::weak_ptr<network::IConnection>& connection);
};

} // namespace triangulum

#endif
