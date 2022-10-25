#pragma once

#include <algorithm>
#include <cassert>
#include <initializer_list>
#include <iterator>
#include <iostream>
#include <utility>

#include "array_ptr.h"

class ReserveProxyObj {
public:
    ReserveProxyObj(size_t capacity_to_reserve)
        : capacity_to_reserve_(capacity_to_reserve)
    {
    }
    size_t Get()
    {
        return capacity_to_reserve_;
    }
private:
    size_t capacity_to_reserve_;
};

ReserveProxyObj Reserve(size_t capacity_to_reserve) {
    return ReserveProxyObj(capacity_to_reserve);
}

template <typename Type>
class SimpleVector {
public:
    using Iterator = Type*;
    using ConstIterator = const Type*;

    // constructors
    SimpleVector() noexcept = default;

    explicit SimpleVector(size_t size)
        : size_(size), capacity_(size), vector_(size)
    {
        std::fill(vector_.Get(), vector_.Get() + size_, Type{});
    }

    explicit SimpleVector(ReserveProxyObj capacity)
        : size_(0), capacity_(capacity.Get())
    {
    }

    SimpleVector(size_t size, const Type& value)
        : size_(size), capacity_(size), vector_(size)
    {
        std::fill(vector_.Get(), vector_.Get() + size_, Type{ value });
    }

     SimpleVector(std::initializer_list<Type> init)
        : size_(init.size()),
        capacity_(init.size()),
        vector_(init.size())
    {
        std::copy(init.begin(), init.end(), vector_.Get());
    }

    SimpleVector(const SimpleVector& other)
    {
        ArrayPtr<Type> tmp(other.capacity_);
        std::copy(other.vector_.Get(), other.vector_.Get() + other.capacity_, tmp.Get());
        vector_.swap(tmp);
        size_ = other.size_;
        capacity_ = other.capacity_;
    }
    
    SimpleVector(SimpleVector&& other)
    {
        swap(std::move(other));
    }

    SimpleVector& operator=(const SimpleVector& rhs)
    {
        if (this != &rhs)
        {
            SimpleVector rhs_copy(rhs);
            vector_.swap(rhs_copy.vector_);
            size_ = rhs_copy.GetSize();
            if (capacity_ < rhs_copy.GetCapacity())
            {
                capacity_ = rhs_copy.GetCapacity();
            }
        }
        return *this;
    }

    SimpleVector& operator=(SimpleVector&& rhs)
    {
        swap(std::move(rhs));
        return *this;
    }

    // 
    size_t GetSize() const noexcept
    {
        return size_;
    }

    size_t GetCapacity() const noexcept
    {
        return capacity_;
    }

    bool IsEmpty() const noexcept
    {
        if (size_)
        {
            return false;
        }
        return true;
    }

    Type& operator[](size_t index) noexcept
    {
        assert(index < size_);
        return *(vector_.Get() + index);
    }

    const Type& operator[](size_t index) const noexcept
    {
        assert(index < size_);
        return *(vector_.Get() + index);
    }

    Type& At(size_t index)
    {
        if (index < size_)
        {
            return *(vector_.Get() + index);
        }
        else
        {
            throw std::out_of_range("Sorry");
        }
    }

    const Type& At(size_t index) const
    {
        if (index < size_)
        {
            return *(vector_.Get() + index);
        }
        else
        {
            throw std::out_of_range("Sorry");
        }
    }

    void Clear() noexcept
    {
        size_ = 0;
    }

    void Resize(size_t new_size)
{
        if (new_size <= size_)
        {
            size_ = new_size;
        }
        else if (new_size <= capacity_)
        {
            for (auto i = size_; i < new_size; ++i)
            {
                PushBack(Type{});
            }
            size_ = new_size;
        }
        else
        {
            ArrayPtr<Type> tmp(new_size);
            std::copy(std::make_move_iterator(&vector_[0]), std::make_move_iterator(&vector_[size_]), tmp.Get());
            vector_.swap(tmp);
            for (auto i = size_; i < new_size; ++i)
            {
                PushBack(Type{});
            }
            size_ = new_size;
            capacity_ = new_size;
        }
    }

    void Reserve(size_t new_capacity)
    {
        if (new_capacity > capacity_)
        {
            capacity_ = new_capacity;
            ArrayPtr<Type> tmp(capacity_);
            std::copy(&vector_[0], &vector_[size_], tmp.Get());
            vector_.swap(tmp);
        }
    }

    void PushBack(const Type& item)
    {
        if (size_ < capacity_)
        {
            vector_[size_++] = item;
        }
        else if (capacity_ == 0)
        {
            ArrayPtr<Type> tmp(1);
            tmp[0] = item;
            vector_.swap(tmp);
            size_ = 1;
            capacity_ = 1;
         }
        else
        {
            capacity_ *= 2;
            ArrayPtr<Type> tmp(capacity_);
            std::copy(&vector_[0], &vector_[size_], tmp.Get());
            tmp[size_++] = item;
            vector_.swap(tmp);
        }
    }

