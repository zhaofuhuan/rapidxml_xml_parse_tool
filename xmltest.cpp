// xmlTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "rapidxml.hpp"
#include <map>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
struct XmlNode
{
	std::shared_ptr<rapidxml::xml_node<>> m_node;
	std::map <std::string, std::string> m_attributeMap;
};

class ProjXml
{
public:
	static ProjXml& Instance()
	{
		static ProjXml projXml;
		return projXml;
	}
	void parseNode(rapidxml::xml_node<>* node)
	{
		if (!node)
		{
			return;
		}
		std::cout << "节点名称: " << node->name() << std::endl;
		std::cout << "节点值: " << node->value() << std::endl;
		XmlNode xmlNode;
		

		xmlNode.m_node = std::shared_ptr<rapidxml::xml_node<>>(node);

		for (rapidxml::xml_attribute<>* attr = node->first_attribute(); attr; attr = attr->next_attribute()) 
		{
			// 获取属性名称和值

			std::cout << "属性名称: " << attr->name() << std::endl;
			std::cout << "属性值: " << attr->value() << std::endl;
			xmlNode.m_attributeMap.insert({ attr->name(), attr->value()});
		}

		m_nodeMap.insert({ node->name(), xmlNode });

		parseNode(node->first_node());
		node = node->next_sibling();
		if (node)
		{
			parseNode(node);
		}
	}

	int parseXml(std::string path)
	{
		std::ifstream file(path);
		if (!file) {
			std::cout << "无法打开xml文件." << std::endl;
			return 0;
		}

		// 将XML文件内容读取到内存中
		std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		buffer.push_back('\0'); // 添加终止符

		// 创建XML文档对象
		rapidxml::xml_document<> doc;
		try {
			// 解析XML文件
			doc.parse<0>(&buffer[0]);
		}
		catch (rapidxml::parse_error& e) {
			std::cout << "XML解析错误: " << e.what() << std::endl;
			return 0;
		}

		// 获取根节点
		rapidxml::xml_node<>* rootNode = doc.first_node();
		if (rootNode == nullptr) {
			std::cout << "XML文件为空." << std::endl;
			return 0;
		}

		// 遍历子节点
		//for (rapidxml::xml_node<>* node = rootNode->first_node(); node; node = node->next_sibling()) {
		//    // 获取节点名称和值
		//    std::cout << "节点名称: " << node->name() << std::endl;
		//    std::cout << "节点值: " << node->value() << std::endl;

		//    // 遍历节点的属性
		//    for (rapidxml::xml_attribute<>* attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
		//        // 获取属性名称和值
		//        std::cout << "属性名称: " << attr->name() << std::endl;
		//        std::cout << "属性值: " << attr->value() << std::endl;
		//    }

		//    std::cout << std::endl;
		//}

		parseNode(rootNode);
		return 1;
	}

	void search(std::string nodeName)
	{
		auto iter = m_nodeMap.find(nodeName);
		if (iter != m_nodeMap.end())
		{
			std::cout << "节点名称: " << nodeName << std::endl;
			std::cout << "节点值: " << iter->second.m_node->value() << std::endl;
			for (auto&  attr:iter->second.m_attributeMap)
			{
				// 获取属性名称和值

				std::cout << "属性名称: " << attr.first<< std::endl;
				std::cout << "属性值: " << attr.second<< std::endl;
				
			}
		}
	}
private:
	std::map<std::string, XmlNode> m_nodeMap;
};

int main() {
    // 打开XML文件
	ProjXml::Instance().parseXml("settingdata.xml");
	/*输出一个名字为ID的节点 输出它的所有的属性信息*/
	ProjXml::Instance().search("ID");
    return 0;
}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
