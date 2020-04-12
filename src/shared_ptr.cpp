// Simple implementation of a shared pointer

#include <iostream>

using namespace std;

template<typename T>
class SharedPtr
{
public:
    SharedPtr()
    {
        m_ptr = nullptr;
        m_count = new size_t(1);
    }

    SharedPtr(const T& data)
    {
        m_ptr = new T(data);
        m_count = new size_t(1);
    }

    SharedPtr(const SharedPtr& other)
    {
        m_ptr = other.m_ptr;
        m_count = other.m_count;
        ++(*m_count);
    }

    ~SharedPtr()
    {
        cout << "Destructor called!" << endl;
        cout << "count = " << *m_count << endl;
        if (--(*m_count) == 0)
        {
            delete m_ptr;
            delete m_count;
        }
    }

    SharedPtr& operator=(const SharedPtr& other)
    {
        --(*m_count);
        m_ptr = other.m_ptr;
        m_count = other.m_count;
        ++(*m_count);
    }

    friend ostream& operator<<(ostream& os, const SharedPtr& ptr)
    {
        os << "data: " << *ptr.m_ptr << ", count: " << *ptr.m_count;
        return os;
    }

//private:
    T* m_ptr;
    size_t* m_count;
};

int main(int argc, char** argv)
{
    SharedPtr<double> ptr1(0.324);
    SharedPtr<double> ptr2;
    ptr2.m_ptr = new double(98.667);
    cout << "ptr1 = " << ptr1 << endl;
    cout << "ptr2 = " << ptr2 << "\n\n";
    SharedPtr<double> ptr3(ptr2);
    cout << "ptr1 = " << ptr1 << endl;
    cout << "ptr2 = " << ptr2 << endl;
    cout << "ptr3 = " << ptr3 << "\n\n";
    SharedPtr<double> ptr4 = ptr3;
    cout << "ptr1 = " << ptr1 << endl;
    cout << "ptr2 = " << ptr2 << endl;
    cout << "ptr3 = " << ptr3 << endl;
    cout << "ptr4 = " << ptr4 << "\n\n";
    ptr4 = ptr1;
    cout << "ptr1 = " << ptr1 << endl;
    cout << "ptr2 = " << ptr2 << endl;
    cout << "ptr3 = " << ptr3 << endl;
    cout << "ptr4 = " << ptr4 << "\n\n";
    ptr2 = ptr1;
    ptr3 = ptr1;
    cout << "ptr1 = " << ptr1 << endl;
    cout << "ptr2 = " << ptr2 << endl;
    cout << "ptr3 = " << ptr3 << endl;
    cout << "ptr4 = " << ptr4 << "\n\n";
}

