//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// lock_manager.cpp
//
// Identification: src/concurrency/lock_manager.cpp
//
// Copyright (c) 2015-2019, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "concurrency/lock_manager.h"

#include "common/config.h"
#include "concurrency/transaction.h"
#include "concurrency/transaction_manager.h"

namespace bustub {
auto LockManager::IsUpgradeCompatible(LockMode current_mode, LockMode new_mode) -> bool {
  if (current_mode == LockMode::INTENTION_SHARED &&
      (new_mode == LockMode::SHARED || new_mode == LockMode::EXCLUSIVE || new_mode == LockMode::INTENTION_EXCLUSIVE ||
       new_mode == LockMode::SHARED_INTENTION_EXCLUSIVE)) {
    return true;
  }
  if (current_mode == LockMode::SHARED &&
      (new_mode == LockMode::EXCLUSIVE || new_mode == LockMode::SHARED_INTENTION_EXCLUSIVE)) {
    return true;
  }
  if (current_mode == LockMode::INTENTION_EXCLUSIVE &&
      (new_mode == LockMode::EXCLUSIVE || new_mode == LockMode::SHARED_INTENTION_EXCLUSIVE)) {
    return true;
  }
  if (current_mode == LockMode::SHARED_INTENTION_EXCLUSIVE && new_mode == LockMode::EXCLUSIVE) {
    return true;
  }
  return false;
}

void LockManager::InsertOrDeleteTableLockSet(Transaction *txn, const std::shared_ptr<LockRequest> &lock_request,
                                             bool insert) {
  // Lambda function to insert or delete from the specified lock set
  auto modify_lock_set = [insert](auto &lock_set, auto oid) {
    if (insert) {
      lock_set->insert(oid);
    } else {
      lock_set->erase(oid);
    }
  };

  switch (lock_request->lock_mode_) {
    case LockMode::SHARED:
      modify_lock_set(txn->GetSharedTableLockSet(), lock_request->oid_);
      break;
    case LockMode::EXCLUSIVE:
      modify_lock_set(txn->GetExclusiveTableLockSet(), lock_request->oid_);
      break;
    case LockMode::INTENTION_SHARED:
      modify_lock_set(txn->GetIntentionSharedTableLockSet(), lock_request->oid_);
      break;
    case LockMode::INTENTION_EXCLUSIVE:
      modify_lock_set(txn->GetIntentionExclusiveTableLockSet(), lock_request->oid_);
      break;
    case LockMode::SHARED_INTENTION_EXCLUSIVE:
      modify_lock_set(txn->GetSharedIntentionExclusiveTableLockSet(), lock_request->oid_);
      break;
  }
}
auto LockManager::GrantLock(const std::shared_ptr<LockRequest> &lock_request,
                            const std::shared_ptr<LockRequestQueue> &lock_request_queue) -> bool {
  for (auto &lr : lock_request_queue->request_queue_) {
    if (lr->granted_) {
      switch (lock_request->lock_mode_) {
        case LockMode::SHARED:
          if (lr->lock_mode_ == LockMode::INTENTION_EXCLUSIVE ||
              lr->lock_mode_ == LockMode::SHARED_INTENTION_EXCLUSIVE || lr->lock_mode_ == LockMode::EXCLUSIVE) {
            return false;
          }
          break;
        case LockMode::EXCLUSIVE:
          return false;
          break;
        case LockMode::INTENTION_SHARED:
          if (lr->lock_mode_ == LockMode::EXCLUSIVE) {
            return false;
          }
          break;
        case LockMode::INTENTION_EXCLUSIVE:
          if (lr->lock_mode_ == LockMode::SHARED || lr->lock_mode_ == LockMode::SHARED_INTENTION_EXCLUSIVE ||
              lr->lock_mode_ == LockMode::EXCLUSIVE) {
            return false;
          }
          break;
        case LockMode::SHARED_INTENTION_EXCLUSIVE:
          if (lr->lock_mode_ != LockMode::INTENTION_SHARED) {
            return false;
          }
          break;
      }
    } else if (lock_request.get() != lr) {
      return false;
    } else {
      return true;
    }
  }
  return false;
}
auto InsertRowLockSet(const std::shared_ptr<std::unordered_map<table_oid_t, std::unordered_set<RID>>> &lock_set,
                      const table_oid_t &oid, const RID &rid) -> void {
  auto row_lock_set = lock_set->find(oid);
  if (row_lock_set == lock_set->end()) {
    lock_set->emplace(oid, std::unordered_set<RID>{});
    row_lock_set = lock_set->find(oid);
  }
  row_lock_set->second.emplace(rid);
}

auto DeleteRowLockSet(const std::shared_ptr<std::unordered_map<table_oid_t, std::unordered_set<RID>>> &lock_set,
                      const table_oid_t &oid, const RID &rid) -> void {
  auto row_lock_set = lock_set->find(oid);
  if (row_lock_set == lock_set->end()) {
    return;
  }
  row_lock_set->second.erase(rid);
}
void LockManager::InsertOrDeleteRowLockSet(Transaction *txn, const std::shared_ptr<LockRequest> &lock_request,
                                           bool insert) {
  auto s_row_lock_set = txn->GetSharedRowLockSet();
  auto x_row_lock_set = txn->GetExclusiveRowLockSet();
  switch (lock_request->lock_mode_) {
    case LockMode::SHARED:
      if (insert) {
        InsertRowLockSet(s_row_lock_set, lock_request->oid_, lock_request->rid_);
      } else {
        DeleteRowLockSet(s_row_lock_set, lock_request->oid_, lock_request->rid_);
      }
      break;
    case LockMode::EXCLUSIVE:
      if (insert) {
        InsertRowLockSet(x_row_lock_set, lock_request->oid_, lock_request->rid_);
      } else {
        DeleteRowLockSet(x_row_lock_set, lock_request->oid_, lock_request->rid_);
      }
      break;
    case LockMode::INTENTION_SHARED:
    case LockMode::INTENTION_EXCLUSIVE:
    case LockMode::SHARED_INTENTION_EXCLUSIVE:
      break;
  }
}
auto LockManager::LockTable(Transaction *txn, LockMode lock_mode, const table_oid_t &oid) -> bool {
  auto isolationlevel = txn->GetIsolationLevel();
  auto state = txn->GetState();
  if (state == TransactionState::COMMITTED || state == TransactionState::ABORTED) {
    return false;
  }
  switch (isolationlevel) {
    case IsolationLevel::READ_UNCOMMITTED:
      if (lock_mode != LockMode::EXCLUSIVE && lock_mode != LockMode::INTENTION_EXCLUSIVE) {
        txn->SetState(TransactionState::ABORTED);
        throw TransactionAbortException(txn->GetTransactionId(), AbortReason::LOCK_SHARED_ON_READ_UNCOMMITTED);
      }
      if (state == TransactionState::SHRINKING &&
          (lock_mode == LockMode::EXCLUSIVE || lock_mode == LockMode::INTENTION_EXCLUSIVE)) {
        txn->SetState(TransactionState::ABORTED);
        throw TransactionAbortException(txn->GetTransactionId(), AbortReason::LOCK_ON_SHRINKING);
      }
      break;

    case IsolationLevel::READ_COMMITTED:
      if (state == TransactionState::SHRINKING && lock_mode != LockMode::INTENTION_SHARED &&
          lock_mode != LockMode::SHARED) {
        txn->SetState(TransactionState::ABORTED);
        throw TransactionAbortException(txn->GetTransactionId(), AbortReason::LOCK_ON_SHRINKING);
      }
      break;

    case IsolationLevel::REPEATABLE_READ:
      if (state == TransactionState::SHRINKING) {
        txn->SetState(TransactionState::ABORTED);
        throw TransactionAbortException(txn->GetTransactionId(), AbortReason::LOCK_ON_SHRINKING);
      }
      break;

    default:
      break;
  }
  table_lock_map_latch_.lock();
  if (table_lock_map_.find(oid) == table_lock_map_.end()) {
    table_lock_map_.emplace(oid, std::make_shared<LockRequestQueue>());
  }
  auto lock_request_queue = table_lock_map_.find(oid)->second;
  lock_request_queue->latch_.lock();
  table_lock_map_latch_.unlock();

  for (auto request : lock_request_queue->request_queue_) {  // NOLINT
    if (request->txn_id_ == txn->GetTransactionId()) {
      if (request->lock_mode_ == lock_mode) {
        lock_request_queue->latch_.unlock();
        return true;
      }

      if (lock_request_queue->upgrading_ != INVALID_TXN_ID) {
        lock_request_queue->latch_.unlock();
        txn->SetState(TransactionState::ABORTED);
        throw TransactionAbortException(txn->GetTransactionId(), AbortReason::UPGRADE_CONFLICT);
      }

      if (!IsUpgradeCompatible(request->lock_mode_, lock_mode)) {
        lock_request_queue->latch_.unlock();
        txn->SetState(TransactionState::ABORTED);
        throw TransactionAbortException(txn->GetTransactionId(), AbortReason::INCOMPATIBLE_UPGRADE);
      }

      lock_request_queue->request_queue_.remove(request);
      InsertOrDeleteTableLockSet(txn, request, false);

      auto upgrade_lock_request = std::make_shared<LockRequest>(txn->GetTransactionId(), lock_mode, oid);

      std::list<std::shared_ptr<LockRequest>>::iterator lr_iter;
      for (lr_iter = lock_request_queue->request_queue_.begin(); lr_iter != lock_request_queue->request_queue_.end();
           lr_iter++) {
        if (!(*lr_iter)->granted_) {
          break;
        }
      }
      lock_request_queue->request_queue_.insert(lr_iter, upgrade_lock_request);
      lock_request_queue->upgrading_ = txn->GetTransactionId();

      std::unique_lock<std::mutex> lock(lock_request_queue->latch_, std::adopt_lock);
      while (!GrantLock(upgrade_lock_request, lock_request_queue)) {
        lock_request_queue->cv_.wait(lock);
        if (txn->GetState() == TransactionState::ABORTED) {
          lock_request_queue->upgrading_ = INVALID_TXN_ID;
          lock_request_queue->request_queue_.remove(upgrade_lock_request);
          lock_request_queue->cv_.notify_all();
          return false;
        }
      }

      lock_request_queue->upgrading_ = INVALID_TXN_ID;
      upgrade_lock_request->granted_ = true;
      InsertOrDeleteTableLockSet(txn, upgrade_lock_request, true);

      if (lock_mode != LockMode::EXCLUSIVE) {
        lock_request_queue->cv_.notify_all();
      }
      return true;
    }
  }

  auto lock_request = std::make_shared<LockRequest>(txn->GetTransactionId(), lock_mode, oid);
  lock_request_queue->request_queue_.push_back(lock_request);

  std::unique_lock<std::mutex> lock(lock_request_queue->latch_, std::adopt_lock);
  while (!GrantLock(lock_request, lock_request_queue)) {
    lock_request_queue->cv_.wait(lock);
    if (txn->GetState() == TransactionState::ABORTED) {
      lock_request_queue->request_queue_.remove(lock_request);
      lock_request_queue->cv_.notify_all();
      return false;
    }
  }

  lock_request->granted_ = true;
  InsertOrDeleteTableLockSet(txn, lock_request, true);

  if (lock_mode != LockMode::EXCLUSIVE) {
    lock_request_queue->cv_.notify_all();
  }

  return true;
}

auto LockManager::UnlockTable(Transaction *txn, const table_oid_t &oid) -> bool {
  table_lock_map_latch_.lock();

  if (table_lock_map_.find(oid) == table_lock_map_.end()) {
    table_lock_map_latch_.unlock();
    txn->SetState(TransactionState::ABORTED);
    throw bustub::TransactionAbortException(txn->GetTransactionId(), AbortReason::ATTEMPTED_UNLOCK_BUT_NO_LOCK_HELD);
  }

  auto s_row_lock_set = txn->GetSharedRowLockSet();
  auto x_row_lock_set = txn->GetExclusiveRowLockSet();

  if (!(s_row_lock_set->find(oid) == s_row_lock_set->end() || s_row_lock_set->at(oid).empty()) ||
      !(x_row_lock_set->find(oid) == x_row_lock_set->end() || x_row_lock_set->at(oid).empty())) {
    table_lock_map_latch_.unlock();
    txn->SetState(TransactionState::ABORTED);
    throw bustub::TransactionAbortException(txn->GetTransactionId(), AbortReason::TABLE_UNLOCKED_BEFORE_UNLOCKING_ROWS);
  }

  auto lock_request_queue = table_lock_map_[oid];

  lock_request_queue->latch_.lock();
  table_lock_map_latch_.unlock();

  for (auto lock_request : lock_request_queue->request_queue_) {  // NOLINT
    if (lock_request->txn_id_ == txn->GetTransactionId() && lock_request->granted_) {
      lock_request_queue->request_queue_.remove(lock_request);

      lock_request_queue->cv_.notify_all();
      lock_request_queue->latch_.unlock();

      bool isRepeatableReadAndLockModeSharedOrExclusive =
          txn->GetIsolationLevel() == IsolationLevel::REPEATABLE_READ &&
          (lock_request->lock_mode_ == LockMode::SHARED || lock_request->lock_mode_ == LockMode::EXCLUSIVE);

      bool isReadCommittedAndLockModeExclusive =
          txn->GetIsolationLevel() == IsolationLevel::READ_COMMITTED && lock_request->lock_mode_ == LockMode::EXCLUSIVE;

      bool isReadUncommittedAndLockModeExclusive = txn->GetIsolationLevel() == IsolationLevel::READ_UNCOMMITTED &&
                                                   lock_request->lock_mode_ == LockMode::EXCLUSIVE;

      bool shouldShrink = isRepeatableReadAndLockModeSharedOrExclusive || isReadCommittedAndLockModeExclusive ||
                          isReadUncommittedAndLockModeExclusive;

      if (shouldShrink) {
        if (txn->GetState() != TransactionState::COMMITTED && txn->GetState() != TransactionState::ABORTED) {
          txn->SetState(TransactionState::SHRINKING);
        }
      }

      InsertOrDeleteTableLockSet(txn, lock_request, false);
      return true;
    }
  }

  lock_request_queue->latch_.unlock();
  txn->SetState(TransactionState::ABORTED);
  throw bustub::TransactionAbortException(txn->GetTransactionId(), AbortReason::ATTEMPTED_UNLOCK_BUT_NO_LOCK_HELD);
}

auto LockManager::LockRow(Transaction *txn, LockMode lock_mode, const table_oid_t &oid, const RID &rid) -> bool {
  if (lock_mode == LockMode::INTENTION_EXCLUSIVE || lock_mode == LockMode::INTENTION_SHARED ||
      lock_mode == LockMode::SHARED_INTENTION_EXCLUSIVE) {
    txn->SetState(TransactionState::ABORTED);
    throw TransactionAbortException(txn->GetTransactionId(), AbortReason::ATTEMPTED_INTENTION_LOCK_ON_ROW);
  }

  auto isolationlevel = txn->GetIsolationLevel();
  auto state = txn->GetState();
  if (state == TransactionState::COMMITTED || state == TransactionState::ABORTED) {
    return false;
  }
  switch (isolationlevel) {
    case IsolationLevel::READ_UNCOMMITTED:
      if (lock_mode != LockMode::EXCLUSIVE && lock_mode != LockMode::INTENTION_EXCLUSIVE) {
        txn->SetState(TransactionState::ABORTED);
        throw TransactionAbortException(txn->GetTransactionId(), AbortReason::LOCK_SHARED_ON_READ_UNCOMMITTED);
      }
      if (state == TransactionState::SHRINKING &&
          (lock_mode == LockMode::EXCLUSIVE || lock_mode == LockMode::INTENTION_EXCLUSIVE)) {
        txn->SetState(TransactionState::ABORTED);
        throw TransactionAbortException(txn->GetTransactionId(), AbortReason::LOCK_ON_SHRINKING);
      }
      break;

    case IsolationLevel::READ_COMMITTED:
      if (state == TransactionState::SHRINKING && lock_mode != LockMode::INTENTION_SHARED &&
          lock_mode != LockMode::SHARED) {
        txn->SetState(TransactionState::ABORTED);
        throw TransactionAbortException(txn->GetTransactionId(), AbortReason::LOCK_ON_SHRINKING);
      }
      break;

    case IsolationLevel::REPEATABLE_READ:
      if (state == TransactionState::SHRINKING) {
        txn->SetState(TransactionState::ABORTED);
        throw TransactionAbortException(txn->GetTransactionId(), AbortReason::LOCK_ON_SHRINKING);
      }
      break;

    default:
      break;
  }

  if (lock_mode == LockMode::EXCLUSIVE) {
    if (!txn->IsTableExclusiveLocked(oid) && !txn->IsTableIntentionExclusiveLocked(oid) &&
        !txn->IsTableSharedIntentionExclusiveLocked(oid)) {
      txn->SetState(TransactionState::ABORTED);
      throw TransactionAbortException(txn->GetTransactionId(), AbortReason::TABLE_LOCK_NOT_PRESENT);
    }
  }

  row_lock_map_latch_.lock();
  if (row_lock_map_.find(rid) == row_lock_map_.end()) {
    row_lock_map_.emplace(rid, std::make_shared<LockRequestQueue>());
  }
  auto lock_request_queue = row_lock_map_.find(rid)->second;
  lock_request_queue->latch_.lock();
  row_lock_map_latch_.unlock();

  for (auto request : lock_request_queue->request_queue_) {  // NOLINT
    if (request->txn_id_ == txn->GetTransactionId()) {
      if (request->lock_mode_ == lock_mode) {
        lock_request_queue->latch_.unlock();
        return true;
      }

      if (lock_request_queue->upgrading_ != INVALID_TXN_ID) {
        lock_request_queue->latch_.unlock();
        txn->SetState(TransactionState::ABORTED);
        throw TransactionAbortException(txn->GetTransactionId(), AbortReason::UPGRADE_CONFLICT);
      }

      if (!IsUpgradeCompatible(request->lock_mode_, lock_mode)) {
        lock_request_queue->latch_.unlock();
        txn->SetState(TransactionState::ABORTED);
        throw TransactionAbortException(txn->GetTransactionId(), AbortReason::INCOMPATIBLE_UPGRADE);
      }

      lock_request_queue->request_queue_.remove(request);
      InsertOrDeleteRowLockSet(txn, request, false);
      auto upgrade_lock_request = std::make_shared<LockRequest>(txn->GetTransactionId(), lock_mode, oid, rid);

      std::list<std::shared_ptr<LockRequest>>::iterator lr_iter;
      for (lr_iter = lock_request_queue->request_queue_.begin(); lr_iter != lock_request_queue->request_queue_.end();
           lr_iter++) {
        if (!(*lr_iter)->granted_) {
          break;
        }
      }
      lock_request_queue->request_queue_.insert(lr_iter, upgrade_lock_request);
      lock_request_queue->upgrading_ = txn->GetTransactionId();

      std::unique_lock<std::mutex> lock(lock_request_queue->latch_, std::adopt_lock);
      while (!GrantLock(upgrade_lock_request, lock_request_queue)) {
        lock_request_queue->cv_.wait(lock);
        if (txn->GetState() == TransactionState::ABORTED) {
          lock_request_queue->upgrading_ = INVALID_TXN_ID;
          lock_request_queue->request_queue_.remove(upgrade_lock_request);
          lock_request_queue->cv_.notify_all();
          return false;
        }
      }

      lock_request_queue->upgrading_ = INVALID_TXN_ID;
      upgrade_lock_request->granted_ = true;
      InsertOrDeleteRowLockSet(txn, upgrade_lock_request, true);

      if (lock_mode != LockMode::EXCLUSIVE) {
        lock_request_queue->cv_.notify_all();
      }
      return true;
    }
  }

  auto lock_request = std::make_shared<LockRequest>(txn->GetTransactionId(), lock_mode, oid, rid);
  lock_request_queue->request_queue_.push_back(lock_request);

  std::unique_lock<std::mutex> lock(lock_request_queue->latch_, std::adopt_lock);
  while (!GrantLock(lock_request, lock_request_queue)) {
    lock_request_queue->cv_.wait(lock);
    if (txn->GetState() == TransactionState::ABORTED) {
      lock_request_queue->request_queue_.remove(lock_request);
      lock_request_queue->cv_.notify_all();
      return false;
    }
  }

  lock_request->granted_ = true;
  InsertOrDeleteRowLockSet(txn, lock_request, true);

  if (lock_mode != LockMode::EXCLUSIVE) {
    lock_request_queue->cv_.notify_all();
  }

  return true;
}

auto LockManager::UnlockRow(Transaction *txn, const table_oid_t &oid, const RID &rid) -> bool {
  row_lock_map_latch_.lock();

  if (row_lock_map_.find(rid) == row_lock_map_.end()) {
    row_lock_map_latch_.unlock();
    txn->SetState(TransactionState::ABORTED);
    throw bustub::TransactionAbortException(txn->GetTransactionId(), AbortReason::ATTEMPTED_UNLOCK_BUT_NO_LOCK_HELD);
  }
  auto lock_request_queue = row_lock_map_[rid];

  lock_request_queue->latch_.lock();
  row_lock_map_latch_.unlock();

  for (auto lock_request : lock_request_queue->request_queue_) {  // NOLINT
    if (lock_request->txn_id_ == txn->GetTransactionId() && lock_request->granted_) {
      lock_request_queue->request_queue_.remove(lock_request);

      lock_request_queue->cv_.notify_all();
      lock_request_queue->latch_.unlock();

      if ((txn->GetIsolationLevel() == IsolationLevel::REPEATABLE_READ &&
           (lock_request->lock_mode_ == LockMode::SHARED || lock_request->lock_mode_ == LockMode::EXCLUSIVE)) ||
          (txn->GetIsolationLevel() == IsolationLevel::READ_COMMITTED &&
           lock_request->lock_mode_ == LockMode::EXCLUSIVE) ||
          (txn->GetIsolationLevel() == IsolationLevel::READ_UNCOMMITTED &&
           lock_request->lock_mode_ == LockMode::EXCLUSIVE)) {
        if (txn->GetState() != TransactionState::COMMITTED && txn->GetState() != TransactionState::ABORTED) {
          txn->SetState(TransactionState::SHRINKING);
        }
      }

      InsertOrDeleteRowLockSet(txn, lock_request, false);
      return true;
    }
  }

  lock_request_queue->latch_.unlock();
  txn->SetState(TransactionState::ABORTED);
  throw bustub::TransactionAbortException(txn->GetTransactionId(), AbortReason::ATTEMPTED_UNLOCK_BUT_NO_LOCK_HELD);
}

void LockManager::AddEdge(txn_id_t t1, txn_id_t t2) {}

void LockManager::RemoveEdge(txn_id_t t1, txn_id_t t2) {}

auto LockManager::HasCycle(txn_id_t *txn_id) -> bool { return false; }

auto LockManager::GetEdgeList() -> std::vector<std::pair<txn_id_t, txn_id_t>> {
  std::vector<std::pair<txn_id_t, txn_id_t>> edges(0);
  return edges;
}

void LockManager::RunCycleDetection() {
  while (enable_cycle_detection_) {
    std::this_thread::sleep_for(cycle_detection_interval);
    {  // TODO(students): detect deadlock
    }
  }
}

}  // namespace bustub
