#include "hzpch.h"
#include "UUID.h"

#include <random>

#include <unordered_map>

namespace Hazel {

	static std::random_device s_RandomDevice;//随机数引擎的种子
	static std::mt19937_64 s_Engine(s_RandomDevice());//使用前面定义的 s_RandomDevice 作为种子初始化引擎，以生成随机数序列
	static std::uniform_int_distribution<uint64_t> s_UniformDistribution;//用于生成均匀分布的随机整数的分布式

	UUID::UUID()
		: m_UUID(s_UniformDistribution(s_Engine))
	{
	}

	UUID::UUID(uint64_t uuid)
		: m_UUID(uuid)
	{
	}

}