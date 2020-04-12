// Simple implementation of a circular buffer.

#include <iostream>
#include <cstring>

using namespace std;

template<typename T>
class CircularBuffer
{
public:
    CircularBuffer(const size_t& _max_size) : max_size(_max_size), head(0), tail(0), full(false)
    {
        ptr = new T[max_size];
    }

    CircularBuffer(const CircularBuffer& other) : max_size(other.max_size)
    {
        ptr =  new T[max_size];
        memcpy(ptr, other.ptr, max_size * sizeof(T));
        head = other.head;
        tail = other.tail;
        full = other.full;
    }

    ~CircularBuffer()
    {
        delete[] ptr;
    }

    CircularBuffer& operator=(const CircularBuffer& other)
    {
        CircularBuffer buf(other);
        return buf;
    }

    T& operator[](const size_t& idx)
    {
        if (idx < max_size)
            return ptr[(head + idx) % max_size];
        else
            throw runtime_error("CircularBuffer: index > max_size");
    }

    friend ostream& operator<<(ostream& os, const CircularBuffer& buf)
    {
        os << "ptr: " << buf.ptr << ", max_size: " << buf.max_size << ", size: " << buf.size();
        return os;
    }

    const T& front() const { return ptr[head]; }
    const T& back() const { return ptr[(tail - 1 + max_size) % max_size]; }
    const T& get(const size_t& idx) const { return ptr[(head+idx) % max_size]; }
    const size_t size() const { return full ? max_size : (tail+max_size) % max_size; }

    void print() const
    {
        for (size_t i = 0; i < max_size; ++i)
            cout << get(i) << " ";
        cout << endl;
    }

    void push_back(const T& value)
    {
        if (full && head == tail)
            head = ++head % max_size;
        ptr[tail] = value;
        tail = ++tail % max_size;
        if (!full && head == tail)
            full = true;
    }

//private:
    T* ptr;
    const size_t max_size;
    size_t head;
    size_t tail;
    bool full;
};



int main(int argc, char** argv)
{
    cout << "Running circular buffer tests...\n";

    int N = 5;
    CircularBuffer<double> buf1(N);
    for (size_t i = 0; i < N; ++i)
        buf1.push_back(i);
    cout << "buf1 = " << buf1 << endl;
    buf1.print();

    CircularBuffer<double> buf2 = buf1;
    cout << "buf2 = " << buf2 << endl;
    buf2.print();

    CircularBuffer<double> buf3(buf1);
    cout << "buf3 = " << buf3 << endl;
    buf3.print();
    cout << "front: " << buf3.front() << endl;
    cout << "back: " << buf3.back() << endl;

    cout << "buf3 new = \n";
    buf3.push_back(99);
    buf3.push_back(77);
    buf3.print();
    cout << "front: " << buf3.front() << endl;
    cout << "back: " << buf3.back() << endl;

    CircularBuffer<int> buf4(N);
    buf4.push_back(4);
    buf4.push_back(5);
    buf4.push_back(6);
    cout << "buf4 = " << buf4 << endl;
    buf4.print();
    cout << "front: " << buf4.front() << endl;
    cout << "back: " << buf4.back() << endl;

    return 0;
}