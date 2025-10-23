#include <algorithm>
#include <cassert>
#include <cstdio>

template <typename T>
class Vector {
public:
    Vector() : begin_(new T[1]), size_(0), capacity_(1) {
    }
    Vector(size_t size, const T& val = T()) : begin_(new T[size]), size_(size), capacity_(size) {
        std::fill(begin_, begin_ + size_, val);
    }
    Vector(std::initializer_list<T> init) : Vector(init.size()) {
        std::copy(init.begin(), init.end(), begin_);
    }
    Vector(const Vector& other)
            : begin_(new T[other.capacity()]), size_(other.size()), capacity_(other.capacity()) {
        std::copy(other.begin(), other.begin() + other.size(), begin_);
    }
    Vector(Vector&& other)
            : begin_(other.begin()), size_(other.size()), capacity_(other.capacity()) {
        other.begin_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    ~Vector() {
        delete[] begin_;
    }

    void resize(size_t size) {
        if (size_ < size) {
            reallocate(size);
        }

        size_ = size;
    }
    void reserve(size_t capacity) {
        if (capacity_ < capacity) {
            reallocate(capacity);
        }
    }

    Vector& operator=(const Vector& other) {
        if (begin_ != other.begin()) {
            delete[] begin_;
            begin_ = new T[other.capacity_];
            size_ = other.size_;
            capacity_ = other.capacity_;
            std::copy(other.begin_, other.begin_ + other.size_, begin_);
        }

        return *this;
    }
    Vector& operator=(Vector&& other) noexcept {
        if (begin_ != other.begin()) {
            delete[] begin_;
            begin_ = other.begin_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.begin_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }


    void push_back(T val) {
        if (size_ == capacity_) {
            reallocate(2 * capacity_);
        }

        begin_[size_] = val;
        ++size_;
    }

    void pop_back() {
        assert(size_ != 0);
        --size_;
    }

    size_t size() const {
        return size_;
    }
    size_t capacity() const {
        return capacity_;
    }
    bool empty() const {
        return size_ == 0;
    }
    T& front() const {
        assert(size_ != 0);
        return *begin_;
    }
    T& back() const {
        assert(size_ != 0);
        return *begin_[size_ - 1];
    }
    T* begin() const {
        return begin_;
    }
    T* end() const {
        return begin_ + size_;
    }

    T& operator[](size_t index) {
        assert(index <= size_);
        return begin_[index];
    }

    void clear() {
        size_ = 0;
    }

private:
    T* begin_;
    std::size_t size_;
    std::size_t capacity_;

    void reallocate(size_t new_capacity) {
        T* old_begin_ = begin_;
        capacity_ = new_capacity;
        begin_ = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            begin_[i] = old_begin_[i];
        }

        if (old_begin_ != nullptr) {
            delete[] old_begin_;
        }
    }
};
