/*
 W³aœciwoœci oraz zasady dzia³ania plunger shota
 */
#ifndef SPACE_INVADERS_PLUNGER_SHOT_H
#define SPACE_INVADERS_PLUNGER_SHOT_H

#include "alien_shot.h"

#include <array>

namespace space_invaders
{
  class IngameState;
  class PlungerShot final : public AlienShot
  {
  public:
    static const std::array<int, 15> SHOT_COLUMNS;

    PlungerShot() = delete;
    PlungerShot(const PlungerShot&) = delete;
    PlungerShot(PlungerShot&&) = delete;
    PlungerShot& operator=(const PlungerShot&) = delete;
    PlungerShot& operator=(PlungerShot&&) = delete;


    PlungerShot(Game& game, IngameState& state);
    ~PlungerShot() override = default;

    void fire() override;
  private:
    int mNextShotColumnIndex;
  };
}


#endif