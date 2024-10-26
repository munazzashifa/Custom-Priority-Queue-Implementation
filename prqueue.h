
/// @file prqueue.h
/// @author Munazza Shifa
/// @date November 08, 2023
///
/// Assignment details and provided code are created and
/// owned by Adam T Koehler, PhD - Copyright 2023.
/// University of Illinois Chicago - CS 251 Fall 2023

// Description: This C++ program defines a custom priority queue class prqueue that uses a binary 
// search tree (BST) to manage elements with associated priorities. It provides functionalities 
// for enqueueing, dequeueing, and peeking at elements based on their priority levels while
// efficiently handling duplicates. The class also supports operations like copying, clearing, 
// and equality comparison of priority queues.

#pragma once

#include <iostream>
#include <sstream>
#include <set>
#include <queue>
#include <stack>
#include <functional>

using namespace std;

template<typename T>
class prqueue {
private:
    struct NODE {
        int priority;  // used to build BST
        T value;       // stored data for the p-queue
        bool dup;      // marked true when there are duplicate priorities
        NODE* parent;  // links back to parent
        NODE* link;    // links to linked list of NODES with duplicate priorities
        NODE* left;    // links to left child
        NODE* right;   // links to right child
    };
    NODE* root; // pointer to root node of the BST
    int sz;     // # of elements in the prqueue
    NODE* curr; // pointer to next item in prqueue (see begin and next)

public:
    //
    // default constructor:
    //
    // Creates an empty priority queue.
    // O(1)
    //
    prqueue() {
        root = nullptr;
        sz = 0;
        curr = nullptr;  
    }


    //
    // operator=
    //
    // Clears "this" tree and then makes a copy of the "other" tree.
    // Sets all member variables appropriately.
    // O(n), where n is total number of nodes in custom BST
    //
    prqueue& operator=(const prqueue& other) {
        if (this == &other) {
            return *this; // Handle self-assignment
        }

        // If 'other' is empty, we're done
        if (other.root == nullptr) {
            return *this;
        }

        // Traverse 'other' and enqueue its elements into 'this'
        queue<NODE*> q;
        q.push(other.root);

        while (!q.empty()) {
            NODE* current = q.front();
            q.pop();

            // Enqueue the current node's value
            enqueue(current->value, current->priority);

            // Enqueue left and right children (if they exist)
            if (current->left) {
                q.push(current->left);
            }
            if (current->right) {
                q.push(current->right);
            }

            // Enqueue linked list nodes with the same priority
            NODE* linkNode = current->link;
            while (linkNode) {
                enqueue(linkNode->value, linkNode->priority);
                linkNode = linkNode->link;
            }
        }

        return *this;
    }


    //
    // clear:
    //
    // Frees the memory associated with the priority queue but is public.
    // O(n), where n is total number of nodes in custom BST
    //
    // Recursive helper function to clear the tree
    void _clearRecursive(NODE* node) {
        if (node == nullptr) {
            return;
        }

        // Recursively clear the left and right subtrees
        _clearRecursive(node->left);
        _clearRecursive(node->right);

        // If the current node has duplicate priorities, clear the linked list
        while (node->link != nullptr) {
            NODE* temp = node;
            node = node->link;
            delete temp;
        }

        // Clear the current node
        delete node;
    }

    // Public clear method
    void clear() {
        // Call the recursive helper function to clear the tree
        _clearRecursive(root);

        // Reset root and size
        root = nullptr;
        sz = 0;
    }


    //
    // destructor:
    //
    // Frees the memory associated with the priority queue.
    // O(n), where n is total number of nodes in custom BST
    //
    ~prqueue() {

        clear();

    }


