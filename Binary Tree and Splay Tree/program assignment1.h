#ifndef PROGRAM_ASSIGNMENT1_H_INCLUDED
#define PROGRAM_ASSIGNMENT1_H_INCLUDED
#include<iostream>
#include<fstream>
#include <vector>
using namespace std;
class Node{
    public:
        Node();
        int key_value;
        Node *parent;
        Node *right;
        Node *left;

};
Node::Node(){
    this->left=NULL;
    this->right=NULL;
    this->parent=NULL;
    this->key_value=0;

}
class binarytree{
    public:
        binarytree();
        ~binarytree();
        void Insert(binarytree* T, Node* z);
        void splayInsert(binarytree* T,Node *leaf);
        Node *searching(binarytree *T,int key,Node *leaf);
        void destructtree(Node *leaf);
        Node *root;
    private:
        void rightrotate(Node *x);
        void leftrotate(Node *x);
        void finding(Node *leaf);
        void splay(Node *leaf);
};
binarytree::binarytree(){
    this->root=NULL;
}
void binarytree::destructtree(Node* leaf){
    if(leaf!=NULL){
        destructtree(leaf->left);
        destructtree(leaf->right);
        delete leaf;
    }
}


binarytree::~binarytree(){
    destructtree(this->root);
}


void binarytree::Insert(binarytree* T, Node *z){
    Node* y = NULL;
    Node* x = T->root;
    while (x!=NULL){
        y = x;
        if (z->key_value < x->key_value){
            x = x->left;
        }
        else {
            x = x->right;
        }
    }
    z->parent = y;
    if (y==NULL){
        T->root=z;
    }
    else if (z->key_value < y->key_value){
        y->left = z;
    }
    else {
        y->right = z;
    }
    z->left = NULL;
    z->right = NULL;

}
void binarytree::leftrotate(Node *x){
    Node *y=x->right;
    x->right=y->left;
    if(y->left!=NULL){
        y->left->parent=x;
    }
    y->parent=x->parent;
    if(x->parent==NULL){
        root=y;
    }
    else if(x==x->parent->left){
        x->parent->left=y;
    }
    else {
        x->parent->right=y;
    }
    y->left=x;
    x->parent =y;
}
void binarytree::rightrotate(Node *x){
    Node *y=x->left;
    x->left=y->right;
    if(y->right!=NULL){
        y->right->parent = x;
    }
    y->parent=x->parent;
    if(x->parent==NULL){
        root=y;
    }
    else if(x==x->parent->right){
        x->parent->right = y;
    }
    else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}
void binarytree::splay(Node *leaf){
    if(leaf->parent==root){
        if(leaf->parent->left==leaf){
            rightrotate(leaf->parent);
        }
        else{
            leftrotate(leaf->parent);
        }
    }
    else{
        if(leaf->parent==leaf->parent->parent->left){
            if(leaf->parent->left==leaf){
                rightrotate(leaf->parent->parent);
                rightrotate(leaf->parent);
            }
            else{
                leftrotate(leaf->parent);
                rightrotate(leaf->parent);
            }
        }
        else{
            if(leaf->parent->left==leaf){
                rightrotate(leaf->parent);
                leftrotate(leaf->parent);
            }
            else{
                leftrotate(leaf->parent->parent);
                leftrotate(leaf->parent);
            }
        }
    }
}

Node *binarytree::searching(binarytree *T,int key,Node *leaf){

    if(leaf!=NULL){
        if(key==leaf->key_value){
        return leaf;
        }
        if(key<leaf->key_value){
        return searching(T,key, leaf->left);
        }
        else{
        return searching(T,key, leaf->right);
        }
    }
    else{
        return NULL;
    }
}
void binarytree::finding(Node *leaf){
    while(leaf!=root){
        splay(leaf);
    }
}
void binarytree::splayInsert(binarytree *T,Node *leaf){

    Insert(T,leaf);
    finding(searching(T,leaf->key_value,root));
}






#endif // PROGRAM_ASSIGNMENT_H_INCLUDED
