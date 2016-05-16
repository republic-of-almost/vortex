#include <game_objects/main_camera.hpp>
#include <game_objects/player.hpp>
#include <core/world/world.hpp>
#include <core/context/context.hpp>
#include <core/transform/transform.hpp>
#include <core/entity/entity_ref.hpp>
#include <core/camera/camera_properties.hpp>
#include <core/transform/transform.hpp>
#include <core/color/color_predefined.hpp>
#include <math/vec/vec3.hpp>
#include <math/vec/vec2.hpp>
#include <common/level_functions.hpp>
#include <common/object_tags.hpp>


namespace Camera_utils {


void
init_main_camera(Core::Context &ctx, Core::World &world, Game_camera &cam)
{
  Core::Entity camera_entity(world);
  Core::Camera main_camera(world);
  
  camera_entity.set_name("Main Camera");
  camera_entity.add_tag(Object_tags::camera);
  Core::Transform curr_trans = camera_entity.get_transform();
  curr_trans.set_position(math::vec3_init(0.f, 0.f, 12.f));
  camera_entity.set_transform(curr_trans);
  
  cam.entity = std::move(camera_entity);
  
  main_camera.set_width(ctx.get_width());
  main_camera.set_height(ctx.get_height());
  
  main_camera.set_attached_entity(cam.entity);
  main_camera.set_type(Core::Camera_type::perspective);
  main_camera.set_clear_flags(Core::Camera_clear::color | Core::Camera_clear::depth);
  main_camera.set_clear_color(Core::Color_utils::purple());
//  main_camera.set_feild_of_view(math::quart_tau() / 3);
  
  cam.camera = std::move(main_camera);
}


void
move_main_camera(Game_camera &cam,
                 const float dt,
                 const Players_container &players_container)
{
  // Camera constants.
  constexpr float camera_distance_far = 20.f;
  constexpr float camera_distance_near = 10.f;

  // We set the camera origin as the first point.
  const math::vec3 camera_origin = math::vec3_init(0,0,Level::get_top_of_level());
  math::vec3 accum_target = camera_origin;
  
  // Go through the players and accumulate the target point.
  for(uint32_t i = 0; i < players_container.size; ++i)
  {
    auto &player = players_container.player[i];
    
    if(!player.entity)
    {
      continue;
    }
    
    // Get the difference and add it to the accum.
    const math::vec3 player_pos  = player.entity.get_transform().get_position();
    const math::vec3 diff        = math::vec3_subtract(player_pos, math::vec3_zero());
    const math::vec3 scaled_diff = math::vec3_scale(diff, 0.5f);
    
    accum_target = math::vec3_add(accum_target, scaled_diff);
  }
  
  const math::vec3 avg_accum = math::vec3_divide(accum_target, math::vec3_init(3.f));
  
  // The closer the target point is to the camera origin the
  // further we pull back because this means the players
  // are at oposite ends of the level.
  math::vec3 pullback_distance = math::vec3_init(0,0,camera_distance_far);
  {
    const math::vec3 pullback_near   = math::vec3_init(0,0,camera_distance_near);
    const math::vec3 pullback_far    = math::vec3_init(0,0,camera_distance_far);
    const math::vec2 cam_origin_vec2 = math::vec2_init(math::vec3_get_x(camera_origin), math::vec3_get_y(camera_origin));
    const math::vec2 accum_vec2      = math::vec2_init(math::vec3_get_x(avg_accum), math::vec3_get_y(avg_accum));
    const float length               = math::abs(math::vec2_length(math::vec2_subtract(cam_origin_vec2, accum_vec2)));
    const float norm_length          = length / Level::get_radius();
    
    pullback_distance = math::vec3_lerp(pullback_far, pullback_near, norm_length);
  }
  
  // Adjust pullback for players jumping
  {
    const math::vec3 accum_jump = math::vec3_init(0,0,math::vec3_get_z(accum_target));
  
    pullback_distance = math::vec3_add(pullback_distance, accum_jump);
  }
  
  // New target point.
  Core::Transform this_trans = cam.entity.get_transform();
  math::vec3 new_pos = math::vec3_zero();
  {
    constexpr float player_influence  = 1.f;
    constexpr float camera_move_speed = 10.f;
    
    const math::vec3 scaled_accum = math::vec3_scale(avg_accum, player_influence);
    cam.target_point = math::vec3_add(scaled_accum, pullback_distance);
    
    const math::vec3 this_pos   = this_trans.get_position();
    const math::vec3 move_dir   = math::vec3_subtract(cam.target_point, this_pos);
    const math::vec3 scaled_dir = math::vec3_scale(move_dir, dt * camera_move_speed);
    
    new_pos = math::vec3_add(this_pos, scaled_dir);
  }
  
  this_trans.set_position(new_pos);
  
  cam.entity.set_transform(this_trans);
}

} // ns