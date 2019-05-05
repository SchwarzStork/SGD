#include "ingame_state.h"
#include "game.h"
#include "player_context.h"
#include "play_player_state.h"
#include "welcome_state.h"

using namespace space_invaders;

IngameState::IngameState(Game& game)
  : State(game),
    mFooterLine(game),
    mAvatar(game),
    mLeftOobDetector(game),
    mRightOobDetector(game),
    mTopOobDetector(game),
    mAvatarLaser(game),
    mLifesText(game),
    mLifeSprite1(game),
    mLifeSprite2(game),
    mAlienLeftDirector(game),
    mAlienRightDirector(game),
    mGameOverText(game),
    mGameOverInstructions(game),
    mFlyingSaucer(game),
    mPlungerShot(game, *this),
    mSquigglyShot(game, *this),
    mRollingShot(game, *this)
{
  // Zielona linia na dole ekranu
  mFooterLine.setImage(game.getSpriteSheet());
  mFooterLine.setX(0);
  mFooterLine.setY(717);
  mFooterLine.setClip({0, 117, 672, 3});

  // Detekcja kolizji
  mLeftOobDetector.setX(-100);
  mLeftOobDetector.setY(0);
  mLeftOobDetector.setExtentX(50);
  mLeftOobDetector.setExtentY(768 / 2);

  mRightOobDetector.setX(672);
  mRightOobDetector.setY(0);
  mRightOobDetector.setExtentX(50);
  mRightOobDetector.setExtentY(768 / 2);

  mTopOobDetector.setX(0);
  mTopOobDetector.setY(0);
  mTopOobDetector.setExtentX(768 / 2);
  mTopOobDetector.setExtentY(70);

  // Wyœwietlanie iloœci ¿yæ
  auto& ctx = mGame.getActivePlayerContext();
  mLifesText.setText(std::to_string(ctx.getLives()));
  mLifesText.setX(27);
  mLifesText.setY(743 - mLifesText.getHeight() + 5);

  mLifeSprite1.setImage(mGame.getSpriteSheet());
  mLifeSprite1.setWidth(40);
  mLifeSprite1.setHeight(24);
  mLifeSprite1.setX(66);
  mLifeSprite1.setY(720);
  mLifeSprite1.setClip({ 85, 5, 40, 24 });
  mLifeSprite1.setVisible(ctx.getLives() > 1);

  mLifeSprite2.setImage(mGame.getSpriteSheet());
  mLifeSprite2.setWidth(40);
  mLifeSprite2.setHeight(24);
  mLifeSprite2.setX(66 + 49);
  mLifeSprite2.setY(720);
  mLifeSprite2.setClip({ 85, 5, 40, 24 });
  mLifeSprite2.setVisible(ctx.getLives() > 2);

  // Generowanie kosmitów
  mAliens = ctx.getAliens();
  if (mAliens.empty()) {
    for (auto i = 0; i < 55; i++) {
      mAliens.push_back(std::make_shared<Alien>(game, i));
    }
  }

  // Zakres ruchów gracza oraz kosmitów
  mAlienLeftDirector.setX(-45);
  mAlienLeftDirector.setY(0);
  mAlienLeftDirector.setExtentX(45);
  mAlienLeftDirector.setExtentY(768 / 2);

  mAlienRightDirector.setX(672 - 45);
  mAlienRightDirector.setY(0);
  mAlienRightDirector.setExtentX(45);
  mAlienRightDirector.setExtentY(768 / 2);


  mGameOverText.setText("GAME OVER");
  mGameOverText.setColor({245, 3, 5, 255 });
  mGameOverText.setX(672 / 2 - mGameOverText.getExtentX());
  mGameOverText.setY(135);
  mGameOverText.setVisible(false);

  mGameOverInstructions.setText("PRESS ENTER TO CONTINUE");
  mGameOverInstructions.setColor({245, 3, 5, 255 });
  mGameOverInstructions.setX(672 / 2 - mGameOverInstructions.getExtentX());
  mGameOverInstructions.setY(mGameOverText.getY() + 40);
  mGameOverInstructions.setVisible(false);

  // Tworzenie zielonych os³on
  mShields = ctx.getShields();
  if (mShields.empty()) {

    auto shield1 = std::make_shared<Shield>(game);
    shield1->setWidth(66);
    shield1->setHeight(48);
    shield1->setX(135 - shield1->getExtentX());
    shield1->setY(575);


    auto shield2 = std::make_shared<Shield>(game);
    shield2->setWidth(66);
    shield2->setHeight(48);
    shield2->setX(269 - shield2->getExtentX());
    shield2->setY(575);
    
  
    auto shield3 = std::make_shared<Shield>(game);
    shield3->setWidth(66);
    shield3->setHeight(48);
    shield3->setX(403 - shield3->getExtentX());
    shield3->setY(575);


    auto shield4 = std::make_shared<Shield>(game);
    shield4->setWidth(66);
    shield4->setHeight(48);
    shield4->setX(537 - shield4->getExtentX());
    shield4->setY(575);

    mShields.push_back(shield1);
    mShields.push_back(shield2);
    mShields.push_back(shield3);
    mShields.push_back(shield4);
  }
}

