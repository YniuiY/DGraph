// 环形缓冲队列
// 写索引和读索引之间始终空一个元素
// 读写索引重合则队列为空

#ifndef RingBuffer_h
#define RingBuffer_h

#include <iostream>
#include <array>

template <class Type, uint32_t size>
class RingBuffer
{
public:
    RingBuffer(): write_(0), read_(0), size_(size) {}
    ~RingBuffer() = default;

    /// @brief  元素入队，队满则入队失败
    /// @param item 入队元素
    /// @return 入队是否成功
    bool Enqueue(const Type& item) {
      if (read_ == ((write_ + 1) % size_)) {
        // 队满
        return false;
      }
      data_.at(write_) = item;
      write_ = (write_ + 1) % size_;
      return true;
    }

    /// @brief 强制将元素入队，队满则覆盖旧数据
    /// @param item 入队元素
    void EnqueueForce(const Type& item) {
      if (read_ == ((write_ + 1) % size_)) {
        // 队满，覆盖最早的数据
        read_ = (read_ + 1) % size_;
        std::cout << "Warning: Ring Buffer is full, overwriting the oldest data." << std::endl;
        std::cout << "read index: " << read_ << std::endl;
        
      }
      std::cout << "write index: " << write_ << std::endl;
      data_.at(write_) = item;
      write_ = (write_ + 1) % size_;
    }

    /// @brief 将最旧的元素出队，如果队空则出队失败
    /// @param item 出队的元素
    /// @return 出队是否成功
    bool Dequeue(Type& item) {
      if (write_ == read_) {
        // 队空
        return false;
      }
      item = data_.at(read_);
      read_ = (read_ + 1) % size_;
      return true;
    }

    /// @brief 是否队空
    /// @return 空：true
    bool IsEmpty() const {
      return write_ == read_;
    }

    /// @brief 是否队满
    /// @return 满：true
    bool IsFull() const {
      return (write_ + 1) % size_ == read_;
    }

    /// @brief 获取环形缓冲区大小
    /// @return 缓冲区大小
    uint32_t GetSize() const {
      return size_;
    }
private:
    std::array<Type, size> data_;
    uint32_t write_;
    uint32_t read_;
    uint32_t size_;
};


#endif //RingBuffer_h