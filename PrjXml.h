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
			std::cout << "节点名称: " << nodeName << std::endl;
			std::cout << "节点值: " << iter->second.m_value << std::endl;
			for (auto& attr : iter->second.m_attributeMap)
			{
				// 获取属性名称和值

				std::cout << "属性名称: " << attr.first << std::endl;
				std::cout << "属性值: " << attr.second << std::endl;

			}
		}
	}
private:
	std::map<std::string, XmlNode> m_nodeMap;
};


