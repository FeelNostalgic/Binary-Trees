#include <iostream>
#include <vector>
#include <utility>
#include "SearchTree.h"

using namespace std;

template <typename Key, typename Value>
class AVL : public SearchTree<Key, Value>
{
private:
    struct Node
    {
        Key key;
        Value value;
        int height;
        Node* left;
        Node* right;

        Node(Key key, Value value) : key(key), value(value), height(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    int getHeight(Node* node)
    {
        return node ? node->height : 0;
    }

    void setHeight(Node* node)
    {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }

    bool rightLeaning(Node* node)
    {
        return getHeight(node->left) <= getHeight(node->right);
    }

    bool leftLeaning(Node* node)
    {
        return getHeight(node->left) >= getHeight(node->right);
    }

    Node* rotateRight(Node* node)
    {
        Node* newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;

        setHeight(node);
        setHeight(newRoot);

        return newRoot;
    }

    Node* rotateLeft(Node* node)
    {
        Node* newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;

        setHeight(node);
        setHeight(newRoot);

        return newRoot;
    }

    Node* balance(Node* node)
    {
        int lh = getHeight(node->left);
        int rh = getHeight(node->right);

        Node* balanced;

        if (lh - rh > 1 && leftLeaning(node->left))
        {
            balanced = rotateRight(node);
        }
        else if (lh - rh > 1)
        {
            node->left = rotateLeft(node->left);
            balanced = rotateRight(node);
        }
        else if (rh - lh > 1 && rightLeaning(node->right))
        {
            balanced = rotateLeft(node);
        }
        else if (rh - lh > 1)
        {
            node->right = rotateRight(node->right);
            balanced = rotateLeft(node);
        }
        else
        {
            balanced = node;
            setHeight(node);
        }

        return balanced;
    }

    int sizeRecursive(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return 1 + sizeRecursive(node->left) + sizeRecursive(node->right);
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
            node = new Node(key, value);
        else if (node->key == key)
            node->value = value;
        else if (node->key > key)
        {
            node->left = insertRecursive(node->left, key, value);
            node = balance(node);
        }
        else
        {
            node->right = insertRecursive(node->right, key, value);
            node = balance(node);
        }
        return node;
    }

    Value searchRecursive(Node* node, Key key)
    {
        if (node == nullptr) return Value();
        else if (node->key == key) return node->value;
        else if (node->key > key) return searchRecursive(node->left, key);
        else return searchRecursive(node->right, key);
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
            // Case 1: Node with 0 or 1 child
            if (node->left == nullptr || node->right == nullptr)
            {
                Node* temp = (node->left != nullptr) ? node->left : node->right;
                // Case leaf node
                if (temp == nullptr)
                {
                    temp = node;
                    node = nullptr;
                }
                else
                { // Case 1 child
                    *node = *temp;
                }
                delete temp;
            }
            // Case 2: Node With two children
            else
            {
                Node* temp = minValueNode(node->right);
                node->key = temp->key;
                node->right = deleteRecursive(node->right, temp->key);
            }
        }

        //Update height
        setHeight(node); 
        //Rebalance
        balance(node);

        return node;
    }

    Node* minValueNode(Node* node)
    {
        Node* current = node;
        while (current->left != nullptr)
        {
            current = current->left;
        }
        return current;
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
    AVL() : root(nullptr) {}
    ~AVL() {};

    bool isEmpty() override
    {
        return root == nullptr;
    }

    int size() override
    {
        return sizeRecursive(root);
    }

    int height() override
    {
        return root->height;
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