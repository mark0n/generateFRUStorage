#ifndef VARLENGTHLANGCODEFIELD_HPP
#define VARLENGTHLANGCODEFIELD_HPP

#include "varLengthField.hpp"

class varLengthLangCodeField : public varLengthField
{
public:
  varLengthLangCodeField();
  std::string getString();
  void setString(std::string str);
};

#endif /* VARLENGTHLANGCODEFIELD_HPP */