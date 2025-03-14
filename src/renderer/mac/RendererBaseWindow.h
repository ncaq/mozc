// Copyright 2010-2021, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef THIRD_PARTY_MOZC_SRC_RENDERER_MAC_RENDERER_BASE_WINDOW_H_
#define THIRD_PARTY_MOZC_SRC_RENDERER_MAC_RENDERER_BASE_WINDOW_H_

#include <Cocoa/Cocoa.h>

#include <cstdint>


namespace mozc {
namespace renderer {
namespace mac {
class RendererBaseWindow {
 public:
  RendererBaseWindow(const RendererBaseWindow &) = delete;
  RendererBaseWindow &operator=(const RendererBaseWindow &) = delete;
  Size GetWindowSize() const;
  virtual void Hide();
  virtual void Show();
  virtual void MoveWindow(const NSPoint &point);
  virtual void ResizeWindow(int32_t width, int32_t height);
  virtual bool IsVisible();
  virtual void SetWindowLevel(NSInteger window_level);

 protected:
  RendererBaseWindow();
  virtual ~RendererBaseWindow();

  NSPanel *window_;
  NSView *view_;
  virtual void InitWindow();

 private:
  virtual void ResetView();
  NSInteger window_level_;
};

}  // namespace mozc::renderer::mac
}  // namespace mozc::renderer
}  // namespace mozc

#endif  // THIRD_PARTY_MOZC_SRC_RENDERER_MAC_RENDERER_BASE_WINDOW_H_
