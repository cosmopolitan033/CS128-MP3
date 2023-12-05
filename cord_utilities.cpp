#include <stdexcept>
#include <cstring>
#include "cord_utilities.hpp"

SharedPointer<Cord> ConcatCords(SharedPointer<Cord> left_cord, SharedPointer<Cord> right_cord) {
    if (!left_cord.Get() || !right_cord.Get()) {
        throw std::invalid_argument("One of the cords is null");
    }

    auto new_cord = SharedPointer<Cord>(new Cord);
    new_cord->left_ = left_cord;
    new_cord->right_ = right_cord;
    new_cord->length_ = left_cord->Length() + right_cord->Length();
    return new_cord;
}

SharedPointer<Cord> SubString(SharedPointer<Cord> cord, unsigned int lower_idx, unsigned int upper_idx) {
    // 验证索引范围
    if (lower_idx >= upper_idx || upper_idx > cord->Length()) {
        throw std::out_of_range("Invalid substring range");
    }

    // 如果是叶节点，直接提取子串
    if (cord->Data() != nullptr) {
        if (lower_idx == 0 && upper_idx == cord->Length()) {
            // 如果子串是整个字符串，无需创建新节点
            return cord;
        } else {
            // 需要创建新的叶节点来存储子串
            unsigned int dataLength = upper_idx - lower_idx;
            char* substrData = new char[dataLength + 1];
            std::memcpy(substrData, cord->Data().data() + lower_idx, dataLength);
            substrData[dataLength] = '\0';
            return SharedPointer<Cord>(new Cord(std::string_view(substrData, dataLength)));
        }
    }

    // 如果子串跨越左子节点和右子节点
    SharedPointer<Cord> leftPart, rightPart;
    if (lower_idx < cord->Left()->Length()) {
        unsigned int leftEnd = std::min(upper_idx, cord->Left()->Length());
        leftPart = SubString(cord->Left(), lower_idx, leftEnd);
    }
    if (upper_idx > cord->Left()->Length()) {
        unsigned int rightStart = std::max(lower_idx, cord->Left()->Length()) - cord->Left()->Length();
        unsigned int rightEnd = upper_idx - cord->Left()->Length();
        rightPart = SubString(cord->Right(), rightStart, rightEnd);
    }

    // 将左右部分连接起来
    return ConcatCords(leftPart, rightPart);
}
