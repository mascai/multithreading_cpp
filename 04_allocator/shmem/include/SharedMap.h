/*
Условие:
Создать библиотеку с именем shmem.
В библиотеке должен быть реализован класс словаря Map, состояние которого разделяется между форками.
Словарь должен поддерживать POD типы и std::string в качестве ключа и значения.
Словарь должен быть реализован на std::map с собственным аллокатором памяти.
Должны быть реализованы методы вставки, удаления, изменения и получения элемента.
Библиотека должна гарантировать базовую безопасность исключений.

*/

#pragma once


#include <map>
#include <string>
#include <memory>

#include "SharedAllocator.h"
#include "Semaphore.h"


namespace SHMEM {

template<class Key, class Val, class Compare = std::less<Key>>
class SharedMap {
public:
    using value_type = std::pair<const Key, Val>;
    using map_type = std::map<Key, Val, Compare, ShAlloc<value_type>>;
public:
  SharedMap(size_t blockSize, size_t blocksCount) {
      char* mmapPtr = static_cast<char*>(::mmap(nullptr,
                            blockSize,
                            blocksCount,
                            PROT_WRITE | PROT_READ, /* can read and write to memory*/
                            MAP_SHARED | MAP_ANONYMOUS, /* visible to other processes | mapping is not backed by any file */
                            0)); /* fd and offset arguments are ignored because of MAP_ANONYMOUS */
      if (mmapPtr == MAP_FAILED) {
          throw std::runtime_error("mmap failed");
      }
      shMemState_ = {blocksCount, blockSize, new char[blockSize * blocksCount], std::move(mmapPtr)};

  }

  auto insert(value_type& val) {
      LockGuard guard(semaphore_);
      return map_.insert(val);
  }

  auto insert(value_type&& val) {
      LockGuard guard(semaphore_);
      return map_.insert(val);
  }

  auto erase(const value_type& val) {
      LockGuard guard(semaphore_);
      return map_.insert(val);
  }

  value_type get(Key key) {
      LockGuard guard(semaphore_);
      return map_.at(key);
  }

  typename map_type::iterator begin() {
      return map_.begin();
  }

  typename map_type::iterator end() {
      return map_.end();
  }

  ~SharedMap() {
      delete shMemState_.used_blocks_table;
      ::munmap(shMemState_.first_block, shMemState_.block_size * shMemState_.blocks_count);
  }

private:
    ShMemState shMemState_;
    Semaphore semaphore_;
    map_type map_;
};

} // SHMEM
