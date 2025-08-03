#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP
#include "coreinfo.hpp"
#include <vector>

struct studentInfoOut {
  std::string name;
  int32_t grade;
  int32_t class_number;
  int32_t password;
};

auto createAdminister() -> bool;

// Administer register new account for student;
auto signUp(const UserSession &session, const studentInfoOut &info,
            int32_t priviledge) -> bool;

// Administer remove a student from the list.
auto removeUser(const UserSession &session, const studentInfoOut &info) -> bool;

// Allow the administer get every uid.
auto fetchUserAll(const UserSession &session) -> std::vector<int32_t>;

// Everyone has logged in can modify his password.
auto modifyPassword(const UserSession &session, int32_t new_password) -> bool;

// Users try to log in.
auto logIn(const studentInfoOut &info) -> std::pair<bool, UserSession>;

#endif