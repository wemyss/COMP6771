#ifndef BTREE_H
#define BTREE_H

#include <cstddef>
#include <iostream>
#include <iterator>
#include <memory>
#include <vector>
#include <utility>
#include <queue>

#include <cassert>

#include "btree_iterator.h"

const size_t DEFAULT_MAX_NODE_ELEMS = 40;

template <typename T> class btree;
template <typename T> std::ostream& operator<<(std::ostream& os, const btree<T>& tree);

template <typename T>
class btree {
public:
    friend class btree_iterator<T>;
    friend class const_btree_iterator<T>;
    typedef btree_iterator<T>                       iterator;
    typedef const_btree_iterator<T>                 const_iterator;
    typedef std::reverse_iterator<iterator>         reverse_iterator;
    typedef std::reverse_iterator<const_iterator>   const_reverse_iterator;

    btree() = default;
    btree(size_t t) : maxNodeElems{t} {};

    btree(const btree<T>& other);
    btree(btree<T>&& other) noexcept = default;
    ~btree() = default;

    btree<T>& operator=(const btree<T>& other);
    btree<T>& operator=(btree<T>&& other) noexcept = default;

    friend std::ostream& operator<< <T>(std::ostream&, const btree<T>&);

    iterator end() const;
    iterator begin() const;
    reverse_iterator rbegin() const;
    reverse_iterator rend() const;
    const_iterator cbegin() const;
    const_iterator cend() const;
    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;


    iterator find(const T& elem);
    const_iterator find(const T& elem) const;

    std::pair<iterator, bool> insert(const T& elem);

    void printRoot() const {
        std::cout << "maxNodeElems: " << maxNodeElems << "\n";
        if (root != nullptr) {
            root->printNode();
        }
    }

private:
    iterator maxElement() const;
    void clear() noexcept;
    void swap(btree<T>& other) noexcept;
    iterator findElem(const T& elem) const;

    struct Node {
        Node();
        Node(unsigned int posP, Node* p, const size_t m);
        Node(unsigned int posP, Node* p, const T& val, const size_t m);
        ~Node() = default;

        void printNode(int level = 0) const;

        void clearChildren();

        void createLeftChildAt(unsigned int i);
        void createRightChild();

        Node* getLeftChildAt(unsigned int i) const;
        Node* getRightChild() const;
        Node* getLeftChild() const;

        bool hasChildAt(unsigned int i) const;
        bool hasParent() const;
        bool hasRightChild() const;
        bool containsElement(const T& v) const;

        // Put X in front of the element at index i. If full, do nothing
        void emplaceElementBefore(unsigned int index, const T& elem);
        bool isFull() const;
        bool isEmpty() const;


        unsigned int posInParent {0U};
        Node* parent {nullptr};
        std::vector<T> elems {};
        std::vector<std::unique_ptr<Node>> leftChildren {};
        std::unique_ptr<Node> rightChild {nullptr};
        size_t maxNodeElems {DEFAULT_MAX_NODE_ELEMS};
    }; // NODE

    size_t maxNodeElems {DEFAULT_MAX_NODE_ELEMS};   // shared ptr so updates are reflected globally, maybe
    std::unique_ptr<Node> root {nullptr};
};

#include "btree.tem"
#endif
