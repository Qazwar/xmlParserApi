/* 
 * File:   XmlAttribute.h
 * Author: dev
 *
 * Created on 9 January, 2015, 12:25 AM
 */

#ifndef XMLATTRIBUTE_H
#define	XMLATTRIBUTE_H

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

namespace xmlp {

    class XmlAttribute : private boost::noncopyable {
        
        std::string name_;
        std::string value_;

    public:
        
        typedef boost::shared_ptr<XmlAttribute> Ptr ;
        typedef boost::shared_ptr<const XmlAttribute> ConstPtr ;

        XmlAttribute(const std::string& name, const std::string& value) : name_(name), value_(value) {

        }
        
        const std::string& getName() const { return name_ ; }
        const std::string& getValue() const { return value_ ; }


    };
}

#endif	/* XMLATTRIBUTE_H */

