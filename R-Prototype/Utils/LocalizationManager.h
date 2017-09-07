#ifndef LOCALIZATION_MANAGER_H
#define LOCALIZATION_MANAGER_H

#define LOCALIZATION_PATH "Data/Localization/"
#define STRING_PATH       "String/"

class LocalizationManager
{
public:
    enum Language {
        ENGLISH,
        SPANISH
    };

    static LocalizationManager& Instance();

    const char* LocalizedString(const char* key, Language language);
    void        LoadTextFile(Language language);
    
private:
    static LocalizationManager* m_instance;
    std::unordered_map<std::string, const char*> m_textMap;
    Language m_currentLanguage;
    
    LocalizationManager();
};

#endif /* LOCALIZATION_MANAGER_H */
