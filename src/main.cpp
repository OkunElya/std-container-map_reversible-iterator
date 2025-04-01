
#include <iostream>
#include "redBlackTree.h"
#include "map.h"

int main()
{
	std_selfmade::map<int,int> test;
	for(int i =0;i<10;i++){
		test.put(std::pair<int,int>(i,i));
	}
	
	// // std::cout<<a.value().second<<"\n";
	// auto b=test.rbegin();
	// auto e=test.rend();
	// std::swap(e,b);
	auto test1(test);
	// std::cout<<(*(--b)).first<<"  "<<(*e).first<<"\n";
	for(auto a :test)
	{
		std::cout<<a<<"\n";
	}
	for(auto a :test1)
	{
		std::cout<<a<<"\n";
	}
	std::cout<< test[2]<<"\n";
	test[2]=3;
	std::cout<< test[2]<<"\n";

	return 0;
}

