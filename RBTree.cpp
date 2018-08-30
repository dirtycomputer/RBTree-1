#include "RBTREENEW.h"
void print(RBTreeNode* root){
    if(root){
        cout<<root->value<<boolalpha<<root->color<<" ";
        if(root->left)
            cout<<root->left->value<<" ";
        else
            cout<<"NULL"<<" ";
        if(root->right)
            cout<<root->right->value<<" ";
        else
            cout<<"NULL"<<" ";
        if(root->parent)
            cout<<root->parent->value<<" ";
        else
            cout<<"header"<<" ";
        cout<<";";
    }
}
void preOrder(RBTreeNode * root){
    if(root){
        print(root);
        preOrder(root->left);
        preOrder(root->right);
    }
}
void midOrder(RBTreeNode * root){
    if(root){
        midOrder(root->left);
        print(root);
        midOrder(root->right);
    }
}
void behOrder(RBTreeNode * root){
    if(root){
        behOrder(root->left);
        behOrder(root->right);
        print(root);
    }
}
int main()
{
    RBTree itree;
    itree.insert_unique(10);
    itree.insert_unique(7);
    itree.insert_unique(8);
    itree.insert_unique(15);
    itree.insert_unique(5);
    itree.insert_unique(6);
    itree.insert_unique(11);
    itree.insert_unique(13);
    itree.insert_unique(12);
    preOrder(itree.header->parent);
    cout<<endl;
    midOrder(itree.header->parent);
    cout<<endl;
    behOrder(itree.header->parent);
    return 0;
}
