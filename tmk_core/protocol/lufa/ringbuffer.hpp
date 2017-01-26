#pragma once
// A simple ringbuffer holding Size elements of type T
template <typename T, uint8_t Size>
class RingBuffer {
 protected:
  T buf_[Size];
  uint8_t head_{0}, tail_{0};
 public:
  inline uint8_t nextPosition(uint8_t position) {
    return (position + 1) % Size;
  }

  inline uint8_t prevPosition(uint8_t position) {
    if (position == 0) {
      return Size - 1;
    }
    return position - 1;
  }

  inline bool enqueue(const T &item) {
    static_assert(Size > 1, "RingBuffer size must be > 1");
    uint8_t next = nextPosition(head_);
    if (next == tail_) {
      // Full
      return false;
    }

    buf_[head_] = item;
    head_ = next;
    return true;
  }

  inline bool get(T &dest, bool commit = true) {
    auto tail = tail_;
    if (tail == head_) {
      // No more data
      return false;
    }

    dest = buf_[tail];
    tail = nextPosition(tail);

    if (commit) {
      tail_ = tail;
    }
    return true;
  }

  inline bool empty() const { return head_ == tail_; }

  inline uint8_t size() const {
    int diff = head_ - tail_;
    if (diff >= 0) {
      return diff;
    }
    return Size + diff;
  }

  inline T& front() {
    return buf_[tail_];
  }

  inline bool peek(T &item) {
    return get(item, false);
  }
};
