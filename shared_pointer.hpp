#ifndef SHARED_POINTER_HPP
#define SHARED_POINTER_HPP

enum class kSharedPointerType { kArray, kObject };

template <typename T>
class SharedPointer {
public:
    SharedPointer(T* address = nullptr, kSharedPointerType type = kSharedPointerType::kObject)
            : holder_(address), type_(type), ref_count_(new unsigned int(1)) {
        if (address == nullptr) {
            ref_count_ = nullptr;
        }
    }
    ~SharedPointer() {
        if (ref_count_ && --(*ref_count_) == 0) {
            if (type_ == kSharedPointerType::kArray) {
                delete[] holder_;
            } else {
                delete holder_;
            }
            delete ref_count_;
        }
    }
    SharedPointer(const SharedPointer& source)
            : holder_(source.holder_), type_(source.type_), ref_count_(source.ref_count_) {
        if (ref_count_) {
            ++(*ref_count_);
        }
    }
    SharedPointer& operator=(const SharedPointer& source) {
        if (this != &source) {
            if (ref_count_ && --(*ref_count_) == 0) {
                if (type_ == kSharedPointerType::kArray) {
                    delete[] holder_;
                } else {
                    delete holder_;
                }
                delete ref_count_;
            }

            holder_ = source.holder_;
            type_ = source.type_;
            ref_count_ = source.ref_count_;
            if (ref_count_) {
                ++(*ref_count_);
            }
        }
        return *this;
    }

    // Provided, do not modify!
//    SharedPointer() = default;
    T& operator*() { return *holder_; }
    T* operator->() { return holder_; }
    const T* operator->() const { return holder_; }
    T* Get() { return holder_; }
    const T* Get() const { return holder_; }
    unsigned int UseCount() const {
        return (ref_count_ != nullptr) ? *ref_count_ : 0;
    }
    operator bool() const {
        return holder_ != nullptr;
    }
private:
    T* holder_ = nullptr;
    kSharedPointerType type_ = kSharedPointerType::kObject;
    unsigned int* ref_count_ = nullptr;
};

// non-member helper function declarations

// non-member helper function definitions

// member function definitions

#endif
