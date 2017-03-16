//
// Created by 吴凡 on 2017/3/9.
//



#include <string.h>
#include <algorithm>
#include <cassert>
#include <iostream>

class DescriptorOwner {
public:
    DescriptorOwner(): descriptor_{nullptr} {
        std::cout << "Default Constructor!\n";
    }
    explicit DescriptorOwner(const char *ptr): descriptor_{strdup(ptr)} {
        std::cout << "Constructor!\n";
    }
    ~DescriptorOwner() {
        std::cout << "Destructor!\n";
        clear();
    }

    DescriptorOwner(DescriptorOwner&& param): descriptor_{param.descriptor_} {
        std::cout << "Move Constructor!\n";
        param.descriptor_ = nullptr;
    }
    DescriptorOwner& operator=(DescriptorOwner&& param) {
        std::cout << "Move Assignment!\n";
        std::swap(descriptor_, param.descriptor_);
        return *this;
    }
    bool empty() const {
        return descriptor_ == nullptr;
    }
    void clear() {
        if(descriptor_) {
            std::cout << "Free" << "\n";
            free(descriptor_);
        }
    }
private:
    void *descriptor_;
};

DescriptorOwner ConstructDescriptorOwner() {
    return DescriptorOwner("Hello Descriptor");
}

int main() {
    DescriptorOwner descriptorOwner2("12345");
    descriptorOwner2 = ConstructDescriptorOwner();
    assert(!descriptorOwner2.empty());

    DescriptorOwner descriptorOwner = ConstructDescriptorOwner();
    assert(!descriptorOwner.empty());
    DescriptorOwner descriptorOwner1 = std::move(descriptorOwner);
    assert(descriptorOwner.empty());
    assert(!descriptorOwner1.empty());
    return 0;
}