#pragma once

#include <string>
#include <map>

typedef std::map<std::string, float> AttributeMap;

class Product
{
public:
  Product(const std::string& name);
  
  const std::string& getName() const;
  void addAttribute(const std::string& attrName, float value);
  const AttributeMap& getAttributeMap() const;
  //! Returns attribute's value if atttribute is present, 0 otherwise.
  float getAttributeValue(const std::string& attrName) const;
  
private:
  bool _isAttributePresent(const std::string& attrName) const;
  
  AttributeMap _attributeMap;
  std::string _name;
};
