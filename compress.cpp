// file: compress.cpp

#include "binary_tree.h"

int byte_compress( byte* data_ptr, int data_size );

void insertionSort(byte_freq* bf_ptr, int bf_size);


int main(int argc, char* argv[])
{
	byte data_ptr[] = {0x03, 0x74, 0x04, 0x04, 0x04, 0x35, 0x35, 0x64, 
					  0x64, 0x64, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00,
					  0x56, 0x45, 0x56, 0x56, 0x56, 0x09, 0x09, 0x09 };
			  
	
	int new_size = byte_compress( data_ptr, 24 );
	
}


int byte_compress( byte* data_ptr, int data_size ){
	
	// all data could be different values
	byte_freq temp_ptr[data_size];
	int temp_size = 0;
	
	byte d;
	
	// find and store frequency of all bytes
	for(int i = 0; i < data_size; i++){
		
		d = data_ptr[i];
		
		int j;
		for(j = 0; j < temp_size; j++){
			
			if(d == temp_ptr[j].data){
				temp_ptr[j].freq++;
				break;
			}
		}
		
		if(j == temp_size){
			temp_ptr[j].data = d;
			temp_ptr[j].freq = 1;
			temp_size++;
		}
	}
	
	// sort the data by frequency 
	insertionSort(temp_ptr, temp_size);
	
	int maxNode = 0, min1 = 0, min2 = 1, tmpSz = temp_size;
	BTreeNode** nodes = new BTreeNode*[tmpSz];
	BTreeNode** delete_nodes = nodes;
	BTreeNode* new_node;
	
	for(int i = 0; i < tmpSz; i++){
		nodes[i] = new BTreeNode(temp_ptr[i], NULL, NULL);
	}
	
	// create a huffman tree from the data
	maxNode = temp_ptr[tmpSz-1].freq;
	while(maxNode != data_size){
		
		min1 = 0;
		min2 = 1;
		for(int i = 2; i < tmpSz; i++){
			
			int freq = nodes[i]->getData().freq , 
			min1_freq = nodes[min1]->getData().freq , 
			min2_freq = nodes[min2]->getData().freq;
			
			if( (freq < min1_freq) ||
				(freq == min1_freq && nodes[min1]->getZero() != NULL)){
				min1 = i;
			}
			else if((freq < min2_freq) ||
					(freq == min2_freq && nodes[min1]->getZero() != NULL)){
				min2 = i;
			}
		}
		
		if(min2 < min1){
			int tmp = min1;
			min1 = min2;
			min2 = tmp;
		}
		
		byte_freq nd = {0xFF, (nodes[min1]->getData().freq) + (nodes[min2]->getData().freq)};
		
		new_node = new BTreeNode(nd, nodes[min1], nodes[min2]);
		
		nodes[min2] = new_node;
		nodes[min1] = NULL;
		
		for(int i = min1; i > 0; i--){
			nodes[i] = nodes[i-1];
		}
		nodes++;
		tmpSz--;
		
		if(new_node->getData().freq > maxNode){
			maxNode = new_node->getData().freq;
		}
		
	}
	
	// create a binary tree object with the huffman tree just made
	BinaryTree huff_tree(*nodes, temp_size);
	
	// recursively traverse huffman tree to record new
	// bit patterns of all leaf nodes holding data
	huff_tree.traverse();
	
	int new_size = huff_tree.getNewsize();
	byte* d_ptr = new byte[new_size];
	byte data;
	
	huffman_code huffCode;
	
	
	// generate new array of bytes from new bit patterns
	int b = (new_size*8)- huff_tree.getNewBitlength();
	for(int i = 0, j = 0; i < data_size; i++){
		data = data_ptr[i];
		
		huffCode = huff_tree.getHuffcode(data);
		
		if(b == 0){
			d_ptr[j] = (huffCode.bit_code << (8-huffCode.bit_length));
			b = huffCode.bit_length;
		}
		else if(8-b >= huffCode.bit_length){
			d_ptr[j] |= (huffCode.bit_code << ((8-b)-huffCode.bit_length));
			b += huffCode.bit_length;
		}
		else{
			d_ptr[j++] |= (huffCode.bit_code >> (huffCode.bit_length-(8-b)));
			d_ptr[j] = (huffCode.bit_code << ((8-huffCode.bit_length)+(8-b)));
			
			b = (huffCode.bit_length-(8-b));
		}
	}
	
	data_ptr = d_ptr;
	
	delete [] delete_nodes;
	
	return new_size;
	
}


void insertionSort(byte_freq* bf_ptr, int bf_size)
{
	
	for(int i=1, j; i< bf_size; i++){
		
		byte_freq temp = bf_ptr[i];
		
		for(j=i; j>0 && temp.freq < bf_ptr[j-1].freq; j--){
			bf_ptr[j] = bf_ptr[j-1];
		}
		bf_ptr[j] = temp;
	}
	
}












