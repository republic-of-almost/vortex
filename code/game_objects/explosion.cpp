#include <game_objects/explosion.hpp>
#include <game_objects/world_objects.hpp>
#include <common/object_tags.hpp>
#include <core/model/model.hpp>
#include <core/resources/texture.hpp>
#include <core/resources/material.hpp>
#include <core/resources/shader.hpp>
#include <core/transform/transform.hpp>
#include <core/renderer/renderer.hpp>
#include <core/renderer/material_renderer.hpp>
#include <math/vec/vec3.hpp>
#include <math/quat/quat.hpp>
#include <math/general/general.hpp>
#include <core/common/directory.hpp>


namespace
{
  Core::Model model;
  Core::Texture texture;
  
  Core::Material material;
}


namespace Game_object {

  
Explosion::Explosion(Core::World &world,
                     const math::vec3 position,
                     const float scale_mul)
: Game_object(world)
, m_time(0.f)
, m_scale_mul(scale_mul)
, m_reproduced(m_scale_mul < 0.1f)
{
  // Load missing assets
  {
    if(!material)
    {
      const char *grid_texture_path = Core::Directory::resource_path("assets/textures/dev_colored_squares_512.png");
      Core::Texture texture(grid_texture_path);
      
      const char *shader_path = Core::Directory::resource_path("assets/shaders/basic_fullbright.ogl");
      Core::Shader shader(shader_path);
      
      material = Core::Material("Explosion");
      material.set_shader(shader);
      material.set_map_01(texture);
    }
  
    if(!model)
    {
      const char *unit_cube_path = Core::Directory::resource_path("assets/models/unit_sphere.obj");
      model = Core::Model(unit_cube_path);
    }
  }

  // Setup entity
  {
    Core::Entity_ref ref = get_entity();

    ref.set_name("Explosion");
    ref.add_tag(Object_tags::explosion | Object_tags::world_cam);
    
    Core::Material_renderer mat_renderer;
    mat_renderer.set_model(model);
    mat_renderer.set_material(material);
    
    ref.set_renderer(mat_renderer);
    
    const Core::Transform transform(
      position,
      math::vec3_zero(),
      math::quat_init()
    );
    
    ref.set_transform(transform);
  }
  
  // Other
  m_time = 0;
}


void
Explosion::on_update(const float dt, World_objects &objs)
{
  Core::Entity_ref ref = get_entity();

  m_time += dt * 10.f;
  
  const float new_scale = 0.5f + math::sin(m_time);
  
  if(m_time > 0.5 && !m_reproduced)
  {
    const float new_scale = 0.5 * m_scale_mul;
  
    const math::vec3 pos = ref.get_transform().get_position();
    
    const float scale = m_scale_mul * 0.5f;
    
    const math::vec3 new_pos = math::vec3_init(math::rand_range(math::vec3_get_x(pos) - scale, math::vec3_get_x(pos) + scale),
                                               math::rand_range(math::vec3_get_y(pos) - scale, math::vec3_get_y(pos) + scale),
                                               math::rand_range(math::vec3_get_z(pos) - scale, math::vec3_get_z(pos) + scale));
    
    objs.push_object(new Explosion(get_world(), new_pos, 0.75f * m_scale_mul));
    
    m_reproduced = true;
  }
  
  if(new_scale < 0)
  {
    destroy();
  }
  
  // Update the scale.
  {
    const math::vec3 scale = math::vec3_init(m_scale_mul * new_scale);
    Core::Transform trans = ref.get_transform();
    trans.set_scale(scale);
    
    ref.set_transform(trans);
  }
}


} // ns