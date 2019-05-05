/*
Funkcjonalno�� czerwonego ufo
 */
#ifndef SPACE_INVADERS_FLYING_SAUCER_H
#define SPACE_INVADERS_FLYING_SAUCER_H

#include "animated_entity.h"

#include <array>

namespace space_invaders
{
  class FlyingSaucer : public AnimatedEntity
  {
  public:
    //Sta�y odst�p czasu przed pojawieniem si� ufo
    static const auto APPEAR_INTERVAL = 1200;
    //Dodanie puntk�w za zestrzelenie ufo
    static const std::array<int, 15> POINT_TABLE;

    FlyingSaucer() = delete;
    FlyingSaucer(const FlyingSaucer&) = delete;
    FlyingSaucer(FlyingSaucer&&) = delete;
    FlyingSaucer& operator=(const FlyingSaucer&) = delete;
    FlyingSaucer& operator=(FlyingSaucer&&) = delete;

    FlyingSaucer(Game& game);
    ~FlyingSaucer() override = default;

    void update(unsigned long dt) override;

    void explode();
    void launch();

    int getPoints() const;

    int getAppearingCounter() const { return mAppearingCounter; }
  private:
    int mAppearingCounter;
  };
}

#endif