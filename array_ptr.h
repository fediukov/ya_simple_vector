#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <utility>

template <typename Type>
class ArrayPtr {
public:
    // constructors/destructor
    ArrayPtr() = default;

    explicit ArrayPtr(const size_t& size)
    {
        if (size)
        {
            raw_ptr_ = new Type[size];
        }
        else
        {
            raw_ptr_ = nullptr;
        }
    }

    ArrayPtr(ArrayPtr&& rhs)
    {
        raw_ptr_ = std::move(rhs.raw_ptr_);
        rhs.raw_ptr_ = nullptr;
    }

    ArrayPtr& operator=(ArrayPtr&& rhs)
    {
        raw_ptr_ = std::move(rhs.raw_ptr_);
        rhs.raw_ptr_ = nullptr;
    }

    explicit ArrayPtr(Type* raw_ptr) noexcept
    {
        raw_ptr_ = raw_ptr;
    }

    ArrayPtr(const ArrayPtr&) = delete;

    ~ArrayPtr() {
        delete[] raw_ptr_;
    }

    //
    ArrayPtr& operator=(const ArrayPtr&) = delete;

    [[nodiscard]] Type* Release() noexcept
    {
        Type* tmp = raw_ptr_;
        raw_ptr_ = nullptr;
        return tmp;
    }

    Type& operator[](size_t index) noexcept
    {
        return raw_ptr_[index];
    }

    const Type& operator[](size_t index) const noexcept
    {
        return raw_ptr_[index];
    }

    explicit operator bool() const
    {
        if (raw_ptr_ == nullptr)
        {
            return false;
        }
        return true;
    }

    Type* Get() const noexcept
    {
        return raw_ptr_;
    }

    void swap(ArrayPtr& other) noexcept
    {
        std::swap(raw_ptr_, other.raw_ptr_);
    }

private:
    Type* raw_ptr_ = nullptr;
};
