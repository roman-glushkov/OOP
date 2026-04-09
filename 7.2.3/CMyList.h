#pragma once

#include <cstddef>
#include <iterator>
#include <stdexcept>
#include <algorithm>

template <typename T>
class CMyList
{
private:
    struct Node
    {
        T data;
        Node* prev;
        Node* next;
        
        Node(const T& value);
    };

public:
    class iterator
    {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        iterator(Node* node = nullptr);

        reference operator*() const;
        pointer operator->() const;

        iterator& operator++();
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);

        bool operator==(const iterator& other) const;
        bool operator!=(const iterator& other) const;

    private:
        Node* m_node;
        friend class CMyList;
    };

    using reverse_iterator = std::reverse_iterator<iterator>;
 
    CMyList();
    CMyList(const CMyList& other);
    CMyList(CMyList&& other) noexcept;
    ~CMyList();

    CMyList& operator=(const CMyList& other);
    CMyList& operator=(CMyList&& other) noexcept;

    void PushFront(const T& value);
    void PushBack(const T& value);
    void PopFront();
    void PopBack();

    iterator begin();
    iterator end();
    reverse_iterator rbegin();
    reverse_iterator rend();

    iterator insert(iterator pos, const T& value);
    iterator erase(iterator pos);

    size_t Size() const;
    bool Empty() const;
    void Clear();

private:
    Node* m_head;
    Node* m_tail;
    size_t m_size;

    void CopyFrom(const CMyList& other);
    void Free();
    void Swap(CMyList& other) noexcept;
};

// ========== Реализация Node ==========
template <typename T>
CMyList<T>::Node::Node(const T& value)
    : data(value)
    , prev(nullptr)
    , next(nullptr)
{
}

// ========== Реализация iterator ==========
template <typename T>
CMyList<T>::iterator::iterator(Node* node)
    : m_node(node)
{
}

template <typename T>
typename CMyList<T>::iterator::reference CMyList<T>::iterator::operator*() const
{
    if (!m_node)
        throw std::out_of_range("Iterator is out of range");
    return m_node->data;
}

template <typename T>
typename CMyList<T>::iterator::pointer CMyList<T>::iterator::operator->() const
{
    if (!m_node)
        throw std::out_of_range("Iterator is out of range");
    return &(m_node->data);
}

template <typename T>
typename CMyList<T>::iterator& CMyList<T>::iterator::operator++()
{
    if (!m_node)
        throw std::out_of_range("Cannot increment end iterator");
    m_node = m_node->next;
    return *this;
}

template <typename T>
typename CMyList<T>::iterator CMyList<T>::iterator::operator++(int)
{
    iterator tmp = *this;
    ++(*this);
    return tmp;
}

template <typename T>
typename CMyList<T>::iterator& CMyList<T>::iterator::operator--()
{
    if (!m_node)
        throw std::out_of_range("Cannot decrement end iterator");
    m_node = m_node->prev;
    return *this;
}

template <typename T>
typename CMyList<T>::iterator CMyList<T>::iterator::operator--(int)
{
    iterator tmp = *this;
    --(*this);
    return tmp;
}

template <typename T>
bool CMyList<T>::iterator::operator==(const iterator& other) const
{
    return m_node == other.m_node;
}

template <typename T>
bool CMyList<T>::iterator::operator!=(const iterator& other) const
{
    return !(*this == other);
}

// ========== Реализация CMyList ==========
template <typename T>
CMyList<T>::CMyList()
    : m_head(nullptr)
    , m_tail(nullptr)
    , m_size(0)
{
}

template <typename T>
CMyList<T>::CMyList(const CMyList& other)
    : m_head(nullptr)
    , m_tail(nullptr)
    , m_size(0)
{
    CopyFrom(other);
}

template <typename T>
CMyList<T>::CMyList(CMyList&& other) noexcept
    : m_head(other.m_head)
    , m_tail(other.m_tail)
    , m_size(other.m_size)
{
    other.m_head = nullptr;
    other.m_tail = nullptr;
    other.m_size = 0;
}

template <typename T>
CMyList<T>::~CMyList()
{
    Free();
}

template <typename T>
CMyList<T>& CMyList<T>::operator=(const CMyList& other)
{
    if (this != &other)
    {
        CMyList tmp(other);
        Swap(tmp);
    }
    return *this;
}

