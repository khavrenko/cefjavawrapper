// Copyright (c) 2010 Lime Wire, LLC. All rights reserved. Use of this source
// Copyright (c) 2013 Agitech http://agitech.net, LLC. All rights reserved. Use of this source
// Contributor Nassim MOUALEK nmoualek@agitech.net, agitechs@gmail.com
// code is governed by a BSD-style license that can be found in the LICENSE file.

#include "SystemUtilities.h"
#include "include/cef_browser.h"
#include <jawt.h>
#include <string>
#include <jni.h>
CefString GetStringFromJNI(JNIEnv* env, jstring jstr)
{
	CefString wstr;
	const char* chr = NULL;
	if(jstr)
		chr = env->GetStringUTFChars(jstr, NULL);
	if(chr)
		wstr = chr;
	env->ReleaseStringUTFChars(jstr, chr);
	return wstr;
}

jstring CreateJNIString(JNIEnv* env, const CefString& str)
{
  std::string cstr(str);
	return env->NewStringUTF(cstr.c_str());
}

jobjectArray CreateJNIStringArray(JNIEnv* env,
								  const std::vector<CefString>& vals)
{
	if(vals.empty())
		return NULL;

	jobjectArray arr = env->NewObjectArray(vals.size(),
		env->FindClass("java/lang/String"),
		CreateJNIString(env, CefString()));

	for(size_t i = 0; i < vals.size(); i++)
		env->SetObjectArrayElement(arr, i, CreateJNIString(env, vals[i]));

	return arr;
}

jobject CreateJNIObject(JNIEnv* env, const char* class_name, CefBase* base, jlong base_ptr)
{
	jclass cls = env->FindClass(class_name);
	if(!cls)
	{
		env->ExceptionClear();
		return NULL;
	}

	jmethodID initID = env->GetMethodID(cls, "<init>", "()V");
	if(initID == 0)
	{
		env->ExceptionClear();
		return NULL;
	}

	jobject obj = env->NewObject(cls, initID);
	if(obj == NULL)
	{
		env->ExceptionClear();
		return NULL;
	}

	if(base && !SetCefBaseForJNIObject(env, obj, base, base_ptr))
		return NULL;	
	return obj;
}

bool SetCefBaseForJNIObject(JNIEnv* env, jobject obj, CefBase* base, jlong base_ptr)
{	
	jclass cls = env->GetObjectClass(obj);
	jfieldID handleID = env->GetFieldID(cls, "N_CefHandle", "J");
	if(handleID == 0)
	{
		env->ExceptionClear();
		return false;
	}

	CefBase* oldbase = (CefBase*)env->GetLongField(obj, handleID);
	
	if(oldbase)
	{		
		// Remove a reference from the previous base object.
		oldbase = (CefBrowser*)env->GetLongField(obj, handleID);				
		int r = oldbase->GetRefCt();						
		oldbase->Release();
	}
	env->SetLongField(obj, handleID, (jlong)base_ptr);
	if(base)
	{
		// Add a reference to the new base object.
		base->AddRef();				
		int r = base->GetRefCt();
		r++;
	}
	return true;
}
jlong GetFieldFromJNIObject(JNIEnv* env, jobject obj, const char* field_name)
{
	jclass cls = env->GetObjectClass(obj);
	jfieldID handleID = env->GetFieldID(cls, field_name, "J");
	if(handleID == 0)
	{
		env->ExceptionClear();
		return NULL;
	}
	return env->GetLongField(obj, handleID);
}
jlong GetCefBaseFromJNIObject(JNIEnv* env, jobject obj)
{
	jclass cls = env->GetObjectClass(obj);
	jfieldID handleID = env->GetFieldID(cls, "N_CefHandle", "J");
	if(handleID == 0)
	{
		env->ExceptionClear();
		return NULL;
	}
	return env->GetLongField(obj, handleID);
}
