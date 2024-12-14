#ifndef SORT_HPP
#define SORT_HPP

#include "../Container/Vector.hpp"
#include <concepts>

template <typename T>
concept Sortable = requires(const T& a, const T& b) {
  {a < b} -> std::same_as<bool>;
  {a > b} -> std::same_as<bool>;
};

class Sort{
private:

public:
    template <Sortable T> static void bubbleSort(Vector<T>& v, bool ascending = true){ // ascending in default
      for(size_t i = 0; i < v.size(); ++i){
        for(size_t j = 0; j < v.size() - i - 1; ++j){
          if( (v[j] > v[j+1] && ascending )
          || (v[j] < v[j+1] && !ascending) ){
              std::swap(v[j], v[j+1]);
          }
        }
      }
    }

    template <Sortable T> static void selectionSort(Vector<T>& v, bool ascending = true){
      for(size_t i = 0; i < v.size(); ++i){
        int minIndex = i;
        for(size_t j = i + 1; j < v.size(); ++j){
          if( (v[j] < v[minIndex] && ascending )
              || (v[j] > v[minIndex] && !ascending) ){
            minIndex = j;
              }
        }
        if(minIndex != i){
          std::swap(v[i], v[minIndex]);
        }
      }
    }



};

#endif