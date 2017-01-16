#include "triangulum/system/ConnectionSystem.h"

#include "triangulum/EntityFactory.h"
#include "triangulum/component/ClientInfo.h"

using namespace entityx;

namespace triangulum {
namespace system {

using namespace component;
using namespace network;

ConnectionSystem::ConnectionSystem()
: m_server()
{
}

void ConnectionSystem::update(EntityManager& entities,
                              EventManager& events,
                              TimeDelta dt)
{
   m_server.process_input();

   m_server.handle_pending_connections([this, &entities] (std::shared_ptr<IConnection> connection) {

      nlohmann::json msg;

      if (!connection->get_msg("login", msg))
      {
         return false;
      }

      if (!msg["name"].is_string())
      {
         std::cout << "Login message format not ok\n";

         send_negative_reply(connection);

         return false;
      }

      std::string name = msg["name"];

      if (does_name_exist(entities, name))
      {
         std::cout << "User name already exists\n";

         send_negative_reply(connection);

         return false;
      }

      auto entity = entities.create();

      EntityFactory::create_player(entity, connection, name);

      send_poistive_reply(connection, entity.id().id());

      std::cout << "New player (" << name << ") created\n";

      return true;
   });


   entities.each<ClientInfo>([](Entity entity, ClientInfo& client_info) {
      if (client_info.connection.expired())
      {
        std::cout << client_info.name << " disconnected\n";
         entity.destroy();
      }
   });
}

bool ConnectionSystem::does_name_exist(EntityManager& entities,
                                       const std::string& name)
{
   ComponentHandle<ClientInfo> client_info;

   for (auto entity : entities.entities_with_components(client_info))
   {
      (void) entity;

      if (client_info.get()->name == name)
      {
         return true;
      }
   }

   return false;
}

void ConnectionSystem::send_poistive_reply(std::shared_ptr<IConnection> connection, uint64_t id)
{
   nlohmann::json resp_msg;

   resp_msg["type"] = "login_resp";

   resp_msg["status"] = "success";

   resp_msg["id"] = id;

   connection->send_msg(resp_msg);
}

void ConnectionSystem::send_negative_reply(std::shared_ptr<IConnection> connection)
{
   nlohmann::json resp_msg;

   resp_msg["type"] = "login_resp";

   resp_msg["status"] = "failure";

   resp_msg["id"] = -1;

   connection->send_msg(resp_msg);
}

} // namespace system
} // namespace triangulum
