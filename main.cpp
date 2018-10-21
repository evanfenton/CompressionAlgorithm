// file: main.cpp

#include <iostream>
#include <stdio.h>
#include "binary_tree.h"

using namespace std;


int byte_compress( byte* data_ptr, int data_size );

void insertionSort(byte_freq* bf_ptr, int bf_size);

void display(byte_freq* bf_ptr, int bf_size);


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
	byte_freq bf = *temp_ptr;
	
	// find and store frequency of all bytes
	for(int i = 0; i < data_size; i++){
		
		d = data_ptr[i];
		
		int j;
		for(j = 0; j < temp_size; j++){
			
			if(d == temp_ptr[j].data){
				//printf("REPEAT 0x%02X\n", d);
				temp_ptr[j].freq++;
				
				printf("REPEAT 0x%02X \t NEW FREQ: %d\n", d, temp_ptr[j].freq);
				break;
			}
		}
		
		if(j == temp_size){
			printf("NEW 0x%02X\n", d);
			temp_ptr[j].data = d;
			temp_ptr[j].freq = 1;
			temp_size++;
		}
	}
	
	// sort the data by frequency and display 
	insertionSort(temp_ptr, temp_size);
	//display(temp_ptr, temp_size);
	
	
	
	// create huffman tree
	int maxNode = 0, min1 = 0, min2 = 1, tmpSz = temp_size;
	BTreeNode** nodes = new BTreeNode*[tmpSz];
	BTreeNode* new_node;
	
	for(int i = 0; i < tmpSz; i++){
		nodes[i] = new BTreeNode(temp_ptr[i], NULL, NULL);
	}
	
	maxNode = temp_ptr[tmpSz-1].freq;
	while(maxNode != data_size){
		
		min1 = 0;
		min2 = 1;
		for(int i = 2; i < tmpSz; i++){
			
			int freq = nodes[i]->get_data().freq , 
			min1_freq = nodes[min1]->get_data().freq , 
			min2_freq = nodes[min2]->get_data().freq;
			
			if( (freq < min1_freq) ||
				(freq == min1_freq && nodes[min1]->get_zero() != NULL)){
				min1 = i;
			}
			else if((freq < min2_freq) ||
					(freq == min2_freq && nodes[min1]->get_zero() != NULL)){
				min2 = i;
			}
		}
		
		if(min2 < min1){
			int tmp = min1;
			min1 = min2;
			min2 = tmp;
		}
		
		byte_freq nd = {0xFF, (nodes[min1]->get_data().freq) + (nodes[min2]->get_data().freq)};
		
		new_node = new BTreeNode(nd, nodes[min1], nodes[min2]);
		
		nodes[min2] = new_node;
		
		nodes++;
		tmpSz--;
		
		if(new_node->get_data().freq > maxNode){
			maxNode = new_node->get_data().freq;
		}
		
	}
	
	
	
	return data_size;
	
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


void display(byte_freq* bf_ptr, int bf_size)
{
	cout << endl;
	
	for(int i = 0; i < bf_size; i++)
	{
		printf("0x%02X \t %d\n", bf_ptr[i].data, bf_ptr[i].freq);
	}
	
}










