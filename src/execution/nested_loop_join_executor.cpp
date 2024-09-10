//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// nested_loop_join_executor.cpp
//
// Identification: src/execution/nested_loop_join_executor.cpp
//
// Copyright (c) 2015-2021, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "execution/executors/nested_loop_join_executor.h"
#include "binder/table_ref/bound_join_ref.h"
#include "common/exception.h"

namespace bustub {

NestedLoopJoinExecutor::NestedLoopJoinExecutor(ExecutorContext *exec_ctx, const NestedLoopJoinPlanNode *plan,
                                               std::unique_ptr<AbstractExecutor> &&left_executor,
                                               std::unique_ptr<AbstractExecutor> &&right_executor)
    : AbstractExecutor(exec_ctx),
      plan_(plan),
      left_executor_(std::move(left_executor)),
      right_executor_(std::move(right_executor)) {
  if (!(plan->GetJoinType() == JoinType::LEFT || plan->GetJoinType() == JoinType::INNER)) {
    // Note for 2022 Fall: You ONLY need to implement left join and inner join.
    throw bustub::NotImplementedException(fmt::format("join type {} not supported", plan->GetJoinType()));
  }
}

void NestedLoopJoinExecutor::Init() {
  left_executor_->Init();
  right_executor_->Init();

  Tuple tuple;
  RID rid;
  std::vector<Tuple> left_tuples;
  std::vector<Tuple> right_tuples;
  while (left_executor_->Next(&tuple, &rid)) {
    left_tuples.emplace_back(tuple);
  }
  while (right_executor_->Next(&tuple, &rid)) {
    right_tuples.emplace_back(tuple);
  }

  Schema left_schema = left_executor_->GetOutputSchema();
  Schema right_schema = right_executor_->GetOutputSchema();
  for (auto &left_tuple : left_tuples) {
    bool need_left_join = true;

    for (auto &right_tuple : right_tuples) {
      Value join_result = plan_->predicate_->EvaluateJoin(&left_tuple, left_schema, &right_tuple, right_schema);
      if (!join_result.IsNull() && join_result.GetAs<bool>()) {
        need_left_join = false;

        std::vector<Value> values;
        for (size_t i = 0; i < left_schema.GetColumnCount(); i++) {
          values.emplace_back(left_tuple.GetValue(&left_schema, i));
        }
        for (size_t i = 0; i < right_schema.GetColumnCount(); i++) {
          values.emplace_back(right_tuple.GetValue(&right_schema, i));
        }
        results_.emplace(values, &plan_->OutputSchema());
      }
    }

    if (need_left_join && plan_->GetJoinType() == JoinType::LEFT) {
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

auto NestedLoopJoinExecutor::Next(Tuple *tuple, RID *rid) -> bool {
  if (results_.empty()) {
    return false;
  }
  *tuple = results_.front();
  results_.pop();
  *rid = tuple->GetRid();
  return true;
}

}  // namespace bustub
