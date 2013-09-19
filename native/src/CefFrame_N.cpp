// Copyright (c) 2010 Lime Wire, LLC. All rights reserved. Use of this source
// Copyright (c) 2013 Agitech http://agitech.net, LLC. All rights reserved. Use of this source
// Contributor Nassim MOUALEK nmoualek@agitech.net, agitechs@gmail.com
// code is governed by a BSD-style license that can be found in the LICENSE file.

#include "CefFrame_N.h"
#include "include/cef_v8.h"
#include "SystemUtilities.h"
#include "include/cef_task.h"
#include "include/cef_runnable.h"

JNIEXPORT void JNICALL Java_org_limewire_cef_CefFrame_1N_N_1Destroy
  (JNIEnv *env, jobject obj)
{
	CefRefPtr<CefFrame> frame(
		(CefFrame*)GetCefBaseFromJNIObject(env, obj));
	if(!frame.get())
		return;

	// Clear the value pointer member of the Java object. This call will
	// release the extra reference to the value object added when the Java
	// object was created.
	SetCefBaseForJNIObject(env, obj, NULL, 0);
}
class LoadUrlTask : public CefTask
{
public:
	JNIEnv *env_; 
	jobject obj_;
	jstring url_;
	LoadUrlTask(JNIEnv *env, jobject obj, jstring url) {
		env_ = env;
		obj_ = obj;
		url_ = url;
	}
	LoadUrlTask() {}
	virtual void Execute(CefThreadId threadId)
	{			
		CefRefPtr<CefFrame> frame( (CefFrame*) GetCefBaseFromJNIObject(env_, obj_) );
		if(!frame)
			return;
		frame->LoadURL(GetStringFromJNI(env_, url_));				
	}
	IMPLEMENT_REFCOUNTING(JavaScriptTask);
};

JNIEXPORT void JNICALL Java_org_limewire_cef_CefFrame_1N_N_1LoadURL
  (JNIEnv *env, jobject obj, jstring url)
{
	CefRefPtr<CefFrame> frame( (CefFrame*) GetCefBaseFromJNIObject(env, obj) );
	if(!frame)
		return;
	frame->LoadURL(GetStringFromJNI(env, url));			
	//CefRefPtr<CefTask> loadUrlTask(new LoadUrlTask(env, obj, url));
	//CefPostTask(TID_UI, loadUrlTask);
}
JNIEXPORT void JNICALL Java_org_limewire_cef_CefFrame_1N_N_1ExecuteJavaScript
  (JNIEnv *env, jobject obj, jstring jsCode, jstring scriptUrl, jint startLine)
{
	CefRefPtr<CefFrame> frame( (CefFrame*) GetCefBaseFromJNIObject(env, obj) );
	if(!frame)
		return;
	frame->ExecuteJavaScript(GetStringFromJNI(env, jsCode), GetStringFromJNI(env, scriptUrl), startLine);		
}

JNIEXPORT jboolean JNICALL Java_org_limewire_cef_CefFrame_1N_N_1IsMain
  (JNIEnv *env, jobject obj)
{
	CefRefPtr<CefFrame> frame(
		(CefFrame*)GetCefBaseFromJNIObject(env, obj));
	if(!frame.get())
		return JNI_FALSE;

	return frame->IsMain() ? JNI_TRUE : JNI_FALSE;
}

JNIEXPORT jboolean JNICALL Java_org_limewire_cef_CefFrame_1N_N_1IsFocused
  (JNIEnv *env, jobject obj)
{
	CefRefPtr<CefFrame> frame(
		(CefFrame*)GetCefBaseFromJNIObject(env, obj));
	if(!frame.get())
		return JNI_FALSE;

	return frame->IsFocused() ? JNI_TRUE : JNI_FALSE;
}
