/* 
 * File:   XmlNode.h
 * Author: dev
 *
 * Created on 9 January, 2015, 12:25 AM
 */

#ifndef XMLNODE_H
#define	XMLNODE_H

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <XmlAttribute.h>
#include <set>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <vector>

namespace xmlp {

    class XmlNode : private boost::noncopyable, public boost::enable_shared_from_this<XmlNode> {
    public:

        typedef boost::shared_ptr<XmlNode> Ptr;
        typedef boost::shared_ptr<const XmlNode> ConstPtr;
        typedef std::vector<XmlNode::Ptr>::iterator ChildItr;
        typedef std::vector<XmlNode::Ptr>::const_iterator ChildConstItr;
        typedef std::set<XmlAttribute>::iterator AttributeItr;
        
    private:

        std::set<XmlAttribute::Ptr> attributes_;
        XmlNode::Ptr parent_;
        std::vector<XmlNode::Ptr> children_;
        std::string content_;
        std::string nodeName_;
        std::string justNodeName_ ;
        
        bool isSingle_;

    public:

        XmlNode(const std::string& tagContent, XmlNode::Ptr parent, bool isSingle = false, const std::string& content = std::string());
        ~XmlNode() {
            
        }
        
        XmlNode(){
            
        }
        
        const std::string& getName() const { return nodeName_ ; }

        void addChild(const std::string&);
        void addChild(const std::string&, bool isSingle, const std::string& content = std::string());
        
        size_t getChildCount() const { return children_.size() ; }

        void deleteChild(const std::string& name);

        void setContent(const std::string& content) { content_ = content ; }
        const std::string& getContent() const { return content_ ; }


        XmlNode::Ptr getParaent() const { return parent_ ; }

        const std::string& getAttributeValue(const std::string& attrName);
        void setAttribute(XmlAttribute::Ptr attribute);

        XmlNode::Ptr getChildNode(const std::string& name);
        size_t getChildrenCount() const { return children_.size() ; }
        ChildConstItr getChildrenBeginIt() const { return children_.begin() ; }
        ChildConstItr getChildrenEndIt() const { return children_.end() ; }
        std::pair<ChildConstItr, ChildConstItr> getChildrenIt() const { return std::pair<ChildConstItr, ChildConstItr>(getChildrenBeginIt(), getChildrenEndIt()); }

        XmlNode::Ptr operator[](int index);
        
        void toString(std::string&);
        
        void getAttrValue(std::string& str, std::string& attrVal);

    private:

        void parseTagContent(const std::string& tagContent);
        //void getAttrValue(std::string& str, std::string& attrVal);


    };

}

#endif	/* XMLNODE_H */

