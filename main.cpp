#include <iostream>

#include "headers/UserInterface.h"
#include "crow.h"
#include "headers/utils.h"
int main()
{
   crow::SimpleApp app;
   // Define a basic route
   CROW_ROUTE(app, "/")([]() {
       return "Hello, Crow!";
   });
    // Define a route with parameters
    CROW_ROUTE(app, "/add/<int>/<int>")([](int a, int b) {
        return crow::response(std::to_string(a + b));
    });
    app.port(18080).multithreaded().run();
    std::vector players = { Player(100),Player(100),Player(100)};
    auto game_properties = GameProperties{5,10,5};
    auto ui = UserInterface(players,game_properties);
    ui.console_ui_loop();
}
