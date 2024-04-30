#include <iostream>
#include <vector>
#include <utility>
#include "SearchTree.h"

using namespace std;

template <typename Key, typename Value>
class BST : public SearchTree<Key, Value>
{
private:
    struct Node
    {
        Key key;
        Value value;
        Node* left;
        Node* right;

        Node(Key key, Value value) : key(key), value(value), left(nullptr), right(nullptr) {}
    };

    Node* root;
    int count;

    int heightRecursive(Node* node)
    {
        if (node == nullptr)
        {
            return -1;
        }
        else
        {
            int leftHeight = heightRecursive(node->left);
            int rightHeight = heightRecursive(node->right);
            return 1 + max(leftHeight, rightHeight);
        }
    }

    bool isElemRecursive(Node* node, Key key)
    {
        if (node == nullptr) return false;
        else if (node->key == key) return true;
        else if (node->key > key) return isElemRecursive(node->left, key);
        else return isElemRecursive(node->right, key);
        return false;
    }

    Node* insertRecursive(Node* node, Key key, Value value)
    {
        if (node == nullptr)
        {
            count++;
            return new Node(key, value);
        }
        else if (key == node->key) // key was already present
        {
            node->value = value;
        }
        else if (node->key > key) //insert left
        {
            node->left = insertRecursive(node->left, key, value);
        }
        else if (node->key < key) //insert right
        {
            node->right = insertRecursive(node->right, key, value);
        }

        return node;
    }

    Value searchRecursive(Node* node, Key key)
    {
        if (node == nullptr)  return Value();
        if (node->key == key) return node->value;
        else if (node->key > key) return searchRecursive(node->left, key);
        else return searchRecursive(node->right, key);
    }

    Node* findMin(Node* node)
    {
        while (node->left != nullptr)
        {
            node = node->left;
        }
        return node;
    }

    Node* deleteRecursive(Node* node, Key key)
    {
        if (node == nullptr) return nullptr; //Key is not in the tree
        if (node->key > key)
        {
            node->left = deleteRecursive(node->left, key);
        }
        else if (node->key < key)
        {
            node->right = deleteRecursive(node->right, key);
        }
        else
        {
            // Case 1: Node without children
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                count--;
                return nullptr;
            }
            // Case 2: Node With one child
            else if (node->left == nullptr) // only right child
            {
                Node* temp = node->right;
                delete node;
                count--;
                return temp;
            }
            else if (node->right == nullptr) // only left child
            {
                Node* temp = node->left;
                delete node;
                count--;
                return temp;
            }
            // Case 3: Node with two children
            else
            {
                Node* temp = findMin(node->right);
                node->key = temp->key;
                node->value = temp->value;
                node->right = deleteRecursive(node->right, temp->key);
            }
        }
        return node;
    }

    void preOrderRecursive(Node* node, vector<Key>& result)
    {
        if (node != nullptr)
        {
            result.push_back(node->key);
            preOrderRecursive(node->left, result);
            preOrderRecursive(node->right, result);
        }
    }

    void inOrderRecursive(Node* node, vector<Key>& result)
    {
        if (node != nullptr)
        {
            inOrderRecursive(node->left, result);
            result.push_back(node->key);
            inOrderRecursive(node->right, result);
        }
    }

    void postOrderRecursive(Node* node, vector<Key>& result)
    {
        if (node != nullptr)
        {
            postOrderRecursive(node->left, result);
            postOrderRecursive(node->right, result);
            result.push_back(node->key);
        }
    }

    void valuesRecursive(Node* node, vector<Value>& result)
    {
        if (node != nullptr)
        {
            result.push_back(node->value);
            valuesRecursive(node->left, result);
            valuesRecursive(node->right, result);
        }
    }

    void keysValuesRecursive(Node* node, vector<pair<Key, Value>>& result)
    {
        if (node != nullptr)
        {
            result.push_back(make_pair(node->key, node->value));
            keysValuesRecursive(node->left, result);
            keysValuesRecursive(node->right, result);
        }
    }

public:
    BST() : root(nullptr), count(0) {}
    ~BST() {};

    bool isEmpty() override
    {
        return root == nullptr;
    }

    int size() override
    {
        return count;
    }

    int height() override
    {
        return heightRecursive(root);
    }

    void insert(Key key, Value value) override
    {
        root = insertRecursive(root, key, value);
    }

    Value search(Key key) override
    {
        return searchRecursive(root, key);
    }

    bool isElem(Key key) override
    {
        return isElemRecursive(root, key);
    }

    void remove(Key key) override
    {
        root = deleteRecursive(root, key);
    }

    vector<Key> preOrder() override
    {
        vector<Key> result;
        preOrderRecursive(root, result);
        return result;
    }

    vector<Key> inOrder() override
    {
        vector<Key> result;
        inOrderRecursive(root, result);
        return result;
    }

    vector<Key> postOrder() override
    {
        vector<Key> result;
        postOrderRecursive(root, result);
        return result;
    }

    vector<Value> values() override
    {
        vector<Value> result;
        valuesRecursive(root, result);
        return result;
    }

    vector<pair<Key, Value>> keysValues() override
    {
        vector<pair<Key, Value>> result;
        keysValuesRecursive(root, result);
        return result;
    }
};