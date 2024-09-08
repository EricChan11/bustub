//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// buffer_pool_manager_instance.cpp
//
// Identification: src/buffer/buffer_pool_manager.cpp
//
// Copyright (c) 2015-2021, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "buffer/buffer_pool_manager_instance.h"

#include "common/exception.h"
#include "common/logger.h"
#include "common/macros.h"
namespace bustub {

BufferPoolManagerInstance::BufferPoolManagerInstance(size_t pool_size, DiskManager *disk_manager, size_t replacer_k,
                                                     LogManager *log_manager)
    : pool_size_(pool_size), disk_manager_(disk_manager), log_manager_(log_manager) {
  // we allocate a consecutive memory space for the buffer pool
  pages_ = new Page[pool_size_];
  page_table_ = new ExtendibleHashTable<page_id_t, frame_id_t>(bucket_size_);
  replacer_ = new LRUKReplacer(pool_size, replacer_k);

  // Initially, every page is in the free list.
  for (size_t i = 0; i < pool_size_; ++i) {
    free_list_.emplace_back(static_cast<int>(i));
  }

  // TODO(students): remove this line after you have implemented the buffer pool manager
  // throw NotImplementedException(
  //     "BufferPoolManager is not implemented yet. If you have finished implementing BPM, please remove the throw "
  //     "exception line in `buffer_pool_manager_instance.cpp`.");
}

BufferPoolManagerInstance::~BufferPoolManagerInstance() {
  delete[] pages_;
  delete page_table_;
  delete replacer_;
}

auto BufferPoolManagerInstance::NewPgImp(page_id_t *page_id) -> Page * {
  std::scoped_lock<std::mutex> lock(latch_);
  frame_id_t fid;
  if (!free_list_.empty()) {
    fid = *free_list_.begin();
    *page_id = AllocatePage();
    free_list_.erase(free_list_.begin());
    page_table_->Insert(*page_id, fid);
    replacer_->RecordAccess(fid);
    pages_[fid].page_id_ = *page_id;
    pages_[fid].pin_count_ = 1;
    replacer_->SetEvictable(fid, false);
    return pages_ + fid;
  }
  if (replacer_->Evict(&fid)) {
    if (pages_[fid].IsDirty()) {
      disk_manager_->WritePage(pages_[fid].GetPageId(), pages_[fid].GetData());
      pages_[fid].is_dirty_ = false;
    }
    pages_[fid].ResetMemory();
    page_table_->Remove(pages_[fid].GetPageId());
    *page_id = AllocatePage();
    page_table_->Insert(*page_id, fid);
    replacer_->RecordAccess(fid);
    pages_[fid].page_id_ = *page_id;
    pages_[fid].pin_count_ = 1;
    replacer_->SetEvictable(fid, false);
    return pages_ + fid;
  }
  page_id = nullptr;
  return nullptr;
}

auto BufferPoolManagerInstance::FetchPgImp(page_id_t page_id) -> Page * {
  std::scoped_lock<std::mutex> lock(latch_);
  frame_id_t fid;
  if (page_table_->Find(page_id, fid)) {
    pages_[fid].pin_count_++;
    replacer_->SetEvictable(fid, false);
    replacer_->RecordAccess(fid);
    // LOG_DEBUG("Fetching page %d", page_id);
    return pages_ + fid;
  }
  if (!free_list_.empty()) {
    fid = *free_list_.begin();
    free_list_.erase(free_list_.begin());
    page_table_->Insert(page_id, fid);
    replacer_->RecordAccess(fid);
    pages_[fid].page_id_ = page_id;
    pages_[fid].pin_count_ = 1;
    replacer_->SetEvictable(fid, false);
    disk_manager_->ReadPage(page_id, pages_[fid].GetData());
    // LOG_DEBUG("Fetching page %d", page_id);
    return pages_ + fid;
  }
  if (replacer_->Evict(&fid)) {
    if (pages_[fid].IsDirty()) {
      disk_manager_->WritePage(pages_[fid].GetPageId(), pages_[fid].GetData());
      pages_[fid].is_dirty_ = false;
    }
    pages_[fid].ResetMemory();
    page_table_->Remove(pages_[fid].GetPageId());
    page_table_->Insert(page_id, fid);
    replacer_->RecordAccess(fid);
    pages_[fid].page_id_ = page_id;
    pages_[fid].pin_count_ = 1;
    replacer_->SetEvictable(fid, false);
    disk_manager_->ReadPage(page_id, pages_[fid].GetData());
    // LOG_DEBUG("Fetching page %d", page_id);
    return pages_ + fid;
  }
  // LOG_DEBUG("Fetching %d no", page_id);
  return nullptr;
}

auto BufferPoolManagerInstance::UnpinPgImp(page_id_t page_id, bool is_dirty) -> bool {
  std::scoped_lock<std::mutex> lock(latch_);
  frame_id_t fid;
  if (!page_table_->Find(page_id, fid)) {
    // LOG_DEBUG("unpin %d no", page_id);
    return false;
  }
  if (pages_[fid].GetPinCount() <= 0) {
    // LOG_DEBUG("unpin %d <0", page_id);
    return false;
  }
  if (is_dirty) {
    pages_[fid].is_dirty_ = is_dirty;
  }
  pages_[fid].pin_count_--;

  if (pages_[fid].pin_count_ == 0) {
    replacer_->SetEvictable(fid, true);
  }
  // LOG_DEBUG("unpin page %d", page_id);
  return true;
}

auto BufferPoolManagerInstance::FlushPgImp(page_id_t page_id) -> bool {
  std::scoped_lock<std::mutex> lock(latch_);
  frame_id_t fid;
  if (!page_table_->Find(page_id, fid)) {
    return false;
  }
  disk_manager_->WritePage(pages_[fid].GetPageId(), pages_[fid].GetData());
  pages_[fid].is_dirty_ = false;
  return true;
}

void BufferPoolManagerInstance::FlushAllPgsImp() {
  for (size_t i = 0; i < pool_size_; i++) {
    FlushPage(pages_[i].GetPageId());
  }
}

auto BufferPoolManagerInstance::DeletePgImp(page_id_t page_id) -> bool {
  std::scoped_lock<std::mutex> lock(latch_);
  frame_id_t fid;
  if (!page_table_->Find(page_id, fid)) {
    return true;
  }
  if (pages_[fid].pin_count_ > 0) {
    return false;
  }
  replacer_->Remove(fid);
  page_table_->Remove(page_id);
  free_list_.emplace_back(fid);
  pages_[fid].ResetMemory();
  pages_[fid].page_id_ = INVALID_PAGE_ID;
  pages_[fid].pin_count_ = 0;
  pages_[fid].is_dirty_ = false;
  DeallocatePage(fid);
  return true;
}

auto BufferPoolManagerInstance::AllocatePage() -> page_id_t { return next_page_id_++; }

}  // namespace bustub
