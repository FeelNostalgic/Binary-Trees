#ifndef SEARCHTREE_H
#define SEARCHTREE_H

template<typename Key, typename Value>
class SearchTree {
public:
    bool isEmpty() ;
    int size() ;
    int height() ;
    void insert(Key k, Value v) ;
    Value search(Key k) ;
    bool isElem(Key k) ;
    void remove(Key k) ;
    std::vector<Key> inOrder() ;
    std::vector<Key> postOrder() ;
    std::vector<Key> preOrder() ;
    std::vector<Value> values() ;
    std::vector< std::pair<Key, Value>> keysValues() ;
};

#endif // SEARCHTREE_H