    //
    // enqueue:
    //
    // Inserts the value into the custom BST in the correct location based on
    // priority.
    // O(logn + m), where n is number of unique nodes in tree and m is number 
    // of duplicate priorities
    //
    void enqueue(T value, int priority) {
        // Create a new node with the provided value and priority.
        NODE* newNode = new NODE;
        newNode->priority = priority;
        newNode->value = value;
        newNode->dup = false;
        newNode->parent = nullptr;
        newNode->link = nullptr;
        newNode->left = nullptr;
        newNode->right = nullptr;

        // If the tree is empty, set the new node as the root.
        if (root == nullptr) {
            root = newNode;
            sz = 1;
            curr = root;
            return;
        }

        // Otherwise, traverse the tree to find the correct position to insert the new node.
        NODE* currentNode = root;
        NODE* parent = nullptr;

        while (currentNode != nullptr) {
            parent = currentNode;

            // Handle duplicate priorities by creating a linked list of nodes with the same priority.
            if (priority == currentNode->priority) {
                while (currentNode->link != nullptr) {
                    parent = currentNode;
                    currentNode = currentNode->link;
                }
                currentNode->link = newNode;
                newNode->link = nullptr;  // Connect the new node to the end of the linked list.
                newNode->parent = parent;
                newNode->dup = true;
                currentNode->dup = true;
                sz++;
                return;
            } else if (priority < currentNode->priority) {
                currentNode = currentNode->left;
            } else {
                currentNode = currentNode->right;
            }
        }

        // Insert the new node in the correct position.
        if (priority < parent->priority) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }

