#include <core/entity/entity_ref.hpp>
#include <core/context/context.hpp>
#include <core/world/world.hpp>
#include <core/world/world_setup.hpp>
#include <core/camera/camera.hpp>
#include <core/camera/camera_properties.hpp>
#include <core/entity/entity.hpp>
#include <core/color/color.hpp>
#include <core/color/color_predefined.hpp>
#include <core/renderer/mesh_renderer.hpp>
#include <core/transform/transform.hpp>
#include <core/input/input.hpp>
#include <core/input/controller.hpp>
#include <math/vec/vec3.hpp>

// Temp Resource loading.
#include <core/model/model.hpp>
#include <core/model/mesh.hpp>
#include <core/material/texture.hpp>
#include <data/resource_data/resource_data.hpp>
#include <utilities/logging.hpp>
#include <vector>
#include <game_objects/bullet.hpp>
#include <player.hpp>
#include <main_camera.hpp>
#include <utilities/timer.hpp>
#include <game_objects/world_objects.hpp>


Resource_data::Resources resources;

int
main()
{
  Resource_data::resources_init(&resources);
  
  Core::Context context(800, 480, false, "Vortex");
  
  Core::Model model("/Users/PhilCK/Developer/core/assets/models/unit_cube.obj");
  assert(model.get_id());
  
  Core::Texture texture("/Users/PhilCK/Developer/core/assets/textures/dev_grid_green_512.png");
  assert(texture.get_id());
  
  Core::World world(Core::World_setup{});
  Core::Mesh_renderer mesh_renderer;
  
  util::timer delta_time_ms;
  delta_time_ms.start();
  
  Core::Entity cam_entity();
  Core::Camera cam;
  
  while(context.is_open())
  {
    const util::milliseconds frame_time = delta_time_ms.split();
    const float dt = static_cast<float>(frame_time) / 1000.f;
    
    
    mesh_renderer.render();
  }

  return 0;
}