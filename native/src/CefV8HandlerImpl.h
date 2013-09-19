// Copyright (c) 2010 Lime Wire, LLC. All rights reserved. Use of this source
// Copyright (c) 2013 Agitech http://agitech.net, LLC. All rights reserved. Use of this source
// Contributor Nassim MOUALEK nmoualek@agitech.net, agitechs@gmail.com
// code is governed by a BSD-style license that can be found in the LICENSE file.

// Copyright (c) 2010 Lime Wire, LLC. All rights reserved. Use of this source
// code is governed by a BSD-style license that can be found in the LICENSE file.

#ifndef _CEFV8HANDLERIMPL_H
#define _CEFV8HANDLERIMPL_H

#include <jni.h>
#include "include/cef_v8.h"

class CefV8HandlerImpl : public CefV8Handler
{
public:
	CefV8HandlerImpl(JNIEnv* env, jobject handler);
	virtual ~CefV8HandlerImpl();

	virtual bool Execute(const CefString& name,
                       CefRefPtr<CefV8Value> object,
                       const CefV8ValueList& arguments,
                       CefRefPtr<CefV8Value>& retval,
                       CefString& exception);
	int AddRef(void);
	int Release(void);
	int GetRefCt(void);

	jobject handler() { return jhandler_; }

private:
	jobject jhandler_;
};

#endif // _CEFV8HANDLERIMPL_H
