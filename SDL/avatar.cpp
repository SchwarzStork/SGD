#include "avatar.h"
#include "game.h"
#include "player_context.h"

using namespace space_invaders;

Avatar::Avatar(Game& game) : AnimatedEntity(game)
{
  setImage(game.getSpriteSheet());
  addAnimationFrame("still", { 86, 5, 40, 24 });
  addAnimationFrame("explosion", { 128, 91, 45, 24 });
  addAnimationFrame("explosion", { 178, 91, 45, 24 });
  setCurrentAnimation("still");
  setX(45);
  setY(648);
  setVelocity(0.25f);
}

void Avatar::explode()
{
  // zatrzymanie i wy³¹czenie mo¿liwoœci ruchu gracza(gdy jest trafiony)
  setDirectionX(0.f);
  setEnabled(false);

  // wybuch statku
  setCurrentAnimation("explosion");
  setAnimationStepSize(6);
  setDisappearCountdown(48);

  // ponowne generowanie modelu gracza
  auto& ctx = mGame.getActivePlayerContext();
  ctx.setLives(ctx.getLives() - 1);
  ctx.setRelaunchTimer(150);
}

void Avatar::reset()
{
  // reset pozycji startowej gracza
  setX(45);

  // ustawienie kolizji oraz widocznoœci
  setEnabled(true);
  setVisible(true);

  // restart animacji gracza
  setCurrentAnimation("still");
}