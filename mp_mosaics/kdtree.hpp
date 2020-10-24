/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if(curDim<0||curDim>=Dim){
      return false;
    }
    if(first[curDim]<second[curDim]){
      return true;
    }else if(first[curDim]>second[curDim]){
      return false;
    }
    return first<second;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    double prev_dist = 0;
    double new_dist = 0;
    for(unsigned i = 0; i<Dim; i++){
      new_dist += pow((potential[i]-target[i]), 2);
      prev_dist += pow((currentBest[i]-target[i]), 2);
    }
    if(new_dist<prev_dist){
      return true;
    }else if(new_dist>prev_dist){
      return false;
    }
    return potential<currentBest;
}

template <int Dim>
unsigned KDTree<Dim>::partition(vector<Point<Dim>>& list, int dimension, unsigned left, unsigned right, unsigned pivotIndex){
  Point<Dim> pivotValue = list[pivotIndex];
  Point<Dim> temp = list[pivotIndex];
  list[pivotIndex] = list[right];
  list[right] = temp;
  unsigned storeIndex = left;
  for(unsigned i = left; i < right; i++){
    if(smallerDimVal(list[i], pivotValue, dimension)){
      temp = list[storeIndex];
      list[storeIndex] = list[i];
      list[i] = temp;
      storeIndex++;
    }
  }
  temp = list[right];
  list[right] = list[storeIndex];
  list[storeIndex] = temp;
  return storeIndex;
}

template <int Dim>
Point<Dim> KDTree<Dim>::quickSelect(vector<Point<Dim>>& list, int dimension, unsigned left, unsigned right, unsigned k){
  if(left==right){
    return list[left];
  }  
  unsigned pivotIndex = k;
  pivotIndex = partition(list, dimension, left, right, pivotIndex);
  if(k==pivotIndex){
    return list[k];
  }else if(k < pivotIndex){
    return quickSelect(list, dimension, left, pivotIndex-1, k);
  }else{
    return quickSelect(list, dimension, pivotIndex+1, right, k);
  }
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::buildTree(vector<Point<Dim>>& newPoints, int dimension, unsigned left, unsigned right){
  if(newPoints.size()==0||left<0||right<0||left>=newPoints.size()||right>=newPoints.size()||dimension>Dim){
    return NULL;
  }
  if(left<=right){
    unsigned middle = (left+right)/2;
    Point<Dim> curPoint = quickSelect(newPoints, dimension, left, right, middle);
    KDTreeNode* curRoot = new KDTreeNode(curPoint);
    curRoot->left = buildTree(newPoints, (dimension+1)%Dim, left, middle-1);
    curRoot->right = buildTree(newPoints, (dimension+1)%Dim, middle+1, right);
    return curRoot;
  }else{
    return NULL;
  }
}


template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    vector<Point<Dim>> myPoints;
    myPoints.assign(newPoints.begin(), newPoints.end());
    KDTreeNode* first = buildTree(myPoints, 0, 0, myPoints.size()-1);
    root = first;
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  KDTreeNode* node;
  root = node;
  copy(node, other->root);
  
}

template <int Dim>
void KDTree<Dim>::copy(KDTreeNode* node, const KDTreeNode*& othernode) {
  /**
   * @todo Implement this function!
   */
  if(othernode != NULL){
  node = new KDTreeNode(othernode->point);
  copy(node->left, othernode->left);
  copy(node->right, othernode->right);
  }
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  if(this != rhs){
    destroy(this->root);
    copy(this->root, rhs->root);
    size = rhs.size;
  }
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  if(this->root != NULL){
    destroy(this->root);
  }

}

template <int Dim>
void KDTree<Dim>::destroy(KDTreeNode* node){
  /**
   * @todo Implement this function!
   */
  if(node != NULL){
  KDTreeNode* next1 = node->left;
  KDTreeNode* next2 = node->right;
  delete node;
  node = NULL;
  destroy(next1);
  destroy(next2);
  }
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearest(const Point<Dim>& query, int dimension, KDTreeNode* curRoot) const{
  Point<Dim> nearest;
  Point<Dim> tempNearest;
  Point<Dim> next = curRoot->point;
  bool leftChecked = false;
  if(curRoot->left == NULL && curRoot->right == NULL){
      return curRoot->point;
  }
  if(smallerDimVal(query, curRoot->point, dimension)){
    if(curRoot->left == NULL){
      nearest = curRoot->point;
      leftChecked = true;
    }else{
      nearest = findNearest(query, (dimension+1)%Dim, curRoot->left);
      leftChecked = true;
    }
  }else{
    if(curRoot->right == NULL){
      nearest = curRoot->point;
      leftChecked = false;
    }else{
    nearest = findNearest(query, (dimension+1)%Dim, curRoot->right);
    leftChecked = false;
    }
  }
  if(shouldReplace(query, nearest, next)){
    nearest = next;
  }
  int rad = 0;
  for(int i = 0; i<Dim; i++){
    rad += pow(query[i]-nearest[i], 2);
  } 
  if(rad>=pow(query[dimension]-next[dimension],2)){
    if(leftChecked){
      if(curRoot->right != NULL){
        tempNearest = findNearest(query, (dimension+1)%Dim, curRoot->right);
      }else{
        tempNearest = curRoot->point;
      }
      
    }else{
      if(curRoot->left != NULL){
        tempNearest = findNearest(query, (dimension+1)%Dim, curRoot->left);
      }else{
        tempNearest = curRoot->point;
      }
    }
    if(shouldReplace(query, nearest, tempNearest)){
      nearest = tempNearest;
    }
  }
  return nearest;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    return findNearest(query, 0, root);
}

