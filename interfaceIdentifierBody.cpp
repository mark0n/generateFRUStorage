#include "interfaceIdentifierBody.hpp"
#include <iostream>
#include <cmath>
#include <string>

const uint8_t picmgSpecificationInterfaceIdentifierLeadingLength = 6;
const uint8_t picmgSpecificationInterfaceIdentifierLines = 4;
const uint8_t interfaceIdentifierGUIDLength = 16;
const uint8_t interfaceIdentifierGUIDLines = 1;
const uint8_t interfaceIdentifierOEMLength = 7;
const uint8_t interfaceIdentifierOEMLines = 2;
const uint8_t picmgMTCAREPNumberLength = 4;
const uint8_t picmgMTCAREPNumberLines = 1;

interfaceIdentifierBody::interfaceIdentifierBody(uint8_t interfaceIdentifier, std::vector<std::string> body) {
  m_identifier = interfaceIdentifier;

  switch(interfaceIdentifier)
  {
    case 1:
    {
      if(body.size() == picmgSpecificationInterfaceIdentifierLines)
      {
        if(body[0].size() + body[1].size() + body[2].size() == picmgSpecificationInterfaceIdentifierLeadingLength*2)
        {
          std::string localBody1 = body[0];
          int identQuant = 0;
            for(int j = localBody1.size()-1; j >= 0; j--)
            {
              std::string ident;
              ident.push_back(localBody1[j-1]);
              ident.push_back(localBody1[j]);
              j--;
              m_data1.identifier[identQuant] = (uint8_t)std::stoi(ident, NULL, 16);
              identQuant++;
            }
            m_data1.major = (uint8_t)std::stoi(body[1], NULL, 16);

            m_data1.minor = (uint8_t)std::stoi(body[2], NULL, 16);
            
            std::string localBody2 = body[3];
            for(int j = localBody2.size()-1; j >= 0; j--)
              {
                std::string opa;
                opa.push_back(localBody2[j-1]);
                opa.push_back(localBody2[j]);
                j--;
                opaque.push_back((uint8_t)std::stoi(opa, NULL, 16));
              }
        }
        else
          throw std::out_of_range("too large");
        interfaceIdentifierBodyDataSize = picmgSpecificationInterfaceIdentifierLeadingLength + opaque.size();
        
      }
      else
        throw std::out_of_range("number of record entries out of valid range");
    }
      break;
    case 2:
    {
      if(body.size() == interfaceIdentifierGUIDLines)
      {
        if(body[0].size() == interfaceIdentifierGUIDLength*2)
        {
          std::string localBody = body[0];
          int guidQuant = 0;
          for(int j = localBody.size()-1; j >= 0; j--)
          {
            std::string guid;
            guid.push_back(localBody[j-1]);
            guid.push_back(localBody[j]);
            j--;
            m_data2.guid[guidQuant] = (uint8_t)std::stoul(guid, NULL, 16);
            guidQuant++;
          }
        }
        else
          throw std::out_of_range("too large");
        interfaceIdentifierBodyDataSize = interfaceIdentifierGUIDLength;
      }
      else
        throw std::out_of_range("number of record entries out of valid range");
    }
      break;
    case 3:
    {
      if(body.size() == interfaceIdentifierOEMLines)
      {
        if(body[0].size() + body[1].size() == interfaceIdentifierOEMLength*2)
        {
          std::string localBody1 = body[0];
          int idanaQuant = 0;
          for(int j = localBody1.size()-1; j >= 0; j--)
          {
            std::string idana;
            idana.push_back(localBody1[j-1]);
            idana.push_back(localBody1[j]);
            j--;
            m_data3.idana[idanaQuant] = (uint8_t)std::stoul(idana, NULL, 16);
            idanaQuant++;
          }
          std::string localBody2 = body[1];
          int desiQuant = 0;
          for(int j = localBody2.size()-1; j >= 0; j--)
          {
            std::string desi;
            desi.push_back(localBody2[j-1]);
            desi.push_back(localBody2[j]);
            j--;
            m_data3.designator[desiQuant] = (uint8_t)std::stoul(desi, NULL, 16);
            desiQuant++;
          }
          interfaceIdentifierBodyDataSize = interfaceIdentifierOEMLength;
        }
        else
          throw std::out_of_range("too large");
      }
      else
        throw std::out_of_range("number of record entries out of valid range");
    }
      break;
    case 4:
    {
      if(body.size() == picmgMTCAREPNumberLines )
      {
        if(body[0].size() == picmgMTCAREPNumberLength*2)
        {
          std::string localBody = body[0];
          int repNumQuant = 0;
          for(int j = localBody.size()-1; j >= 0; j--)
          {
            std::string repNum;
            repNum.push_back(localBody[j-1]);
            repNum.push_back(localBody[j]);
            j--;
            m_data4.mtcaRepNumber[repNumQuant] = (uint8_t)std::stoul(repNum, NULL, 16);
            repNumQuant++;
          }
        }
        else
          throw std::out_of_range("too large");
        interfaceIdentifierBodyDataSize = picmgMTCAREPNumberLength;
      }
    }
      break;
    default:
      throw std::out_of_range("Interface Identifier out of valid range");
      break;
  }
}

