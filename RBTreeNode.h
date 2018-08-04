#include <iostream>
typedef bool rbtree_colortype;
const rbtree_colortype rbtreeRed=false;
const rbtree_colortype rbtreeBlack=true;
class RBTreeNode_Base{
	typedef rbtree_colortype color_type;
	typedef RBTreeNode_Base * base_ptr;

	color_type color;
	base_ptr parent;
	base_ptr left;
	base_ptr right;

	static base_ptr minimum(base_ptr x){
		while(x->left!=0)
			x=x->left;
		return x;
	}

	static base_ptr minimum(base_ptr x){
		while(x->right!=0)
			x=x->right;
		return x;
	}
}
template<class Value>
class RBTreeNode:public RBTreeNode_Base
{
	typedef RBTreeNode<Value>* link_type;
	Value value_field;
}

base_ptr node;
void increment(){
	if(node->right!=0){
		node=node->right;
		while(node->left!=0)
			node=node->left; //如果有右子节点，右走到尽头再向左边走
	}
	else{
		base_ptr y=node->parent;//如果没有右子节点，则寻找其父节点
		while(node == y->right){
			node=y;
			y=y->parent;
		}
		if(node->right!=y)
			node=y;
	}
}

void decrement(){
	if(node->color==rbtreeRed && node->parent->parent==node)
		node=node->right;
	else if(node->left!=0){
		base_ptr y=node->left；
		while(y->right!-0)
			y=y->right;
		node=y;
	}
	else{
		base_ptr y=node->parent;
		while(node==y->left){
			node=y;
			y=y->parent;
		}
		node=y;
	}
}

RBTreeNode& operator++() { increment(); return *this;}
RBTreeNode operator++(int){
	self tmp=*this;
	increment();
	return tmp;
}

RBTreeNode& operator--() { decrement(); return *this;}
RBTreeNode operator--(int){
	self tmp=*this;
	decrement();
	return tmp;
}


template<class Value>
class RBTree{
protected:
	typedef rbtree_colortype color_type;
	typedef RBTreeNode_Base * base_ptr;
	typedef RBTreeNode<Value> RBTreeNode;
	typedef rbtree_colortype color_type; 
public:
	typedef Key key_type; //?
	typedef Value value_type;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef RBTreeNode<Value>* link_type;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
protected:
	link_type get_node(){return (link_type)malloc(sizeof(RBTreeNode_Base));}
	void put_node(link_type p){free(p);}

	link_type create_node(const value_type& x){
		link_type tmp=get_node();
		tmp->value_field=x;
		return tmp; //?异常处理
	}
	link_type clone_node(link_type x){
		link_type tmp=create_node(x->value_field);
		tmp->color=x->color;
		tmp->left=0;
		tmp->right=0;
		return tmp;
	}
	void destroy_node(link_type p){
		destroy(&p->value_field);
		put_node(p);
	}
protected:
	size_type node_count;
	link_type header; //实现上的一个技巧
	Compare key_compare; //节点间的键值比较准则，function object.	

	link_type& root() const {return (link_type&) header->parent;}
	link_type& leftmost() const {return (link_type&) header->left;}
	link_type& rightmost() const {return (link_type&) header->right;}

	static link_type& left(link_type x){ return (link_type&)(x->left);}
	static link_type& right(link_type x){ return (link_type&)(x->right);}
	static link_type& left(link_type x){ return (link_type&)(x->left);}
	static reference value(link_type x){return x->value_field;}
	//static const Key& key(link_type x){return KeyOfValue() (value(x));}
	static color_type&  color(link_type x){return (color_type&) (x->color);}
	static link_type& left(base_ptr x){return (link_type&) x->left;}
	static link_type& right(base_ptr x){return (link_type&) x->right;}
	static link_type& parent(base_ptr x){return (link_type&) x->parent;}
	static reference value(base_ptr x){return ((link_type&)x)->value_field;}
	static const Key& key(base_ptr x){return KeyOfValue()(value(link_type(x)));}
	static color_type& color(base_ptr x){return (color_type&)(link_type(x)->color);}

	static link_type minimum(link_type x){
		return (link_type) RBTreeNode_Base::minimum(x);
	}

	static link_type maximum(link_type x){
		return (link_type) RBTreeNode_Base::maximum(x);
	}
private:
	iterator _insert(base_ptr x,base_ptr y,const value_type& v);
	link_type _copy(link_type x,link_type p);
	void _erase(link_type x);
	void init(){
		header=get_node();
		color(header)=rbtreeRed;
		root()=0;
		leftmost()=header;
		rightmost()=header;
	}
public:
	RBTree(const Compare& comp=Compare()):node_count(0),key_compare(comp) {init();}
	~RBTree(){clear(); put_node(header);}
public:
	Compare key_comp() const{return key_compare;}
	iterator begin(){return leftmost();}
	iterator end() {return header;}
	bool empty() const{return node_count;}
	size_type size() const {return node_count;}
	size_type max_size() const {return size_type(-1);}
};

RBTree<Value>::insert_equal(const Value& v){
	link_type y=header;
	link_type x=root();
	while(x!=0){
		y=x;
		x=key_compare(KeyOfValue()(v),key(x))?left(x):right(x);
	}
	return _insert(x,y,v);
}

RBTree<Value>::insert_unique(const Value& v){
	link_type y=hader;
	link_type x=root();
	bool comp=true;
	while(x!=0){
		y=x;
		comp=key_compare(KeyOfValue()(v),key(x));
		x=comp?left(x):right(x);
	}
	iterator j=iterator (y);
	if(comp)
		if(j==begin())
			return pair<iterator,bool> (_insert(x,y,v),true);
		else:
			--j;
	if(key_compare(key(j.node),KeyOfValue()(v)))
		return pair<iterator,bool>(_insert(x,y,z),true);
	return pair<iterator,bool>(j,false);
}

RBTree<Value>::_insert(base_ptr x_,base_ptr y_,const Value &v){
	link_type x=(link_type) x_;
	link_type y=(link_type) y_;
	link_type z;

	if(y==header || x!=0 || key_compare(KeyOfValue()(v),key(y))){
		z=create_node(v);
		left(y)=z;
		if(y==header){
			root()=z;
			rightmost()=z;
		}
		else if(y==leftnost())
			leftmost()=z;
	}
	else{
		z=create_node(v);
		right(y)=z;
		if(y==rightmost())
			rightmost()=z;
	}
	parent(z)=y;
	left(z)=0;
	right(z)=0;
	_rb_tree_rebalance(z,header->parent);
	++node_count;
	return iterator(z);
}