void IngameState::update(unsigned long dt)
{
  // Zatrzymanie gry w przypadku stanu Game Over
  if (mGameOverText.isVisible()) {
    return;
  }

  mFooterLine.update(dt);
  mAvatar.update(dt);
  mAvatarLaser.update(dt);
  mFlyingSaucer.update(dt);
  mPlungerShot.update(dt);
  mSquigglyShot.update(dt);
  mRollingShot.update(dt);
  for (auto shield : mShields) {
    shield->update(dt);
  }

  // despawn ufo gdy dotrze do koñca swojej trasy
  if (mFlyingSaucer.isVisible()) {
    if (mFlyingSaucer.getDirectionX() > 0.f) {
      if (mRightOobDetector.collides(mFlyingSaucer)) {
        mFlyingSaucer.setEnabled(false);
        mFlyingSaucer.setVisible(false);
      }
    } else {
      if (mLeftOobDetector.collides(mFlyingSaucer)) {
        mFlyingSaucer.setEnabled(false);
        mFlyingSaucer.setVisible(false);
      }
    }
  }

  // detekcja kolizji pocisków(czy powinno siê je zdespawniæ czy nie)
  if (mAvatarLaser.isEnabled()) {
    if (mAvatarLaser.collides(mTopOobDetector)) {
      mAvatarLaser.setCurrentAnimation("top-wall-hit");
      mAvatarLaser.explode();
    }
  }

  if (mPlungerShot.isVisible()) {
    if (mPlungerShot.collides(mFooterLine)) {
      mPlungerShot.explode();
    }
  }

  if (mSquigglyShot.isVisible()) {
    if (mSquigglyShot.collides(mFooterLine)) {
      mSquigglyShot.explode();
    }
  }

  if (mRollingShot.isVisible()) {
    if (mRollingShot.collides(mFooterLine)) {
      mRollingShot.explode();
    }
  }

  // decrement the relaunch timer if it has been activated or handle destruction state.
  auto& ctx = mGame.getActivePlayerContext();
  auto relaunchTimer = ctx.getRelaunchTimer();
  if (relaunchTimer > 0) {
    relaunchTimer--;
    ctx.setRelaunchTimer(relaunchTimer);
    return;
  } else if (mAvatar.isEnabled() == false) {
    const auto playerCount = mGame.getPlayerCount();
    if (playerCount == 1) {
      // ::: SINGLE PLAYER :::
		//Sprawdzenie iloœci ¿yæ(czy j¹ zakoñczyæ przy braku)
      if (ctx.getLives() <= 0) {
       //Sprawdzenie/aktualizacja punktacji
        const auto score = ctx.getScore();
        if (mGame.getHiScore() < score) {
          mGame.setHiScore(score);
        }
        mGameOverText.setVisible(true);
        mGameOverInstructions.setVisible(true);
        return;
      } else {
        //Wyswietlanie obecnej ilosci ¿yæ
        const auto lives = ctx.getLives();
        mLifesText.setText(std::to_string(lives));
        if (lives == 2) {
          mLifeSprite2.setVisible(false);
          mLifeSprite1.setVisible(true);
        } else if (lives == 1) {
          mLifeSprite2.setVisible(false);
          mLifeSprite1.setVisible(false);
        }

        mAvatar.reset();
      }
    } else {
      // ::: MULTI-PLAYER :::
      ctx.setAliens(mAliens);
      ctx.setShields(mShields);

      const auto activePlayer = mGame.getActivePlayer();
      if (activePlayer == Game::Player::PLAYER_1) {
        mGame.setActivePlayer(Game::Player::PLAYER_2);
        return;
      } else {

        auto& player1Ctx = mGame.getPlayerContext1();
        auto& player2Ctx = mGame.getPlayerContext2();
        if (player2Ctx.getLives() <= 0) {
          const auto player1Score = player1Ctx.getScore();
          if (mGame.getHiScore() < player1Score) {
            mGame.setHiScore(player1Score);
          }

          const auto player2Score = player2Ctx.getScore();
          if (mGame.getHiScore() < player2Score) {
            mGame.setHiScore(player2Score);
          }

          mGameOverText.setVisible(true);
          mGameOverInstructions.setVisible(true);
          auto scene = mGame.getScene();
          auto score1 = scene->getScore1Text();
          score1->setVisible(true);
          return;
        } else {
          mGame.setActivePlayer(Game::Player::PLAYER_1);
          return;
        }
      }
    }
  }
//Sprawdzanie czy model nie wychodzi poza obszar swoich dzia³añ
  const auto avatarDirection = mAvatar.getDirectionX();
  if (avatarDirection < 0.f) {
    if (mAlienLeftDirector.collides(mAvatar)) {
      mAvatar.setDirectionX(0.f);
      mAvatar.setX(mAlienLeftDirector.getX() + mAlienLeftDirector.getWidth());
    }
  } else if (avatarDirection > 0.f) {
    if (mAlienRightDirector.collides(mAvatar)) {
      mAvatar.setDirectionX(0.f);
      mAvatar.setX(mAlienRightDirector.getX() - mAvatar.getWidth());
    }
  }

  auto alienMovementChangeRequired = false;
  auto aliensDirection = mAliens[0]->getDirectionX();
  for (auto& alien : mAliens) {
    if (aliensDirection > 0) {
      if (mAlienRightDirector.collides(*alien)) {
        alienMovementChangeRequired = true;
        break;
      }
    } else {
      if (mAlienLeftDirector.collides(*alien)) {
        alienMovementChangeRequired = true;
        break;
      }
    }
  }

  auto activeAlienCount = 0;
  if (mAvatar.isEnabled()) {
    for (auto& alien : mAliens) {
      // "opuszczenie" kosmity o wiersz
      if (alienMovementChangeRequired) {
        alien->setDirectionX(-aliensDirection);
        alien->setY(alien->getY() + alien->getHeight());
      }
      if (alien->isVisible()) {
        activeAlienCount++;
        alien->update(dt);

        if (alien->collides(mFooterLine)) {
          mAvatar.explode();
        } else if (alien->collides(mAvatar)) {
          mAvatar.explode();
        }
      }
    }
  }

  // Kontrola iloœci kosmitow - gdy brak odpalamy nastêpny poziom
  if (activeAlienCount <= 0) {
    ctx.setLevel(ctx.getLevel() + 1);
    auto scene = mGame.getScene();
    scene->setState(std::make_shared<PlayPlayerState>(mGame));
    return;
  }

  // Kontrola czy pocisk gracza trafi³
  if (mAvatarLaser.isEnabled()) {
    if (mAvatarLaser.collides(mFlyingSaucer)) {
      mAvatarLaser.setDirectionY(0);
      mAvatarLaser.setEnabled(false);
      mAvatarLaser.setVisible(false);

      // Wybuch ufo przy trafieniu
      mFlyingSaucer.explode();

      // Punktacja na podstawie oddanych strza³ów przez gracza
      auto& ctx = mGame.getActivePlayerContext();
      auto points = mFlyingSaucer.getPoints();
      ctx.addScore(points);
    } else {
      // kontakt pocisku z os³on¹
      for (auto shield : mShields) {
        if (shield->collides(mAvatarLaser)) {
          mAvatarLaser.explode();
          break;
        }
      }

      // Czy pocisk trafil kosmite
      for (auto& alien : mAliens) {
        if (mAvatarLaser.collides(*alien)) {
          mAvatarLaser.setCurrentAnimation("alien-hit");
          mAvatarLaser.explode();
          mAvatarLaser.setX(alien->getCenterX() - mAvatarLaser.getExtentX());
          mAvatarLaser.setY(alien->getCenterY() - mAvatarLaser.getExtentY());
          alien->disappear();

          auto& ctx = mGame.getActivePlayerContext();
          auto points = alien->getPoints();
          ctx.addScore(points);

          // przyspieszenie ruchu kosmitów
          auto newStepSize = alien->getStepSize() - Alien::STEP_DECREMENT_SIZE;
          for (auto& a : mAliens) {
            a->setStepSize(newStepSize);
            a->setAnimationStepSize(newStepSize);
          }
          break;
        }
      }
    }
  }

  // Stwórz rolling shot jeœli mozna go odpaliæ
  if (mAvatar.isEnabled() && mRollingShot.isReadyToBeFired() && mRollingShot.getLock() <= 0) {
    mRollingShot.fire();
  }

  // Stwórz plunger shot je¿eli jest taka mo¿liwoœæ
  if (mAvatar.isEnabled() && activeAlienCount > 1 && mPlungerShot.isReadyToBeFired()) {
    mPlungerShot.fire();
  }

  // Tworzenie squiggly shota lub czerwonego ufo
  if (mAvatar.isEnabled() && mSquigglyShot.isReadyToBeFired() && !mFlyingSaucer.isVisible()) {
    if (mFlyingSaucer.getAppearingCounter() <= 0 && activeAlienCount >= 8) {
      mFlyingSaucer.launch();
    } else {
      mSquigglyShot.fire();
    }
  }

  // Czy pocisk kosmity coœ trafi³
  if (mRollingShot.isVisible()) {
	  // Uderzenie w gracza
    if (mRollingShot.collides(mAvatar)) {
      mRollingShot.setEnabled(false);
      mRollingShot.setVisible(false);
      mAvatar.explode();
    } else if (mRollingShot.collides(mAvatarLaser)) {
      mRollingShot.setEnabled(false);
      mRollingShot.setVisible(false);
      mAvatarLaser.setCurrentAnimation("explode");
      mAvatarLaser.explode();
    } else {
      // Uderzenie w tarcze
      for (auto shield : mShields) {
        if (shield->collides(mRollingShot)) {
          mRollingShot.explode();
          break;
        }
      }
    }
  }

  if (mPlungerShot.isVisible()) {
    if (mPlungerShot.collides(mAvatar)) {
      mPlungerShot.setEnabled(false);
      mPlungerShot.setVisible(false);
      mAvatar.explode();
    } else if (mPlungerShot.collides(mAvatarLaser)) {
      mPlungerShot.setEnabled(false);
      mPlungerShot.setVisible(false);
      mAvatarLaser.setCurrentAnimation("explode");
      mAvatarLaser.explode();
    } else {
      for (auto shield : mShields) {
        if (shield->collides(mPlungerShot)) {
          mPlungerShot.explode();
          break;
        }
      }
    }
  }

  if (mSquigglyShot.isVisible()) {
    if (mSquigglyShot.collides(mAvatar)) {
      mSquigglyShot.setEnabled(false);
      mSquigglyShot.setVisible(false);
      mAvatar.explode();
    } else if (mSquigglyShot.collides(mAvatarLaser)) {
      mSquigglyShot.setEnabled(false);
      mSquigglyShot.setVisible(false);
      mAvatarLaser.setCurrentAnimation("explode");
      mAvatarLaser.explode();
    } else {
      for (auto shield : mShields) {
        if (shield->collides(mSquigglyShot)) {
          mSquigglyShot.explode();
          break;
        }
      }
    }
  }
}

