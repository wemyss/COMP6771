#ifndef BTREE_ITERATOR_H
#define BTREE_ITERATOR_H

#include <iterator>
#include <memory>

template <typename T> class btree;
template <typename T> class const_btree_iterator;

template <typename T> class btree_iterator {
public:
    typedef std::ptrdiff_t              difference_type;
    typedef std::forward_iterator_tag   iterator_category;
    typedef T                           value_type;
    typedef T*                          pointer;
    typedef T&                          reference;

    typedef typename btree<T>::Node Node;
    typedef const_btree_iterator<T> const_btree_iter;

    btree_iterator() = default;
    btree_iterator(Node* n, unsigned int p = 0U, bool isValid = true);
    btree_iterator(const btree_iterator& b) = default;
    btree_iterator(btree_iterator&& b) noexcept = default;

    reference operator*() const;
    pointer operator->() const;

    btree_iterator& operator++();
    btree_iterator operator++(int);
    btree_iterator& operator--();
    btree_iterator operator--(int);

    // SELF
    bool operator==(const btree_iterator& other) const;
    bool operator!=(const btree_iterator& other) const;

    bool operator==(const const_btree_iter& other) const {
        return other == *this;
    }
    bool operator!=(const const_btree_iter& other) const {
        return other != *this;
    }


private:
    Node* currPtr {nullptr};
    unsigned int pos {0U};
    bool isValid {false};
};

template <typename T> class const_btree_iterator {
public:
    typedef std::ptrdiff_t              difference_type;
    typedef std::forward_iterator_tag   iterator_category;
    typedef T                           value_type;
    typedef T*                          pointer;
    typedef T&                          reference;

    typedef typename btree<T>::Node Node;
    typedef btree_iterator<T> btree_iter;

    const_btree_iterator() = default;
    const_btree_iterator(Node* n, unsigned int p) : btree_it{n, p} {}

    const_btree_iterator(const btree_iter& b) : btree_it{b} {}
    const_btree_iterator(const const_btree_iterator& b) = default;
    const_btree_iterator(const_btree_iterator&& b) noexcept = default;

    reference operator*() const {
        return *btree_it;
    }
    pointer operator->() const {
        return &(operator*());
    }
    const_btree_iterator& operator++() {
        ++btree_it;
        return *this;
    }
    const_btree_iterator& operator--() {
        --btree_it;
        return *this;
    }

    bool operator==(const const_btree_iterator& other) const {
        return btree_it == other.btree_it;
    }
    bool operator!=(const const_btree_iterator& other) const {
        return !operator==(other);
    }
    bool operator==(const btree_iter& other) const {
        return btree_it == other;
    }
    bool operator!=(const btree_iter& other) const {
        return btree_it != other;
    }

private:
    btree_iter btree_it {};
};

#include "btree_iterator.tem"
#endif
