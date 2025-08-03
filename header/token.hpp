#ifndef TOKEN_HPP
#define TOKEN_HPP
#include "config.hpp"
#include "myMap.hpp"
#include <string>

auto applyToken(const UserSession &session) -> std::string;

auto quireSession(const std::string token) -> std::pair<UserSession, bool>;

auto logOut(const std::string token) -> bool;

#endif