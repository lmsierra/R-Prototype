#include "stdafx.h"
#include "sys.h"
#include "MenuScreen.h"
#include "MenuConstants.h"
#include "GameModeManager.h"
#include "LocalizationManager.h"
#include "ConfigManager.h"

MenuScreen::MenuScreen(const char* tag) : IGameMode(tag)
{
    m_title            = nullptr;
    m_option           = 0;
    m_dirKeyReleased   = false;
    m_prevEnterKey     = false;
    m_showMarkers      = true;
    m_navigableOptions = true;
}


MenuScreen::~MenuScreen()
{
    
}


void MenuScreen::Initialize(const char* title, std::vector<const char*> options, bool showMarkers)
{
    m_title          = title;
    m_options        = options;
    m_showMarkers    = showMarkers;
    
    m_hints.clear();
    m_developerNotes.clear();
    m_hints.push_back(LocalizationManager::Instance().LocalizedString("hint_move",  ConfigManager::Instance().GetLanguage()));
    
    m_hints.push_back(LocalizationManager::Instance().LocalizedString("hint_enter", ConfigManager::Instance().GetLanguage()));
    
    m_developerNotes.push_back(LocalizationManager::Instance().LocalizedString("developer_note", ConfigManager::Instance().GetLanguage()));
}


void MenuScreen::Destroy()
{
    
}


void MenuScreen::Activate()
{
    
}


void MenuScreen::Deactivate()
{
    
}


void MenuScreen::Run()
{
    
}


void MenuScreen::Input()
{
    if(m_navigableOptions && SYS_KeyPressed(MENU_KEY_UP) && m_dirKeyReleased)
        m_option = (m_option - 1 < 0)? m_options.size() - 1 : m_option - 1;
    
    if(m_navigableOptions && SYS_KeyPressed(MENU_KEY_DOWN) && m_dirKeyReleased)
        m_option = (m_option + 1) % m_options.size();
    
    if(!SYS_KeyPressed(MENU_KEY_UP) && !SYS_KeyPressed(MENU_KEY_DOWN))
        m_dirKeyReleased = true;
    else
        m_dirKeyReleased = false;
    
    if(SYS_KeyPressed(MENU_KEY_ACCEPT) == GLFW_RELEASE && m_prevEnterKey == GLFW_PRESS)
        OnOptionSelected(m_option);
    
    m_prevEnterKey = SYS_KeyPressed(MENU_KEY_ACCEPT);
}


void MenuScreen::SetDeveloperNotes(std::vector<const char*> developerNotes)
{
    m_developerNotes = developerNotes;
}


void MenuScreen::SetHints(std::vector<const char*> hints)
{
    m_hints    = hints;
}


void MenuScreen::Draw()
{
    vec2 position = DrawTitle(m_title);
    DrawOptions(m_options, position);
    DrawSelectedOptionMarkers(m_options, position);
    DrawHints(m_hints);
    DrawDeveloperNote(m_developerNotes);
}


vec2 MenuScreen::DrawTitle(const char* title) const
{
    if(!title)
        return vmake(SCR_WIDTH * .5f, (SIZE_OPTION + SIZE_OPTION) * m_options.size() + MARGIN_OPTION_FROM_TITLE);
    
    vec2 titlePosition = vmake(SCR_WIDTH * .5 - SIZE_TITLE * (strlen(m_title) * .5f), SCR_HEIGHT * .5f + SIZE_TITLE * .5f);
    FONT_DrawString(titlePosition,
                    m_title,
                    v3make(255, 140, 0),
                    vmake(SIZE_TITLE, SIZE_TITLE));
    
    return titlePosition;
}


void MenuScreen::DrawOptions(std::vector<const char*> options, vec2 position) const
{
    if(options.size() == 0) return;
    
    vec2 currentPosition = position;
    for(int i = 0; i < options.size(); i++)
    {
        if(i == 0)
            currentPosition = vmake(SCR_WIDTH * .5f - SIZE_OPTION * strlen(options[0]) * .5f,
                                    currentPosition.y - (MARGIN_OPTION_FROM_TITLE + SIZE_OPTION));
        else
            currentPosition = vmake(SCR_WIDTH * .5f - SIZE_OPTION * strlen(options[i]) * .5f,
                                    currentPosition.y - (MARGIN_OPTIONS + SIZE_OPTION));
        
        vec3 color;
        if(m_showMarkers)
        {
            if(m_navigableOptions)
                color = (m_option == i)? v3make(255, 140, 0) : v3make(100, 100, 100);
            else color = (m_option == i)? v3make(255, 140, 0) : v3make(255, 255, 255);
        }
        else
            color = v3make(255, 255, 255);
        FONT_DrawString(currentPosition, options[i], color);
    }
}


