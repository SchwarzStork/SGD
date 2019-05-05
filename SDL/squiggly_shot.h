/*
W³aœciwoœci oraz zasady dzia³ania squiggly shot
*/
#ifndef SPACE_INVADERS_SQUIGGLY_SHOT_H
#define SPACE_INVADERS_SQUIGGLY_SHOT_H

#include "alien_shot.h"

#include <array>

namespace space_invaders
{
  class IngameState;
  class SquigglyShot final : public AlienShot
  {
  public:
    static const std::array<int, 15> SHOT_COLUMNS;

    SquigglyShot() = delete;
    SquigglyShot(const SquigglyShot&) = delete;
    SquigglyShot(SquigglyShot&&) = delete;
    SquigglyShot& operator=(const SquigglyShot&) = delete;
    SquigglyShot& operator=(SquigglyShot&&) = delete;

    SquigglyShot(Game& game, IngameState& state);
    ~SquigglyShot() override = default;

    void fire() override;
  private:
    int mNextShotColumnIndex;
  };
}

#endif