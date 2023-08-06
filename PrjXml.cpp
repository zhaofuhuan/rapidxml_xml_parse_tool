#include "PrjXml.h"


void ProjXml::parseNode(rapidxml::xml_node<>* node)
{
	if (!node)
	{
		return;
	}
	std::cout << "节点名称: " << node->name() << std::endl;
	std::cout << "节点值: " << node->value() << std::endl;
	XmlNode xmlNode;
	xmlNode.m_value = node->value();

	for (rapidxml::xml_attribute<>* attr = node->first_attribute(); attr; attr = attr->next_attribute())
	{
		// 获取属性名称和值
		std::cout << "属性名称: " << attr->name() << std::endl;
		std::cout << "属性值: " << attr->value() << std::endl;
		xmlNode.m_attributeMap.insert({ attr->name(), attr->value() });
	}

	m_nodeMap.insert({ node->name(), xmlNode });

	parseNode(node->first_node());
	node = node->next_sibling();
	if (node)
	{
		parseNode(node);
	}
}

int ProjXml::parseXml(std::string path)
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
