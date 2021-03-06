#ifndef EXPLOSION_INCLUDED_0377F28D_5ECA_4177_88FD_311040A61AC5
#define EXPLOSION_INCLUDED_0377F28D_5ECA_4177_88FD_311040A61AC5


#include <game_objects/game_object.hpp>
#include <math/vec/vec_types.hpp>


namespace Game_object {


class Explosion : public Game_object
{
public:
  
  explicit        Explosion(Core::World &world,
                            const math::vec3 position,
                            const float scale_mul = 2.f);
  
  void            on_update(const float dt, World_objects &objs) override;

private:

  float m_time = 0.f;
  float m_scale_mul = 2.f;
  bool m_reproduced = false;

};


} // ns


#endif // inc guard