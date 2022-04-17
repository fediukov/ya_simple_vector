#pragma once
#include <cassert>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <utility>

// � �������, ����������� �� �������������� inline, ����� ���� ���������
// ���������� ����������� � ������ �������� ����������.
// ������ inline �������� �������, ��� ���� ��������� � ������������ �����,
// ����� ��� ����������� ����� ����� �� ������ ������ ���������� �� ��������� ������ ����������
inline void Test1() {
    // ������������� ������������� �� ���������
    {
        SimpleVector<int> v;
        assert(v.GetSize() == 0u);
        assert(v.IsEmpty());
        assert(v.GetCapacity() == 0u);
        std::cout << "Test 1.01 is done" << std::endl;
    }

    // ������������� ������� ���������� �������
    {
        SimpleVector<int> v(5);
        assert(v.GetSize() == 5u);
        assert(v.GetCapacity() == 5u);
        assert(!v.IsEmpty());
        for (size_t i = 0; i < v.GetSize(); ++i) {
            assert(v[i] == 0);
        }
        std::cout << "Test 1.02 is done" << std::endl;
    }


    // ������������� �������, ������������ �������� ���������
    {
        SimpleVector<int> v(3, 42);
        assert(v.GetSize() == 3);
        assert(v.GetCapacity() == 3);
        for (size_t i = 0; i < v.GetSize(); ++i) {
            assert(v[i] == 42);
        }
        std::cout << "Test 1.03 is done" << std::endl;
    }

    // ������������� ������� ��� ������ initializer_list
    {
        SimpleVector<int> v{ 1, 2, 3 };
        assert(v.GetSize() == 3);
        assert(v.GetCapacity() == 3);
        assert(v[2] == 3);
        std::cout << "Test 1.04 is done" << std::endl;
    }

    // ������ � ��������� ��� ������ At
    {
        SimpleVector<int> v(3);
        assert(&v.At(2) == &v[2]);
        try {
            v.At(3);
            assert(false);  // ��������� ������������ ����������
        }
        catch (const std::out_of_range&) {
        }
        catch (...) {
            assert(false);  // �� ��������� ����������, �������� �� out_of_range
        }
        std::cout << "Test 1.05 is done" << std::endl;
    }

    // ������� �������
    {
        SimpleVector<int> v(10);
        const size_t old_capacity = v.GetCapacity();
        v.Clear();
        assert(v.GetSize() == 0);
        assert(v.GetCapacity() == old_capacity);
        std::cout << "Test 1.06 is done" << std::endl;
    }

    // ��������� �������
    {
        SimpleVector<int> v(3);
        v[2] = 17;
//        for (auto i = 0; i != v.GetSize(); ++i) std::cout << &v[i] << " "; std::cout << std::endl;
        v.Print(); 
        v.Resize(7);
//        for (auto i = 0; i != v.GetSize(); ++i) std::cout << &v[i] << " "; std::cout << std::endl;
        v.Print();
        assert(v.GetSize() == 7);
        assert(v.GetCapacity() >= v.GetSize());
        assert(v[2] == 17);
        assert(v[3] == 0);
        std::cout << "Test 1.07 is done" << std::endl;
    }
    {
        SimpleVector<int> v(3);
        v[0] = 42;
        v[1] = 55;
        const size_t old_capacity = v.GetCapacity();
        v.Resize(2);
        assert(v.GetSize() == 2);
        assert(v.GetCapacity() == old_capacity);
        assert(v[0] == 42);
        assert(v[1] == 55);//*/
        std::cout << "Test 1.08 is done" << std::endl;
    }
    {
        const size_t old_size = 3;
        SimpleVector<int> v(3);
        v[0] = 1;
        v[1] = 1;
        v[2] = 1;
        //std::cout << v.GetSize() << "/" << v.GetCapacity() << " " << v.begin() << std::endl;
        //v.Print();
        v.Resize(old_size + 5);
        //std::cout << v.GetSize() << "/" << v.GetCapacity() << " " << v.begin() << std::endl;
        //v.Print();
        v[3] = 3;
        v[4] = 4;
        v[5] = 5;
        v[6] = 6;
        v[7] = 7;
        //v[8] = 8;
        //v.Print();
        v.Resize(old_size + 6);
        //std::cout << v.GetSize() << "/" << v.GetCapacity() << " " << v.begin() << std::endl;
        //v.Print();
        v.Resize(old_size + 8);
        //std::cout << v.GetSize() << "/" << v.GetCapacity() << " " << v.begin() << std::endl;
        //v.Print();
        v.Resize(old_size + 4);
        //std::cout << v.GetSize() << "/" << v.GetCapacity() << " " << v.begin() << std::endl;
        //v.Print();
        v.Resize(old_size + 6);
        //std::cout << v.GetSize() << "/" << v.GetCapacity() << " " << v.begin() << std::endl;
        //v.Print();
        //assert(v[3] == 0);
        std::cout << "Test 1.09 is done" << std::endl;
    }

    // ������������ �� SimpleVector
    {
        // ������ ������
        {
            SimpleVector<int> v;
            assert(v.begin() == nullptr);
            assert(v.end() == nullptr);
        }

        // �������� ������
        {
            SimpleVector<int> v(10, 42);
            assert(v.begin());
            assert(*v.begin() == 42);
            assert(v.end() == v.begin() + v.GetSize());
        }
        std::cout << "Test 1.10 is done" << std::endl;
    }//*/
}

