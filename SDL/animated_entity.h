/*
Logika animacji sprite'�w

 Logika dla dw�ch typ�w animacji:
 
 Tryb automatyczny
 Tryb manualny
 
 Tryb automatyczny sprawdza ilo�� 'krok�w', po okre�lonej liczbie resetuje animacje
 Tryb manualny to g��wnie placeholder dla sprite'�w kt�re musz� mie� r�cznie przypisane zmiany w animacji
*/
#ifndef SPACE_INVADERS_ANIMATED_ENTITY_H
#define SPACE_INVADERS_ANIMATED_ENTITY_H

#include "movable_entity.h"

#include <unordered_map>
#include <string>
#include <vector>

namespace space_invaders
{
  class AnimatedEntity : public MovableEntity
  {
  public:


    AnimatedEntity() = delete;
    AnimatedEntity(const AnimatedEntity&) = delete;
    AnimatedEntity(AnimatedEntity&&) = delete;
    AnimatedEntity& operator=(const AnimatedEntity&) = delete;
    AnimatedEntity& operator=(AnimatedEntity&&) = delete;

   

    AnimatedEntity(Game& game);
    ~AnimatedEntity() override = default;

    void update(unsigned long dt) override;

    void setAnimationStepSize(int stepSize);
    void setCurrentAnimation(const std::string& name);
    void setAnimationFrame(unsigned int frameIndex);
    void addAnimationFrame(const std::string& name, const SDL_Rect& rect);
  private:
    int mAnimationStepSize;
    int mAnimationCounter;
    int mAnimationFrameIndex;

    std::vector<SDL_Rect> mCurrentAnimation;
    std::unordered_map<std::string, std::vector<SDL_Rect>> mAnimations;
  };
}

#endif