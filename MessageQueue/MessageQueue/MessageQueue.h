#pragma once

#include <queue>
#include <chrono>
//#include <stdexcept>

template<typename T>
struct Message {
    int urgency;
    std::chrono::system_clock::time_point expiry;
    T message;

    bool operator<(const Message<T>& other) const {
        if (urgency != other.urgency) {
            return urgency > other.urgency;
        }
        else {
            return expiry > other.expiry;
        }
    }
};

template<typename T>
class MessageQueue {
public:
    MessageQueue(size_t max_size) : max_size_(max_size) {}

    void push(Message<T> msg) {
        if (queue_.size() == max_size_) {
            clear_expired();
        }

        if (queue_.size() == max_size_) {
            throw std::exception("MessageQueue is full and all messages are valid");
        }

        queue_.push(msg);
    }

    Message<T> pop() {
        while (!queue_.empty()) {
            auto msg = queue_.top();
            if (msg.expiry > std::chrono::system_clock::now()) {
                queue_.pop();
                return msg;
            }
            else {
                queue_.pop();
            }
        }

        throw std::exception("MessageQueue is empty");
    }

    bool empty() const {
        return queue_.empty();
    }

    size_t size() const {
        return queue_.size();
    }

    bool has_valid_message() const {
        return !queue_.empty() && queue_.top().expiry > std::chrono::system_clock::now();
    }

    void clear() {
        while (!queue_.empty()) {
            queue_.pop();
        }
    }

private:
    void clear_expired() {
        while (!queue_.empty()) {
            auto msg = queue_.top();
            if (msg.expiry > std::chrono::system_clock::now()) {
                break;
            }
            else {
                queue_.pop();
            }
        }
    }

    size_t max_size_;
    std::priority_queue<Message<T>> queue_;
};

