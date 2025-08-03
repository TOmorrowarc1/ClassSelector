#ifndef COURSE_HPP
#define COURSE_HPP
#include "coreinfo.hpp"

struct courseInfoOut {
  std::string name;
  std::string teacher;
  int32_t total_number;
};

auto addCourse(const UserSession &session, const courseInfoOut &new_course)
    -> bool;

auto modifyCourse(const UserSession &session, const courseInfoOut &new_course)
    -> bool;

auto launchCourse(const UserSession &session, const std::string &name) -> bool;

auto searchCourse(const UserSession &session, const std::string &name)
    -> courseInfoOut;

auto selectCourse(const UserSession &session, const std::string &name) -> bool;

auto checkCourse(const UserSession &session, const std::string &name)
    -> std::pair<bool, std::string>;

auto dropCourse(const UserSession &session, const std::string &name) -> bool;

#endif