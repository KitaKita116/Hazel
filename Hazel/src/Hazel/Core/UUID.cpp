#include "hzpch.h"
#include "UUID.h"

#include <random>

#include <unordered_map>

namespace Hazel {

	static std::random_device s_RandomDevice;//��������������
	static std::mt19937_64 s_Engine(s_RandomDevice());//ʹ��ǰ�涨��� s_RandomDevice ��Ϊ���ӳ�ʼ�����棬���������������
	static std::uniform_int_distribution<uint64_t> s_UniformDistribution;//�������ɾ��ȷֲ�����������ķֲ�ʽ

	UUID::UUID()
		: m_UUID(s_UniformDistribution(s_Engine))
	{
	}

	UUID::UUID(uint64_t uuid)
		: m_UUID(uuid)
	{
	}

}