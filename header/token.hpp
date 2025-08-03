#ifndef TOKEN_HPP
#define TOKEN_HPP
#include "config.hpp"
#include "myMap.hpp"
#include <string>

auto applyToken(const UserSession &session) -> std::pair<std::string, bool>;

auto quireSession(const std::string token) -> UserSession;

auto logOut(const std::string token) -> bool;

#endif