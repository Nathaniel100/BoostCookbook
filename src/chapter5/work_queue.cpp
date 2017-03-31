//
// Created by 吴凡 on 2017/3/30.
//

#include <boost/thread.hpp>
#include <boost/functional.hpp>
#include <boost/noncopyable.hpp>
#include <deque>

class work_queue : private boost::noncopyable {
public:
    using task = boost::function<void()>;

    void push_task(task t) {
        boost::unique_lock<boost::mutex> lock(mutex_);
        tasks_.push_back(std::move(t));
        lock.unlock();
        cond_.notify_one();
    }

    std::shared_ptr<task> try_pop_task() {
        boost::lock_guard<boost::mutex> lock(mutex_);
        if(tasks_.empty()) return std::shared_ptr<task>(nullptr);
        std::shared_ptr<task> res = std::make_shared<task>(tasks_.front());
        tasks_.pop_front();
        return res;
    }

    std::shared_ptr<task> pop_task() {
        boost::unique_lock<boost::mutex> lock(mutex_);
        cond_.wait(lock, [this]{
            return !tasks_.empty();
        });
        std::shared_ptr<task> res = std::make_shared<task>(tasks_.front());
        tasks_.pop_front();
        return res;
    }
private:
    std::deque<task> tasks_;
    boost::mutex mutex_;
    boost::condition_variable cond_;
};

work_queue queue;
void do_nothing() {
}
constexpr int task_numbers = 300000;
void pusher() {
    for(int i = 0; i < task_numbers; ++i) {
        queue.push_task(&do_nothing);
    }
}

void popper() {
    for(int i = 0; i < task_numbers; ++i) {
        queue.pop_task();
    }
}

int main() {
    boost::thread t1{pusher};
    boost::thread t2{pusher};
    boost::thread t3{pusher};
    boost::thread t4{popper};
    boost::thread t5{popper};
    boost::thread t6{popper};

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();

    assert(!queue.try_pop_task());

    queue.push_task(&do_nothing);

    assert(queue.try_pop_task());
    return 0;
}

