#include <iostream>
#include <stdexcept>
#include "XmlParser.h"
#include "XmlNode.h"

int main(int argc, char** argv) {

    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <XmlFileAbsPath>" << std::endl;
        return EXIT_FAILURE;
    }

    try {

//        xmlp::XmlParser parser(argv[1]);
//
        std::string str;
//        parser.getXmlContentAsString(str);
//        std::cout << str << std::endl;
        
        
        xmlp::XmlParser parser1("<root><node1 attr=value ></node1><node2 attr2='value is'></node2></root>");

        str.clear();
        parser1.getXmlContentAsString(str);
        std::cout << str << std::endl;
        
        

    } catch (const std::runtime_error& err) {
        std::cout << " Caught Exception : " << err.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;

}
