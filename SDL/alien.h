/*
 Funkcjonalnoœæ(zachowanie itd) dla kosmitów
 */
#ifndef SPACE_INVADERS_ALIEN_H
#define SPACE_INVADERS_ALIEN_H

#include "animated_entity.h"

namespace space_invaders
{
  class Alien : public AnimatedEntity
  {
  public:
    /*zakres ruchu kosmitów */
    static const int INITIAL_STEP_SIZE = 55;
    /*Przyspieszenie pozosta³ych kosmitów im wiecej zostalo zniszczonych */
    static const int STEP_DECREMENT_SIZE = 1;
   
    static const int ALIENS_PER_ROW = 11;



    Alien() = delete;
    Alien(const Alien&) = delete;
    Alien(Alien&&) = delete;
    Alien& operator=(const Alien&) = delete;
    Alien& operator=(Alien&&) = delete;

   

    Alien(Game& game, int index);
    ~Alien() override = default;

    void disappear();

    int getPoints() const { return mPoints; }
  private:
    int resolveYPosition();
  private:
    int mIndex;
    int mPoints;
  };
  typedef std::shared_ptr<Alien> AlienPtr;
}

#endif