// file: binary_tree.h

typedef unsigned short int byte;

struct byte_freq {
	
	byte data;
	int freq;
};

struct huffman_code {
	
	byte data, bit_code;
	int bit_length;
};

class BTreeNode{
	
	public:
	BTreeNode();
	BTreeNode(byte_freq d, BTreeNode* z, BTreeNode* o);
	BTreeNode* get_zero();
	BTreeNode* get_one();
	byte_freq get_data();
	void set_data(byte_freq d);
	
	void set_zero(BTreeNode* z);
	void set_one(BTreeNode* o);
	
	private:
	byte_freq node_data;
	BTreeNode* zero; // left node
	BTreeNode* one; // right node
};

class BinaryTree {
	
	public:
	BinaryTree(BTreeNode* r, int size);
	~BinaryTree();
	
	void traverse();
	
	void recursive(BTreeNode* node, byte current, int length);
	
	private:
	BTreeNode* root;
	void deleteTree(BTreeNode* node);
	int findNextPwrOf2(int num);
	
	int huffIndex;
	
	huffman_code* huffCodes;
	
};

