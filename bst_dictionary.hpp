#ifndef BST_DICTIONARY_HPP
#define BST_DICTIONARY_HPP

#include "abstract_dictionary.hpp"

template <typename KeyType, typename ValueType>
class BSTDictionary : public AbstractDictionary<KeyType, ValueType> {
public:
  // Constructor
  BSTDictionary() = default;

  // Copy Constructor
  BSTDictionary(const BSTDictionary<KeyType, ValueType> &rhs);

  // Assignment Operator
  BSTDictionary<KeyType, ValueType> &
  operator=(BSTDictionary<KeyType, ValueType> rhs);

  // Destructor
  ~BSTDictionary();

  // return true if dict is empty, else false
  bool isEmpty() const;

  // return number of key-value pairs in the dict
  std::size_t size() const;

  // add an item to the dict
  // throws std::logic_error on duplicate key
  void add(const KeyType &key, const ValueType &value);

  // remove key-value from the dict
  // throws std::logic_error if dict is empty
  void remove(const KeyType &key);

  // remove all key-values from the dict
  void clear();

  // get a copy of value associated with key
  // throws std::logic_error if entry does not exist
  ValueType get(const KeyType &key) const;

  // return true if dict contains key
  bool contains(const KeyType &key) const;

  // return height of the tree
  std::size_t height() const;

private:
  // the internal node type
  template <typename K, typename I> struct Node {
    I data;
    K key;
    Node<K, I> *left = nullptr;
    Node<K, I> *right = nullptr;
  };

  // helper function to determine (recursively) the height of the tree
  // rooted at curr
  std::size_t get_height(Node<KeyType, ValueType> *curr) const;

  // the root of the tree
  Node<KeyType, ValueType> *root = nullptr;

  // number of key-value pairs
  std::size_t m_size = 0;

  // helper struct for recursion simulation
  template <typename K, typename I> struct stackvar {
    Node<K, I> *rhs = nullptr;
    Node<K, I> **lhs = nullptr;
  };

  // helper function to find the inorder successor of a node
  // and its parent
  void inorder(Node<KeyType, ValueType> *curr, Node<KeyType, ValueType> *&in,
               Node<KeyType, ValueType> *&parent);

  // helper function to find a node and its parent
  // curr == nullptr if not in the tree
  // parent == nullptr if not in tree or is the root
  void search(KeyType key, Node<KeyType, ValueType> *&curr,
              Node<KeyType, ValueType> *&parent) const;
};

#include "bst_dictionary.tpp"

#endif
