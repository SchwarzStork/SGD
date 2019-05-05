/*
Statek kosmiczny gracza
 */
#ifndef SPACE_INVADERS_AVATAR_H
#define SPACE_INVADERS_AVATAR_H

#include "animated_entity.h"

namespace space_invaders
{
  class Avatar : public AnimatedEntity
  {
  public:

    Avatar() = delete;
    Avatar(const Avatar&) = delete;
    Avatar(Avatar&&) = delete;
    Avatar& operator=(const Avatar&) = delete;
    Avatar& operator=(Avatar&&) = delete;

    Avatar(Game& game);
    ~Avatar() override = default;

    void explode();
    void reset();
  };
}

#endif