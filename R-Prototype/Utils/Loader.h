#ifndef LOADER_H
#define LOADER_H

class Loader
{
public:
    static Loader& Instance();
    bool LoadLevel(const int level);
    int  GetNumLevels();
    void LoadConfig();
    void Save();
    
private:
    static Loader* m_instance;
    
    int m_numLevels;
    
    Loader();
    
    //Utils
    int   ToInt(char* str)   const;
    float ToFloat(char* str) const;
    uint  ToUInt(char* str)  const;
};

#endif /* LOADER_H */
