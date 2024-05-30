// Author: Di Yang
// Update: 2024-04-12

#ifndef PARAM_H_
#define PARAM_H_

#include <string>
#include <cstdint>

namespace dgraph {

class Param {
 public:
  Param() {
    topic_ = "";
    timestamp_ = 0;
    frame_id_ = 0;
    data_ = nullptr;
    data_size_ = 0;
  }
  ~Param() {
    
  }

  /// @brief set topic
  /// @param topic 
  void SetTopic(std::string const& topic) {
    topic_ = topic;
  }

  /// @brief set timestamp
  /// @param timestamp 
  void SetTimestamp(uint64_t const& timestamp) {
    timestamp_ = timestamp;
  }

  /// @brief set frame id
  /// @param frame_id 
  void SetFrameId(uint32_t const& frame_id) {
    frame_id_ = frame_id;
  }

  /// @brief get topic cann't be change
  /// @return string topic
  std::string const& GetTopic() const {
    return topic_;
  }

  /// @brief get timestamp cann't be change
  /// @return uint64_t timestamp
  uint64_t const& GetTimestamp() const {
    return timestamp_;
  }

  /// @brief get frame id cann't be change
  /// @return uint32_t frame id
  uint32_t const& GetFrameId() const {
    return frame_id_;
  }

  virtual void SetData(std::uint8_t* data, std::size_t size) {
    data_ = data;
    data_size_ = size;
  }

  virtual std::uint8_t* GetData() const {
    return data_;
  }

  virtual void Clear() {
    topic_ = "";
    timestamp_ = 0;
    frame_id_ = 0;
    data_size_ = 0;
    if (data_) {
      delete data_;
      data_ = nullptr;
    }
  }

 private:
  std::string topic_;
  uint64_t timestamp_;
  uint32_t frame_id_;
  std::uint8_t* data_;
  std::size_t data_size_;
};

} // namespace dgraph

#endif // PARAM_H_