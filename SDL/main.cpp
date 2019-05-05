/*
Odpalenie gry
*/
#include "game.h"

using namespace space_invaders;

int main(int argc, char* args[])
{
  Game game(672, 768);
  return game.run();
}