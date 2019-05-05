/*
W³aœciwoœci rolling shot
*/
#ifndef SPACE_INVADERS_ROLLING_SHOT_H
#define SPACE_INVADERS_ROLLING_SHOT_H

#include "alien_shot.h"

#include <array>

namespace space_invaders
{
  class RollingShot final : public AlienShot
  {
  public:

    RollingShot() = delete;
    RollingShot(const RollingShot&) = delete;
    RollingShot(RollingShot&&) = delete;
    RollingShot& operator=(const RollingShot&) = delete;
    RollingShot& operator=(RollingShot&&) = delete;

    RollingShot(Game& game, IngameState& state);
    ~RollingShot() override = default;

    void update(unsigned long dt) override;
    void fire() override;

    int getLock() const { return mLock; }
  private:
    int mLock;
  };
}
#endif