/// @file tests.cpp
/// @author Munazza Shifa
/// @date November 08, 2023

/// Assignment details and provided code are created and
/// owned by Adam T Koehler, PhD - Copyright 2023.
/// University of Illinois Chicago - CS 251 Fall 2023

// Catch 2.x - Single Include Framework Testing
#define CATCH_CONFIG_MAIN

#include "prqueue.h"
#include "catch.hpp"

using namespace std;

TEST_CASE("Test enqueue() function") {
    SECTION("Enqueue elements with different priorities") {
        prqueue<int> pq;
        pq.enqueue(10, 2);
        pq.enqueue(20, 1);
        pq.enqueue(30, 3);

        REQUIRE(pq.size() == 3);

        int value, priority;
        value = pq.dequeue();
        priority = 1;
        REQUIRE(value == 20);
        REQUIRE(pq.size() == 2);

        value = pq.dequeue();
        priority = 2;
        REQUIRE(value == 10);
        REQUIRE(pq.size() == 1);

        value = pq.dequeue();
        priority = 3;
        REQUIRE(value == 30);
        REQUIRE(pq.size() == 0);
    }

    SECTION("Enqueue elements with the same priority") {
        prqueue<std::string> pq;
        pq.enqueue("Apple", 2);
        pq.enqueue("Banana", 2);
        pq.enqueue("Orange", 2);

        REQUIRE(pq.size() == 3);

        std::string value;
        int priority;

        // Dequeue the elements with the same priority in the order they were enqueued.
        value = pq.dequeue();
        priority = 2;
        REQUIRE(value == "Apple");
        REQUIRE(pq.size() == 2);

        value = pq.dequeue();
        priority = 2;
        REQUIRE(value == "Banana");
        REQUIRE(pq.size() == 1);

        value = pq.dequeue();
        priority = 2;
        REQUIRE(value == "Orange");
        REQUIRE(pq.size() == 0);
    }

    SECTION("Enqueue elements with mixed priorities") {
        prqueue<char> pq;
        pq.enqueue('A', 3);
        pq.enqueue('B', 1);
        pq.enqueue('C', 2);
        pq.enqueue('D', 1);
        pq.enqueue('E', 3);

        REQUIRE(pq.size() == 5);

        char value;
        int priority;

        // Dequeue the elements in ascending order of priority.
        value = pq.dequeue();
        priority = 1;
        REQUIRE(value == 'B');
        REQUIRE(pq.size() == 4);

        value = pq.dequeue();
        priority = 1;
        REQUIRE(value == 'D');
        REQUIRE(pq.size() == 3);

        value = pq.dequeue();
        priority = 2;
        REQUIRE(value == 'C');
        REQUIRE(pq.size() == 2);

        value = pq.dequeue();
        priority = 3;
        REQUIRE(value == 'A');
        REQUIRE(pq.size() == 1);

        value = pq.dequeue();
        priority = 3;
        REQUIRE(value == 'E');
        REQUIRE(pq.size() == 0);
    }
}

TEST_CASE("Test toString() function") {
    SECTION("Test toString() on an empty priority queue") {
        prqueue<int> pq;
        string expected = "";
        REQUIRE(pq.toString() == expected);
    }

    SECTION("Test toString() with elements of different priorities") {
        prqueue<std::string> pq;
        pq.enqueue("Apple", 2);
        pq.enqueue("Banana", 1);
        pq.enqueue("Orange", 3);

        string expected = "1 value: Banana\n2 value: Apple\n3 value: Orange\n";
        REQUIRE(pq.toString() == expected);
    }

    SECTION("Test toString() with elements of the same priority") {
        prqueue<char> pq;
        pq.enqueue('A', 2);
        pq.enqueue('B', 2);
        pq.enqueue('C', 2);

        string expected = "2 value: A\n2 value: B\n2 value: C\n";
        REQUIRE(pq.toString() == expected);
    }

    SECTION("Test toString() with mixed priorities") {
        prqueue<int> pq;
        pq.enqueue(10, 3);
        pq.enqueue(20, 1);
        pq.enqueue(30, 2);
        pq.enqueue(40, 2);

        string expected = "1 value: 20\n2 value: 30\n2 value: 40\n3 value: 10\n";
        REQUIRE(pq.toString() == expected);
    }
}

