#include "XmlNode.h"
#include <boost/algorithm/string.hpp>
#include <algorithm>
#include <iostream>
#include <boost/foreach.hpp>
#include <stdexcept>
#include <boost/lexical_cast.hpp>


namespace xmlp {

    XmlNode::XmlNode(const std::string& tagContent, XmlNode::Ptr parent, bool isSingle, const std::string& content) :
    parent_(parent),
    content_(content),
    isSingle_(isSingle) {
        std::string tc(tagContent);
        boost::algorithm::trim(tc);
        parseTagContent(tc);
    }

    void XmlNode::addChild(const std::string& tagContent) {
        children_.push_back(XmlNode::Ptr(new XmlNode(tagContent, shared_from_this())));
    }

    void XmlNode::addChild(const std::string& tagContent, bool isSingle, const std::string& content) {
        children_.push_back(XmlNode::Ptr(new XmlNode(tagContent, shared_from_this(), isSingle, content)));
    }

    void XmlNode::deleteChild(const std::string& nodeName) {
        for (ChildItr childIt = children_.begin(); childIt != children_.end(); ++childIt) {
            if (boost::equal((*childIt)->nodeName_, nodeName)) {
                children_.erase(childIt);
                return;
            }
        }
        throw std::runtime_error("XmlNode::deleteChild() - No such node present with name: " + nodeName);
    }

    const std::string& XmlNode::getAttributeValue(const std::string& attrName) {

        BOOST_FOREACH(XmlAttribute::Ptr attr, attributes_) {
            if (boost::iequals(attrName, attr->getName())) {
                return attr->getValue();
            }
        }
        throw std::runtime_error("XmlNode::getAttributeValue() - No Attribute for given name: " + attrName);
    }

    XmlNode::Ptr XmlNode::getChildNode(const std::string& nodeName) {
        for (ChildItr childIt = children_.begin(); childIt != children_.end(); ++childIt) {
            if (boost::equal((*childIt)->nodeName_, nodeName)) {
                return *childIt;
            }
        }
        throw std::runtime_error("XmlNode::getChildNode() - No child exists with tagName: " + nodeName);
    }

    XmlNode::Ptr XmlNode::operator[](int index) {
        for (ChildItr childIt = children_.begin(); childIt != children_.end(); ++childIt) {
            int i = 0;
            if (i++ == index) {
                return *childIt;
            }
        }
        throw std::runtime_error("XmlNode::operator[]() - No child exists for Index: " + boost::lexical_cast<std::string>(index));
    }

    void XmlNode::setAttribute(XmlAttribute::Ptr attribute) {
        std::pair < std::set<XmlAttribute::Ptr>::iterator, bool> retVal = attributes_.insert(attribute);
        if (!retVal.second) {
            throw std::runtime_error("XmlNode::setAttribute() - Could not insert attribute : Name : " + attribute->getName() + " Value: " + attribute->getValue());
        }
    }

    void XmlNode::parseTagContent(const std::string& tagContent) {

        std::size_t pos = tagContent.find(' ');
        std::string attrName;
        std::string attrValue;

        if (pos != std::string::npos) {

            // Found - Might some attributes present

            nodeName_ = tagContent.substr(0, pos);
            boost::algorithm::trim(nodeName_);
            std::string remainingTagContent = tagContent.substr(pos + 1);

            while ((pos = remainingTagContent.find('=')) != std::string::npos) {

                // Attribute present, Let's parse it

                attrName = remainingTagContent.substr(0, pos);
                boost::algorithm::trim(attrName);
                remainingTagContent = remainingTagContent.substr(pos + 1);
                boost::algorithm::trim(remainingTagContent);

                getAttrValue(remainingTagContent, attrValue);

                boost::algorithm::trim(attrValue);

                attributes_.insert(XmlAttribute::Ptr(new XmlAttribute(attrName, attrValue)));

            }
            
            if(!remainingTagContent.empty()){
                if(remainingTagContent.find('=') == std::string::npos){
                    throw std::runtime_error("XmlNode::parseTagContent() - Wrong Xml Content : " + tagContent);
                }
            }
        }
        nodeName_ = tagContent;
        boost::algorithm::trim(nodeName_);
        size_t posNodeName = nodeName_.find(' ');
        if(posNodeName == std::string::npos){
            justNodeName_ = nodeName_ ;
        }else{
            justNodeName_ = nodeName_.substr(0, posNodeName);
        }

    }

    void XmlNode::getAttrValue(std::string& str, std::string& attrVal) {
     
        const std::string origStr = str ;
        size_t pos1 = str.find(' ');
        if (pos1 != std::string::npos) {
            // Got some value
        }
        size_t pos2 = str.find('=');
        size_t pos;
        pos = std::min(pos1, pos2);
        if (pos1 == std::string::npos) {
            pos = pos2;
        }
        if (pos2 == std::string::npos) {
            pos = pos1;
        }
        attrVal = str.substr(0, pos);
        if (pos < str.size() - 1) {
            str = str.substr(pos);
        }

        if (attrVal.at(0) == '\'') {
            // Process for quotes
            size_t endPosOfQuoteInStr = str.find('\'');
            if(endPosOfQuoteInStr == std::string::npos){
                throw std::runtime_error(" XmlNode::getAttrValue() - Error in Xml content : " + origStr);
            }
            size_t startPosOfQuoteInAttr = attrVal.find('\'');
            attrVal = attrVal.substr(startPosOfQuoteInAttr + 1) + str.substr(0, endPosOfQuoteInStr);
            str = str.substr(endPosOfQuoteInStr + 1);
        } else if (attrVal.at(0) == '\"') {
            // Process for quotes
            size_t endPosOfQuoteInStr = str.find('\"');
            if(endPosOfQuoteInStr == std::string::npos){
                throw std::runtime_error(" XmlNode::getAttrValue() - Error in Xml content : " + origStr);
            }
            size_t startPosOfQuoteInAttr = attrVal.find('\"');
            attrVal = attrVal.substr(startPosOfQuoteInAttr + 1) + str.substr(0, endPosOfQuoteInStr);
            str = str.substr(endPosOfQuoteInStr + 1);
        }

    }

    void XmlNode::toString(std::string& strRet) {
        std::stringstream str;
        str << "<" << justNodeName_ ;

        BOOST_FOREACH(XmlAttribute::Ptr attr, attributes_) {
            str << " " << attr->getName() << "=" ;
            
            if(attr->getValue().find(' ') != std::string::npos) {
                str << "'" << attr->getValue() << "'" ;
            }else{
                str << attr->getValue();
            }
        }

        if (isSingle_) {
            str << " />" << std::endl;
            strRet += str.str();
            str.str("");
        } else {
            str << ">" << std::endl;

            if (getContent().length()) {
                str << getContent() << std::endl;
                str << "</" << justNodeName_ << ">" << std::endl;
            } else {
                strRet += str.str();
                str.str("");

                BOOST_FOREACH(XmlNode::Ptr child, children_) {
                    child->toString(strRet);
                }
                str << "</" << justNodeName_ << ">" << std::endl;
            }


        }
        strRet += str.str();
    }
}
