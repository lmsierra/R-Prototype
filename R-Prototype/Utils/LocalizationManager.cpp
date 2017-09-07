#include "stdafx.h"
#include "LocalizationManager.h"
#include "rapidxml.hpp"

using namespace rapidxml;

LocalizationManager* LocalizationManager::m_instance = 0;


LocalizationManager::LocalizationManager() {
    m_currentLanguage = ENGLISH;
}


LocalizationManager& LocalizationManager::Instance()
{
    if(!m_instance)
        m_instance = new LocalizationManager();
    
    return *m_instance;
}


void LocalizationManager::LoadTextFile(Language language)
{
    const char* filename;
    switch (language) {
        case ENGLISH:
            filename = "strings.xml";
            break;
        case SPANISH:
            filename = "es-strings.xml";
            break;
        default:
            filename = "strings.xml";
            break;
    }
    
    int length = sizeof(LOCALIZATION_PATH) / sizeof(char) + sizeof(STRING_PATH) / sizeof(char) + sizeof(filename) / sizeof(*filename);
    
    char* pathBuf = (char*) malloc(length + 99);
    strcpy(pathBuf, LOCALIZATION_PATH);
    strcat(pathBuf, STRING_PATH);
    strcat(pathBuf, filename);
    
    const char* filepath = pathBuf;
    free(pathBuf);
    
    FILE* file = fopen(filepath, "rb");
    if(file == nullptr) return;
    
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char* buf = (char*) malloc(size + 1);
    fread(buf, sizeof(char), size, file);
    buf[size] = '\0';
    
    xml_document<> doc;
    doc.parse<0>(buf);
    
    xml_node<>* strings = doc.first_node("strings");
    if(!strings) return;
    
    xml_node<>* item = strings->first_node("item");

    while (item)
    {
        m_textMap[std::string(item->first_attribute("name")->value())] = item->value();
        item = item->next_sibling("item");
    };
}


const char* LocalizationManager::LocalizedString(const char* key, Language language)
{
    if(language != m_currentLanguage || m_textMap.size() <= 0)
    {
        LoadTextFile(language);
    }

    m_currentLanguage = language;
    
    return (m_textMap.find(std::string(key)) != m_textMap.end())? m_textMap.at(std::string(key)) : key;
}
