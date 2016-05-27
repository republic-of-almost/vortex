#include <game_states/game_over.hpp>
#include <game_objects/explosion.hpp>
#include <game_objects/enemy.hpp>
#include <core/input/controller.hpp>


void
game_over_init(Core::Context &ctx,
               Core::World &world)
{
}


Game_state
game_over_update(Core::Context &context,
                 Core::World &world,
                 const float dt)
{
  Core::Input::Controller controller(context, 0);
  if(controller.is_button_down_on_frame(Core::Input::Button::button_4))
  {
    return Game_state::selection;
  }

  return Game_state::game_over;
}