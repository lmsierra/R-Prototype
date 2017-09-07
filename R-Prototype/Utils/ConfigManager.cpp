#include "stdafx.h"
#include "ConfigManager.h"
#include "Loader.h"

ConfigManager *ConfigManager::m_instance = 0;

ConfigManager::ConfigManager()
{
    m_langIndex    = 0;
    m_sound        = false;
    m_currentLevel = 0;
}


ConfigManager& ConfigManager::Instance()
{
    if(!m_instance)
        m_instance = new ConfigManager();
    
    return *m_instance;
}


bool ConfigManager::IsSoundActive() const
{
    return m_sound;
}


LocalizationManager::Language ConfigManager::GetLanguage() const
{
    return m_languages[m_langIndex];
}


void ConfigManager::SetSound(bool sound)
{
    m_sound = sound;
}


void ConfigManager::SetLanguage(uint index)
{
    m_langIndex = index;
}


void ConfigManager::SetNextLanguage()
{
    m_langIndex++;
    if(m_langIndex >= sizeof(m_languages) / sizeof(*m_languages))
        m_langIndex = 0;
}


uint ConfigManager::GetLanguageIndex() const
{
    return m_langIndex;
}


uint ConfigManager::GetCurrentLevel() const
{
    return m_currentLevel;
}


void ConfigManager::SetCurrentLevel(uint currentLevel)
{
    m_currentLevel = currentLevel;
}

void ConfigManager::Init()
{
    Loader::Instance().LoadConfig();
}