inline void Test2() {
    // PushBack
    {
        SimpleVector<int> v(1);
        v.PushBack(42);
        assert(v.GetSize() == 2);
        assert(v.GetCapacity() >= v.GetSize());
        assert(v[0] == 0);
        assert(v[1] == 42);
        std::cout << "Test 2.01 is done" << std::endl;
    }//*/

    // ���� ������� �����, PushBack �� ����������� Capacity
    {
        SimpleVector<int> v(2);
        v.Resize(1);
        const size_t old_capacity = v.GetCapacity();
        v.PushBack(123);
        assert(v.GetSize() == 2);
        assert(v.GetCapacity() == old_capacity);
        std::cout << "Test 2.02 is done" << std::endl;
    }

    // PopBack
    {
        SimpleVector<int> v{ 0, 1, 2, 3 };
        const size_t old_capacity = v.GetCapacity();
        const auto old_begin = v.begin();
        v.PopBack();
        assert(v.GetCapacity() == old_capacity);
        assert(v.begin() == old_begin);
        assert((v == SimpleVector<int>{0, 1, 2}));
        std::cout << "Test 2.03 is done" << std::endl;
    }//*/

    // ����������� �����������
    {
        SimpleVector<int> numbers{ 1, 2 };
        auto numbers_copy(numbers);
        assert(&numbers_copy[0] != &numbers[0]);
        assert(numbers_copy.GetSize() == numbers.GetSize());
        for (size_t i = 0; i < numbers.GetSize(); ++i) {
            assert(numbers_copy[i] == numbers[i]);
            assert(&numbers_copy[i] != &numbers[i]);
        }
        std::cout << "Test 2.04 is done" << std::endl;
    }

    // ���������
    {
        assert((SimpleVector{ 1, 2, 3 } == SimpleVector{ 1, 2, 3 }));
        assert((SimpleVector{1, 2, 3} != SimpleVector{1, 2, 2}));

        assert((SimpleVector{1, 2, 3} < SimpleVector{1, 2, 3, 1}));
        assert((SimpleVector{1, 2, 3} > SimpleVector{1, 2, 2, 1}));

        assert((SimpleVector{ 1, 2, 3 } >= SimpleVector{ 1, 2, 3 }));
        assert((SimpleVector{ 1, 2, 4 } >= SimpleVector{ 1, 2, 3 }));
        assert((SimpleVector{ 1, 2, 3 } <= SimpleVector{ 1, 2, 3 }));
        assert((SimpleVector{ 1, 2, 3 } <= SimpleVector{ 1, 2, 4 }));
        std::cout << "Test 2.05 is done" << std::endl;
    }

    // ����� �������� ��������
    {
        SimpleVector<int> v1{ 42, 666 };
        SimpleVector<int> v2;
        v2.PushBack(0);
        v2.PushBack(1);
        v2.PushBack(2);
        const int* const begin1 = &v1[0];
        const int* const begin2 = &v2[0];

        const size_t capacity1 = v1.GetCapacity();
        const size_t capacity2 = v2.GetCapacity();

        const size_t size1 = v1.GetSize();
        const size_t size2 = v2.GetSize();

        static_assert(noexcept(v1.swap(v2)));
        v1.swap(v2);
        assert(&v2[0] == begin1);
        assert(&v1[0] == begin2);
        assert(v1.GetSize() == size2);
        assert(v2.GetSize() == size1);
        assert(v1.GetCapacity() == capacity2);
        assert(v2.GetCapacity() == capacity1);
        std::cout << "Test 2.06 is done" << std::endl;
    }//*/

    // ������������
    {
        SimpleVector<int> src_vector{ 1, 2, 3, 4 };
        SimpleVector<int> dst_vector{ 1, 2, 3, 4, 5, 6 };
        dst_vector = src_vector;
        assert(dst_vector == src_vector);
        std::cout << "Test 2.07 is done" << std::endl;
    }

    // ������� ���������
    {
        SimpleVector<int> v{ 1, 2, 3, 4 };
        v.PushBack(5);
        v.Resize(4);
        v.Insert(v.begin() + 2, 42);
        assert((v == SimpleVector<int>{1, 2, 42, 3, 4}));
        std::cout << "Test 2.08 is done" << std::endl;
    }
    {
        SimpleVector<int> v{ 1, 2, 3, 4 };
        v.Print();
        v.Insert(v.begin() + 2, 42);
        v.Print();
        assert((v == SimpleVector<int>{1, 2, 42, 3, 4}));
        std::cout << "Test 2.09 is done" << std::endl;
    }
    {
        SimpleVector<int> v;
        v.Insert(v.begin(), 42);
        v.Print();
        assert((v == SimpleVector<int>{42}));
        std::cout << "Test 2.10 is done" << std::endl;
    }
    {
        SimpleVector<int> v{ 1, 2, 3, 4 };
        auto it = v.Insert(v.begin(), 42);
        v.Print();
        std::cout << *it << std::endl;
        assert((v == SimpleVector<int>{42, 1, 2, 3, 4}));
        std::cout << "Test 2.11 is done" << std::endl;
    }


    // �������� ���������
    {
        SimpleVector<int> v{ 1, 2, 3, 4 };
        v.Print();
        v.Erase(v.cbegin() + 2);
        v.Print();
        assert((v == SimpleVector<int>{1, 2, 4}));
        std::cout << "Test 2.12 is done" << std::endl;
    }//*/
}

