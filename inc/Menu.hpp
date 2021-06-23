/**
 * @file Menu.hpp
 * @author Delicat Jakub (delicat.kuba@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef __MENU_HPP__
#define __MENU_HPP__
#include <vector>
#include <string>
#include <functional>
#include <initializer_list>

/**
 * @brief Menu class for choosing options.
 */
class Menu{
    public:
    /**
     * @brief menu options
     */
    std::vector<std::pair<std::string, std::function<void(void)>>> options;

    /**
     * @brief Construct a new Menu object
     * @param list of name of option and function. Suggested to use lambda.
     */
    Menu(std::initializer_list<std::pair<std::string, std::function<void(void)>>> list);


    /**
     * @brief Choose options and do option
     */
    void Choose() const; 
};
/**
 * @brief Print options for menu
 * @param cout output stream 
 * @param menu printed menu
 * @return std::ostream& 
 */
std::ostream &operator<<(std::ostream &cout, const Menu &menu);

/**
 * @brief Choosing option in Menu and activate function 
 * @param cin input stream
 * @param menu menu where the option is choosed
 * @return std::istream& 
 */
std::istream &operator>>(std::istream &cin, const Menu &menu);
#endif // __MENU_HPP__