#ifndef __CRITICAL_OBSERVABLE_H
#define __CRITICAL_OBSERVABLE_H

#include <set>
#include <functional>

namespace critical {

enum ObservingPriority {
  HIGHEST = 0,
  HIGH = 1,
  LOW = 2,
  LOWEST = 3,
};

template <class T> 
class Observable {
  protected:
    std::map<ObservingPriority, std::set<T*>> listeners;

  public:
    void addListener(T* listener, ObservingPriority priority = ObservingPriority::LOWEST) {
      listeners[priority].insert(listener);
    };

    void removeListener(T* listener) {
      for (auto& [_, set]: listeners) {
        auto it = set.find(listener);
        if (it != set.end()) {
          set.erase(it);
        }
      }
    };

    void notifyListeners(std::function<void(T* listener)> notify) {
      for (const auto [p, set]: listeners) {
        for (T* l: set) {
          notify(l);
        }
      }
    };

};

}

#endif