#include <iostream>

#include "headers/UserInterface.h"
#include "headers/utils.h"
int main()
{
   std::vector players = { Player(100),Player(100),Player(100)};
   auto game_properties = GameProperties{5,10,5};
   auto ui = UserInterface(players,game_properties);
   ui.console_ui_loop();
}