void TestReserveConstructor() {
    using namespace std;

    cout << "TestReserveConstructor"s << endl;
    SimpleVector<int> v(Reserve(5));
    assert(v.GetCapacity() == 5);
    assert(v.IsEmpty());
    cout << "Done!"s << endl << endl;//*/
}

void TestReserveMethod() {
    using namespace std;

    cout << "TestReserveMethod"s << endl;
    SimpleVector<int> v;
    // ������������� 5 ���� � �������
    v.Reserve(5);
    assert(v.GetCapacity() == 5);
    assert(v.IsEmpty());

    // ���������� ��������� capacity �� 1
    v.Reserve(1);
    // capacity ������ �������� �������
    assert(v.GetCapacity() == 5);
    // �������� 10 ��������� � ������
    for (int i = 0; i < 10; ++i) {
        v.PushBack(i);
    }
    assert(v.GetSize() == 10);
    // �������� capacity �� 100
    v.Reserve(100);
    // ��������, ��� ������ �� ���������
    assert(v.GetSize() == 10);
    assert(v.GetCapacity() == 100);
    // ��������, ��� �������� �� �����
    for (int i = 0; i < 10; ++i) {
        assert(v[i] == i);
    }
    cout << "Done!"s << endl << endl;
}

class X {
public:
    X()
        : X(5) {
    }
    X(size_t num)
        : x_(num) {
    }
    X(const X& other) = delete;
    X& operator=(const X& other) = delete;
    X(X&& other) {
        x_ = std::exchange(other.x_, 0);
    }
    X& operator=(X&& other) {
        x_ = std::exchange(other.x_, 0);
        return *this;
    }
    size_t GetX() const {
        return x_;
    }

private:
    size_t x_;
};

