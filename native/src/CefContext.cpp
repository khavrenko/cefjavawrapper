// Copyright (c) 2010 Lime Wire, LLC. All rights reserved. Use of this source
// Copyright (c) 2013 Agitech http://agitech.net, LLC. All rights reserved. Use of this source
// Contributor Nassim MOUALEK nmoualek@agitech.net, agitechs@gmail.com
// code is governed by a BSD-style license that can be found in the LICENSE file.


#include "CefV8HandlerImpl.h"
#include "include/cef_v8.h"
#include "include/cef_task.h"
#include "include/cef_runnable.h"
#include "CefContext.h"
#include "SystemUtilities.h"
#include "CefBaseImpl.h"
#include "client_app.h"
#include "TlHelp32.h"
// Path to Java DLL.
wchar_t g_JavaPath[512] = {0};

// JNI environment pointers for each thread.
JNIEnv* g_PerThreadEnv[3] = {0};

cef_thread_id_t GetCurrrentThreadID(){
	if(CefCurrentlyOn(TID_UI))
		return TID_UI;
	else if(CefCurrentlyOn(TID_IO))
		return TID_IO;
	else if(CefCurrentlyOn(TID_FILE))
		return TID_FILE;
	else if(CefCurrentlyOn(TID_DB))
		return TID_DB;
	else if(CefCurrentlyOn(TID_FILE_USER_BLOCKING))
		return TID_FILE_USER_BLOCKING;
	else if(CefCurrentlyOn(TID_PROCESS_LAUNCHER))
	  return TID_PROCESS_LAUNCHER;
	else
	  return TID_RENDERER;
}
JNIEnv* GetJNIEnv()
{
	return g_PerThreadEnv[GetCurrrentThreadID()];  	
}

// Task used to attach Java to CEF threads.
class JavaThreadInitTask : public CefTask
{
public:
	JavaThreadInitTask() {}	
	virtual void Execute()
	{
		JavaVM* jvm = GetJavaVM();
		JNIEnv* jenv;
		if(jvm && jvm->AttachCurrentThread((void**)&jenv, NULL) == 0)
		{						
			g_PerThreadEnv[GetCurrrentThreadID()] = jenv;
			HANDLE id = GetCurrentThread();
			SetThreadPriority(id, 2);
		}
	}
	IMPLEMENT_REFCOUNTING(JavaThreadInitTask);
};

// Task used to detach Java from CEF threads.
class JavaThreadDestroyTask : public CefTask
{
public:
	JavaThreadDestroyTask() {}
	virtual void Execute()
	{
		JavaVM* jvm = GetJavaVM();
		if(jvm)
		{
			jvm->DetachCurrentThread();
			
		}
	}
	IMPLEMENT_REFCOUNTING(JavaThreadDestroyTask);
};

JNIEXPORT jboolean JNICALL Java_org_limewire_cef_CefContext_N_1Initialize
  (JNIEnv *env, jclass c, jstring argPathToJavaDLL, jstring cachePath)
{
	// Store the path to the Java DLL globally.
  std::wstring path = GetStringFromJNI(env, argPathToJavaDLL);
#ifdef _WIN32
	wcsncpy_s(g_JavaPath, 512, path.c_str(), _TRUNCATE);
#else
  wcsncpy(g_JavaPath, path.c_str(), 512);
#endif

	CefSettings settings;
	CefBrowserSettings browserSettings;
	//settings.browser_subprocess_path "C:/Program Files (x86)/java/jdk1.6.0_31/bin/java.exe";
#ifdef _WIN32
	settings.multi_threaded_message_loop = true;
#endif // _WIN32
	settings.single_process = false;
	settings.pack_loading_disabled = false;
	CefString cachePathStr(GetStringFromJNI(env, cachePath));
	cef_string_set(cachePathStr.c_str(), cachePathStr.length(),
		&settings.cache_path, true);
	 
	// Initialize CEF.
	 CefRefPtr<ClientApp> cef_app(new ClientApp);


	 CefMainArgs main_args(GetModuleHandle(NULL));	 
	if(!CefInitialize(main_args, settings, cef_app.get()))
		return JNI_FALSE;

	CefRefPtr<CefTask> initTask(new JavaThreadInitTask);
	CefPostTask(TID_UI, initTask);
	CefPostTask(TID_IO, initTask);
	CefPostTask(TID_FILE, initTask);
	
	return JNI_TRUE;
}
DWORD GetMainThreadId() {
    const std::tr1::shared_ptr<void> hThreadSnapshot(
        CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0), CloseHandle);
    if (hThreadSnapshot.get() == INVALID_HANDLE_VALUE) {
        throw std::runtime_error("GetMainThreadId failed");
    }
    THREADENTRY32 tEntry;
    tEntry.dwSize = sizeof(THREADENTRY32);
    DWORD result = 0;
    DWORD currentPID = GetCurrentProcessId();
    for (BOOL success = Thread32First(hThreadSnapshot.get(), &tEntry);
        !result && success && GetLastError() != ERROR_NO_MORE_FILES;
        success = Thread32Next(hThreadSnapshot.get(), &tEntry))
    {
        if (tEntry.th32OwnerProcessID == currentPID) {
            result = tEntry.th32ThreadID;
        }
    }
    return result;
}
JNIEXPORT void JNICALL Java_org_limewire_cef_CefContext_N_1Shutdown
  (JNIEnv *env, jclass)
{
	
	CefRefPtr<CefTask> destroyTask(new JavaThreadDestroyTask());
	CefPostTask(TID_UI, destroyTask);
	CefPostTask(TID_IO, destroyTask);
	CefPostTask(TID_FILE, destroyTask);
	
	CefShutdown();

}

