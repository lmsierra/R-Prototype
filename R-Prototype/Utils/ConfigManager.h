#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include "LocalizationManager.h"

class ConfigManager {
public:
    static ConfigManager& Instance();
    
    bool                          IsSoundActive()    const;
    LocalizationManager::Language GetLanguage()      const;
    uint                          GetLanguageIndex() const;
    uint                          GetCurrentLevel()  const;
    void                          SetSound(bool sound);
    void                          SetLanguage(uint index);
    void                          SetCurrentLevel(uint currentLevel);
    void                          SetNextLanguage();
    void                          Init();
private:
    static ConfigManager* m_instance;

    bool m_sound;
    uint m_langIndex;
    uint m_currentLevel;
    
    LocalizationManager::Language m_languages[2] = {
        LocalizationManager::ENGLISH,
        LocalizationManager::SPANISH
    };
    
    ConfigManager();
};

#endif /* CONFIG_MANAGER_H */
