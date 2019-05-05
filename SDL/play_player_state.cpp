#include "play_player_state.h"
#include "game.h"
#include "ingame_state.h"

using namespace space_invaders;

PlayPlayerState::PlayPlayerState(Game& game)
  : State(game),
    mTickCounter(VISIBLITY_TICKS),
    mText(game)
{
  // Okre�lenie kt�ry gracz gra(1 czy 2)
  int playerIdx = (mGame.getActivePlayer() == Game::Player::PLAYER_1 ? 1 : 2);
  mText.setText("PLAY PLAYER<" + std::to_string(playerIdx) + ">");
  mText.setX(672 / 2 - mText.getWidth() / 2);
  mText.setY(400);
}

void PlayPlayerState::update(unsigned long dt)
{
  mTickCounter--;
  if (mTickCounter <= 0) {
    auto scene = mGame.getScene();
    scene->setState(std::make_shared<IngameState>(mGame));
  }
}

void PlayPlayerState::render(SDL_Renderer& renderer)
{
  mText.render(renderer);
}

void PlayPlayerState::onEnter()
{
 
}

void PlayPlayerState::onExit()
{
  
}

void PlayPlayerState::onKeyUp(SDL_KeyboardEvent& event)
{
 
}

void PlayPlayerState::onKeyDown(SDL_KeyboardEvent& event)
{
  
}