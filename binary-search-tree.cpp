#include "binary-search-tree.h"
#include <iostream>
#include <queue>

typedef BinarySearchTree::DataType DataType;
typedef BinarySearchTree::Node Node;

using namespace std;

BinarySearchTree::Node::Node(DataType newval)
{
    val = newval;
    left = nullptr;
    right = nullptr;
}

int BinarySearchTree::getNodeDepth(Node* node) const
{
    if (node == nullptr)
        return 0;
    else{
        int ld = getNodeDepth(node->left);
        int rd = getNodeDepth(node->right);
        if (ld > rd)
            return (ld + 1);
        else
            return (rd + 1);
    }
}

BinarySearchTree::BinarySearchTree()
{
    size_ = 0;
    root_ = nullptr;
}

BinarySearchTree::~BinarySearchTree()
{
    deleteNode(root_);
}

void BinarySearchTree::deleteNode(Node* n){
    if(n){
        deleteNode(n->left);
        deleteNode(n->right);
        delete n;
    }
}

unsigned int BinarySearchTree::size() const
{
    return size_;
}

DataType BinarySearchTree::max() const
{
    Node* current = root_;
    while(current->right != nullptr){
        current = current->right;
    }
    return current->val;
}

DataType BinarySearchTree::min() const
{
    Node* current = root_;
    while(current->left != nullptr){
        current = current->left;
    }
    return current->val;
}

unsigned int BinarySearchTree::depth() const
{
    return (getNodeDepth(root_) - 1);
}

void BinarySearchTree::print() const
{
    print(root_);
}

void BinarySearchTree::print(Node* T) const
{
    if (T == nullptr) return;
    cout << T->val << "\n";
    print(T->left);
    print(T->right);
}

bool BinarySearchTree::exists(DataType val) const
{
    Node* current = root_;
    while(current != nullptr){
        if (current->val == val)
            return true;
        if (current->val < val)
            current = current->right;
        else
            current = current->left;
    }
    return false;
}

Node* BinarySearchTree::getRootNode()
{
    return root_;
}

Node** BinarySearchTree::getRootNodeAddress()
{
    return &root_;
}

bool BinarySearchTree::insert(DataType val)
{
    Node* insert = new Node(val);
    if (root_ == nullptr){
        root_ = insert;
        size_++;
        return true;
    }
    if (exists(val))
        return false;

    Node* current = root_;
    Node* previous = nullptr;

    while (current != nullptr){
        previous = current;
        if(val < current->val)
            current = current->left;
        else
            current = current->right;
    }

    if (val < previous->val)
        previous->left = insert;
    else
        previous->right = insert;

    size_++;
    return true;
}

Node* findPredecessor(Node* ptr) {
    Node* temp = ptr->left;
    while (temp->right != nullptr){
        temp = temp->right;
    }
    return temp;
}

Node* BinarySearchTree::RecursiveDelete(Node* current, DataType val){
    if(current == nullptr)
        return nullptr;

    if(current->val < val)
        current->right = RecursiveDelete(current->right, val);
    else if(current->val > val)
        current->left = RecursiveDelete(current->left, val);

    else{
        if(current->left == nullptr && current->right == nullptr){
            current = nullptr;
            delete current;
            return nullptr;
        }
        else if (current->right == nullptr){
            Node* a = current->left;
            delete current;
            return a;
        }
        else if(current->left == nullptr){
            Node* b = current->right;
            delete current;
            return b;
        }
        Node* c = findPredecessor(current);
        current->val = c->val;
        current->left = RecursiveDelete(current->left, c->val);
    }
    return current;
}

bool BinarySearchTree::remove(DataType val){
    if (exists(val) && size_ !=0){
        RecursiveDelete(root_, val);
        if (size_ == 1){
            root_ = nullptr;
        }
        size_--;
        return true;
    }
    return false;
}
