#include <iostream>
#include <sstream> 
#include "BST.cpp"
#include "AVL.cpp"

using namespace std;

string BoolToText(bool boolean);
void TestBST();
void TestAVL();
string HyphenTitle(string name);

int main()
{
    TestAVL();
    return 0;
};

void TestBST()
{
    cout << "-----BST-----" << endl;
    BST<int, string> bst;

    cout << "Is tree empty: " << BoolToText(bst.isEmpty()) << endl;

    cout << endl << "-----Insert-----" << endl;
    bst.insert(50, "Fifty");
    bst.insert(30, "Thirty");
    bst.insert(70, "Seventy");
    bst.insert(20, "Twenty");
    bst.insert(40, "Forty");
    bst.insert(60, "Sixty");
    bst.insert(80, "Eighty");

    cout << "Size of tree: " << bst.size() << endl;
    cout << "Height of tree: " << bst.height() << endl;

    cout << endl << "-----Order-----" << endl;
    cout << "Pre-order traversal: ";
    for (int key : bst.preOrder()) {
        cout << key << " ";
    }
    cout << endl;

    cout << "In-order traversal: ";
    for (int key : bst.inOrder()) {
        cout << key << " ";
    }
    cout << endl;

    cout << "Post-order traversal: ";
    for (int key : bst.postOrder()) {
        cout << key << " ";
    }
    cout << endl;

    cout << "Values in the tree: ";
    for (const string& value : bst.values()) {
        cout << value << " ";
    }
    cout << endl;

    cout << "Keys and values in the tree: ";
    for (const auto& pair : bst.keysValues()) {
        cout << "(" << pair.first << ", " << pair.second << ") ";
    }
    cout << endl;

    cout << endl << "-----Search-----" << endl;
    cout << "Searching for key 10: " << bst.search(10) << endl;
    cout << "Searching for key 40: " << bst.search(40) << endl;
    cout << "Is key 70 present? " << BoolToText(bst.isElem(70)) << endl;
    cout << "Is key 90 present? " << BoolToText(bst.isElem(90)) << endl;

    cout << endl << "-----Remove-----" << endl;
    bst.remove(40);
    cout << "Size of tree after removing key 40: " << bst.size() << endl;
    cout << "Is key 40 present now? " << BoolToText(bst.isElem(40)) << endl;

    cout << "In-order traversal: ";
    for (int key : bst.inOrder()) {
        cout << key << " ";
    }
    cout << endl << endl << endl;
}

void TestAVL()
{
    cout << HyphenTitle("AVL") << endl;
    cout << endl << HyphenTitle("Insert") << endl;
    AVL<int, string> avl;
    avl.insert(10, "A");
    avl.insert(5, "B");
    avl.insert(15, "C");
    avl.insert(25, "D");
    avl.insert(2, "E");

    cout << "Is tree empty: " << BoolToText(avl.isEmpty()) << endl;
    cout << "Size of tree: " << avl.size() << endl;
    cout << "Height of tree: " << avl.height() << endl;

    cout << endl << HyphenTitle("Order") << endl;
    cout << "Pre-order traversal: ";
    for (int key : avl.preOrder()) {
        cout << key << " ";
    }
    cout << endl;

    cout << "In-order traversal: ";
    for (int key : avl.inOrder()) {
        cout << key << " ";
    }
    cout << endl;

    cout << "Post-order traversal: ";
    for (int key : avl.postOrder()) {
        cout << key << " ";
    }
    cout << endl;

    cout << "Values in the tree: ";
    for (const string& value : avl.values()) {
        cout << value << " ";
    }
    cout << endl;

    cout << "Keys and values in the tree: ";
    for (const auto& pair : avl.keysValues()) {
        cout << "(" << pair.first << ", " << pair.second << ") ";
    }
    cout << endl;

    cout << endl << HyphenTitle("Search") << endl;
    cout << "Searching for key 10: " << avl.search(10) << endl;
    cout << "Searching for key 40: " << avl.search(40) << endl;
    cout << "Is key 40 present? " << BoolToText(avl.isElem(40)) << endl;
    cout << "Is key 10 present? " << BoolToText(avl.isElem(10)) << endl;

    cout << endl << HyphenTitle("Remove") << endl;
    avl.remove(10);
    cout << "Size of tree after removing key 10: " << avl.size() << endl;
    cout << "Is key 10 present now? " << BoolToText(avl.isElem(10)) << endl;

    cout << "In-order traversal: ";
    for (int key : avl.inOrder()) {
        cout << key << " ";
    }
    cout << endl << endl;
}

string HyphenTitle(string name)
{
    int length = name.length();
    int targetLength = 25;
    int hyphenLenght = (targetLength - length) / 2;
    string hyphenTitle = string(hyphenLenght, '-') + name + string(hyphenLenght, '-');

    if (hyphenTitle.length() < targetLength) {
        hyphenTitle += '-';
    }

    return hyphenTitle;
}

string BoolToText(bool boolean)
{
    return boolean == 1 ? "True" : "False";
}