TEST_CASE("Test clear() function") {
    SECTION("Test clear() on an empty priority queue") {
        prqueue<int> pq;
        pq.clear();
        REQUIRE(pq.size() == 0);
    }

    SECTION("Test clear() on a non-empty priority queue") {
        prqueue<int> pq;
        pq.enqueue(10, 2);
        pq.enqueue(20, 1);
        pq.enqueue(30, 3);

        REQUIRE(pq.size() == 3);

        pq.clear();
        REQUIRE(pq.size() == 0);
    }

    SECTION("Test clear() with elements of the same priority") {
        prqueue<char> pq;
        pq.enqueue('A', 2);
        pq.enqueue('B', 2);
        pq.enqueue('C', 2);

        REQUIRE(pq.size() == 3);

        pq.clear();
        REQUIRE(pq.size() == 0);
    }

    SECTION("Test clear() after dequeueing") {
        prqueue<std::string> pq;
        pq.enqueue("Apple", 2);
        pq.enqueue("Banana", 1);
        pq.enqueue("Orange", 3);

        REQUIRE(pq.size() == 3);

        pq.dequeue();
        pq.clear();
        REQUIRE(pq.size() == 0);
    }
}

TEST_CASE("Test operator== function") {
    SECTION("Test operator== on two empty priority queues") {
        prqueue<int> pq1;
        prqueue<int> pq2;
        REQUIRE(pq1 == pq2);
    }

    SECTION("Test operator== on two priority queues with different elements") {
        prqueue<int> pq1;
        pq1.enqueue(10, 2);
        pq1.enqueue(20, 1);
        prqueue<int> pq2;
        pq2.enqueue(30, 3);
        pq2.enqueue(40, 2);

        REQUIRE_FALSE(pq1 == pq2);
    }

    SECTION("Test operator== on two priority queues with the same elements") {
        prqueue<char> pq1;
        pq1.enqueue('A', 2);
        pq1.enqueue('B', 2);
        pq1.enqueue('C', 2);
        prqueue<char> pq2;
        pq2.enqueue('A', 2);
        pq2.enqueue('B', 2);
        pq2.enqueue('C', 2);

        REQUIRE(pq1 == pq2);
    }

    SECTION("Test operator== on two priority queues with mixed priorities") {
        prqueue<std::string> pq1;
        pq1.enqueue("Apple", 2);
        pq1.enqueue("Banana", 1);
        pq1.enqueue("Orange", 3);
        prqueue<string> pq2;
        pq2.enqueue("Orange", 3);
        pq2.enqueue("Apple", 2);
        pq2.enqueue("Banana", 1);

        REQUIRE(pq1 == pq2);
    }

    SECTION("Test operator== on two priority queues with duplicate elements") {
        prqueue<int> pq1;
        pq1.enqueue(10, 2);
        pq1.enqueue(20, 2);
        pq1.enqueue(30, 2);
        prqueue<int> pq2;
        pq2.enqueue(10, 2);
        pq2.enqueue(20, 2);
        pq2.enqueue(30, 2);

        REQUIRE(pq1 == pq2);
    }
}


