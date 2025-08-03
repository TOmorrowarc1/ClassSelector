#include "token.hpp"
#include "myMap.hpp"
#include <random>

const std::string ALAPHBET =
    "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
const int32_t TOKENLENGTH = 10;

ConcurrentMap<std::string, UserSession> vaild_token;

auto applyToken(const UserSession &session) -> std::string {
  std::string result;
  do {
    srand(time(0));
    result.clear();
    for (int32_t i = 0; i < TOKENLENGTH; ++i) {
      result += ALAPHBET[rand() % ALAPHBET.length()];
    }
  } while (!vaild_token.insert(result, session));
  return result;
}

auto quireSession(const std::string token) -> std::pair<UserSession, bool> {
  return vaild_token.search(token);
}

auto logOut(const std::string token) -> bool {
  return vaild_token.erase(token);
}