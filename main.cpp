#include <iostream>
#include "radix_tree.h"

int main() {
	RadixTrie trie;
	std::string name;
	while (std::getline(std::cin, name)) {
		if(name.empty()){break;}
		trie.append(name);
	}
	
	trie.print_names();
	trie.print_tree();
	
	return 0;
}
