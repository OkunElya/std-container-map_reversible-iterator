#include <container_map/map.h> 
int main()
{
	std_selfmade::map<int,int> test;
	for(int i =0;i<10;i++){
		test.put(std::pair<int,int>(i,i));
	}
	
	auto test1(test);

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

