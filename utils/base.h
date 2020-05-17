//
// Created by maiji on 05/17/2020.
//

#ifndef INTEL_SIMD_BASE_H
#define INTEL_SIMD_BASE_H

#include <functional>

#define DISALLOW_COPY_AND_ASSIGN(ClassName) \
  private: \
  ClassName(const ClassName&) = delete; \
  void operator=(const ClassName&) = delete

#define DEFER_CONCAT_IMPL(x,y) x##y
#define DEFER_CONCAT(x,y) DEFER_CONCAT_IMPL(x,y)

class DeferredAction {
  DISALLOW_COPY_AND_ASSIGN(DeferredAction);
  public:
    explicit DeferredAction(std::function<void(void)> f):f_(std::move(f)){}
    ~DeferredAction() { f_(); }
  private:
    std::function<void(void)> f_;
};

#define DEFER(action) \
  DeferredAction DEFER_CONCAT(__deferred__, __LINE__) \
  ([&]() -> void action)

#endif // INTEL_SIMD_BASE_H
