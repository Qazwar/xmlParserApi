#include <iostream>
#include <stdexcept>
#include "XmlParser.h"
#include "XmlNode.h"

int main() {
    std::cout << " Testing Message Api " << std::endl;

    try {
        xmlp::XmlParser parser("/home/dev/xmlFile.xml");
        
        std::string str ;
        parser.getXmlContentAsString(str);
        std::cout << str << std::endl ;
        
//        xmlp::XmlNode node;
//        std::string str = "value1 attr2='my string'" ;
//        std::string attrVal ;
//        
////        node.getAttrValue(str, attrVal);
////        std::cout << " remaining String: " << str << std::endl ;
////        std::cout << " Attr Value: " << attrVal << std::endl ;
//        
//        str = "\"my string\"" ;
//        node.getAttrValue(str, attrVal);
//        std::cout << " remaining String: " << str << std::endl ;
//        std::cout << " Attr Value: " << attrVal << std::endl ;
        
    } catch (const std::runtime_error& err) {
        std::cout << " Caught Exception : " << err.what() << std::endl;
        return EXIT_FAILURE ;
    }

    return EXIT_SUCCESS ;

}
