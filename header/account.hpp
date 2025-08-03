#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP
#include "coreinfo.hpp"
#include <vector>

struct studentInfo {
  std::string name;
  int32_t grade;
  int32_t class_number;
  int32_t password;
};

auto createAdminister() -> bool;

// Administer register new account for student;
auto signUp(const UserSession &session, const studentInfo &info,
            int32_t priviledge) -> bool;

// Administer remove a student from the list.
auto removeUser(const studentInfo &info) -> bool;

// Allow the administer get all uid for a class;
auto fetchUserClass(const studentInfo &class_info) -> std::vector<int32_t>;

// Allow the administer get every uid.
auto fetchUserAll(const studentInfo &class_info) -> std::vector<int32_t>;

// Everyone has logged in can modify his password.
auto modifyPassword(const UserSession &session, int32_t new_password) -> bool;

// Users log in.
auto logIn(const studentInfo &info) -> std::pair<bool, UserSession>;

// Users log out.
auto logOut(const UserSession &session) -> bool;

#endif