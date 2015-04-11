#pragma once

#include <string>
#include <map>

typedef std::map<std::string, float> AttributeMap;

class Machine;

class Service
{
public:
    Service(Machine* parent = nullptr);

    Machine* getParent();

    void addAttribute(const std::string& attrName, float value);

    const AttributeMap& getAttributeMap() const;

    //! Returns attribute's value if atttribute is present, 0 otherwise.
    float getAttributeValue(const std::string& attrName) const;

private:
    bool _isAttributePresent(const std::string& attrName) const;

    Machine* _parent;
    AttributeMap _attributeMap;
};