JNIEXPORT jobject JNICALL Java_org_limewire_cef_CefContext_N_1CreateV8Undefined
  (JNIEnv *env, jclass)
{
	CefRefPtr<CefV8Value> value(CefV8Value::CreateUndefined());
	return CreateJNIObject(env, "org/limewire/cef/CefV8Value_N", value.get(), (jlong)value.get());
}

JNIEXPORT jobject JNICALL Java_org_limewire_cef_CefContext_N_1CreateV8Null
  (JNIEnv *env, jclass)
{
	CefRefPtr<CefV8Value> value(CefV8Value::CreateNull());
	return CreateJNIObject(env, "org/limewire/cef/CefV8Value_N", value.get(), (jlong)value.get());
}

JNIEXPORT jobject JNICALL Java_org_limewire_cef_CefContext_N_1CreateV8Bool
  (JNIEnv *env, jclass, jboolean val)
{
	CefRefPtr<CefV8Value> value(
		CefV8Value::CreateBool(val==JNI_TRUE?true:false));
	return CreateJNIObject(env, "org/limewire/cef/CefV8Value_N", value.get(), (jlong)value.get());
}

JNIEXPORT jobject JNICALL Java_org_limewire_cef_CefContext_N_1CreateV8Int
  (JNIEnv *env, jclass, jint val)
{
	CefRefPtr<CefV8Value> value(CefV8Value::CreateInt(val));
	return CreateJNIObject(env, "org/limewire/cef/CefV8Value_N", value.get(), (jlong)value.get());
}

JNIEXPORT jobject JNICALL Java_org_limewire_cef_CefContext_N_1CreateV8Double
  (JNIEnv *env, jclass, jdouble val)
{
	CefRefPtr<CefV8Value> value(CefV8Value::CreateDouble(val));
	return CreateJNIObject(env, "org/limewire/cef/CefV8Value_N", value.get(), (jlong)value.get());
}

JNIEXPORT jobject JNICALL Java_org_limewire_cef_CefContext_N_1CreateV8String
  (JNIEnv *env, jclass, jstring val)
{
	CefRefPtr<CefV8Value> value(
		CefV8Value::CreateString(GetStringFromJNI(env, val)));
	return CreateJNIObject(env, "org/limewire/cef/CefV8Value_N", value.get(), (jlong)value.get());
}

JNIEXPORT jobject JNICALL Java_org_limewire_cef_CefContext_N_1CreateV8Object
  (JNIEnv *env, jclass, jobject user_data)
{
	CefRefPtr<CefV8Accessor> base;
	if(user_data) 
		base = new CefBaseImpl(env, user_data);
	CefRefPtr<CefV8Value> value(CefV8Value::CreateObject(base));
	return CreateJNIObject(env, "org/limewire/cef/CefV8Value_N", value.get(), (jlong)value.get());
}

JNIEXPORT jobject JNICALL Java_org_limewire_cef_CefContext_N_1CreateV8Array
  (JNIEnv *env, jclass)
{
	CefRefPtr<CefV8Value> value(CefV8Value::CreateArray(0));
	return CreateJNIObject(env, "org/limewire/cef/CefV8Value_N", value.get(), (jlong)value.get());
}

JNIEXPORT jobject JNICALL Java_org_limewire_cef_CefContext_N_1CreateV8Function
  (JNIEnv *env, jclass, jstring name, jobject hobj)
{
	if(!hobj)
		return NULL;

	CefRefPtr<CefV8Handler> handler(new CefV8HandlerImpl(env, hobj));
	CefRefPtr<CefV8Value> value(
		CefV8Value::CreateFunction(GetStringFromJNI(env, name), handler));
	return CreateJNIObject(env, "org/limewire/cef/CefV8Value_N", value.get(), (jlong)value.get());
}
