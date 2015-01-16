/* 
 * File:   XmlParser.h
 * Author: dev
 *
 * Created on 9 January, 2015, 1:09 AM
 */

#ifndef XMLPARSER_H
#define	XMLPARSER_H

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <XmlNode.h>


namespace xmlp {

    class XmlParser {
        std::string xmlFileName_;
        std::ifstream fileStream_;
        bool isComment_;
        bool isNodeStart_;
        XmlNode::Ptr root_;
        std::string string_;
        std::vector<std::string> nodes_;

        void parse();
        bool isgraph(char ch);
        void parseTag(const std::string&, std::string&);
        void addMsg(const std::string& msg);

    public:

        XmlParser(const std::string& xmlFile) : xmlFileName_(xmlFile),
        fileStream_(xmlFile.c_str(), std::ios::in),
        isComment_(false),
        root_(new XmlNode("main", XmlNode::Ptr())) {
            if (!fileStream_.good()) {
                throw std::runtime_error("XmlParser::XmlParser() - Could not read the given Xml file: " + xmlFile);
            }
            parse();
        }
        XmlNode::Ptr getNode(const std::string& label);
        void addChild(const std::string& label, XmlNode::Ptr parent);
        void addChild(const std::string& label, XmlNode::Ptr parent, bool isSingle, const std::string& content = std::string());
        
    };
}

#endif	/* XMLPARSER_H */

