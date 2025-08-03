#include "account.hpp"
#include "logger.hpp"
#include "myMap.hpp"
#include "myString.hpp"

struct NumberComparator {
  auto operator()(int32_t a, int32_t b) const -> bool { return a < b; }
};

struct UserInfoIn {
  FixedString<10> name;
  int32_t grade;
  int32_t class_order;
  int32_t priviledge;
  int32_t password;
};

int32_t hash(const UserInfoIn &target) {
  return target.name.Hash() ^ (target.grade << 10 + target.class_order);
}

PersistentMap<int32_t, UserInfoIn, NumberComparator>
    user_info(file_name_account);

auto createAdminister() -> bool {
  UserInfoIn admin_info;
  std::string name = "administer";
  admin_info.name = name;
  admin_info.priviledge = 7;
  admin_info.password = 123456;
  admin_info.grade = 0;
  admin_info.class_order = 0;
  int32_t uid = admin_info.name.Hash();
  return user_info.insert(uid, admin_info);
}

auto signUp(const UserSession &session, const studentInfoOut &info,
            int32_t priviledge) -> bool {
  if (session.priviledge_ != 7 || priviledge != 1) {
    return false;
  }
  UserInfoIn admin_info;
  admin_info.name = info.name;
  admin_info.priviledge = priviledge;
  admin_info.password = info.password;
  admin_info.grade = info.grade;
  admin_info.class_order = info.class_number;
  int32_t uid = hash(admin_info);
  return user_info.insert(uid, admin_info);
}

auto removeUser(const UserSession &session, const studentInfoOut &info)
    -> bool {
  if (session.priviledge_ != 7) {
    return false;
  }
  UserInfoIn target{FixedString<10>(info.name), info.grade, info.class_number};
  int32_t uid = hash(target);
  return user_info.erase(uid);
}

auto fetchUserAll(const UserSession &session) -> std::vector<int32_t> {
  std::vector<int32_t> result;
  if (session.priviledge_ != 7) {
    return result;
  }
  auto result_info = user_info.traverseKey(1 << 31, ~(1 << 31));
  for (auto iter = result_info.begin(); iter != result_info.end(); ++iter) {
    result.push_back(*iter);
  }
  return result;
}

auto modifyPassword(const UserSession &session, int32_t new_password) -> bool {
  auto userInfo = user_info.search(session.uid_);
  if (!userInfo.second) {
    return false;
  }
  userInfo.first.password = new_password;
  user_info.erase(session.uid_);
  user_info.insert(session.uid_, userInfo.first);
  return true;
}

auto logIn(const studentInfoOut &info) -> std::pair<bool, UserSession> {
  UserInfoIn target{FixedString<10>(info.name), info.grade, info.class_number};
  UserSession result;
  result.uid_ = hash(target);
  auto userInfo = user_info.search(result.uid_);
  if (userInfo.second && userInfo.first.password == info.password) {
    result.priviledge_ = userInfo.first.priviledge;
  }
  return std::pair<bool, UserSession>(userInfo.second, result);
}