SimpleVector<int> GenerateVector(size_t size) {
    SimpleVector<int> v(size);
    std::iota(v.begin(), v.end(), 1);
    return v;
}

void TestTemporaryObjConstructor() {
    const size_t size = 1000000;
    std::cout << "Test with temporary object, copy elision" << std::endl;
    SimpleVector<int> moved_vector(GenerateVector(size));
    assert(moved_vector.GetSize() == size);
    std::cout << "Done!" << std::endl << std::endl;
}

void TestTemporaryObjOperator() {
    const size_t size = 1000000;
    std::cout << "Test with temporary object, operator=" << std::endl;
    SimpleVector<int> moved_vector;
    assert(moved_vector.GetSize() == 0);
    moved_vector = GenerateVector(size);
    assert(moved_vector.GetSize() == size);
    std::cout << "Done!" << std::endl << std::endl;//*/
}

void TestNamedMoveConstructor() {
    const size_t size = 1000000;
    std::cout << "Test with named object, move constructor" << std::endl;
    SimpleVector<int> vector_to_move(GenerateVector(size));
    assert(vector_to_move.GetSize() == size);

    SimpleVector<int> moved_vector(std::move(vector_to_move));
    assert(moved_vector.GetSize() == size);
    assert(vector_to_move.GetSize() == 0);
    std::cout << "Done!" << std::endl << std::endl;//*/
}

void TestNamedMoveOperator() {
    const size_t size = 1000000;
    std::cout << "Test with named object, operator=" << std::endl;
    SimpleVector<int> vector_to_move(GenerateVector(size));
    assert(vector_to_move.GetSize() == size);

    SimpleVector<int> moved_vector = std::move(vector_to_move);
    assert(moved_vector.GetSize() == size);
    assert(vector_to_move.GetSize() == 0);
    std::cout << "Done!" << std::endl << std::endl;//*/
}

void TestNoncopiableMoveConstructor() {
    /*const size_t size = 5;
    std::cout << "Test noncopiable object, move constructor" << std::endl;
    SimpleVector<X> vector_to_move;
    for (size_t i = 0; i < size; ++i) {
        vector_to_move.PushBack(X(i));
    }

    SimpleVector<X> moved_vector = std::move(vector_to_move);
    assert(moved_vector.GetSize() == size);
    assert(vector_to_move.GetSize() == 0);

    for (size_t i = 0; i < size; ++i) {
        assert(moved_vector[i].GetX() == i);
    }
    std::cout << "Done!" << std::endl << std::endl;//*/
}

void TestNoncopiablePushBack() {
    /*const size_t size = 5;
    std::cout << "Test noncopiable push back" << std::endl;
    SimpleVector<X> v;
    for (size_t i = 0; i < size; ++i) {
        v.PushBack(X(i));
    }

    assert(v.GetSize() == size);

    for (size_t i = 0; i < size; ++i) {
        assert(v[i].GetX() == i);
    }
    std::cout << "Done!" << std::endl << std::endl;//*/
}

void TestNoncopiableInsert() {
    /*const size_t size = 5;
    std::cout << "Test noncopiable insert" << std::endl;
    SimpleVector<X> v;
    for (size_t i = 0; i < size; ++i) {
        v.PushBack(X(i));
    }

    // � ������
    v.Insert(v.begin(), X(size + 1));
    assert(v.GetSize() == size + 1);
    assert(v.begin()->GetX() == size + 1);
    // � �����
    v.Insert(v.end(), X(size + 2));
    assert(v.GetSize() == size + 2);
    assert((v.end() - 1)->GetX() == size + 2);
    // � ��������
    v.Insert(v.begin() + 3, X(size + 3));
    assert(v.GetSize() == size + 3);
    assert((v.begin() + 3)->GetX() == size + 3);
    std::cout << "Done!" << std::endl << std::endl;//*/
}

void TestNoncopiableErase() {
    /*const size_t size = 3;
    std::cout << "Test noncopiable erase" << std::endl;
    SimpleVector<X> v;
    for (size_t i = 0; i < size; ++i) {
        v.PushBack(X(i));
    }

    auto it = v.Erase(v.begin());
    assert(it->GetX() == 1);
    std::cout << "Done!" << std::endl << std::endl;//*/
}



