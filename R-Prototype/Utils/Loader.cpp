#include "stdafx.h"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml.hpp"
#include "Loader.h"
#include "ConfigManager.h"
#include "EntityManager.h"
#include "Enemy.h"

using namespace rapidxml;

Loader* Loader::m_instance = 0;

Loader::Loader()
{
    m_numLevels = -1;
}


Loader& Loader::Instance() {
    if(!m_instance)
        m_instance = new Loader();
    
    return *m_instance;
}


bool Loader::LoadLevel(const int level)
{
    
    if(level < 0 || (m_numLevels > 0 && level >= m_numLevels))
        return false;
    
    FILE* file = fopen("data/levels.xml", "rb");
    if(file == nullptr) return false;

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    // Allocate contents in a buffer
    char* buf = (char*)malloc(size+1);
    fread(buf, sizeof(char), size, file);
    buf[size] = '\0';
    
    xml_document<> doc;
    doc.parse<0>(buf);
    
    xml_node<>* game = doc.first_node("game");
    if(!game) return false;
    
    if(m_numLevels < 0)
    {
        m_numLevels = ToInt(game->first_attribute("numlevels")->value());
        if(level >= m_numLevels)
            return false;
    }
    
    
    xml_node<>* lvl = game->first_node("level");
    if(!lvl) return false;
    
    for(int i = 0; i < level; i++)
    {
        lvl = lvl->next_sibling("level");
    }
    
    char* levelName = lvl->first_attribute("name")->value();
    xml_node<>* lvldata = lvl->first_node("data");
    
    xml_node<>* background = lvldata->first_node("background");
    if(background)
    {
        const char* image = background->first_attribute("src")->value();
        float width       = ToFloat(background->first_attribute("width")->value());
        float height      = ToFloat(background->first_attribute("height")->value());
        float velocityX   = ToFloat(background->first_attribute("velocityx")->value());
        float velocityY   = ToFloat(background->first_attribute("velocityy")->value());
        
        EntityManager::CreateBackground(vmake(width, height), vmake(velocityX, velocityY), image);
    }
    
    xml_node<>* enemy = lvldata->first_node("enemy");
    while(enemy)
    {
        float posX = ToFloat(enemy->first_attribute("positionx")->value());
        float posY = ToFloat(enemy->first_attribute("positiony")->value());
        float velX = ToFloat(enemy->first_attribute("velocityx")->value());
        float velY = ToFloat(enemy->first_attribute("velocityy")->value());
        uint  type = ToUInt(enemy->first_attribute("type")->value());
                
        Enemy::EnemyType enemyType;
        
        switch (type) {
            case 1:
                enemyType = Enemy::ENEMY_1;
                break;
            case 2:
                enemyType = Enemy::ENEMY_2;
                break;
            case 4:
                enemyType = Enemy::ENEMY_4;
                break;
            default:
                enemyType = Enemy::ENEMY_ERROR;
                break;
        }
        
        if(enemyType != Enemy::ENEMY_ERROR)
            EntityManager::CreateEnemy(enemyType, vmake(posX, posY), vmake(velX, velY));
        
        enemy = enemy->next_sibling("enemy");
    }
    
    xml_node<>* asteroid = lvldata->first_node("asteroid");
    while(asteroid)
    {
        float posX  = ToFloat(asteroid->first_attribute("positionx")->value());
        float posY  = ToFloat(asteroid->first_attribute("positiony")->value());
        float sizeX = ToFloat(asteroid->first_attribute("width")->value());
        float sizeY = ToFloat(asteroid->first_attribute("height")->value());
        float velX  = ToFloat(asteroid->first_attribute("velocityx")->value());
        float velY  = ToFloat(asteroid->first_attribute("velocityy")->value());
        
        EntityManager::CreateAsteroid(vmake(posX, posY), vmake(sizeX, sizeY), vmake(velX, velY));
        
        asteroid = asteroid->next_sibling("asteroid");
    }
    
    fclose(file);
    
    return true;
}


int Loader::GetNumLevels()
{
    if(m_numLevels < 0)
    {
        FILE* file = fopen("data/levels.xml", "rb");
        if(file == nullptr) return false;
        
        fseek(file, 0, SEEK_END);
        long size = ftell(file);
        fseek(file, 0, SEEK_SET);
        
        // Allocate contents in a buffer
        char* buf = (char*)malloc(size+1);
        fread(buf, sizeof(char), size, file);
        buf[size] = '\0';
        
        xml_document<> doc;
        doc.parse<0>(buf);
        
        xml_node<>* game = doc.first_node("game");
        if(!game) return -1;
        
        m_numLevels = ToInt(game->first_attribute("numlevels")->value());
        fclose(file);
    }
    
    return m_numLevels;
}

void Loader::LoadConfig()
{
    FILE* file = fopen("data/player_config.xml", "rb");
    if(file == nullptr) return;
    
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    // Allocate contents in a buffer
    char* buf = (char*)malloc(size+1);
    fread(buf, sizeof(char), size, file);
    buf[size] = '\0';
    
    xml_document<> doc;
    doc.parse<0>(buf);
    
    xml_node<>* savedGame = doc.first_node("saved_game");
    if(!savedGame) return;
    
    uint langIndex    = ToInt(savedGame->first_node("language")->value());
    uint currentLevel = ToInt(savedGame->first_node("currentLevel")->value());
    bool sound        = ToInt(savedGame->first_node("sound")->value());
    
    ConfigManager::Instance().SetSound(sound);
    ConfigManager::Instance().SetCurrentLevel(currentLevel);
    ConfigManager::Instance().SetLanguage(langIndex);
    
    fclose(file);
}


void Loader::Save()
{
    xml_document<> doc;
    xml_node<>* xmlVersion = doc.allocate_node(node_declaration);
    xmlVersion->append_attribute(doc.allocate_attribute("version", "1.0"));
    xmlVersion->append_attribute(doc.allocate_attribute("encoding", "utf-8"));
    doc.append_node(xmlVersion);
    
    xml_node<>* state = doc.allocate_node(node_element, "saved_game");
    doc.append_node(state);
    
    xml_node<>* langNode = doc.allocate_node(node_element, "language");
    langNode->value(std::to_string(ConfigManager::Instance().GetLanguageIndex()).c_str());
    state->append_node(langNode);
    
    xml_node<>* soundNode = doc.allocate_node(node_element, "sound");
    soundNode->value(std::to_string(ConfigManager::Instance().IsSoundActive()).c_str());
    state->append_node(soundNode);
    
    xml_node<>* levelNode = doc.allocate_node(node_element, "currentLevel");
    levelNode->value(std::to_string(ConfigManager::Instance().GetCurrentLevel()).c_str());
    state->append_node(levelNode);
    
    FILE* file = fopen("data/player_config.xml", "w");
    
    std::string docStr;
    print(std::back_inserter(docStr), doc, 0);

    fwrite(docStr.c_str(), sizeof(char), docStr.size(), file);
    
    fclose(file);
}


int Loader::ToInt(char *str) const
{
    int ret = 0;
    sscanf(str, "%i", &ret);
    return ret;
}


float Loader::ToFloat(char* str) const
{
    float ret = 0;
    sscanf(str, "%f", &ret);
    return ret;
}


uint Loader::ToUInt(char* str) const
{
    uint ret = 0;
    sscanf(str, "%u", &ret);
    return ret;
}
