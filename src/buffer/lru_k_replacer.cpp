//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// lru_k_replacer.cpp
//
// Identification: src/buffer/lru_k_replacer.cpp
//
// Copyright (c) 2015-2022, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "buffer/lru_k_replacer.h"

namespace bustub {

LRUKReplacer::LRUKReplacer(size_t num_frames, size_t k) : replacer_size_(num_frames), k_(k) {}

auto LRUKReplacer::Evict(frame_id_t *frame_id) -> bool {
  std::scoped_lock<std::mutex> lock(latch_);
  if (curr_size_ == 0) {
    return false;
  }
  if (!less_k_.empty()) {
    for (auto i = less_k_.rbegin(); i != less_k_.rend(); i++) {
      if (frames_[*i].evitable_) {
        *frame_id = *i;
        less_k_.erase(frames_[*i].pos_);
        frames_.erase(*frame_id);
        curr_size_--;
        return true;
      }
    }
  }
  if (!more_k_.empty()) {
    for (auto i = more_k_.rbegin(); i != more_k_.rend(); i++) {
      if (frames_[*i].evitable_) {
        *frame_id = *i;
        more_k_.erase(frames_[*i].pos_);
        frames_.erase(*frame_id);
        curr_size_--;
        return true;
      }
    }
  }
  return false;
}

void LRUKReplacer::RecordAccess(frame_id_t frame_id) {
  std::scoped_lock<std::mutex> lock(latch_);
  if (frame_id > static_cast<int>(replacer_size_)) {
    throw std::exception();
  }
  frames_[frame_id].count_++;
  if (frames_[frame_id].count_ == 1) {
    curr_size_++;
    less_k_.push_front(frame_id);
    frames_[frame_id].pos_ = less_k_.begin();
  }
  if (frames_[frame_id].count_ == k_) {
    less_k_.erase(frames_[frame_id].pos_);
    more_k_.push_front(frame_id);
    frames_[frame_id].pos_ = more_k_.begin();
  } else if (frames_[frame_id].count_ > k_) {
    more_k_.erase(frames_[frame_id].pos_);
    more_k_.push_front(frame_id);
    frames_[frame_id].pos_ = more_k_.begin();
  }
}

void LRUKReplacer::SetEvictable(frame_id_t frame_id, bool set_evictable) {
  std::scoped_lock<std::mutex> lock(latch_);
  if (frame_id > static_cast<int>(replacer_size_)) {
    throw std::exception();
  }
  if (frames_.find(frame_id) == frames_.end()) {
    return;
  }
  if (set_evictable && (set_evictable != frames_[frame_id].evitable_)) {
    curr_size_++;
  } else if (!set_evictable && (set_evictable != frames_[frame_id].evitable_)) {
    curr_size_--;
  }
  frames_[frame_id].evitable_ = set_evictable;
}

void LRUKReplacer::Remove(frame_id_t frame_id) {
  std::scoped_lock<std::mutex> lock(latch_);
  if (frame_id > static_cast<int>(replacer_size_)) {
    throw std::exception();
  }
  if (frames_.find(frame_id) == frames_.end()) {
    return;
  }
  if (!frames_[frame_id].evitable_) {
    return;
  }
  if (frames_[frame_id].count_ < k_) {
    less_k_.erase(frames_[frame_id].pos_);
  } else {
    more_k_.erase(frames_[frame_id].pos_);
  }
  curr_size_--;
  frames_.erase(frame_id);
}

auto LRUKReplacer::Size() -> size_t {
  std::scoped_lock<std::mutex> lock(latch_);
  return curr_size_;
}

}  // namespace bustub