TEST_CASE("Test begin() and next() functions") {
    SECTION("Test begin() and next() on an empty priority queue") {
        prqueue<int> pq;
        int value, priority;

        pq.begin();
        REQUIRE_FALSE(pq.next(value, priority)); // No elements to traverse
    }

    SECTION("Test begin() and next() on a priority queue with elements") {
        prqueue<int> pq;
        pq.enqueue(10, 2);
        pq.enqueue(20, 1);
        pq.enqueue(30, 3);

        int value, priority;

        pq.begin();
        REQUIRE(pq.next(value, priority) == true);
        REQUIRE(priority == 1);
        REQUIRE(value == 20);

        REQUIRE(pq.next(value, priority) == true);
        REQUIRE(priority == 2);
        REQUIRE(value == 10);

        REQUIRE(pq.next(value, priority) == true);
        REQUIRE(priority == 3);
        REQUIRE(value == 30);

        REQUIRE(pq.next(value, priority) == false); // No more elements to traverse
    }

    SECTION("Test begin() and next() on a priority queue with elements of the same priority") {
        prqueue<std::string> pq;
        pq.enqueue("Apple", 2);
        pq.enqueue("Banana", 2);
        pq.enqueue("Orange", 2);

        std::string value;
        int priority;

        pq.begin();
        REQUIRE(pq.next(value, priority) == true);
        REQUIRE(priority == 2);
        REQUIRE(value == "Apple");

        REQUIRE(pq.next(value, priority) == true);
        REQUIRE(priority == 2);
        REQUIRE(value == "Banana");

        REQUIRE(pq.next(value, priority) == true);
        REQUIRE(priority == 2);
        REQUIRE(value == "Orange");

        REQUIRE(pq.next(value, priority) == false); // No more elements to traverse
    }

    SECTION("Test begin() and next() on a priority queue with mixed priorities") {
        prqueue<int> pq;
        pq.enqueue(10, 3);
        pq.enqueue(20, 1);
        pq.enqueue(30, 2);
        pq.enqueue(40, 2);

        int value, priority;

        pq.begin();
        REQUIRE(pq.next(value, priority) == true);
        REQUIRE(priority == 1);
        REQUIRE(value == 20);

        REQUIRE(pq.next(value, priority) == true);
        REQUIRE(priority == 2);
        REQUIRE(value == 30);

        REQUIRE(pq.next(value, priority) == true);
        REQUIRE(priority == 2);
        REQUIRE(value == 40);

        REQUIRE(pq.next(value, priority) == true);
        REQUIRE(priority == 3);
        REQUIRE(value == 10);

        REQUIRE(pq.next(value, priority) == false); // No more elements to traverse
    }
}

TEST_CASE("Test dequeue() function") {
    SECTION("Test dequeue() on an empty priority queue") {
        prqueue<int> pq;
        int value;

        value = pq.dequeue();
        REQUIRE(value == 0); // Default value for int
    }

    SECTION("Test dequeue() on a priority queue with elements") {
        prqueue<int> pq;
        pq.enqueue(10, 2);
        pq.enqueue(20, 1);
        pq.enqueue(30, 3);

        int value;

        value = pq.dequeue();
        REQUIRE(value == 20); // Dequeued element with the lowest priority

        value = pq.dequeue();
        REQUIRE(value == 10);

        value = pq.dequeue();
        REQUIRE(value == 30); // Dequeued element with the highest priority

        value = pq.dequeue();
        REQUIRE(value == 0); // Default value for int (queue is empty)
    }

    SECTION("Test dequeue() on a priority queue with elements of the same priority") {
        prqueue<std::string> pq;
        pq.enqueue("Apple", 2);
        pq.enqueue("Banana", 2);
        pq.enqueue("Orange", 2);

        std::string value;

        value = pq.dequeue();
        REQUIRE(value == "Apple"); // Dequeued elements in the order they were enqueued

        value = pq.dequeue();
        REQUIRE(value == "Banana");

        value = pq.dequeue();
        REQUIRE(value == "Orange");

        value = pq.dequeue();
        REQUIRE(value == ""); // Default value for std::string (queue is empty)
    }

    SECTION("Test dequeue() on a priority queue with mixed priorities") {
        prqueue<int> pq;
        pq.enqueue(10, 3);
        pq.enqueue(20, 1);
        pq.enqueue(30, 2);
        pq.enqueue(40, 2);

        int value;

        value = pq.dequeue();
        REQUIRE(value == 20); // Dequeued element with the lowest priority

        value = pq.dequeue();
        REQUIRE(value == 30); // Dequeued element with the same priority as the previous

        value = pq.dequeue();
        REQUIRE(value == 40); // Dequeued element with the same priority as the previous

        value = pq.dequeue();
        REQUIRE(value == 10); // Dequeued element with the highest priority

        value = pq.dequeue();
        REQUIRE(value == 0); // Default value for int (queue is empty)
    }
}

