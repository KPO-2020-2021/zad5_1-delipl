#include "Menu.hpp"
#include <iostream>


Menu::Menu(std::initializer_list<std::pair<std::string, std::function<void(void)>>> list){
    for(auto &elem: list)
        this->options.push_back(elem);
}


std::ostream &operator<<(std::ostream &strm, const Menu &menu){
    std::size_t i = 0;
    strm << std::endl;
    for(auto &optionName: menu.options)
        strm << ++i << ". " << optionName.first << std::endl; 

    return strm;
}
std::istream &operator>>(std::istream &strm, const Menu &menu){
    std::size_t i = 0;
    strm >> i; 
    if(!strm)
        throw std::logic_error("Menu input error");

    if(i == 0 || i > menu.options.size())
        throw std::logic_error("Menu input error: there is no option");
    
    menu.options[i-1].second();
    
    return strm;
}