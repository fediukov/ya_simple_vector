#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <utility>

template <typename Type>
class ArrayPtr {
public:
    // �������������� ArrayPtr ������� ����������
    ArrayPtr() = default;

    // ������ � ���� ������ �� size ��������� ���� Type.
    // ���� size == 0, ���� raw_ptr_ ������ ���� ����� nullptr
    explicit ArrayPtr(const size_t& size) {
        if (size)
        {
            raw_ptr_ = new Type[size];
            //for (auto i = 0; i != size; ++i) std::cout << &raw_ptr_[i] << " "; std::cout << std::endl;
        }
        else
        {
            raw_ptr_ = nullptr;
        }
    }

    explicit ArrayPtr(size_t&& size) {
        if (size)
        {
            raw_ptr_ = new Type[std::move(size)];
        }
        else
        {
            raw_ptr_ = nullptr;
        }
    }

    ArrayPtr& operator=(const size_t& size)
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

    ArrayPtr& operator=(size_t&& size)
    {
        if (size)
        {
            raw_ptr_ = new Type[std::move(size)];
        }
        else
        {
            raw_ptr_ = nullptr;
        }
    }

    // ����������� �� ������ ���������, ��������� ����� ������� � ���� ���� nullptr
    explicit ArrayPtr(Type* raw_ptr) noexcept {
        raw_ptr_ = raw_ptr;
    }

    // ��������� �����������
    ArrayPtr(const ArrayPtr&) = delete;

    ~ArrayPtr() {
        delete[] raw_ptr_;
    }

    // ��������� ������������
    ArrayPtr& operator=(const ArrayPtr&) = delete;

    // ���������� ��������� �������� � ������, ���������� �������� ������ �������
    // ����� ������ ������ ��������� �� ������ ������ ����������
    [[nodiscard]] Type* Release() noexcept {
        // ��������. ���������� ����� ��������������
        Type* tmp = raw_ptr_;
        raw_ptr_ = nullptr;
        return tmp;
    }

    // ���������� ������ �� ������� ������� � �������� index
    Type& operator[](size_t index) noexcept {
        return raw_ptr_[index];
    }

    // ���������� ����������� ������ �� ������� ������� � �������� index
    const Type& operator[](size_t index) const noexcept {
        return raw_ptr_[index];
    }

    // ���������� true, ���� ��������� ���������, � false � ��������� ������
    explicit operator bool() const {
        if (raw_ptr_ == nullptr)
        {
            return false;
        }
        return true;
    }

    // ���������� �������� ������ ���������, ��������� ����� ������ �������
    Type* Get() const noexcept {
        return raw_ptr_;
    }

    // ������������ ��������� ��������� �� ������ � �������� other
    void swap(ArrayPtr& other) noexcept {
        std::swap(raw_ptr_, other.raw_ptr_);
    }

private:
    Type* raw_ptr_ = nullptr;
};
