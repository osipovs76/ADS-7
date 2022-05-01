// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <string>


template<typename T>
class TPQueue {
 private:
  struct ITEM {
    T value;
    ITEM* next, * prev;
  };
  ITEM* head, * tail;
  TPQueue::ITEM* create(const T& value, ITEM*prev) {
    ITEM* item = new ITEM;
    item->value = value;
    item->next = nullptr;
    item->prev = prev;
    return item;
  }

 public:
  TPQueue() :head(nullptr), tail(nullptr) {}
  ~TPQueue() {
    while (head)
      pop();
  }
  void push(const T& value) {
    if (tail && head) {
      ITEM* current = tail;
      while (current && value.prior > (current->value).prior) {
        current = current->prev;
      }
      if (current) {
        ITEM* temp = current->next;
        current->next = create(value, current);
        current = current->next;
        current->next = temp;
        if (temp)
          temp->prev = current;
        else
          tail = current;
      } else {
        current = create(value, nullptr);
        current->next = head;
        head->prev = current;
        head = current;
      }
    } else {
      head = create(value, nullptr);
      tail = head;
    }
  }
  T pop() {
    if (!head || !tail)
      throw std::string("empty");
    ITEM* temp = head->next;
    if (temp)
      temp->prev = nullptr;
    T value = head->value;
    delete head;
    head = temp;
    if (!head)
      tail = nullptr;
    return value;
  }
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
