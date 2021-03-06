#ifndef ENEMY_INCLUDED_C60D1C26_65C3_4BF9_AAA6_23A27358D168
#define ENEMY_INCLUDED_C60D1C26_65C3_4BF9_AAA6_23A27358D168


#include <game_objects/game_object.hpp>
#include <game_objects/game_objects_fwd.hpp>
#include <core/world/world_fwd.hpp>
#include <core/entity/entity.hpp>
#include <stdint.h>


namespace Game_object {


class Enemy : public Game_object
{
public:

  enum class Type
  {
    climber,    // Climbs up and down.
    shooter,    // Stays at the bottom and shoots up.
    breeder,    // Climbs to the top and drops eggs.
    boomerang,  // Spins all the way to the top.
    
    
    egg,      // Spaned by the breader. // Keep this the last type, we use size - 1 not to spawn eggs.
    
    size // nothing under here.
  };
  
  explicit        Enemy(Core::World &world, Type type);
  void            on_start() override;
  void            on_update(const float dt, World_objects &objs) override;
  void            on_collision(Game_object *other) override;
  void            on_message(const uint32_t id, void *data) override;

//private:

  float           m_point_on_circle = 0;
  float           m_depth = 0;
  float           m_lifetime = 0;
  int32_t         m_direction = 1;
  int32_t         m_user_data = 0;
  const Type      m_type = Type::climber;
  uint32_t        m_destroyed_by = UINT32_MAX;
  
  enum class State
  {
    alive,
    dying,
    dying_with_powerup_chance,
    dead,
  };
  
  State           m_state = State::alive;

};


namespace Enemy_utils {


/*
  General utilitiy class to update the position of an enemy on the tube.
*/
void
update_position(Core::Entity_ref ref,
                const float position_on_circle,
                const float depth);


} // ns


} // ns


#endif // inc guard