template <typename T>
CMyList<T>& CMyList<T>::operator=(CMyList&& other) noexcept
{
    if (this != &other)
    {
        Free();
        m_head = other.m_head;
        m_tail = other.m_tail;
        m_size = other.m_size;
        
        other.m_head = nullptr;
        other.m_tail = nullptr;
        other.m_size = 0;
    }
    return *this;
}

template <typename T>
void CMyList<T>::Free()
{
    Node* current = m_head;
    while (current)
    {
        Node* toDelete = current;
        current = current->next;
        delete toDelete;
    }
}

template <typename T>
void CMyList<T>::CopyFrom(const CMyList& other)
{
    for (Node* current = other.m_head; current; current = current->next)
    {
        PushBack(current->data);
    }
}

template <typename T>
void CMyList<T>::Swap(CMyList& other) noexcept
{
    std::swap(m_head, other.m_head);
    std::swap(m_tail, other.m_tail);
    std::swap(m_size, other.m_size);
}

template <typename T>
void CMyList<T>::PushFront(const T& value)
{
    Node* newNode = new Node(value);
    
    if (Empty())
    {
        m_head = newNode;
        m_tail = newNode;
    }
    else
    {
        newNode->next = m_head;
        m_head->prev = newNode;
        m_head = newNode;
    }
    ++m_size;
}

template <typename T>
void CMyList<T>::PushBack(const T& value)
{
    Node* newNode = new Node(value);
    
    if (Empty())
    {
        m_head = newNode;
        m_tail = newNode;
    }
    else
    {
        newNode->prev = m_tail;
        m_tail->next = newNode;
        m_tail = newNode;
    }
    ++m_size;
}

template <typename T>
void CMyList<T>::PopFront()
{
    if (Empty())
        throw std::out_of_range("List is empty");
    
    Node* toDelete = m_head;
    m_head = m_head->next;
    
    if (m_head)
        m_head->prev = nullptr;
    else
        m_tail = nullptr;
    
    delete toDelete;
    --m_size;
}

template <typename T>
void CMyList<T>::PopBack()
{
    if (Empty())
        throw std::out_of_range("List is empty");
    
    Node* toDelete = m_tail;
    m_tail = m_tail->prev;
    
    if (m_tail)
        m_tail->next = nullptr;
    else
        m_head = nullptr;
    
    delete toDelete;
    --m_size;
}

template <typename T>
typename CMyList<T>::iterator CMyList<T>::begin()
{
    return iterator(m_head);
}

template <typename T>
typename CMyList<T>::iterator CMyList<T>::end()
{
    return iterator(nullptr);
}

template <typename T>
typename CMyList<T>::reverse_iterator CMyList<T>::rbegin()
{
    return reverse_iterator(end());
}

template <typename T>
typename CMyList<T>::reverse_iterator CMyList<T>::rend()
{
    return reverse_iterator(begin());
}

template <typename T>
typename CMyList<T>::iterator CMyList<T>::insert(iterator pos, const T& value)
{
    if (pos == begin())
    {
        PushFront(value);
        return begin();
    }
    
    if (pos == end())
    {
        PushBack(value);
        return iterator(m_tail);
    }
    
    Node* currentNode = pos.m_node;
    Node* newNode = new Node(value);
    
    newNode->prev = currentNode->prev;
    newNode->next = currentNode;
    currentNode->prev->next = newNode;
    currentNode->prev = newNode;
    
    ++m_size;
    
    return iterator(newNode);
}

template <typename T>
typename CMyList<T>::iterator CMyList<T>::erase(iterator pos)
{
    if (pos == end())
        throw std::out_of_range("Cannot erase end iterator");
    
    if (Empty())
        throw std::out_of_range("List is empty");
    
    Node* toDelete = pos.m_node;
    iterator nextPos(toDelete->next);
    
    if (toDelete == m_head)
    {
        PopFront();
        return nextPos;
    }
    
    if (toDelete == m_tail)
    {
        PopBack();
        return end();
    }
    
    toDelete->prev->next = toDelete->next;
    toDelete->next->prev = toDelete->prev;
    
    delete toDelete;
    --m_size;
    
    return nextPos;
}

template <typename T>
size_t CMyList<T>::Size() const
{
    return m_size;
}

template <typename T>
bool CMyList<T>::Empty() const
{
    return m_size == 0;
}

template <typename T>
void CMyList<T>::Clear()
{
    Free();
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}