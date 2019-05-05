/*
Abstrakcja dla wszystkich obiekt�w ktore da si� wyrenderowa�

Enkapsulacja definicji umo�liwaj�ca render obiektu
 */
#ifndef SPACE_INVADERS_DRAWABLE_ENTTIY_H
#define SPACE_INVADERS_DRAWABLE_ENTTIY_H

#include "collideable_entity.h"
#include "image.h"

namespace space_invaders
{
  class DrawableEntity : public CollideableEntity
  {
  public:

    DrawableEntity() = delete;
    DrawableEntity(const DrawableEntity&) = delete;
    DrawableEntity(DrawableEntity&&) = delete;
    DrawableEntity& operator=(const DrawableEntity&) = delete;
    DrawableEntity& operator=(DrawableEntity&&) = delete;


    DrawableEntity(Game& game);
    virtual ~DrawableEntity();

    void update(unsigned long dt) override;
    void render(SDL_Renderer& renderer);

    void setImage(ImagePtr image);

    void setClip(const SDL_Rect& clip);
    void setDisappearCountdown(int timer);

    bool isVisible() const { return mVisible; }

    SDL_Rect normalize(const SDL_Rect& rect) const;

          ImagePtr getImage()       { return mImage; }
    const ImagePtr getImage() const { return mImage; }

          SDL_Rect& getClip()       { return mClip; }
    const SDL_Rect& getClip() const { return mClip; }

    void setVisible(bool visible) { mVisible = visible; }
  private:
    bool     mVisible;
    ImagePtr mImage;
    SDL_Rect mClip;
    int      mDisappearCountdown;
  };
}

#endif