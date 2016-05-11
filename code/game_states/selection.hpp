#ifndef SELECTION_INCLUDED_6FFC83A8_6568_4EEE_993A_E7FEF3C177E9
#define SELECTION_INCLUDED_6FFC83A8_6568_4EEE_993A_E7FEF3C177E9


#include <core/world/world_fwd.hpp>
#include <core/context/context_fwd.hpp>
#include <common/common_fwd.hpp>
#include <game_objects/game_objects_fwd.hpp>


void
selection_init(Core::Context &ctx,
               Core::World &world);


Game_state
selection_update(Core::Context &ctx,
                 Core::World &world,
                 Players_container &player_info,
                 const float dt);


#endif // inc guard