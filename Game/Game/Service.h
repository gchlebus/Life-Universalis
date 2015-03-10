#pragma once

#include <string>
#include <map>

typedef std::map<std::string, float> AttributeMap;
class BuildingComponent;

class Service
{
public:
    Service(const std::string& name, BuildingComponent* parent);
    
    const std::string& getName() const; //Chodzi tu o name głównej potrzeby czy to jest jakiś po prostu identifier???
    void addAttribute(const std::string& attrName, float value);
    const AttributeMap& getAttributeMap() const;
    
    //! Returns attribute's value if atttribute is present, 0 otherwise.
    float getAttributeValue(const std::string& attrName) const;
    BuildingComponent* getParent();

private:
    bool _isAttributePresent(const std::string& attrName) const;
    
    BuildingComponent* _parent;

    AttributeMap _attributeMap;
    std::string _name;
};
