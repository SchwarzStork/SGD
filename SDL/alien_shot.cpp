#include "alien_shot.h"
#include "game.h"
#include "player_context.h"
#include "ingame_state.h"

using namespace space_invaders;

AlienShot::AlienShot(Game& game, IngameState& state) : AnimatedEntity(game), mState(state), mProgressTicks(0)
{

}

void AlienShot::update(unsigned long dt)
{
  if (isVisible()) {
    AnimatedEntity::update(dt);
    mProgressTicks++;
  }
}

void AlienShot::fire()
{
  setEnabled(true);
  setVisible(true);
  setCurrentAnimation("normal");
  setDirectionY(1.f);
  mProgressTicks = 1;
}

void AlienShot::explode()
{
  setEnabled(false);
  setCurrentAnimation("explode");
  setDisappearCountdown(10);
  setDirectionY(0.f);
}

bool AlienShot::isReadyToBeFired() const
{
  // Pocisk nie wylatuje gdy jest ju¿ jeden na danej trajektorii
  if (isVisible() == true) {
    return false;
  }

  const auto reloadRate = getReloadRate();
  
  // Referencja dla ka¿dego pocisku gotowego do wystrzelenia
  const auto& rollingShot = mState.getRollingShot();
  const auto& plungerShot = mState.getPlungerShot();
  const auto& squigglyShot = mState.getSquigglyShot();

  // Warunek sprawdzaj¹cy czas prze³adowania pocisku(nie mo¿e wystrzeliæ za wczeœnie)
  if (this != &rollingShot && rollingShot.mProgressTicks > 0 && reloadRate >= rollingShot.mProgressTicks) {
    return false;
  } else if (this != &plungerShot && plungerShot.mProgressTicks > 0 && reloadRate >= plungerShot.mProgressTicks) {
    return false;
  } else if (this != &squigglyShot && squigglyShot.mProgressTicks > 0 && reloadRate >= squigglyShot.mProgressTicks) {
    return false;
  }

  return true;
}

int AlienShot::getReloadRate() const
{
  // Pobranie obecnego wyniku
  const auto& ctx = mGame.getActivePlayerContext();
  const auto currentScore = ctx.getScore();

  // Czas prze³adowania na podstawie wyniku gracza(wy¿ej - szybciej)
  if (currentScore <= 200) {
    return 48;
  } else if (currentScore <= 1000) {
    return 16;
  } else if (currentScore <= 2000) {
    return 11;
  } else if (currentScore <= 3000) {
    return 8;
  } else {
    return 7;
  }
}