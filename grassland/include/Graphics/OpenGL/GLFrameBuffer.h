#pragma once
#include "GLHeader.h"
#include "GLTexture.h"
#include "GLWindow.h"

namespace Grassland {
typedef uint32_t GRL_OPENGL_FRAMEBUFFER_SLOT;
#define GRL_OPENGL_FRAMEBUFFER_SLOT_DEPTH -1
#define GRL_OPENGL_FRAMEBUFFER_SLOT_COLOR0 0
#define GRL_OPENGL_FRAMEBUFFER_SLOT_COLOR1 1
#define GRL_OPENGL_FRAMEBUFFER_SLOT_COLOR2 2
#define GRL_OPENGL_FRAMEBUFFER_SLOT_COLOR3 3
#define GRL_OPENGL_FRAMEBUFFER_SLOT_COLOR4 4
#define GRL_OPENGL_FRAMEBUFFER_SLOT_COLOR5 5
#define GRL_OPENGL_FRAMEBUFFER_SLOT_COLOR6 6
#define GRL_OPENGL_FRAMEBUFFER_SLOT_COLOR7 7
#define GRL_OPENGL_FRAMEBUFFER_SLOT_COLOR8 8
#define GRL_OPENGL_FRAMEBUFFER_SLOT_COLOR9 9
#define GRL_OPENGL_FRAMEBUFFER_SLOT_COLOR10 10
#define GRL_OPENGL_FRAMEBUFFER_SLOT_COLOR11 11
#define GRL_OPENGL_FRAMEBUFFER_SLOT_COLOR12 12
#define GRL_OPENGL_FRAMEBUFFER_SLOT_COLOR13 13
#define GRL_OPENGL_FRAMEBUFFER_SLOT_COLOR14 14
#define GRL_OPENGL_FRAMEBUFFER_SLOT_COLOR15 15
#define GRL_OPENGL_FRAMEBUFFER_SLOT_COLOR16 16
#define GRL_OPENGL_FRAMEBUFFER_SLOT_COLOR17 17
#define GRL_OPENGL_FRAMEBUFFER_SLOT_COLOR18 18
#define GRL_OPENGL_FRAMEBUFFER_SLOT_COLOR19 19
#define GRL_OPENGL_FRAMEBUFFER_SLOT_COLOR20 20
#define GRL_OPENGL_FRAMEBUFFER_SLOT_COLOR21 21
#define GRL_OPENGL_FRAMEBUFFER_SLOT_COLOR22 22
#define GRL_OPENGL_FRAMEBUFFER_SLOT_COLOR23 23
#define GRL_OPENGL_FRAMEBUFFER_SLOT_COLOR24 24
#define GRL_OPENGL_FRAMEBUFFER_SLOT_COLOR25 25
#define GRL_OPENGL_FRAMEBUFFER_SLOT_COLOR26 26
#define GRL_OPENGL_FRAMEBUFFER_SLOT_COLOR27 27
#define GRL_OPENGL_FRAMEBUFFER_SLOT_COLOR28 28
#define GRL_OPENGL_FRAMEBUFFER_SLOT_COLOR29 29
#define GRL_OPENGL_FRAMEBUFFER_SLOT_COLOR30 30
#define GRL_OPENGL_FRAMEBUFFER_SLOT_COLOR31 31
#define GRL_OPENGL_FRAMEBUFFER_SLOT_COLOR_LAST 31

class GRLIOpenGLFrameBuffer : public GRLIBase {
 public:
  virtual uint32_t GetHandle() const = 0;
  virtual int32_t GetWidth() const = 0;
  virtual int32_t GetHeight() const = 0;
  virtual GRL_RESULT CheckStatus() const = 0;
  virtual GRL_RESULT BindTexture(GRLIOpenGLTexture *pTexture,
                                 GRL_OPENGL_FRAMEBUFFER_SLOT slot =
                                     GRL_OPENGL_FRAMEBUFFER_SLOT_COLOR0) = 0;
  virtual GRL_RESULT Resize(int32_t width, int32_t height) = 0;
};

GRL_RESULT GRLCreateOpenGLFrameBuffer(int32_t width,
                                      int32_t height,
                                      GRLIOpenGLFrameBuffer **ppFrameBuffer);

GRL_RESULT GRLOpenGLBindFrameBuffer(GRLIOpenGLFrameBuffer *pFramebuffer);

GRL_RESULT GRLOpenGLGetFrameBufferSize(int32_t *width, int32_t *height);
}  // namespace Grassland
