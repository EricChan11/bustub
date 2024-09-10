#include "execution/executors/topn_executor.h"

namespace bustub {

TopNExecutor::TopNExecutor(ExecutorContext *exec_ctx, const TopNPlanNode *plan,
                           std::unique_ptr<AbstractExecutor> &&child_executor)
    : AbstractExecutor(exec_ctx), plan_(plan), child_(std::move(child_executor)) {}

void TopNExecutor::Init() {
  child_->Init();
  n_ = plan_->GetN();
  Tuple child_tuple{};
  RID child_rid;
  using Comparator = std::function<bool(const Tuple &, const Tuple &)>;

  Comparator comparator = [order_bys = plan_->GetOrderBy(), schema = child_->GetOutputSchema()](const Tuple &tuple_a,
                                                                                                const Tuple &tuple_b) {
    for (const auto &order_key : order_bys) {
      auto val_a = order_key.second->Evaluate(&tuple_a, schema);
      auto val_b = order_key.second->Evaluate(&tuple_b, schema);

      switch (order_key.first) {
        case OrderByType::INVALID:
        case OrderByType::DEFAULT:
        case OrderByType::ASC:
          if (val_a.CompareLessThan(val_b) == CmpBool::CmpTrue) {
            return true;
          } else if (val_a.CompareGreaterThan(val_b) == CmpBool::CmpTrue) {
            return false;
          }
          break;

        case OrderByType::DESC:
          if (val_a.CompareGreaterThan(val_b) == CmpBool::CmpTrue) {
            return true;
          } else if (val_a.CompareLessThan(val_b) == CmpBool::CmpTrue) {
            return false;
          }
          break;

        default:
          break;
      }
    }
    return false;
  };

  std::priority_queue<Tuple, std::vector<Tuple>, Comparator> pq(comparator);

  while (child_->Next(&child_tuple, &child_rid)) {
    if (pq.size() < n_) {
      pq.push(child_tuple);
    } else if (comparator(child_tuple, pq.top())) {
      pq.pop();
      pq.push(child_tuple);
    }
  }

  child_tuples_.reserve(pq.size());
  while (!pq.empty()) {
    child_tuples_.push_back(pq.top());
    pq.pop();
  }

  std::reverse(child_tuples_.begin(), child_tuples_.end());

  child_iter_ = child_tuples_.begin();
}
auto TopNExecutor::Next(Tuple *tuple, RID *rid) -> bool {
  if (n_ <= 0 || child_iter_ == child_tuples_.end()) {
    return false;
  }

  *tuple = *child_iter_;
  *rid = tuple->GetRid();
  ++child_iter_;
  n_--;

  return true;
}

}  // namespace bustub
