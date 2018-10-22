// file: binary_tree.cpp

#include "binary_tree.h"
#include <stdio.h>


BTreeNode::BTreeNode(){
	
	zero = NULL;
	one = NULL;
	node_data.data = 0xFF;
	node_data.freq = 0;
	
}

BTreeNode::BTreeNode(byte_freq d, BTreeNode* z, BTreeNode* o){
	
	zero = z;
	one = o;
	node_data = d;
	
}

BTreeNode* BTreeNode::get_zero(){
	return zero;
}
	
BTreeNode* BTreeNode::get_one(){
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
	


BinaryTree::BinaryTree(BTreeNode* r, int size){
	
	root = r;
	huffCodes = new huffman_code[size];
	huffIndex = 0;
}

BinaryTree::~BinaryTree(){
	
	deleteTree(root);
	delete [] huffCodes;
}



void BinaryTree::traverse(){
	
	recursive(root, 0, 0);
}


void BinaryTree::recursive(BTreeNode* node, byte current, int length){
	
	if(node->get_zero() != NULL){
		recursive(node->get_zero(), current, length+1);
	}
	
	if(node->get_one() != NULL){
		recursive(node->get_one(), ((current<<1)|0x01), length+1);
	}
	else{
		
		printf("DATA: %d\nBIT CODE: 0x%02X\nLENGTH OF CODE: %d\n\n",
		node->get_data().data, current, length);
		
		huffCodes[huffIndex].data = node->get_data().data;
		huffCodes[huffIndex].bit_code = current;
		huffCodes[huffIndex].bit_length = length;
	}
}


void BinaryTree::deleteTree(BTreeNode* node){
	
	BTreeNode* zeroChild = node->get_zero();
	BTreeNode* oneChild = node->get_one();
	
	if(zeroChild != NULL){
		deleteTree(zeroChild);
	}
	
	if(oneChild != NULL){
		deleteTree(oneChild);
	}
	else{
		delete node;
	}
}

































