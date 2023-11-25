#include<iostream>
#include<list>
#include<memory>
#include<unordered_map>
constexpr int QUEUE_MAX_SIZE=3;

class CacheNode
{
	public:
		int id;
	
	CacheNode(int inpId): id(inpId) {}

	bool operator<(CacheNode& obj)
	{
		std::cout << " ==============V6P: called "<<  123456  << "==================" << std::endl;

		return (obj.id < id);
	}

	bool operator==(CacheNode& obj)
	{
		std::cout << " ==============V6P: called "<<  123456  << "==================" << std::endl;

		return (obj.id ==id);
	}
};

void handleCacheRequest(const CacheNode &cacheNode,std::unordered_map<int,std::shared_ptr<CacheNode>> &cacheHash,std::list<std::shared_ptr<CacheNode>> &cacheQueue)
{
	std::unordered_map<int,std::shared_ptr<CacheNode>>::iterator iter=cacheHash.find(cacheNode.id);

	if(iter != cacheHash.end())
	{
		std::cout << " ==============V6P: Found element in cache "<<  123456  << "==================" << std::endl;

		cacheQueue.remove(cacheHash[cacheNode.id]);
		cacheQueue.push_front(std::make_shared<CacheNode>(cacheNode));

		cacheHash[cacheNode.id]=cacheQueue.front();
	}
	else
	{
		if(cacheQueue.size() >= QUEUE_MAX_SIZE)
		{
			std::cout << " ==============V6P: Remove queue full "<<  123456  << "==================" << std::endl;

			cacheHash.erase(cacheQueue.back()->id);
			cacheQueue.pop_back();
		}
		
		cacheQueue.push_front(std::make_shared<CacheNode>(cacheNode));
		cacheHash.insert(std::make_pair(cacheNode.id,cacheQueue.front()));
	}
}

void display(std::list<std::shared_ptr<CacheNode>> &cacheQueue)
{
	for(const auto &cacheInfo : cacheQueue)
	{
			std::cout << " ==============V6P: QueueDisplay "<<  cacheInfo->id  << "==================" << std::endl;
	}
}


int main()
{
	std::list<std::shared_ptr<CacheNode>> cacheQueue;
    ;
	std::unordered_map<int,std::shared_ptr<CacheNode>> cacheHash;
	
    cacheQueue.push_back(std::make_shared<CacheNode>(1));
	cacheHash.insert(std::make_pair(1,cacheQueue.back()));

    cacheQueue.push_back(std::make_shared<CacheNode>(2));
	cacheHash.insert(std::make_pair(2,cacheQueue.back()));

    cacheQueue.push_back(std::make_shared<CacheNode>(3));
	cacheHash.insert(std::make_pair(3,cacheQueue.back()));	

	display(cacheQueue);

	CacheNode cacheObj(4);
	handleCacheRequest(cacheObj,cacheHash,cacheQueue);


	display(cacheQueue);

	CacheNode cacheObj2(2);
	handleCacheRequest(cacheObj2,cacheHash,cacheQueue);


	display(cacheQueue);


	return 0;
}