    void PushBack(Type&& item)
    {
        if (size_ < capacity_)
        {
            vector_[size_++] = std::move(item);
        }
        else if (capacity_ == 0)
        {
            ArrayPtr<Type> tmp(1);
            tmp[0] = std::move(item);
            vector_.swap(tmp);
            size_ = 1;
            capacity_ = 1;
        }
        else
        {
            capacity_ *= 2;
            ArrayPtr<Type> tmp(capacity_);
            std::copy(std::make_move_iterator(&vector_[0]), std::make_move_iterator(&vector_[size_]), tmp.Get());
            tmp[size_++] = std::move(item);
            vector_.swap(tmp);
        }
    }

    Iterator Insert(ConstIterator pos, const Type& value)
    {
        assert(pos >= begin() && pos <= end());
        Iterator it = const_cast<Iterator>(pos);
        int dist = it - begin();
        if (size_ < capacity_)
        {
            std::copy_backward(it, vector_.Get() + size_, vector_.Get() + size_ + 1);
            *(it) = value;
            ++size_;
        }
        else if (!capacity_)
        {
            PushBack(value);
        }
        else
        {
            capacity_ *= 2;
            ArrayPtr<Type> tmp(capacity_);
            std::copy(begin(), it, tmp.Get());
            std::copy(it, end(), tmp.Get() + dist + 1);
            *(tmp.Get() + dist) = value;
            vector_.swap(tmp);
            ++size_;
        }
        return begin() + dist;
    }

    Iterator Insert(ConstIterator pos, Type&& value)
    {
        assert(pos >= begin() && pos <= end());
        Iterator it = const_cast<Iterator>(pos);
        int dist = it - begin();
        if (size_ < capacity_)
        {
            std::copy_backward(std::make_move_iterator(it), std::make_move_iterator(vector_.Get() + size_), vector_.Get() + size_ + 1);
            *(it) = std::move(value);
            ++size_;
        }
        else if (!capacity_)
        {
            PushBack(std::move(value));
        }
        else
        {
            capacity_ *= 2;
            ArrayPtr<Type> tmp(capacity_);
            std::copy(std::make_move_iterator(begin()), std::make_move_iterator(it), tmp.Get());
            std::copy(std::make_move_iterator(it), std::make_move_iterator(end()), tmp.Get() + dist + 1);
            *(tmp.Get() + dist) = std::move(value);
            vector_.swap(tmp);
            ++size_;
        }
        return begin() + dist;
    }

    void PopBack() noexcept {
        if (size_)
        {
            --size_;
        }
        else
        {
            //throw;
        }
    }

    Iterator Erase(ConstIterator pos)
    {
        assert(pos >= begin() && pos < end());
        Iterator it = const_cast<Iterator>(pos);
        if (it != end())
        {
            // added make_move_iterator
            std::copy(std::make_move_iterator(it + 1), std::make_move_iterator(end()), it);
            --size_;
        }
        return it;
    }

    void swap(SimpleVector& other) noexcept
    {
        vector_.swap(other.vector_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    void swap(SimpleVector&& other) noexcept
    {
        vector_.swap(other.vector_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    
    Iterator begin() noexcept
    {
        return vector_.Get();
    }

    Iterator end() noexcept
    {
        return vector_.Get() + size_;
    }

    ConstIterator begin() const noexcept
    {
        return vector_.Get();
    }

    ConstIterator end() const noexcept
    {
        return vector_.Get() + size_;
    }

    ConstIterator cbegin() const noexcept
    {
        return vector_.Get();
    }

    ConstIterator cend() const noexcept {
        return vector_.Get() + size_;
    }

    void Print()
    {
        for (size_t i = 0; i < size_; ++i)
        {
            std::cout << vector_[i] << " ";
        }
        std::cout << std::endl;
    }

private:
    size_t size_ = 0;
    size_t capacity_ = 0;
    ArrayPtr<Type> vector_ = {};
};

// comparison operators
template <typename Type>
inline bool operator==(const SimpleVector<Type>& lhs, const SimpleVector<Type>& rhs) {
    if (lhs.GetSize() != rhs.GetSize())
    {
        return false;
    }
    for (size_t i = 0; i < lhs.GetSize(); ++i)
    {
        if (lhs[i] != rhs[i])
        {
            return false;
        }
    }
    return true;
}

template <typename Type>
inline bool operator!=(const SimpleVector<Type>& lhs, const SimpleVector<Type>& rhs) {
    return !(lhs == rhs);
}

template <typename Type>
inline bool operator<(const SimpleVector<Type>& lhs, const SimpleVector<Type>& rhs) {
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename Type>
inline bool operator>=(const SimpleVector<Type>& lhs, const SimpleVector<Type>& rhs) {
    return !(lhs < rhs);
}

template <typename Type>
inline bool operator>(const SimpleVector<Type>& lhs, const SimpleVector<Type>& rhs) {
    return !(rhs>=lhs);
}

template <typename Type>
inline bool operator<=(const SimpleVector<Type>& lhs, const SimpleVector<Type>& rhs) {
    return !(lhs > rhs);
}

