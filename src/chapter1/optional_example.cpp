//
// Created by 吴凡 on 2017/3/7.
//

#include <boost/optional.hpp>
#include <iostream>

class DeviceLock {
public:
    explicit DeviceLock(const char* device) {
        // acquire lock
        std::cout << "Device is locked\n";
    }

    ~DeviceLock() {
        // release lock
    }

    void use() {
        // already has lock
        std::cout << "Success!\n";
    }

    static boost::optional<DeviceLock> try_lock_device() {
        if(rand() % 2) {
            return boost::none;
        }
        return boost::optional<DeviceLock>(DeviceLock("device name"));
    }
};

int main() {
    srand((unsigned int) time(nullptr));
    for(int i = 0; i < 10; ++i) {
        boost::optional<DeviceLock> t = DeviceLock::try_lock_device();
        if(t) {
            t->use();
            return 0;
        } else {
            std::cout << "Try again...\n";
        }
    }
    std::cout << "Failure\n";
    return 0;
}

