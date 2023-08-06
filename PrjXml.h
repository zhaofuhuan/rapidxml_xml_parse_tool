#pragma once
#include <iostream>
#include "rapidxml.hpp"
#include <map>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
struct XmlNode
{
	std::string  m_value;
	std::map <std::string, std::string> m_attributeMap;
	/*XmlNode& operator = ( XmlNode node)
	{
		this->m_attributeMap = node.m_attributeMap;
		this->m_node = std::move(node.m_node);
		return *this;
	}*/
};
class ProjXml
{
public:
	static ProjXml& Instance()
	{
		static ProjXml projXml;
		return projXml;
	}
	void parseNode(rapidxml::xml_node<>* node);
	int parseXml(std::string path);

	void search(std::string nodeName)
	{
		auto iter = m_nodeMap.find(nodeName);
		if (iter != m_nodeMap.end())
		{
			std::cout << "�ڵ�����: " << nodeName << std::endl;
			std::cout << "�ڵ�ֵ: " << iter->second.m_value << std::endl;
			for (auto& attr : iter->second.m_attributeMap)
			{
				// ��ȡ�������ƺ�ֵ

				std::cout << "��������: " << attr.first << std::endl;
				std::cout << "����ֵ: " << attr.second << std::endl;

			}
		}
	}
private:
	std::map<std::string, XmlNode> m_nodeMap;
};


