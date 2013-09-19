// Copyright (c) 2010 Lime Wire, LLC. All rights reserved. Use of this source
// Copyright (c) 2013 Agitech http://agitech.net, LLC. All rights reserved. Use of this source
// Contributor Nassim MOUALEK nmoualek@agitech.net, agitechs@gmail.com
// code is governed by a BSD-style license that can be found in the LICENSE file.

#ifndef _SYSTEM_UTILITIES_WIN_H
#define _SYSTEM_UTILITIES_WIN_H

#include <jni.h>
#include <jawt.h>
#include <windows.h>

JAWT* GetJAWT(JNIEnv *e, jclass c, jobject inFrame);

// Gets the window handle from Java  and returns it. |frame| is an AWT Component
// like a JFrame that is backed by a real Windows window.
HWND GetJavaWindowHandle(JNIEnv *e, jclass c, jobject inFrame);

#endif // _SYSTEM_UTILITIES_WIN_H

