#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

class TextureManager
{
public:
    static TextureManager& Instance();
    
    GLuint GetTextureFromFile(const char* filename);
    void   ReleaseTexture(const char* filename);
    void   ReleaseTextures();

private:
    static TextureManager* m_instance;
    
    std::unordered_map<const char*, GLuint> m_textureMap;
    
    TextureManager();
    ~TextureManager();
    
    GLuint LoadTexture(const char* filename);
    GLuint RemoveTexture(const char* texture);
    void   UnloadTexture(GLuint texture);
};

#endif /* TEXTURE_MANAGER_H */
