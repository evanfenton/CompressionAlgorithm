# garmin_code
Algorithm for compressing an array of bytes.

I used Huffman Coding to compress the data. Basically, I create a Huffman tree (binary tree) from the data given where each unique byte
is assigned its new bit pattern based on the frequency it appears in the data. The data is represented as leaf nodes in 
the tree (they have no child nodes). The more frequent data is higher up in the tree, while less frequent is lower. 

The path from the root to each leaf node reveals the new bit pattern of the data in the leaf node because left child links
represent a 0 bit while right child links represent a 1 bit. 

The steps to the algorithm are:
1.	Store the data with the frequency at which it appears in the data
2.	Sort the data by frequency using insertion sort
3.	Create a Huffman tree from the sorted data
4.	Recursively traverse the Huffman tree, storing the bit patterns of each unique data
5.	Generate a new array of bytes with the new bit patterns and copy it to the original
6.	Return the new length

To decompress the data, you would just feed the compressed version into the Huffman tree. 
