//
// Created by 吴凡 on 2017/3/30.
//
#include <boost/thread/shared_mutex.hpp>
#include <map>
#include <string>

struct user_info {
    int age;
    std::string name;
};

class users_online {
public:
    bool is_online(const std::string &user_name) const {
        boost::shared_lock<boost::shared_mutex> read_lock(shared_mutex_);
        return users_.find(user_name) != users_.end();
    }

    int get_age(const std::string &user_name) const {
        boost::shared_lock<boost::shared_mutex> read_lock(shared_mutex_);
        return users_.at(user_name).age;
    }

    void set_online(const std::string &user_name, const user_info &info) {
        boost::lock_guard<boost::shared_mutex> write_lock(shared_mutex_);
        users_[user_name] = info;
    }
private:
    std::map<std::string, user_info> users_;
    mutable boost::shared_mutex shared_mutex_;
};

// ...