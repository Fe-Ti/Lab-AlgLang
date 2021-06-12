// Copyright 2021 Fe-Ti <btm.007@mail.ru>

#ifndef RAOI
#define RAOI

#include <iterator>

template<typename T>
class RAO_iterator // bamboo pipestem iterator
{
    T* _pos;

  public:
    //    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;                   // Value type
    using difference_type = std::ptrdiff_t; // Diff. type
    using pointer = T*;                     // Pointer type
    using reference = T&;                   // Reference type

    RAO_iterator(T* pos)
      : _pos(pos)
    {
    }

    bool operator==(const RAO_iterator<T>& other) const
    {
        return _pos == other._pos;
    }
    bool operator!=(const RAO_iterator<T>& other) const
    {
        return _pos != other._pos;
    }
    pointer operator->() const { return _pos; }
    reference operator*() const { return *_pos; }
    RAO_iterator<T>& operator++()
    {
        ++_pos;
        return *this;
    }
    RAO_iterator<T> operator++(int)
    {
        RAO_iterator<T> temp = *this;
        ++_pos;
        return temp;
    }

    RAO_iterator<T>& operator--()
    {
        --_pos;
        return *this;
    }
    RAO_iterator<T> operator--(int)
    {
        RAO_iterator<T> temp = *this;
        --_pos;
        return temp;
    }
    reference operator[](size_t index) const { return _pos[index]; }
    RAO_iterator<T> operator+(difference_type const& diff) const
    {
        return RAO_iterator<T>(_pos + diff);
    }

    friend inline RAO_iterator<T> operator+(difference_type const& diff,
                                            const RAO_iterator<T>& iter);

    RAO_iterator<T> operator-(difference_type const& diff) const
    {
        return RAO_iterator<T>(_pos - diff);
    }
    difference_type operator-(const RAO_iterator<T>& other) const
    {
        return std::distance(other._pos, _pos);
    }
    RAO_iterator<T>& operator+=(difference_type const& diff)
    {
        _pos += diff;
        return *this;
    }
    RAO_iterator<T>& operator-=(difference_type const& diff)
    {
        _pos -= diff;
        return *this;
    }
    bool operator>(const RAO_iterator<T>& other) const
    {
        return _pos > other._pos;
    }
    bool operator<(const RAO_iterator<T>& other) const
    {
        return _pos < other._pos;
    }
    bool operator>=(const RAO_iterator<T>& other) const
    {
        return _pos >= other._pos;
    }
    bool operator<=(const RAO_iterator<T>& other) const
    {
        return _pos <= other._pos;
    }
};

template<typename T>
RAO_iterator<T>
operator+(RAO_iterator::difference_type const& diff,
          const RAO_iterator<T>& iter)
{
    return RAO_iterator<T>(iter._pos + diff);
}

#endif