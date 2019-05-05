/*
Kolizja, ruch oraz rysowanie sprite'�w wymaganych obiektow(przeciwnicy, gracz)
 */
#ifndef SPACE_INVADERS_MOVABLE_ENTITY_H
#define SPACE_INVADERS_MOVABLE_ENTITY_H

#include "drawable_entity.h"

namespace space_invaders
{
  class MovableEntity : public DrawableEntity
  {
  public:

    MovableEntity() = delete;
    MovableEntity(const MovableEntity&) = delete;
    MovableEntity(MovableEntity&&) = delete;
    MovableEntity& operator=(const MovableEntity&) = delete;
    MovableEntity& operator=(MovableEntity&&) = delete;


    MovableEntity(Game& game);
    ~MovableEntity() override = default;

    void update(unsigned long dt) override;

    void setStepSize(int stepSize);

    void setVelocity(float velocity)  { mVelocity = velocity; }
    void setDirectionX(float x)       { mDirectionX = x;      }
    void setDirectionY(float y)       { mDirectionY = y;      }

    int getStepSize() const     { return mStepSize;     }
    int getStepCounter() const  { return mStepCounter;  }
    float getVelocity() const   { return mVelocity;     }
    float getDirectionX() const { return mDirectionX;   }
    float getDirectionY() const { return mDirectionY;   }
  private:
    int   mStepSize;
    int   mStepCounter;
    float mVelocity;
    float mDirectionX;
    float mDirectionY;
  };
}

#endif