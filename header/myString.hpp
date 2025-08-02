#ifndef MYSTRING_HPP
#define MYSTRING_HPP
#include <cstring>
#include <stdint.h>
#include <string>

template <int32_t MaxLength> class FixedString {
private:
  char data[MaxLength + 1];

public:
  FixedString() { data[0] = '\0'; }

  FixedString(const char *str) {
    strncpy(data, str, MaxLength);
    data[MaxLength] = '\0';
  }

  FixedString(const std::string &other) {
    strncpy(data, &other[0], MaxLength);
    data[MaxLength] = '\0';
  }

  FixedString(const FixedString &other) {
    strncpy(data, other.data, MaxLength);
    data[MaxLength] = '\0';
  }

  auto operator=(const std::string &other) -> FixedString & {
    strncpy(data, &other[0], MaxLength);
    data[MaxLength] = '\0';
    return *this;
  }

  auto operator=(const FixedString &other) -> FixedString & {
    if (this != &other) {
      strncpy(data, other.data, MaxLength);
      data[MaxLength] = '\0';
    }
    return *this;
  }

  auto str() const -> std::string { return data; }
  auto c_str() const -> const char * { return data; }
  auto length() const -> int32_t { return strlen(data); }
  auto is_clear() const -> bool { return data[0] == '\0'; }
  void clear() { data[0] = '\0'; }

  auto compare(const FixedString &other) const -> int32_t {
    return strcmp(data, other.data);
  }
};

template <int32_t MaxLength> struct FixStringComparator {
  auto operator()(const FixedString<MaxLength> &lhs,
                  const FixedString<MaxLength> &rhs) const -> int32_t {
    return lhs.compare(rhs);
  }
};

template <int32_t MaxLength> struct FixStringLess {
  auto operator()(const FixedString<MaxLength> &lhs,
                  const FixedString<MaxLength> &rhs) const -> bool {
    return lhs.compare(rhs) < 0;
  }
};
#endif