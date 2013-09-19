// Copyright (c) 2010 Lime Wire, LLC. All rights reserved. Use of this source
// Copyright (c) 2013 Agitech http://agitech.net, LLC. All rights reserved. Use of this source
// Contributor Nassim MOUALEK nmoualek@agitech.net, agitechs@gmail.com
// code is governed by a BSD-style license that can be found in the LICENSE file.


#ifndef _CEFBASEIMPL_H
#define _CEFBASEIMPL_H
#include <include/cef_runnable.h>
#include <include/cef_v8.h>
#include <jni.h>
#include <vector>

class CefBaseImpl: public virtual CefV8Accessor{
public:
	CefBaseImpl(JNIEnv* env, jobject object);
	virtual ~CefBaseImpl();
	int AddRef(void);
	int Release(void);
	int GetRefCt(void);
	bool Get(const CefString &,const CefRefPtr<CefV8Value>,CefRefPtr<CefV8Value> &,CefString &);
	bool Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString& exception);
	jobject object() { return jobject_; }
private:
	jobject jobject_;
};
#endif // _CEFBASEIMPL_H
