#pragma once

struct Element {
    int value;
    int priority;
    long long timestamp;

    bool operator<(const Element& other) const {
        if (priority == other.priority) {
            return timestamp > other.timestamp;
        }
        return priority < other.priority;
    }

    bool operator>(const Element& other) const {
        if (priority == other.priority) {
            return timestamp < other.timestamp;
        }
        return priority > other.priority;
    }
};