interfaceIdentifierBody::~interfaceIdentifierBody() {
}

std::vector<uint8_t> interfaceIdentifierBody::getBinaryData() const 
{
  switch(m_identifier)
  {
    case 1:
    {
      std::vector<uint8_t>binary( ( uint8_t * )&m_data1, ( ( uint8_t * )&m_data1 ) + picmgSpecificationInterfaceIdentifierLeadingLength);
      binary.insert(binary.end(), opaque.begin(), opaque.end());
      return binary;
    }
      break;
    case 2:
    {
      return std::vector<uint8_t>( ( uint8_t * )&m_data2, ( ( uint8_t * )&m_data2 ) + interfaceIdentifierGUIDLength );
    }
      break;
    case 3:
    {
      return std::vector<uint8_t>( ( uint8_t * )&m_data3, ( ( uint8_t * )&m_data3 ) + interfaceIdentifierOEMLength );
    }
      break;
    case 4:
    {
      return std::vector<uint8_t>( ( uint8_t * )&m_data4, ( ( uint8_t * )&m_data4 ) + picmgMTCAREPNumberLength );
    }
      break;
    default:
      throw std::out_of_range("Interface Identifier out of valid range");
      break;
  }
}

void interfaceIdentifierBody::printData()
{
  switch(m_identifier)
  {
    case 1:
    {
      std::cout << "Other PICMG Specification-defined Interface Identifier (1h)" << std::endl;
      std::cout << "The PICMG specification unique identifier, LSB first";
      for(int i = 0; i < 4; i++)
        std::cout << m_data1.identifier[i];
      std::cout << std::endl;
      std::cout << "The PICMG specification major revision number: " << m_data1.major << std::endl;
      std::cout << "The PICMG specification minor revision number: " << m_data1.minor << std::endl;
      std::cout << "The opaque interface identifier body: ";
      for(int i = 0; i < (int)opaque.size(); i++)
        std::cout << opaque[i];
      std::cout << std::endl;
    }
      break;
    case 2:
    {
      std::cout << "Interface Identifier GUID (2h)" << std::endl;
      std::cout << "Interface identifier GUID, LSB first: ";
      for(int i = 0; i < 16; i++)
        std::cout << m_data2.guid[i];
      std::cout << std::endl;
    }
      break;
    case 3:
    {
      std::cout << "OEM interface identifier (3h)" << std::endl;
      std::cout << "Manufacturer ID (IANA), LSB first: ";
      for(int i = 0; i < 3; i++)
        std::cout << m_data3.idana[i];
      std::cout << "OEM-defined interface designator, LSB first: ";
      for(int i = 0; i < 4; i++)
        std::cout << m_data3.designator[i];
      std::cout << std::endl;
    }
      break;
    case 4:
    {
      std::cout << "PICMG MTCA.4 REP Number (4h)" << std::endl;
      std::cout << "The MTCA.4 REP Number, LSB first: ";
      for(int i = 0; i < 4; i++)
        std::cout << m_data4.mtcaRepNumber[i];
      std::cout << std::endl;
    }
      break;
    default:
      throw std::out_of_range("Interface Identifier out of valid range");
      break;
  }
}

int interfaceIdentifierBody::size() const {
  return interfaceIdentifierBodyDataSize;
}
