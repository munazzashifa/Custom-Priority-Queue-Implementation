    // Recursive function to clear the tree
    void clearRecursive(NODE* node) {
        if (node == nullptr) {
            return;
        }

        // Recursively clear the left and right subtrees
        clearRecursive(node->left);
        clearRecursive(node->right);

        // Free memory for the current node
        delete node;

        // Reset the current node's pointers to null
        node->left = nullptr;
        node->right = nullptr;
        node->link = nullptr;
        node->parent = nullptr;
    }