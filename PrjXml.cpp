#include "PrjXml.h"


void ProjXml::parseNode(rapidxml::xml_node<>* node)
{
	if (!node)
	{
		return;
	}
	std::cout << "�ڵ�����: " << node->name() << std::endl;
	std::cout << "�ڵ�ֵ: " << node->value() << std::endl;
	XmlNode xmlNode;
	xmlNode.m_value = node->value();

	for (rapidxml::xml_attribute<>* attr = node->first_attribute(); attr; attr = attr->next_attribute())
	{
		// ��ȡ�������ƺ�ֵ
		std::cout << "��������: " << attr->name() << std::endl;
		std::cout << "����ֵ: " << attr->value() << std::endl;
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
		std::cout << "�޷���xml�ļ�." << std::endl;
		return 0;
	}

	// ��XML�ļ����ݶ�ȡ���ڴ���
	std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	buffer.push_back('\0'); // �����ֹ��

	// ����XML�ĵ�����
	rapidxml::xml_document<> doc;
	try {
		// ����XML�ļ�
		doc.parse<0>(&buffer[0]);
	}
	catch (rapidxml::parse_error& e) {
		std::cout << "XML��������: " << e.what() << std::endl;
		return 0;
	}

	// ��ȡ���ڵ�
	rapidxml::xml_node<>* rootNode = doc.first_node();
	if (rootNode == nullptr) {
		std::cout << "XML�ļ�Ϊ��." << std::endl;
		return 0;
	}

	// �����ӽڵ�
	//for (rapidxml::xml_node<>* node = rootNode->first_node(); node; node = node->next_sibling()) {
	//    // ��ȡ�ڵ����ƺ�ֵ
	//    std::cout << "�ڵ�����: " << node->name() << std::endl;
	//    std::cout << "�ڵ�ֵ: " << node->value() << std::endl;

	//    // �����ڵ������
	//    for (rapidxml::xml_attribute<>* attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
	//        // ��ȡ�������ƺ�ֵ
	//        std::cout << "��������: " << attr->name() << std::endl;
	//        std::cout << "����ֵ: " << attr->value() << std::endl;
	//    }

	//    std::cout << std::endl;
	//}

	parseNode(rootNode);
	return 1;
}
