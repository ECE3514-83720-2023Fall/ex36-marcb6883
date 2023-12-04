#include "bst_dictionary.hpp"

#include <cassert>
#include <stack>
#include <stdexcept>

// return height from a node
template <typename KeyType, typename ValueType>
std::size_t BSTDictionary<KeyType, ValueType>::get_height(Node<KeyType, ValueType> *curr) const
{
	if(curr == nullptr) {
		return 0;
	} else {
		return std::max(get_height(curr->left),get_height(curr->right)) + 1;
	}
}

// return height of the BST
template <typename KeyType, typename ValueType>
std::size_t BSTDictionary<KeyType, ValueType>::height() const
{
	return get_height(root);
}

template <typename KeyType, typename ValueType>
BSTDictionary<KeyType, ValueType>::BSTDictionary(
                                                 const BSTDictionary<KeyType, ValueType> &rhs) {
    
    Node<KeyType, ValueType> **lhs = &root;
    
    std::stack<stackvar<KeyType, ValueType>> s;
    
    stackvar<KeyType, ValueType> rootvar;
    rootvar.rhs = rhs.root;
    rootvar.lhs = lhs;
    s.push(rootvar);
    
    while (!s.empty()) {
        stackvar<KeyType, ValueType> currentvar = s.top();
        s.pop();
        
        Node<KeyType, ValueType> *curr_rhs = currentvar.rhs;
        Node<KeyType, ValueType> **curr_lhs = currentvar.lhs;
        
        if (curr_rhs == nullptr)
            continue;
        
        // allocate new node and copy contents
        Node<KeyType, ValueType> *temp = new Node<KeyType, ValueType>;
        temp->key = curr_rhs->key;
        temp->data = curr_rhs->data;
        *curr_lhs = temp;
        
        m_size += 1;
        
        // push left subtree
        currentvar.rhs = curr_rhs->left;
        currentvar.lhs = &((*curr_lhs)->left);
        s.push(currentvar);
        
        // push right subtree
        currentvar.rhs = curr_rhs->right;
        currentvar.lhs = &((*curr_lhs)->right);
        s.push(currentvar);
    }
}

template <typename KeyType, typename ValueType>
BSTDictionary<KeyType, ValueType> &BSTDictionary<KeyType, ValueType>::operator=(
                                                                                BSTDictionary<KeyType, ValueType> rhs) {
    
    std::swap(root, rhs.root);
    std::swap(m_size, rhs.m_size);
    
    return *this;
}

template <typename KeyType, typename ValueType>
BSTDictionary<KeyType, ValueType>::~BSTDictionary() {
    clear();
}

template <typename KeyType, typename ValueType>
void BSTDictionary<KeyType, ValueType>::clear()
{
    std::stack<Node<KeyType, ValueType> *> s;
    s.push(root);
    
    // TODO -- implement clear
 
}

template <typename KeyType, typename ValueType>
std::size_t BSTDictionary<KeyType, ValueType>::size() const {
    return m_size;
}

template <typename KeyType, typename ValueType>
bool BSTDictionary<KeyType, ValueType>::contains(const KeyType &key) const {
    Node<KeyType, ValueType> *curr;
    Node<KeyType, ValueType> *curr_parent;
    search(key, curr, curr_parent);
    
    return (curr != nullptr) && (curr->key == key);
}

template <typename KeyType, typename ValueType>
void BSTDictionary<KeyType, ValueType>::add(const KeyType &key,
                                            const ValueType &item)
{
    Node<KeyType, ValueType> *curr;
    Node<KeyType, ValueType> *curr_parent;
    if (!isEmpty()) {
        search(key, curr, curr_parent);
        if (curr->key == key)
            throw std::logic_error("Duplicate key in add");
    }
    
    // TODO -- implement add
 
}

template <typename KeyType, typename ValueType>
bool BSTDictionary<KeyType, ValueType>::isEmpty() const {
    return (root == nullptr);
}

template <typename KeyType, typename ValueType>
ValueType BSTDictionary<KeyType, ValueType>::get(const KeyType &key) const {
    Node<KeyType, ValueType> *curr;
    Node<KeyType, ValueType> *curr_parent;
    search(key, curr, curr_parent);
    
    if ((curr == nullptr) || curr->key != key) {
        throw std::logic_error("Nonexistant key in get");
    }
    
    return curr->data;
}

template <typename KeyType, typename ValueType>
void BSTDictionary<KeyType, ValueType>::remove(const KeyType &key) {
    if (isEmpty()) {
        throw std::logic_error("Empty dictionary in remove");
    }
    
    Node<KeyType, ValueType> *curr;
    Node<KeyType, ValueType> *curr_parent;
    search(key, curr, curr_parent);
    
    if (curr->key != key) {
        throw std::logic_error("Nonexistant key in remove");
    }
    
    // if at leaf
    if ((curr->left == nullptr) && (curr->right == nullptr)) {
        if (curr_parent == nullptr) {
            root = nullptr;
        } else {
            if (curr == curr_parent->left)
                curr_parent->left = nullptr;
            if (curr == curr_parent->right)
                curr_parent->right = nullptr;
        }
        delete curr;
    } else if ((curr->left == nullptr) && (curr->right != nullptr)) // right child
    {
        if (curr_parent == nullptr) {
            root = curr->right;
        } else {
            if (curr == curr_parent->left)
                curr_parent->left = curr->right;
            if (curr == curr_parent->right)
                curr_parent->right = curr->right;
        }
        delete curr;
    } else if ((curr->left != nullptr) && (curr->right == nullptr)) // left child
    {
        if (curr_parent == nullptr) {
            root = curr->left;
        } else {
            if (curr == curr_parent->left)
                curr_parent->left = curr->left;
            if (curr == curr_parent->right)
                curr_parent->right = curr->left;
        }
        delete curr;
    } else // two children
    {
        // find the inorder successor
        Node<KeyType, ValueType> *succ;
        Node<KeyType, ValueType> *succ_parent;
        inorder(curr, succ, succ_parent);
        curr->key = succ->key; // copy contents of succ to curr
        curr->data = succ->data;
        
        // remove successor, two cases
        // successor is a left child
        if (succ_parent->left == succ) {
            succ_parent->left = succ->right;
            delete succ;
        }
        // or successor is a right child
        else if (succ_parent->right == succ) {
            succ_parent->right = succ->right;
            delete succ;
        }
        // logically impossible
        else {
            assert(false);
        }
    }
    
    m_size -= 1;
}

template <typename KeyType, typename ValueType>
void BSTDictionary<KeyType, ValueType>::inorder(
        Node<KeyType, ValueType> *curr, Node<KeyType, ValueType> *&in,
        Node<KeyType, ValueType> *&parent)
{
    
    parent = curr;
    in = curr->right; // move right once
    
    // TODO -- implement inorder
    
}

template <typename KeyType, typename ValueType>
void BSTDictionary<KeyType, ValueType>::search(
    KeyType key, Node<KeyType, ValueType> *&curr,
    Node<KeyType, ValueType> *&parent) const
{
    curr = root;
    parent = nullptr;
    
    if (isEmpty())
        return;
    
    // TODO -- implement search
    // want to do a search of the tree
    // return the node that has the key and a pointer to its parent
    // else where the node would go in the BST
    
}
