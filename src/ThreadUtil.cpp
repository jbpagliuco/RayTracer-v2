#include <ThreadUtil.h>

#include <map>
#include <Windows.h>

namespace RT
{
	std::map<U32, U32> indexMap;

	void MapThreadIndex(U32 systemId, U32 threadId)
	{
		indexMap[systemId] = threadId;
	}
	
	U32 GetThreadIndex()
	{
		return indexMap.at(GetCurrentThreadId());
	}
}