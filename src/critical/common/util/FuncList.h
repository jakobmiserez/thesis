#ifndef _CRITICAL_FUNCLIST_H
#define _CRITICAL_FUNCLIST_H

#include <optional>
#include <vector>
#include <set>
#include <algorithm>
#include <functional>

namespace critical {

template <class T>
class FuncList {
  private:
    std::vector<T> list;

  public:
    FuncList(std::vector<T>& list): list(list) {};
    virtual ~FuncList() {};

  public:
    FuncList<T>& filter(std::function<bool(T&)> filter) {
      std::vector<T> newList;
      std::copy_if(list.begin(), list.end(), std::back_inserter(newList), filter);
      this->list = newList;
      return *this;
    };

    FuncList<T>& filterOut(std::set<T> blackList) {
      auto lambda = [blackList](T& t) { return blackList.find(t) != blackList.end(); };
      return filter(lambda);
    };

    template <class M>
    FuncList<M> filterMap(std::function<bool(T&)> filter, std::function<M(T&)> map) {
      std::vector<M> newList;
      for (int i = 0; i < list.size(); i++) {
        T& elem = list[i];
        if (filter(elem)) {
          newList.push_back(map(elem));
        }
      }
      return FuncList<M>(newList);
    }

    template <class M>
    FuncList<M> mapFilter(std::function<M(T&)> map, std::function<bool(T&)> filter) {
      std::vector<M> newList;
      for (int i = 0; i < list.size(); i++) {
        T& elem = list[i];
        M elem2 = map(elem);
        if (filter(elem2)) {
          newList.push_back(elem2);
        }
      }
      return FuncList<M>(newList);
    }

    template <class M1, class M2>
    FuncList<M2> mapFilterMap(
      std::function<M1(T&)> map1, 
      std::function<bool(M1&)> filter,
      std::function<M2(M1&)> map2
    ) {
      std::vector<M2> newList;
      for (int i = 0; i < list.size(); i++) {
        T& elem = list[i];
        M1 elem1 = map1(elem);
        if (filter(elem1)) {
          newList.push_back(map2(elem1));
        }
      }
      return FuncList<M2>(newList);
    }

    template <class M1, class M2>
    FuncList<std::pair<T, M2>> mapFilterMapKeep(
      std::function<M1(T&)> map1, 
      std::function<bool(M1&)> filter,
      std::function<M2(M1&)> map2
    ) {
      std::vector<M2> newList;
      for (int i = 0; i < list.size(); i++) {
        T& elem = list[i];
        M1 elem1 = map1(elem);
        if (filter(elem1)) {
          newList.push_back(std::make_pair(elem, map2(elem1)));
        }
      }
      return FuncList<std::pair<T, M2>>(newList);
    }

    template <class M>
    FuncList<M> map(std::function<M(T&)> map) {
      std::vector<M> newList;
      newList.reserve(list.size());
      std::transform(list.begin(), list.end(), std::back_inserter(newList), map);

      return FuncList<M>(newList);
    };

    template <class M>
    FuncList<std::pair<T, M>> mapKeep(std::function<M(T&)> map) {
      std::vector<std::pair<T, M>> newList;
      newList.reserve(list.size());
      std::transform(list.begin(), list.end(), std::back_inserter(newList), [map](T& t) {
        return std::make_pair(t, map(t));
      });

      return FuncList<std::pair<T, M>>(newList);
    }

    template <class M>
    std::optional<std::pair<T, M>> findMax(std::function<M(T&)> value) {
      if (list.size() == 0) {
        return {};
      }

      T t = list[0];
      M m = value(t);
      for (int i = 1; i < list.size(); i++) {
        T t2 = list[i];
        M m2 = value(t2);
        if (m2 > m) {
          t = t2;
          m = m2;
        }
      }
      return std::make_pair(t, m);
    };

    template <class M>
    std::optional<std::pair<T, M>> findMin(std::function<M(T&)> value) {
      if (list.size() == 0) {
        return {};
      }

      T t = list[0];
      M m = value(t);
      for (int i = 1; i < list.size(); i++) {
        T t2 = list[i];
        M m2 = value(t2);
        if (m2 < m) {
          t = t2;
          m = m2;
        }
      }
      return std::make_pair(t, m);
    };

    template <class M>
    std::optional<T> findArgMin(std::function<M(T&)> value) {
      if (list.size() == 0) {
        return {};
      }

      T t = list[0];
      M m = value(t);
      for (int i = 1; i < list.size(); i++) {
        T t2 = list[i];
        M m2 = value(t2);
        if (m2 < m) {
          t = t2;
          m = m2;
        }
      }
      return t;
    };

    FuncList<T> forEach(std::function<void(T&)> func) {
      for (T& elem: list) {
        func(elem);
      }
      return *this;
    }

    std::vector<T> collect() {
      return list;
    }

    std::size_t size() {
      return list.size();
    }

    FuncList<T>& sort(std::function<bool(const T&, const T&)> cmp) {
      std::sort(list.begin(), list.end(), cmp);
      return *this;
    }

    FuncList<T>& head(int n) {
      if (n < list.size())
        list.resize(n);
      return *this;
    }

    std::optional<T> first() {
      if (list.empty()) {
        return {};
      }
      return list[0];
    }

  public:
    static FuncList<T> from(std::vector<T> list) {
      return FuncList<T>(list);
    };
    //static FuncList<T> from(std::vector<T> list) {
      //return FuncList<T>(list);
    //};
};

}


#endif 