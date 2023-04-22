#include <iostream>
#include "MessageQueue.h"


int main() {
    MessageQueue<std::string> q(3);

    try
    {
        q.push({ 1, std::chrono::system_clock::now() + std::chrono::seconds(10), "Low urgency message" });
        q.push({ 3, std::chrono::system_clock::now() + std::chrono::seconds(10), "High urgency message 1" });
        q.push({ 2, std::chrono::system_clock::now() + std::chrono::seconds(10), "Medium urgency message" });
        q.push({ 3, std::chrono::system_clock::now() + std::chrono::seconds(10), "High urgency message 2" });

    }
    catch (const std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
    }
    std::cout << "Queue size: " << q.size() << std::endl;
    std::cout << "Has valid message: " << q.has_valid_message() << std::endl;

    while (q.has_valid_message()) {
        auto msg = q.pop();
        std::cout << "Received message with urgency " << msg.urgency << ": " << msg.message << std::endl;
    }

    std::cout << "Queue size: " << q.size() << std::endl;

    q.clear();
    std::cout << "Queue size after clear: " << q.size() << std::endl;
    std::cout << "Is empty after clear: " << q.empty() << std::endl;

    return 0;
}