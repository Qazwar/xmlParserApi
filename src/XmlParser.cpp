#include "XmlParser.h"
#include <boost/algorithm/string.hpp>
#include <algorithm>

namespace xmlp {

    bool XmlParser::isgraph(char ch) {
        if (ch != 0 && ch != 9 && ch != 10 && ch != ' ')
            return true;
        return false;
    }

    void XmlParser::parseTag(const std::string& tag, std::string& tagText) {

        size_t len = tag.length();
        size_t pos = std::min(tag.find(' '), tag.find('\n'));
        if (pos == std::string::npos || pos > len) {
            pos = tag.find('>');
        }
        if (tag[1] == '/') {
            tagText = tag.substr(2, pos - 2);
        } else if (tag[len - 2] == '/') {
            tagText = tag.substr(1, pos - 1);
            size_t mlen = tagText.length();
            if (tagText[mlen - 1] == '/') {
                tagText = tagText.substr(0, mlen - 1);
            }
        } else {
            tagText = tag.substr(1, pos - 1);
        }
        //std::cout << " tag: " << tag << " tagText: " << tagText << std::endl ;
    }

    void XmlParser::addMsg(const std::string& msg) {
        string_ = msg;
    }

    void XmlParser::addChild(const std::string& label, XmlNode::Ptr parent) {
        parent->addChild(label);
    }

    void XmlParser::addChild(const std::string& label, XmlNode::Ptr parent, bool isSingle, const std::string& content) {
        parent->addChild(label, isSingle, content);
    }

    XmlNode::Ptr XmlParser::getNode(const std::string& label) {
        return root_->getChildNode(label);
    }

    void XmlParser::parse() {
        
        char ch;
        std::string nodeName;
        std::string nodeLabelText;
        std::string content;
        bool isMatch = false;
        bool isContent = false;
        std::string title;
        XmlNode::Ptr curr = root_;

        while (fileStream_.eof() != std::ios::eofbit) {
            fileStream_.get(ch);
            if(!(fileStream_.gcount() > 0)){
                break ;
            }
            if (ch == '<') {

                isMatch = true;
                if (isContent && content.length()) {
                    curr->setContent(content);
                    content.clear();
                }
                isContent = false;

            }
            if (isMatch) {
                nodeName += ch;
            }
            if (isContent && isgraph(ch)) {
                content += ch;
            }
            if (nodeName.length() > 1 && nodeName.substr(0, 5) == "<?xml" && nodeName.substr(nodeName.length() - 2, 2) == "?>") {
                string_ = nodeName;
                nodeName.clear();
                isMatch = false;
            } else if (nodeName.length() > 2 && nodeName.substr(0, 4) == "<!--" && nodeName.substr(nodeName.length() - 3, 3) == "-->") {
                nodeName.clear();
                isMatch = false;
            } else if ( nodeName.length() > 0 && nodeName[0] == '<' && nodeName[nodeName.length() - 1] == '>') {
                if (nodeName[1] == '/') {
                    parseTag(nodeName, nodeLabelText);
                    if (nodes_.back() != nodeLabelText) {
                        throw std::runtime_error("XmlParser::parse() - Error in XML. Tag not closed : " + nodeLabelText);
                    }
                    nodes_.pop_back();
                    curr = curr->getParaent() ;
                } else if (nodeName[nodeName.length() - 2] == '/') {
                    parseTag(nodeName, nodeLabelText);
                    nodeName = nodeName.substr(1, nodeName.length() - 3);
                    addChild(nodeName, curr, true);
                    //counts[nodeLabelText]++;
                } else {
                    parseTag(nodeName, nodeLabelText);
                    nodeName = nodeName.substr(1, nodeName.length() - 2);
                    addChild(nodeName, curr);
                    curr = curr->getChildNode(nodeName);
                    isContent = true;
                    nodes_.push_back(nodeLabelText);
                    //counts[labeltext]++;
                }
                
                nodeName.clear();
                isMatch = false ;
            }
        }// while

    }


}
