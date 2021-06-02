#include "doctest.h"
#include <iostream>
#include <sstream>
#include "Menu.hpp"
void Foo(){
    std::cout << "Hejka!" << std::endl;
}
void Goo(std::string i){
    std::cout << "Hejka! " << i << std::endl;
}
TEST_CASE("1. Menu Constructor"){
    
    Menu menu(
        {{"Wysylanie hejki", Foo}}
    );
    CHECK(1 == 1);
}
TEST_CASE("2. Menu print"){
    
    Menu menu(
        {{"Wysylanie hejki", Foo}}
    );
    std::cout << menu;
    CHECK(1 == 1);
}
TEST_CASE("2. Menu print"){
    std::istringstream in("1");
    std::string imie = "Deli";
    auto lambda = [imie](){Goo(imie);};
    Menu menu(
        {
            {"Wysylanie hejki", Foo },
            {"Wysylanie kolejnej", lambda }
        }

    );
    in >> menu;
    std::istringstream olo("2");
    olo >> menu;
}