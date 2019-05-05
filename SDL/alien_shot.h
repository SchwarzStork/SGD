/*
 Pociski kosmitów
	Rolling shot
	Zawsze wykonany przez kosmitê najblizej gracza
 
	Plunger shot
	Sta³a trajektoria pocisku z wystrzelonej kolumny, nie wykonuje sie gdy w kolumnie jest tylko 1 kosmita
 
	Squiggly shot
	j/w nie wykonuje sie gdy przylatuje czerwone ufo
 
	Tabela na podstawie poni¿szych informacji:
	http://www.computerarcheology.com/Arcade/SpaceInvaders/Code.html
 */
#ifndef SPACE_INVADER_ALIEN_SHOT_H
#define SPACE_INVADER_ALIEN_SHOT_H

#include "animated_entity.h"

namespace space_invaders
{
  class IngameState;
  class AlienShot : public AnimatedEntity
  {
  public:
 

    AlienShot() = delete;
    AlienShot(const AlienShot&) = delete;
    AlienShot(AlienShot&&) = delete;
    AlienShot& operator=(const AlienShot&) = delete;
    AlienShot& operator=(AlienShot&&) = delete;

  

    AlienShot(Game& game, IngameState& state);
    ~AlienShot() override = default;

    void update(unsigned long dt) override;

    virtual void fire();
    void explode();
    bool isReadyToBeFired() const;

    int getReloadRate() const;
  protected:
    IngameState&  mState;
    int           mProgressTicks;
  };
}


#endif