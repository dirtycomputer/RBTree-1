#ifndef RBTREENEW_H_INCLUDED
#define RBTREENEW_H_INCLUDED
#include<iostream>
using namespace std;
class RBTreeNode{
public:
    bool color;
    int value;
    RBTreeNode * parent,* left,*right;
public:
    RBTreeNode(){this->color=true;}
    RBTreeNode(int value){this->value=value;this->color=true;}
    RBTreeNode(int value,bool color){this->value=value; this->color=color;}
};
class RBTree{
    typedef RBTreeNode * link_type;
private:
    void init(){
        header=new RBTreeNode();
        header->color=true;
        root()=0;
        leftmost()=header;
        rightmost()=header;
    }
public:
    link_type header; //实现上的技巧
    link_type& root(){return (link_type&) header->parent;}
    link_type& left(link_type x){return (link_type&) x->left;}
    link_type& right(link_type x){return (link_type&) x->right;}
    link_type& leftmost(){return (link_type&) header->left;}
    int getvalue(link_type x){return x->value;}
    link_type& rightmost(){return (link_type&) header->right;}
    RBTree(){init();}
    void _insert(link_type x_,link_type y_,const int &v){
        link_type x=(link_type) x_;
        link_type y=(link_type) y_;
        link_type z;
        if(y==header || x!=0 || v<getvalue(y)){
            z=new RBTreeNode(v);
            left(y)=z;
            if(header==y){
                root()=z;
                rightmost()=z;
            }
            else if(y==leftmost())
                leftmost()=z;
        }
        else{
            z=new RBTreeNode(v);
            right(y)=z;
            if(y==rightmost())
                rightmost()=z;
        }
        z->parent = y;
        left(z)=0;
        right(z)=0;
        _rb_tree_rebalance(z,header->parent);
    }
    void insert_equal(const int& v){
        link_type y=header;
        link_type x=root();
        while(x!=0){
            y=x;
            x=v<x->value?left(x):right(x);
        }
        _insert(x,y,v);
    }
    void decrement(link_type& x){
        if(x->color==true &&  x->parent->parent==x){
            x=x->right;
        }
        else if(x->left!=0){
            link_type y=x->left;
            while(y->right!=0)
                y=y->right;
            x=y;
        }
        else{
            link_type y=x->parent;
            while(x==y->left){
                x=y;
                y=y->parent;
            }
            x=y;
        }
    }
     bool insert_unique(const int& v){
        link_type y=header;
        link_type x=root();
        bool result=false;
        bool comp=true;
        while(x!=0){
            y=x;
            comp=v<x->value;
            x=comp?left(x):right(x);
        }
        link_type j= y;
        if(comp){
            if(j==leftmost()){
                _insert(x,y,v);
                result=true;
            }
            else{
                decrement(j); //存在问题
            }
        }
        if(j->value<v){
            _insert(x,y,v);
            result=true;
        }
        return result;
    }
    inline void _rb_tree_rebalance(link_type x,link_type &root){
        x->color=true;
        while(x!=root && x->parent->color==true){
            if(x->parent==x->parent->parent->left){//父节点是祖父节点的左节点
                link_type y=x->parent->parent->right;
                if(y && y->color==true){
                    x->parent->color=false;
                    y->color=false;
                    x->parent->parent->color=true;
                    x=x->parent->parent;
                }
                else{//无伯父节点，或者伯父节点为黑
                    if(x==x->parent->right){
                        x=x->parent;
                        _rb_tree_rotate_left(x,root);
                    }
                    x->parent->color=false;
                    x->parent->parent->color=true;
                    _rb_tree_rotate_right(x->parent->parent,root);
                }
            }
            else{
                link_type y=x->parent->parent->left;
                if(y && y->color==true){
                    x->parent->color=false;
                    y->color=false;
                    x->parent->parent->color=true;
                    x=x->parent->parent;  //继续往上层检查
                }
                else{
                    if(x==x->parent->left){
                        x=x->parent;
                        _rb_tree_rotate_right(x,root);
                    }
                    x->parent->color=false;
                    x->parent->parent->color=true;
                    _rb_tree_rotate_left(x->parent->parent,root);
                }
            }
        }
        root->color=false;
    }
        inline void _rb_tree_rotate_left(link_type x,link_type  & root){
            link_type y=x->right;
            x->right=y->left;
            if(y->left!=0)
                y->left->parent=x;
            y->parent=x->parent;
            if(x==root)
                root=y;
            else if(x==x->parent->left)
                x->parent->left=y;
            else
                x->parent->right=y;
            y->left=x;
            x->parent=y;
        }
        inline void _rb_tree_rotate_right(link_type x,link_type  & root){
            link_type y=x->left;
            x->left=y->right;
            if(y->right!=0)
                y->right->parent=x;
            y->parent=x->parent;
            if(x==root)
                root=y;
            else if(x==x->parent->right)
                x->parent->right=y;
            else
                x->parent->left=y;
            y->right=x;
            x->parent=y;
        }

};


#endif // RBTREENEW_H_INCLUDED