void MenuScreen::DrawSelectedOptionMarkers(std::vector<const char*> options, vec2 position) const
{
    if(!m_showMarkers || options.size() == 0 ) return;
    
    position = vmake(0, position.y - (MARGIN_OPTION_FROM_TITLE + SIZE_OPTION));
    
    vec2 markerPosTL = vmake(SCR_WIDTH * .5f - SIZE_OPTION * strlen(options[m_option]) * .5f - SIZE_MARKER + MARGIN_MARKER,
                             position.y - (SIZE_OPTION + MARGIN_OPTIONS) * m_option + (SIZE_OPTION - MARGIN_MARKER));
    
    vec2 markerPosBL = vmake(SCR_WIDTH * .5f - SIZE_OPTION * strlen(options[m_option]) * .5f - SIZE_MARKER + MARGIN_MARKER,
                             position.y - (SIZE_OPTION + MARGIN_OPTIONS) * m_option - (SIZE_OPTION * .5f + MARGIN_MARKER));
    
    vec2 markerPosTR = vmake(SCR_WIDTH * .5f + SIZE_OPTION * strlen(options[m_option]) * .5f - MARGIN_MARKER,
                             position.y - (SIZE_OPTION + MARGIN_OPTIONS) * m_option + (SIZE_OPTION - MARGIN_MARKER));
    
    vec2 markerPosBR = vmake(SCR_WIDTH * .5f + SIZE_OPTION * strlen(options[m_option]) * .5f - MARGIN_MARKER,
                             position.y - (SIZE_OPTION + MARGIN_OPTIONS) * m_option - (SIZE_OPTION * .5f + MARGIN_MARKER));
    
    FONT_DrawString(markerPosTL, TEXT_MARKER_TOP_LEFT     ,v3make(255, 140, 0), vmake(SIZE_MARKER, SIZE_MARKER));
    FONT_DrawString(markerPosTR, TEXT_MARKER_TOP_RIGHT    ,v3make(255, 140, 0), vmake(SIZE_MARKER, SIZE_MARKER));
    FONT_DrawString(markerPosBL, TEXT_MARKER_BOTTOM_LEFT  ,v3make(255, 140, 0), vmake(SIZE_MARKER, SIZE_MARKER));
    FONT_DrawString(markerPosBR, TEXT_MARKER_BOTTOM_RIGHT ,v3make(255, 140, 0), vmake(SIZE_MARKER, SIZE_MARKER));
}


void MenuScreen::DrawHints(std::vector<const char*> hints) const
{
    if(hints.size() == 0) return;
    
    for(int i = 0; i < hints.size(); i++)
    {
        FONT_DrawString(vmake(sizeof(hints[i]) / sizeof(char), SIZE_NOTE * i + MARGIN_TOP_BOTTOM_SCR),
                        hints[i],
                        v3make(255, 255, 255),
                        vmake(SIZE_NOTE, SIZE_NOTE));
    }
}


void MenuScreen::DrawDeveloperNote(std::vector<const char*> notes) const
{
    if(notes.size() == 0) return;
    
    for(int i = 0; i < notes.size(); i++)
    {
        FONT_DrawString(vmake(SCR_WIDTH - SIZE_NOTE * strlen(notes[i]) - MARGIN_LEFT_RIGHT_SCR, SIZE_NOTE * i + MARGIN_TOP_BOTTOM_SCR),
                        notes[i],
                        v3make(255, 255, 255),
                        vmake(SIZE_NOTE, SIZE_NOTE));
    }
}


void MenuScreen::ShowMarkers(bool show)
{
    m_showMarkers = show;
}


void MenuScreen::SetNavigableOptions(bool navigable)
{
    m_navigableOptions = navigable;
}


void MenuScreen::SetCurrentOption(uint option)
{
    m_option = option;
}


bool MenuScreen::IsInGameMode()
{
    return false;
}
