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

#ifndef THIRD_PARTY_MOZC_SRC_WIN32_TIP_TIP_LANG_BAR_MENU_H_
#define THIRD_PARTY_MOZC_SRC_WIN32_TIP_TIP_LANG_BAR_MENU_H_

#include <ctfutb.h>
#include <msctf.h>
#include <rpcsal.h>
#include <unknwn.h>
#include <wil/com.h>
#include <windows.h>

#include <cstddef>
#include <string>
#include <vector>

#include "win32/tip/tip_dll_module.h"
#include "win32/tip/tip_lang_bar_callback.h"

namespace mozc {
namespace win32 {

// This declaration is necessary because this header file is included multiple
// times.
template <>
bool IsIIDOf<ITfLangBarItemButton>(REFIID riid);

namespace tsf {

// MIDL_INTERFACE expects a string literal rather than a constant array of
// characters.
#ifdef GOOGLE_JAPANESE_INPUT_BUILD
#define IIDSTR_IMozcLangBarItem "C6057858-8A94-4B40-8C99-D1C4B4A0B9DB"
#define IIDSTR_IMozcLangBarToggleItem "72B4C4E3-B9F3-478A-B8A8-753AFF37EB94"
#else  // GOOGLE_JAPANESE_INPUT_BUILD
#define IIDSTR_IMozcLangBarItem "75B2153A-504B-48C9-9257-BA8D60E523E6"
#define IIDSTR_IMozcLangBarToggleItem "9ABF0C3B-4AC6-4DED-9EF6-97E728852CF3"
#endif  // !GOOGLE_JAPANESE_INPUT_BUILD

class TipBarCallback;

enum TipLangBarItemFlags {
  kTipLangBarItemTypeDefault = 0,
  kTipLangBarItemTypeChecked = TF_LBMENUF_CHECKED,  // 0x1
  // ImeLangBarItemTypeSubMenu = TF_LBMENUF_SUBMENU  // 0x2 (not supported)
  kTipLangBarItemTypeSeparator = TF_LBMENUF_SEPARATOR,        // 0x4
  kTipLangBarItemTypeRadioChecked = TF_LBMENUF_RADIOCHECKED,  // 0x8
  kTipLangBarItemTypeGrayed = TF_LBMENUF_GRAYED,              // 0x10
};

// Represents a tuple to specify the content of a language bar menu item.
struct TipLangBarMenuItem {
  int flags_;
  UINT item_id_;
  UINT text_id_;
  UINT icon_id_for_non_theme_;
  UINT icon_id_for_theme_;
};

// Represents the data possessed internally by a language bar menu item.
struct TipLangBarMenuData {
  int flags_;
  UINT item_id_;
  UINT text_id_;
  UINT icon_id_for_non_theme_;
  UINT icon_id_for_theme_;
  int length_;
  wchar_t text_[TF_LBI_DESC_MAXLEN];
};

// Represents the data possessed by a language bar menu.
class TipLangBarMenuDataArray {
 public:
  HRESULT Init(HINSTANCE instance, const TipLangBarMenuItem *menu, int count);

  size_t size() const;
  TipLangBarMenuData *data(size_t i);

 private:
  std::vector<TipLangBarMenuData> data_;
};

MIDL_INTERFACE(IIDSTR_IMozcLangBarItem)
IMozcLangBarItem : public IUnknown {
  // Sets the status of this language bar menu.
  virtual STDMETHODIMP SetEnabled(bool enabled) = 0;
};

MIDL_INTERFACE(IIDSTR_IMozcLangBarToggleItem)
IMozcLangBarToggleItem : public IUnknown {
  // Selects a menu item which has the given |menu_id|.
  virtual STDMETHODIMP SelectMenuItem(UINT menu_id) = 0;
};

// Represents the common operations for a button-menu item in the language bar.
class TipLangBarButton : public TipComImplements<ITfLangBarItemButton,
                                                 ITfSource, IMozcLangBarItem> {
 public:
  TipLangBarButton(wil::com_ptr_nothrow<TipLangBarCallback> lang_bar_callback,
                   const GUID &guid, bool is_menu, bool show_in_tray);

  // The ITfLangBarItem interface methods
  STDMETHODIMP GetInfo(TF_LANGBARITEMINFO *item_info) override = 0;
  STDMETHODIMP GetStatus(DWORD *status) override;
  STDMETHODIMP Show(BOOL show) override;
  STDMETHODIMP GetTooltipString(BSTR *tooltip) override;

  // The ITfLangBarItemButton interface methods
  STDMETHODIMP OnClick(TfLBIClick click, POINT point,
                       const RECT *rect) override;
  STDMETHODIMP InitMenu(ITfMenu *menu) override = 0;
  STDMETHODIMP OnMenuSelect(UINT menu_id) override = 0;
  STDMETHODIMP GetIcon(HICON *icon) override = 0;
  STDMETHODIMP GetText(BSTR *text) override;

  // The ITfSource interface methods
  STDMETHODIMP AdviseSink(REFIID interface_id, IUnknown *unknown,
                          DWORD *cookie) override;
  STDMETHODIMP UnadviseSink(DWORD cookie) override;

  // The IMozcLangBarItem interface method
  STDMETHODIMP SetEnabled(bool enabled) override;

  // Initializes an ImeButtonMenu instance.
  // This function allocates resources for an ImeButtonMenu instance.
  HRESULT Init(HINSTANCE instance, int string_id,
               const TipLangBarMenuItem *menu, int count);

  // Notifies the language bar of a change in a language bar item.
  STDMETHODIMP OnUpdate(DWORD update_flag);

  // Returns true if a 32-bpp icon can be displayed as a context menu item on
  // the LangBar.  See http://b/2260057 and http://b/2265755
  // for details.
  static bool CanContextMenuDisplay32bppIcon();

 protected:
  // Update the item description. The caller is also responsible for calling
  // OnUpdate method to notify the change to the system.
  void SetDescription(const std::wstring &description);

  // Returns the i-th data in the language bar menu.
  // Returns nullptr if i is out of bounds.
  TipLangBarMenuData *menu_data(size_t i);

  // Returns the size of the language bar menu.
  size_t menu_data_size() const;

  // Returns the item information for langbar menu.
  const TF_LANGBARITEMINFO *item_info() const;

  // Returns true if the attribute is menu button.
  bool IsMenuButton() const;

  // Sets if context menu is enabled or not. Is setting affects only when
  // IsMenuButton() returns false.
  void SetContextMenuEnabled(bool enabled);

  wil::com_ptr_nothrow<ITfLangBarItemSink> item_sink_;
  // Save the TipLangBarCallback object that owns this button to prevent the
  // object from being deleted.
  wil::com_ptr_nothrow<TipLangBarCallback> lang_bar_callback_;

 private:
  // Represents the information of an instance copied to the TSF manager.
  // The TSF manager uses this information to identifies an instance as
  // a menu button.
  TF_LANGBARITEMINFO item_info_;

  // Represents the data possessed by the language bar menu.
  TipLangBarMenuDataArray menu_data_;

  // Records TF_LBI_STATUS_* bits and represents the status of the this langbar
  // menu.
  DWORD status_;

  // Represents if context menu is enabled or not. This flag is not used when
  // IsMenuButton() returns true.
  bool context_menu_enabled_;
};

// Represents the common operations for a button-menu item with an icon in the
// language bar.
class TipLangBarMenuButton final : public TipLangBarButton {
 public:
  TipLangBarMenuButton(TipLangBarCallback *langbar_callback, const GUID &guid,
                       bool show_in_tray);

