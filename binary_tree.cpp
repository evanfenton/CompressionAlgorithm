// file: binary_tree.cpp

#include "binary_tree.h"
#include <math.h>


BTreeNode::BTreeNode(int f){
	
	zero = NULL;
	one = NULL;
	node_data.data = 0xFF;
	node_data.freq = f;
	
}

const BTreeNode* BTreeNode::get_zero(){
	return zero;
}
	
const BTreeNode* BTreeNode::get_one(){
	return one;
}

byte_freq BTreeNode::get_data(){
	return node_data;
}

void BTreeNode::set_data(byte_freq d){
	node_data = d;
}

void BTreeNode::set_zero(BTreeNode* z){
	zero = z;
}

void BTreeNode::set_one(BTreeNode* o){
	one = o;
}
	


BinaryTree::BinaryTree(int data_size){
	
	root = new BTreeNode(data_size);
	
	int nxt = findNextPwrOf2(data_size);
	
	if(nxt == data_size){
		
		root->set_zero(new BTreeNode(nxt/2));
		root->set_one(new BTreeNode(nxt/2));
	}
	else if( data_size-nxt == findNextPwrOf2(data_size-nxt) ){
		
		root->set_zero(new BTreeNode(data_size-nxt));
		root->set_one(new BTreeNode(nxt));
	}
	else{
		
		root->set_zero(new BTreeNode(nxt));
		root->set_one(new BTreeNode(data_size-nxt));
	}
	
}





BinaryTree::~BinaryTree(){
	
	
}
	
void BinaryTree::insert(byte_freq d){
	
	
}


int BinaryTree::findNextPwrOf2(int num){
	
	int i = 0, maxPwr = 1;
	while(pow(2,i) <= num){
		
		if(pow(2,i) > maxPwr){ 
			maxPwr = pow(2,i); 
		}
		i++;
	}
	
	return maxPwr;
}


void BinaryTree::deleteTree(const BTreeNode* node){
	
	
}

































