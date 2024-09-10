//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// nested_index_join_executor.cpp
//
// Identification: src/execution/nested_index_join_executor.cpp
//
// Copyright (c) 2015-19, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "execution/executors/nested_index_join_executor.h"

namespace bustub {

NestIndexJoinExecutor::NestIndexJoinExecutor(ExecutorContext *exec_ctx, const NestedIndexJoinPlanNode *plan,
                                             std::unique_ptr<AbstractExecutor> &&child_executor)
    : AbstractExecutor(exec_ctx), plan_(plan), left_executor_(std::move(child_executor)) {
  if (!(plan->GetJoinType() == JoinType::LEFT || plan->GetJoinType() == JoinType::INNER)) {
    // Note for 2022 Fall: You ONLY need to implement left join and inner join.
    throw bustub::NotImplementedException(fmt::format("join type {} not supported", plan->GetJoinType()));
  }
}

void NestIndexJoinExecutor::Init() {
  left_executor_->Init();

  Schema left_schema = left_executor_->GetOutputSchema();

  IndexInfo *right_index_info = exec_ctx_->GetCatalog()->GetIndex(plan_->GetIndexOid());
  Index *right_index = right_index_info->index_.get();

  TableInfo *right_table_info = exec_ctx_->GetCatalog()->GetTable(plan_->GetInnerTableOid());
  Schema right_schema = right_table_info->schema_;
  TableHeap *right_table = right_table_info->table_.get();

  Tuple left_tuple;
  RID left_rid;
  while (left_executor_->Next(&left_tuple, &left_rid)) {
    bool need_left_join = true;

    Value left_key_value = plan_->KeyPredicate()->Evaluate(&left_tuple, left_schema);
    Tuple left_key_tuple = Tuple(std::vector<Value>{left_key_value}, &right_index_info->key_schema_);
    std::vector<RID> result_rids;
    right_index->ScanKey(left_key_tuple, &result_rids, nullptr);

    for (auto &right_rid : result_rids) {
      need_left_join = false;

      Tuple right_tuple;
      right_table->GetTuple(right_rid, &right_tuple, exec_ctx_->GetTransaction());
      std::vector<Value> values;
      for (size_t i = 0; i < left_schema.GetColumnCount(); i++) {
        values.emplace_back(left_tuple.GetValue(&left_schema, i));
      }
      for (size_t i = 0; i < right_schema.GetColumnCount(); i++) {
        values.emplace_back(right_tuple.GetValue(&right_schema, i));
      }
      results_.emplace(values, &plan_->OutputSchema());
    }

    if (need_left_join && plan_->join_type_ == JoinType::LEFT) {
      std::vector<Value> values;
      for (size_t i = 0; i < left_schema.GetColumnCount(); i++) {
        values.emplace_back(left_tuple.GetValue(&left_schema, i));
      }
      for (size_t i = 0; i < right_schema.GetColumnCount(); i++) {
        values.emplace_back(ValueFactory::GetNullValueByType(right_schema.GetColumn(i).GetType()));
      }
      results_.emplace(values, &plan_->OutputSchema());
    }
  }
}

auto NestIndexJoinExecutor::Next(Tuple *tuple, RID *rid) -> bool {
  if (results_.empty()) {
    return false;
  }
  *tuple = results_.front();
  results_.pop();
  *rid = tuple->GetRid();
  return true;
}

}  // namespace bustub
