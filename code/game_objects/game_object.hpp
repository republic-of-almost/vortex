#ifndef GAME_OBJECT_INCLUDED_2CB14921_92BB_4CBD_8249_46751E7DBDD9
#define GAME_OBJECT_INCLUDED_2CB14921_92BB_4CBD_8249_46751E7DBDD9


#include <core/world/world_fwd.hpp>
#include <core/entity/entity.hpp>
#include <core/entity/entity_ref.hpp>


namespace Game_object {


class Game_object
{
public:

  explicit            Game_object(Core::World &world);
  virtual             ~Game_object();
  
  virtual void        on_start()                        {}
  virtual void        on_update(const float dt)         {}
  virtual void        on_end()                          {}
  virtual void        on_collision(Game_object *other)  {}
  
  Core::Entity_ref    get_entity() const;
  
private:

  Core::World       &m_world;
  Core::Entity      m_entity;

};


} // ns


#endif // inc guard