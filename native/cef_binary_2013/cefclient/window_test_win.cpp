// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "cefclient/window_test.h"

namespace window_test {

namespace {

// Toggles the current display state.
void Toggle(CefWindowHandle handle, UINT nCmdShow) {
  HWND root_wnd = ::GetAncestor(handle, GA_ROOT);

  // Retrieve current window placement information.
  WINDOWPLACEMENT placement;
  ::GetWindowPlacement(root_wnd, &placement);

  if (placement.showCmd == nCmdShow)
    ::ShowWindow(root_wnd, SW_RESTORE);
  else
    ::ShowWindow(root_wnd, nCmdShow);
}

}  // namespace

void SetPos(CefWindowHandle handle, int x, int y, int width, int height) {
  HWND root_wnd = ::GetAncestor(handle, GA_ROOT);

  // Retrieve current window placement information.
  WINDOWPLACEMENT placement;
  ::GetWindowPlacement(root_wnd, &placement);

  // Retrieve information about the display that contains the window.
  HMONITOR monitor = MonitorFromRect(&placement.rcNormalPosition,
                                     MONITOR_DEFAULTTONEAREST);
  MONITORINFO info;
  info.cbSize = sizeof(info);
  GetMonitorInfo(monitor, &info);

  // Make sure the window is inside the display.
  CefRect display_rect(
      info.rcWork.left,
      info.rcWork.top,
      info.rcWork.right - info.rcWork.left,
      info.rcWork.bottom - info.rcWork.top);
  CefRect window_rect(x, y, width, height);
  ModifyBounds(display_rect, window_rect);

  if (placement.showCmd == SW_MINIMIZE || placement.showCmd == SW_MAXIMIZE) {
    // The window is currently minimized or maximized. Restore it to the desired
    // position.
    placement.rcNormalPosition.left = window_rect.x;
    placement.rcNormalPosition.right = window_rect.x + window_rect.width;
    placement.rcNormalPosition.top = window_rect.y;
    placement.rcNormalPosition.bottom = window_rect.y + window_rect.height;
    ::SetWindowPlacement(root_wnd, &placement);
    ::ShowWindow(root_wnd, SW_RESTORE);
  } else {
    // Set the window position.
    ::SetWindowPos(root_wnd, NULL, window_rect.x, window_rect.y,
                   window_rect.width, window_rect.height, SWP_NOZORDER);
  }
}

void Minimize(CefWindowHandle handle) {
  Toggle(handle, SW_MINIMIZE);
}

void Maximize(CefWindowHandle handle) {
  Toggle(handle, SW_MAXIMIZE);
}

void Restore(CefWindowHandle handle) {
  ::ShowWindow(::GetAncestor(handle, GA_ROOT), SW_RESTORE);
}

}  // namespace window_test
