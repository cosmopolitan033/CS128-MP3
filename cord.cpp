#include <string>
#include <cstring>
#include <stdexcept>
#include "cord.hpp"

SharedPointer<char> Cord::ToString() const {
    if (data_ != nullptr) {
        size_t length_with_null = length_ + 1;
        char* result = new char[length_with_null];
        std::memcpy(result, data_, length_);
        result[length_] = '\0';
        return SharedPointer<char>(result, kSharedPointerType::kArray);
    }

    std::string result;
    if (left_) {
        SharedPointer<char> left_string = left_->ToString();
        result.append(left_string.Get());
    }
    if (right_) {
        SharedPointer<char> right_string = right_->ToString();
        result.append(right_string.Get());
    }

    char* final_result = new char[result.length() + 1];
    std::memcpy(final_result, result.c_str(), result.length());
    final_result[result.length()] = '\0';

    return SharedPointer<char>(final_result, kSharedPointerType::kArray);
}
