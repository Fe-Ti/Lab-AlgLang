// Copyright 2021 Fe-Ti <btm.007@mail.ru>

#ifndef RAOI
#define RAOI

template<typename T>
class RAO_iterator // bamboo pipestem iterator
{
    T* _pos;

  public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;                   // Value type
    using difference_type = std::ptrdiff_t; // Diff. type
    using pointer = T*;                     // Pointer type
    using reference = T&;                   // Reference type

    RAO_iterator(T* pos)
      : _pos(pos)
    {
    }

    bool operator==(RAO_iterator const& other) const
    {
        return _pos == other._pos;
    }
    bool operator!=(RAO_iterator const& other) const
    {
        return _pos != other._pos;
    }
    pointer operator->() const
    {
        return _pos;
    }
    reference operator*() const
    {
        return *_pos;
    }
    RAO_iterator& operator++()
    {
        ++_pos;
        return *this;
    }
    RAO_iterator operator++(int)
    {
        RAO_iterator temp = *this;
        ++_pos;
        return temp;
    }

    RAO_iterator& operator--()
    {
        --_pos;
        return *this;
    }
    RAO_iterator operator--(int)
    {
        RAO_iterator temp = *this;
        --_pos;
        return temp;
    }
    reference operator[](size_t index) const
    {
        return _pos[index];
    }
    RAO_iterator operator+(difference_type const& diff) const
    {
        return RAO_iterator(_pos + diff);
    }

    friend inline RAO_iterator operator+(difference_type const& diff,
                                         RAO_iterator const& iter);

    RAO_iterator operator-(difference_type const& diff) const
    {
        return RAO_iterator(_pos - diff);
    }
    difference_type operator-(RAO_iterator const& other) const
    {
        return std::distance(other._pos, _pos);
    }
    RAO_iterator& operator+=()
    {
        _pos += diff;
        return *this;
    }
    RAO_iterator& operator-=()
    {
        _pos -= diff;
        return *this;
    }
    bool operator>(RAO_iterator const& other) const
    {
        return _pos > other._pos;
    }
    bool operator<(RAO_iterator const& other) const
    {
        return _pos < other._pos;
    }
    bool operator>=(RAO_iterator const& other) const
    {
        return _pos >= other._pos;
    }
    bool operator<=(RAO_iterator const& other) const
    {
        return _pos <= other._pos;
    }
};

RAO_iterator
operator+(RAO_iterator::difference_type const& diff, RAO_iterator const& iter)
{
    return RAO_iterator(iter._pos + diff);
}

#endif