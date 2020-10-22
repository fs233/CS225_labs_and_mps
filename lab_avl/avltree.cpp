/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{ 
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node*& mid = t->right;
    t->right = mid->left;
    mid->left = t;
    t = mid; 
    t->height = 1+std::max(heightOrNeg1(t->left), heightOrNeg1(t->right));
    t->left->height = 1+std::max(heightOrNeg1(t->left->left), heightOrNeg1(t->left->right));
}
template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* mid = t->left;
    t->left = mid->right;
    mid->right = t;
    t = mid; 
    t->height = 1+std::max(heightOrNeg1(t->left), heightOrNeg1(t->right));
    t->right->height = 1+std::max(heightOrNeg1(t->right->left), heightOrNeg1(t->right->right));
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    if(subtree == NULL){
        return;
    }
    int bal = heightOrNeg1(subtree->right)-heightOrNeg1(subtree->left);
    if(bal==-2){ 
        int lbal = heightOrNeg1(subtree->left->right)-heightOrNeg1(subtree->left->left);
        
        if(lbal==-1){
            rotateRight(subtree);
           
        }else{
            rotateLeftRight(subtree);
            
        }
    }else if(bal == 2){
        int rbal = heightOrNeg1(subtree->right->right)-heightOrNeg1(subtree->right->left);
        
        if(rbal==1){
            rotateLeft(subtree);
            
        }else{
            rotateRightLeft(subtree);
            
        }
    }
    subtree->height = 1+std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{   
    if(subtree == NULL){
        subtree = new Node(key, value);
    }
    if(key > subtree->key){
        insert(subtree->right, key, value);
    }else if(key < subtree->key){
        insert(subtree->left, key, value);
    }
    rebalance(subtree);
    // your code here
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{   
    if (subtree == NULL){
        return;
    }
    if (key < subtree->key) {
        remove(subtree->left, key);
        // your code here
    } else if (key > subtree->key) {
        remove(subtree->right, key);
        // your code here
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node* temp = subtree->left;
            while(temp->right != NULL){
                temp = temp->right;
            }
            Node* iop = temp;
            swap(iop, subtree);
            remove(subtree->left, key);
        } else {
            /* one-child remove */
            // your code here
            Node* left = subtree->left;
            Node* right = subtree->right;
            if(left != NULL){
                swap(left, subtree);
                remove(subtree->left, key);
            }else if(right != NULL){
                swap(right, subtree);
                remove(subtree->right, key);
            }
        }
        
        // your code here
    }
    rebalance(subtree);
}
