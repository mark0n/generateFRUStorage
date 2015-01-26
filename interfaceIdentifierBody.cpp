/* 
 * File:   interfaceIdentifierBody.cpp
 * Author: Joshua Lamb
 * 
 * Created on December 18, 2014, 11:53 AM
 */

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
          case 0x01:
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
          case 0x02:
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
          case 0x03:
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
          case 0x04:
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

std::vector<uint8_t> interfaceIdentifierBody::getBinaryData() const {
    switch(m_identifier)
    {
          case 0x01:
          {
              std::vector<uint8_t>binary( ( uint8_t * )&m_data1, ( ( uint8_t * )&m_data1 ) + picmgSpecificationInterfaceIdentifierLeadingLength);
              binary.insert(binary.end(), opaque.begin(), opaque.end());
              return binary;
          }
              break;
          case 0x02:
          {
              return std::vector<uint8_t>( ( uint8_t * )&m_data2, ( ( uint8_t * )&m_data2 ) + interfaceIdentifierGUIDLength );
          }
              break;
          case 0x03:
          {
              return std::vector<uint8_t>( ( uint8_t * )&m_data3, ( ( uint8_t * )&m_data3 ) + interfaceIdentifierOEMLength );
          }
              break;
          case 0x04:
          {
              return std::vector<uint8_t>( ( uint8_t * )&m_data4, ( ( uint8_t * )&m_data4 ) + picmgMTCAREPNumberLength );
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