  STDMETHODIMP GetInfo(TF_LANGBARITEMINFO *item_info) override;

  // A part of the ITfLangBarItemButton interface methods
  STDMETHODIMP InitMenu(ITfMenu *menu) override;
  STDMETHODIMP OnMenuSelect(UINT menu_id) override;
  STDMETHODIMP GetIcon(HICON *icon) override;

  // Initializes an ImeButtonMenu instance.
  // This function allocates resources for an ImeButtonMenu instance.
  HRESULT Init(HINSTANCE instance, UINT string_id,
               const TipLangBarMenuItem *menu, int count,
               UINT menu_icon_id_for_non_theme, UINT menu_icon_id_for_theme);

 private:
  // Represents the icon of the language bar menu.
  UINT menu_icon_id_for_theme_;
  UINT menu_icon_id_for_non_theme_;
};

// Represents the common operations for a toggle button-menu item in the
// language bar.
class TipLangBarToggleButton : public TipLangBarButton,
                               public IMozcLangBarToggleItem {
 public:
  TipLangBarToggleButton(TipLangBarCallback *langbar_callback, const GUID &guid,
                         bool is_menu, bool show_in_tray);

  // The IUnknown interface methods
  // TODO(yuryu): Directly derive from TipLangBarButton and remove these
  // overrides.
  STDMETHODIMP_(ULONG) AddRef() override { return TipLangBarButton::AddRef(); }
  STDMETHODIMP_(ULONG) Release() override {
    return TipLangBarButton::Release();
  }
  STDMETHODIMP QueryInterface(REFIID guid, void **object) override;

  // The IMozcLangBarToggleItem interface methods
  STDMETHODIMP SelectMenuItem(UINT menu_id) override;

  // The IMozcLangBarItem interface method
  // Overridden from TipLangBarButton.
  STDMETHODIMP SetEnabled(bool enabled) override;

  STDMETHODIMP GetInfo(TF_LANGBARITEMINFO *item_info) override;

  STDMETHODIMP InitMenu(ITfMenu *menu) override;
  STDMETHODIMP OnMenuSelect(UINT menu_id) override;
  STDMETHODIMP GetIcon(HICON *icon) override;

  // Initializes an ImeButtonMenu instance.
  // This function allocates resources for an ImeButtonMenu instance.
  HRESULT Init(HINSTANCE instance, int string_id,
               const TipLangBarMenuItem *menu, int count,
               const TipLangBarMenuItem &menu_for_disabled);

 private:
  // Represents the index of the selected menu item.
  UINT menu_selected_;
  bool disabled_;
  std::wstring description_for_enabled_;
  TipLangBarMenuData menu_data_for_disabled_;
};

// Represents the common operations for a button-menu item in the system
// language bar.
class TipSystemLangBarMenu : public TipComImplements<ITfSystemLangBarItemSink> {
 public:
  TipSystemLangBarMenu(
      wil::com_ptr_nothrow<TipLangBarCallback> lang_bar_callback,
      const GUID &guid);

  // The ITfLangBarSystemItem interface methods
  STDMETHODIMP InitMenu(ITfMenu *menu) override;
  STDMETHODIMP OnMenuSelect(UINT menu_id) override;

  // Initializes an ImeButtonMenu instance.
  // This function allocates resources for an ImeButtonMenu instance.
  HRESULT Init(HINSTANCE instance, const TipLangBarMenuItem *menu, int count);

 private:
  // Save the TipLangBarCallback object that owns this menu to prevent the
  // object from being deleted.
  wil::com_ptr_nothrow<TipLangBarCallback> lang_bar_callback_;

  // Represents the data possessed by the language bar menu.
  TipLangBarMenuDataArray menu_data_;
};

}  // namespace tsf
}  // namespace win32
}  // namespace mozc

#endif  // THIRD_PARTY_MOZC_SRC_WIN32_TIP_TIP_LANG_BAR_MENU_H_
