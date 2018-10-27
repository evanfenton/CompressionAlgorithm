// file: binary_tree.cpp

#include "binary_tree.h"

BTreeNode::BTreeNode(byte_freq d, BTreeNode* z, BTreeNode* o){
	
	zero = z;
	one = o;
	node_data = d;
}

BTreeNode* BTreeNode::getZero(){
	return zero;
}
	
BTreeNode* BTreeNode::getOne(){
	return one;
}

byte_freq BTreeNode::getData(){
	return node_data;
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
	
	getNewBitPattern(root, 0, 0);
}

void BinaryTree::getNewBitPattern(BTreeNode* node, byte current, int length){
	
	// NODES WILL ALWAYS HAVE NO CHILDREN OR TWO
	if(node->getZero() != NULL){
		getNewBitPattern(node->getZero(), (current<<1), length+1);
	}
	
	if(node->getOne() != NULL){
		getNewBitPattern(node->getOne(), ((current<<1)|0x01), length+1);
	}
	else{
		huffCodes[huffIndex].bf = node->getData();
		huffCodes[huffIndex].bit_code = current;
		huffCodes[huffIndex].bit_length = length;
		huffIndex++;
	}
}

void BinaryTree::deleteTree(BTreeNode* node){
	
	BTreeNode* zeroChild = node->getZero();
	BTreeNode* oneChild = node->getOne();
	
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

huffman_code BinaryTree::getHuffcode(byte data){
	
	for(int i = 0; i < huffIndex; i++){
		
		if(data == huffCodes[i].bf.data){
			return huffCodes[i];
		}
	}
}

int BinaryTree::getNewsize(){
	
	int sum = 0;
	
	for(int i = 0; i < huffIndex; i++){
		sum += (huffCodes[i].bit_length * huffCodes[i].bf.freq);
	}
	
	new_bitlength = sum;
	
	while(sum % 8 != 0) sum++;
	
	return sum/8;
}

int BinaryTree::getNewBitlength(){
	return new_bitlength;
}

























