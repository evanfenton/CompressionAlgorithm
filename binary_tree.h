// file: binary_tree.h

typedef unsigned short int byte;

struct byte_freq {
	
	byte data;
	int freq;
};

class BTreeNode{
	
	public:
	BTreeNode();
	BTreeNode(byte_freq d, BTreeNode* z, BTreeNode* o);
	const BTreeNode* get_zero();
	const BTreeNode* get_one();
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
	BinaryTree(int data_size);
	~BinaryTree();
	
	void insert(byte_freq d);
	
	private:
	BTreeNode* root;
	void deleteTree(const BTreeNode* node);
	int findNextPwrOf2(int num);
	
};

