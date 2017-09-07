#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H

#include "IGameMode.h"

class MenuScreen : public IGameMode {
public:
    MenuScreen(const char* tag = "MenuScreen");
    virtual ~MenuScreen();
    
    virtual void Initialize(const char* title, std::vector<const char*> options, bool showMarkers = true);
    virtual void Destroy();
    virtual void Activate();
    virtual void Deactivate();
    virtual void Run();
    virtual void Draw();
    virtual void Input();
    virtual bool IsInGameMode();
    
    void SetDeveloperNotes(std::vector<const char*> developerNotes);
    void SetHints(std::vector<const char*> hints);
    void ShowMarkers(bool show);
    void SetNavigableOptions(bool navigable);
    void SetCurrentOption(uint option);
    
protected:
    const char*              m_title;
    std::vector<const char*> m_options;
    std::vector<const char*> m_developerNotes;
    std::vector<const char*> m_hints;
    int                      m_option;
    bool                     m_navigableOptions;
    bool                     m_showMarkers;
    bool                     m_dirKeyReleased;
    bool                     m_prevEnterKey;
    
    virtual vec2 DrawTitle(const char* title) const;
    virtual void DrawOptions(std::vector<const char*> options, vec2 position) const;
    virtual void DrawSelectedOptionMarkers(std::vector<const char*> options, vec2 position) const;
    virtual void DrawHints(std::vector<const char*> hints) const;
    virtual void DrawDeveloperNote(std::vector<const char*> notes) const;
    virtual void OnOptionSelected(uint option) {}
};

#endif /* MENU_SCREEN_H */