void IngameState::render(SDL_Renderer& renderer)
{
  mGameOverText.render(renderer);
  mGameOverInstructions.render(renderer);
  mFooterLine.render(renderer);
  mAvatar.render(renderer);
  mFlyingSaucer.render(renderer);
  mLifesText.render(renderer);
  mLifeSprite1.render(renderer);
  mLifeSprite2.render(renderer);
  for (auto& alien : mAliens) {
    alien->render(renderer);
  }
  for (auto shield : mShields) {
    shield->render(renderer);
  }
  mAvatarLaser.render(renderer);
  mPlungerShot.render(renderer);
  mSquigglyShot.render(renderer);
  mRollingShot.render(renderer);
}

void IngameState::onEnter()
{

}

void IngameState::onExit()
{
  
}

void IngameState::onKeyUp(SDL_KeyboardEvent& event)
{
  switch (event.keysym.sym) {
  case SDLK_LEFT:
    if (mAvatar.isEnabled() && mAvatar.getDirectionX() < 0.f) {
      mAvatar.setDirectionX(0.f);
    }
    break;
  case SDLK_RIGHT:
    if (mAvatar.isEnabled() && mAvatar.getDirectionX() > 0.f) {
      mAvatar.setDirectionX(0.f);
    }
    break;
  case SDLK_SPACE:
    if (mAvatar.isEnabled() && mAvatarLaser.isVisible() == false) {
      mAvatarLaser.setVisible(true);
      mAvatarLaser.setEnabled(true);
      mAvatarLaser.setDirectionY(-1.f);
      mAvatarLaser.setX(mAvatar.getCenterX() - mAvatarLaser.getExtentX());
      mAvatarLaser.setY(mAvatar.getY());
      mAvatarLaser.setCurrentAnimation("normal");
      mAvatarLaser.setAnimationFrame(0);

      auto& ctx = mGame.getActivePlayerContext();
      ctx.setShotCount(ctx.getShotCount() + 1);
    }
    break;
  }
}

void IngameState::onKeyDown(SDL_KeyboardEvent& event)
{
  switch (event.keysym.sym) {
  case SDLK_LEFT:
    if (mAvatar.isEnabled()) {
      mAvatar.setDirectionX(-1.f);
    }
    break;
  case SDLK_RIGHT:
    if (mAvatar.isEnabled()) {
      mAvatar.setDirectionX(1.f);
    }
    break;
  case SDLK_RETURN:
    if (mGameOverText.isVisible()) {
      mGame.getPlayerContext1().reset();
      mGame.getPlayerContext2().reset();

      // Powrót do ekranu startowego
      auto scene = mGame.getScene();
      scene->setState(std::make_shared<WelcomeState>(mGame));
    }
    break;
  }
}