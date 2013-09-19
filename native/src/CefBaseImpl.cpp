// Copyright (c) 2010 Lime Wire, LLC. All rights reserved. Use of this source
// Copyright (c) 2013 Agitech http://agitech.net, LLC. All rights reserved. Use of this source
// Contributor Nassim MOUALEK nmoualek@agitech.net, agitechs@gmail.com
// code is governed by a BSD-style license that can be found in the LICENSE file.


#include "CefBaseImpl.h"
#include "SystemUtilities.h"
bool CefBaseImpl::Get(const CefString &,const CefRefPtr<CefV8Value>,CefRefPtr<CefV8Value> &,CefString &){
	return true;
}
bool CefBaseImpl::Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString& exception){
	return true;
}
int CefBaseImpl::AddRef(void){
	return (uintptr_t)jobject_;	
}
int CefBaseImpl::GetRefCt(void){
	return (uintptr_t)jobject_;	
}
int CefBaseImpl::Release(void){
	JNIEnv* env = GetJNIEnv();
	if(env)
		env->DeleteGlobalRef(jobject_);	
	return 0;
}
CefBaseImpl::CefBaseImpl(JNIEnv* env, jobject object)
{
	// Create a new global reference.
	jobject_ = env->NewGlobalRef(object);
}

CefBaseImpl::~CefBaseImpl()
{
	// Release the global reference.
	JNIEnv* env = GetJNIEnv();
	if(env)
		env->DeleteGlobalRef(jobject_);
}