        newNode->parent = parent;
        sz++;
    }


    //
    // dequeue:
    //
    // returns the value of the next element in the priority queue and removes
    // the element from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number 
    // of duplicate priorities
    //
    T dequeue() {
        if (root == nullptr) {
            // Handle the case when the priority queue is empty by returning a default value.
            return T{};
        }

        NODE* node = root;
        NODE* prev = nullptr;

        // Traverse to the leftmost node to find the element with the highest priority.
        while (node->left != nullptr) {
            prev = node;
            node = node->left;
        }

        T valueOut = node->value;

        // Decrease the size of the priority queue.
        sz--;

        if (node->dup && node->link != nullptr) {
            if (node->right != nullptr) {
                node->link->right = node->right;
                node->right->parent = node->link;
            }
            // Update the parent's left child to the linked list node.
            if (prev != nullptr) {
                prev->left = node->link;
                node->link->parent = prev;
            } else {
                // If the node to dequeue is the root, update the root.
                root = node->link;
                node->link->parent = nullptr;
            }

            delete node; // Free memory for the dequeued node.
            return valueOut;
        } 
        else {
            if (node->right != nullptr) {
                node->right->parent = prev;
            }

            // Update the parent's left child to the right child.
            if (prev != nullptr) {
                prev->left = node->right;
            } else {
                // If the node to dequeue is the root, update the root.
                root = node->right;
                if (root != nullptr) {
                    root->parent = nullptr;
                }
            }

            delete node; // Free memory for the dequeued node.
            return valueOut;
        }
    }


    //
    // Size:
    //
    // Returns the # of elements in the priority queue, 0 if empty.
    // O(1)
    //
    int size() {

        return sz;

    }


    //
    // begin
    //
    // Resets internal state for an inorder traversal.  After the
    // call to begin(), the internal state denotes the first inorder
    // node; this ensure that first call to next() function returns
    // the first inorder node value.
    //
    // O(logn), where n is number of unique nodes in tree
    //
    void begin() {
        // Start at the leftmost node (node with the lowest priority).
        curr = root;
        // Traverse left until the leftmost node is reached.
        while (curr && curr->left) {
            curr = curr->left;
        }
    }


    //
    // next
    //
    // Uses the internal state to return the next inorder priority, and
    // advance the internal state in anticipation of future calls.
    //
    // False is returned when the internal state has reached null,
    // meaning no more values/priorities are available.  This is the end of the
    // inorder traversal. True is returned in all other cases as the inertnal
    // state has not reached the end of the priority queue. 
    //
    // Therefore, when another thing exists for future next() calls, 
    // true would be returned, when future next() calls would be invalid.
    // false would be returned.
    //
    // O(?) - hard to say.  But approximately O(logn + m).  Definitely not O(n).
    //
    bool next(T& value, int& priority) {
        // If the current node is null, there are no more values to return.
        if (!curr) {
            return false;
        }
        // Retrieve the value and priority of the current node.
        value = curr->value;
        priority = curr->priority;

        // Check if there is a linked list of nodes with the same priority.
        if (curr->link) {
            curr = curr->link;
            return true;
        }

        // When there are no more linked list nodes with the same priority, we need to
        // find the next node to visit in the BST structure.
        while (curr->parent && curr->priority == curr->parent->priority) {
            curr = curr->parent;
        }

         // Step 1: Check if there is a right child.
        if (curr->right) {
            curr = curr->right;
            // Traverse all the way left to find the next node with the lowest priority
            // in the right subtree.
            while (curr->left) {
                curr = curr->left;
            }
            return true;
        }

        // Step 2: If there's no right child, backtrack to the parent and continue
        // checking for higher-priority nodes.
        while (curr->parent) {
            if (curr->parent->priority > curr->priority) {
                curr = curr->parent;
                return true;
            }
            curr = curr->parent;
        }

         // If we reach this point without returning true, it means we've traversed the entire BST, 
         // and there are no more higher-priority nodes.
        return false;
    }


    //
    // toString:
    //
    // Returns a string of the entire priority queue, in order.  Format:
    // "1 value: Ben
    //  2 value: Jen
    //  2 value: Sven
    //  3 value: Gwen"
    //
    // Recursive helper function to build the string representation
    void _toStringRecursive(NODE* node, ostream& output) {
        if (node == nullptr) {
            return;
        }

        // Recursively visit the left subtree (nodes with lower priority).
        _toStringRecursive(node->left, output);

        // Append the current node's information to the output stream.
        if (node->dup) {
            NODE* current = node;
            while (current) {
                //cout << current->priority << " value: " << current->value << endl;
                output << current->priority << " value: " << current->value << "\n";
                current = current->link;
            }
        } else {
            output << node->priority << " value: " << node->value << "\n";
        }

        // Recursively visit the right subtree (nodes with higher priority).
        _toStringRecursive(node->right, output);
    }

    // Public toString method
    string toString() {
        // Create a stringstream to build the string representation
        stringstream ss;

        // Call the recursive helper function with the stringstream
        _toStringRecursive(root, ss);

        // Convert the stringstream to a string
        return ss.str();
    }


    //
    // peek:
    //
    // returns the value of the next element in the priority queue but does not
    // remove the item from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number 
    // of duplicate priorities
    //
    T peek() {
        // Use a helper function to find the first node with the highest priority.
        NODE* firstNode = _findFirstNode(root);

        if (firstNode != nullptr) {
            return firstNode->value;
        } else {
            // Handle the case when the priority queue is empty by returning a default value.
            return T{};
        }
    }

    // Private helper function to find the first node (leftmost node) with the highest priority.
    NODE* _findFirstNode(NODE* node) {
        if (node == nullptr) {
            return nullptr;  // The priority queue is empty.
        }

        // Traverse to the leftmost node to find the element with the highest priority.
        while (node->left != nullptr) {
            node = node->left;
        }

        return node;
    }


    //
    // ==operator
    //
    // Returns true if this priority queue as the priority queue passed in as
    // other.  Otherwise returns false.
    // O(n), where n is total number of nodes in custom BST
    //
    bool operator==(const prqueue& other) const {
        // Check if the sizes of the two priority queues are different.
        if (sz != other.sz) {
            return false;
        }

        // Helper function for recursive comparison.
        function<bool(NODE*, NODE*)> areEqual = [&](NODE* leftNode, NODE* rightNode) {
            if (!leftNode && !rightNode) {
                return true; // Both nodes are null, indicating equality.
            }
            if (!leftNode || !rightNode) {
                return false; // One node is null while the other is not, indicating inequality.
            }

            // Compare priorities and values of the nodes.
            if (leftNode->priority != rightNode->priority || leftNode->value != rightNode->value) {
                return false;
            }

            // Recursively compare left and right subtrees.
            return areEqual(leftNode->left, rightNode->left) && areEqual(leftNode->right, rightNode->right) && areEqual(leftNode->link, rightNode->link);
        };

        // Call the helper function to compare the root nodes of the BSTs.
        return areEqual(root, other.root);
    }


    //
    // getRoot - Do not edit/change!
    //
    // Used for testing the BST.
    // return the root node for testing.
    //
    void* getRoot() {
        return root;
    }
};



