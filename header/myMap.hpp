#ifndef MYMAP_HPP
#define MYMAP_HPP
#include <fstream>
#include <iostream>
#include <map>
#include <mutex>
#include <string>
#include <vector>

template <typename KeyType, typename ValueType, typename Comparator>
class PersistentMap {
private:
  std::map<KeyType, ValueType, Comparator> content_;
  std::mutex map_lock_;
  const std::string file_;

public:
  PersistentMap() = delete;
  PersistentMap(const PersistentMap &other) = delete;

  PersistentMap(const std::string &name);
  ~PersistentMap();

  // search for value following the key.
  auto search(const KeyType &key) const -> std::pair<ValueType, bool>;
  // return "false" if there is no such key, vice versa.
  auto insert(const KeyType &key, const ValueType &value) -> bool;
  // return "true" if the key exists.
  auto erase(const KeyType &key) -> bool;
};

template <typename KeyType, typename ValueType, typename Comparator>
PersistentMap<KeyType, ValueType, Comparator>::PersistentMap(
    const std::string &name)
    : file_(name) {
  std::lock_guard<std::mutex> lock(map_lock_);

  std::fstream pointer =
      std::fstream(file_, std::ios::binary, std::ios::in | std::ios::out);
  if (!pointer.good()) {
    pointer.close();
    return;
  }

  int32_t size = 0;
  pointer.read((char *)&size, sizeof(int32_t));
  int32_t map_size = size * (sizeof(KeyType) + sizeof(ValueType));

  std::vector<char> buffer(size);
  pointer.read((char *)&buffer.data(), map_size);
  const char *current_pos = buffer.data();
  const char *const end_pos = buffer.data() + map_size;

  for (int32_t i = 0; i < size; ++i) {
    if (current_pos + sizeof(KeyType) + sizeof(ValueType) > end_pos) {
      std::cerr << "Error: Corrupted file, unexpected end of buffer.\n";
      break;
    }
    KeyType key;
    ValueType value;
    std::memcpy(&key, current_pos, sizeof(Key));
    current_pos += sizeof(KeyType);
    std::memcpy(&value, current_pos, sizeof(Value));
    current_pos += sizeof(ValueType);
    content_[key] = value;
  }

  pointer.close();
}

template <typename KeyType, typename ValueType, typename Comparator>
PersistentMap<KeyType, ValueType, Comparator>::~PersistentMap() {
  std::lock_guard<std::mutex> lock(map_lock_);

  std::fstream pointer = std::fstream(file_, std::ios::binary, std::ios::out);

  int32_t size = content_.size();
  int32_t map_size =
      sizeof(int32_t) + size * (sizeof(KeyType) + sizeof(ValueType));

  std::vector<char> buffer(map_size);
  char *current_pos = buffer.data();

  std::memcpy(current_pos, &map_size, sizeof(int32_t));
  current_pos += sizeof(int32_t);

  for (const auto &pair : content_) {
    std::memcpy(current_pos, &pair.first, sizeof(KeyType));
    current_pos += sizeof(KeyType);
    std::memcpy(current_pos, &pair.second, sizeof(ValueType));
    current_pos += sizeof(ValueType);
  }

  pointer.write(buffer.data(), map_size);

  pointer.close();
}

template <typename KeyType, typename ValueType, typename Comparator>
auto PersistentMap<KeyType, ValueType, Comparator>::search(
    const KeyType &key) const -> std::pair<ValueType, bool> {
  std::lock_guard<std::mutex> lock(map_lock_);
  auto iter = content_.find(key);
  if (iter == content_.end()) {
    return std::pair<ValueType, bool>(ValueType(), false);
  }
  return std::pair<ValueType, bool>(iter->second, true);
}

template <typename KeyType, typename ValueType, typename Comparator>
auto PersistentMap<KeyType, ValueType, Comparator>::insert(
    const KeyType &key, const ValueType &value) -> bool {
  std::lock_guard<std::mutex> lock(map_lock_);
  bool flag = false;
  if (content_.count(key) == 0) {
    content_[key] = value;
    flag = true;
  }
  return flag;
}

template <typename KeyType, typename ValueType, typename Comparator>
auto PersistentMap<KeyType, ValueType, Comparator>::erase(const KeyType &key)
    -> bool {
  std::lock_guard<std::mutex> lock(map_lock_);
  bool flag = false;
  if (content_.count(key) != 0) {
    content_.erase(key);
    flag = true;
  }
  return flag;
}

#endif