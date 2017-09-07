#include "stdafx.h"
#include "sys.h"

extern int Main(void);

bool     bFirstFrame     = true;
uint64_t dwLastFrameTime = 0;

//-----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  int retval = -1;

  if (glfwInit() == GL_TRUE)
  {
      
    if (glfwOpenWindow(SCR_WIDTH, SCR_HEIGHT, 0, 0, 0, 0, 8, 0, SCR_FULLSCREEN ? GLFW_FULLSCREEN : GLFW_WINDOW) == GL_TRUE) /* rgba, depth, stencil */
    {
        retval = Main();
        glfwCloseWindow();
    }
    glfwTerminate();
  }
  return retval;
}

//-----------------------------------------------------------------------------
void SYS_Pump()
{
  // GLFW takes care...
}

//-----------------------------------------------------------------------------
void SYS_Show()
{
  if(SCR_FPS)
  {
    uint64_t now = mach_absolute_time();
      
    if(! bFirstFrame && SCR_FPS)
    {
      uint64_t ellapsed = now - dwLastFrameTime;
      float desired = (1000.f / SCR_FPS);
          
      if((float)ellapsed < desired)
      {
        usleep((uint32_t) (desired - ellapsed));
      }
    }
      
    dwLastFrameTime = now;
  }
    
  bFirstFrame = false;
    
  glfwSwapBuffers();
}

//-----------------------------------------------------------------------------
bool SYS_GottaQuit()
{
  return glfwGetKey(GLFW_KEY_ESC) || !glfwGetWindowParam(GLFW_OPENED);
}

//-----------------------------------------------------------------------------
void SYS_Sleep(int ms)
{
    usleep(1000 * ms);
}

//-----------------------------------------------------------------------------
bool SYS_KeyPressed(int key)
{
  return glfwGetKey(key);
}

//-----------------------------------------------------------------------------
ivec2 SYS_MousePos()
{
  int x, y;
  ivec2 pos;
  glfwGetMousePos(&x, &y);
  pos.x = x;
  pos.y = SCR_HEIGHT - y;
  return pos;
}

//-----------------------------------------------------------------------------
bool SYS_MouseButonPressed(int button)
{
  return glfwGetMouseButton(button);
}
