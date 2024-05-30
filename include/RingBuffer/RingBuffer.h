// 环形缓冲队列
// 写索引和读索引之间始终空一个元素
// 读写索引重合则队列为空

#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <array>
#include <atomic>
#include <iostream>

template <class Type, uint32_t size>
class RingBuffer {
 public:
  RingBuffer() : write_(0), read_(0), size_(size) {}
  ~RingBuffer() = default;

  /**
   * @brief  元素入队，队满则入队失败
   * @param item 入队元素
   * @return 入队是否成功
   */
  bool Push(const Type& item) {
    if (read_ == ((write_ + 1) % size_)) {
      // 写索引和读索引之间空一个元素
      // 队满
      std::cout << "Ring Buffer is Full\n";
      return false;
    }
    data_.at(write_) = item;
    write_ = (write_ + 1) % size_;
    return true;
  }

  /**
   * @brief 强制将元素入队，队满则覆盖旧数据
   * @param item 入队元素
   */
  void PushForce(const Type& item) {
    if (read_ == ((write_ + 1) % size_)) {
      // 写索引和读索引之间空一个元素
      // 队满，覆盖最早的数据
      read_ = (read_ + 1) % size_;
      std::cout << "Warning: Ring Buffer is full, overwriting the oldest data."
                << std::endl;
      std::cout << "read index: " << read_ << std::endl;
    }
    std::cout << "write index: " << write_ << std::endl;
    data_.at(write_) = item;
    write_ = (write_ + 1) % size_;
  }

  /**
   * @brief 获取队列最前端的元素
   * @return 队列最前端的元素
   */
  Type* Front() {
    Type* item = nullptr;
    if (write_ == read_) {
      // 队空
      std::cout << "RingBuffer is Empty\n";
      return item;
    }

    item = &data_.at(read_);
    return item;
  }

  /**
   * @brief 元素出队，队空则出队失败
   * @return 出队是否成功
   */
  bool Pop() {
    if (write_ == read_) {
      // 队空
      return false;
    }
    read_ = (read_ + 1) % size_;
    return true;
  }

  /**
   * @brief 元素出队，队空则出队失败
   * @param item 出队元素
   * @return 出队是否成功
   */
  bool Pop(Type& item) {
    if (write_ == read_) {
      // 队空
      return false;
    }
    item = data_.at(read_);
    read_ = (read_ + 1) % size_;
    return true;
  }

  /**
   * @brief 队空
   * @return 空：true
   */
  bool IsEmpty() const { return write_ == read_; }

  /**
   * @brief 队满
   * @return 满：true
   */
  bool IsFull() const { return (write_ + 1) % size_ == read_; }

  /**
   * @brief 获取环形缓冲区大小
   * @return 缓冲区大小
   */
  uint32_t GetSize() const { return size_; }

 private:
  std::array<Type, size> data_;
  std::uint32_t write_;
  std::uint32_t read_;
  uint32_t size_;
};

#endif  // RING_BUFFER_H