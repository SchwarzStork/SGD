/*
 Pocisk ze statku gracza
*/
#ifndef SPACE_INVADERS_AVATAR_LASER_H
#define SPACE_INVADERS_AVATAR_LASER_H

#include "animated_entity.h"

namespace space_invaders
{
  class AvatarLaser : public AnimatedEntity
  {
  public:

    AvatarLaser() = delete;
    AvatarLaser(const AvatarLaser&) = delete;
    AvatarLaser(AvatarLaser&&) = delete;
    AvatarLaser& operator=(const AvatarLaser&) = delete;
    AvatarLaser& operator=(AvatarLaser&&) = delete;

    AvatarLaser(Game& game);
    ~AvatarLaser() override = default;

    void explode();
  };
}

#endif