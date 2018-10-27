// file: binary_tree.h

#include <stdio.h>

typedef unsigned char byte;

struct byte_freq {
	
	byte data;
	int freq;
};

struct huffman_code {
	
	byte_freq bf;
	byte bit_code;
	int bit_length;
};

class BTreeNode{
	
	public:
	BTreeNode(byte_freq d, BTreeNode* z, BTreeNode* o);
	BTreeNode* getZero();
	BTreeNode* getOne();
	byte_freq getData();
	
	private:
	byte_freq node_data;
	BTreeNode* zero; 	// left node
	BTreeNode* one; 	// right node
};

class BinaryTree {
	
	public:
	BinaryTree(BTreeNode* r, int size);
	~BinaryTree();
	
	huffman_code getHuffcode(byte data);
	
	int getNewsize();
	int getNewBitlength();
	
	void traverse();
	
	// recursive function to get new bit patterns
	void getNewBitPattern(BTreeNode* node, byte current, int length);
	
	private:
	BTreeNode* root;
	int new_bitlength;
	int huffIndex;
	huffman_code* huffCodes;
	
	void deleteTree(BTreeNode* node);
};

