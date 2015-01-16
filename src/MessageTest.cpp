#include <iostream>
#include <stdexcept>
#include "XmlParser.h"
#include "XmlNode.h"

int main() {
    std::cout << " Testing Message Api " << std::endl;

    try {
        xmlp::XmlParser parser("/home/dev/xmlFile.xml");
        
        std::string str ;
        parser.getNode("root")->toString(str);
        std::cout << str << std::endl ;
        
        // <root name=value><child cname=cvalue /><child cname2=cvalue2 /></root>
//        messageapi::XmlNode::Ptr node(new messageapi::XmlNode("<root name1=value1 name2=value2>", messageapi::XmlNode::Ptr()));
//        node->addChild("<child cname=cvalue />");
//        node->addChild("<child cname2=cvalue2 />");
//        std::string str ;
//        node->toString(str);
//        std::cout << str << std::endl ;
        
    } catch (const std::runtime_error& err) {
        std::cout << " Caught Exception : " << err.what() << std::endl;
        return EXIT_FAILURE ;
    }

    return EXIT_SUCCESS ;

}
