#ifndef COREINFO_HPP
#define COREINFO_HPP
#include <stdint.h>
#include <string>

struct UserSession {
  int32_t uid_;
  int32_t priviledge_;
};

extern std::string file_name_logger;
extern std::string file_name_account;
extern std::string file_name_course_static;
extern std::string file_name_course_remain;
extern std::string file_name_course_enrol;

#endif