TEST_CASE("Test peek() function") {
    SECTION("Test peek() on an empty priority queue") {
        prqueue<int> pq;
        int value;

        value = pq.peek();
        REQUIRE(value == 0); // Default value for int
    }

    SECTION("Test peek() on a priority queue with elements") {
        prqueue<int> pq;
        pq.enqueue(10, 2);
        pq.enqueue(20, 1);
        pq.enqueue(30, 3);

        int value;

        value = pq.peek();
        REQUIRE(value == 20); // Peeked at the element with the lowest priority (not removed)

        value = pq.dequeue(); // Dequeue an element
        REQUIRE(value == 20);

        value = pq.peek();
        REQUIRE(value == 10); // Peeked at the next element with the lowest priority

        value = pq.dequeue(); // Dequeue an element
        REQUIRE(value == 10);

        value = pq.peek();
        REQUIRE(value == 30); // Peeked at the element with the highest priority (not removed)
    }

    SECTION("Test peek() on a priority queue with elements of the same priority") {
        prqueue<std::string> pq;
        pq.enqueue("Apple", 2);
        pq.enqueue("Banana", 2);
        pq.enqueue("Orange", 2);

        std::string value;

        value = pq.peek();
        REQUIRE(value == "Apple"); // Peeked at the first element with the same priority (not removed)

        value = pq.dequeue(); // Dequeue an element
        REQUIRE(value == "Apple");

        value = pq.peek();
        REQUIRE(value == "Banana"); // Peeked at the next element with the same priority (not removed)

        value = pq.dequeue(); // Dequeue an element
        REQUIRE(value == "Banana");

        value = pq.peek();
        REQUIRE(value == "Orange"); // Peeked at the last element with the same priority (not removed)
    }

    SECTION("Test peek() on a priority queue with mixed priorities") {
        prqueue<int> pq;
        pq.enqueue(10, 3);
        pq.enqueue(20, 1);
        pq.enqueue(30, 2);
        pq.enqueue(40, 2);

        int value;

        value = pq.peek();
        REQUIRE(value == 20); // Peeked at the element with the lowest priority (not removed)

        value = pq.dequeue(); // Dequeue an element
        REQUIRE(value == 20);

        value = pq.peek();
        REQUIRE(value == 30); // Peeked at the element with the same priority as the previous (not removed)

        value = pq.dequeue(); // Dequeue an element
        REQUIRE(value == 30);

        value = pq.peek();
        REQUIRE(value == 40); // Peeked at the next element with the same priority (not removed)
    }
}

TEST_CASE("Test equality operator (operator==)") {
    SECTION("Test equality operator on two empty priority queues") {
        prqueue<int> pq1;
        prqueue<int> pq2;
        REQUIRE(pq1 == pq2); // Two empty queues should be equal
    }

    SECTION("Test equality operator on two priority queues with different elements") {
        prqueue<int> pq1;
        pq1.enqueue(10, 2);
        pq1.enqueue(20, 1);
        prqueue<int> pq2;
        pq2.enqueue(30, 3);
        pq2.enqueue(40, 2);

        REQUIRE_FALSE(pq1 == pq2); // Different elements, so not equal
    }

    SECTION("Test equality operator on two priority queues with the same elements") {
        prqueue<string> pq1;
        pq1.enqueue("Apple", 2);
        pq1.enqueue("Banana", 1);
        prqueue<string> pq2;
        pq2.enqueue("Apple", 2);
        pq2.enqueue("Banana", 1);

        REQUIRE(pq1 == pq2); // Same elements, so equal
    }

    SECTION("Test equality operator on two priority queues with mixed priorities") {
        prqueue<int> pq1;
        pq1.enqueue(10, 3);
        pq1.enqueue(20, 1);
        pq1.enqueue(30, 2);
        pq1.enqueue(40, 2);
        prqueue<int> pq2;
        pq2.enqueue(20, 1);
        pq2.enqueue(30, 2);
        pq2.enqueue(40, 2);
        pq2.enqueue(10, 3);

        REQUIRE(pq1 == pq2); // Same elements and priorities, so equal
    }

    SECTION("Test equality operator on two priority queues with different sizes") {
        prqueue<int> pq1;
        pq1.enqueue(10, 2);
        pq1.enqueue(20, 1);
        pq1.enqueue(30, 3);
        prqueue<int> pq2;
        pq2.enqueue(10, 2);
        pq2.enqueue(20, 1);

        REQUIRE_FALSE(pq1 == pq2); // Different sizes, so not equal
    }

    SECTION("Test equality operator on two priority queues with duplicate elements") {
        prqueue<int> pq1;
        pq1.enqueue(10, 2);
        pq1.enqueue(20, 2);
        pq1.enqueue(30, 2);
        prqueue<int> pq2;
        pq2.enqueue(10, 2);
        pq2.enqueue(20, 2);
        pq2.enqueue(30, 2);

        REQUIRE(pq1 == pq2); // Same elements and priorities, so equal
    }
}



