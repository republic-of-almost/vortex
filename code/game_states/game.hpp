#ifndef GAME_INCLUDED_74006336_21A6_4078_906C_81BFDC593032
#define GAME_INCLUDED_74006336_21A6_4078_906C_81BFDC593032



#include <game_objects/game_objects_fwd.hpp>
#include <common/common_fwd.hpp>
#include <core/common/core_fwd.hpp>


void
game_init(Core::Context &ctx,
          Core::World &world);


Game_state
game_update(Core::Context &ctx,
            Core::World &world,
            Game_object::World_objects &objs,
            const float dt);


#endif // inc guard