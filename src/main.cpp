
#include <iostream>
#include "redBlackTree.h"
#include "map.h"

int main()
{
	std_selfmade::map<int,int> test;
	for(int i =0;i<100;i++){
	test.put(std::pair<int,int>(i,i));
	}
	
	// std::cout<<a.value().second<<"\n";
	std::cout<<"init begin\n";
	auto b=test.rbegin();
	std::cout<<"init end\n";
	auto e=test.rend();
	std::swap(e,b);
	std::cout<<(*(--b)).first<<"  "<<(*e).first<<"\n";
	return 0;
}

