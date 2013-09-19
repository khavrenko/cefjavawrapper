#include "JavaScriptTask.h"
#include <include/cef_runnable.h>
#include <include/cef_v8.h>
#include <jni.h>
#include <vector>
JavaScriptTask::JavaScriptTask(CefFrame * frame):
										frame_(NULL){
		frame_ = frame;
	}

virtual void Execute(CefThreadId threadId)	
	{
		frame_->ExecuteJavaScript("alert('gawed')", "", 0);
	}

int JavaScriptTask::AddRef(void){
	return 0;	
}
int JavaScriptTask::GetRefCt(void){
	return 0;	
}
int JavaScriptTask::Release(void){
	return 0;
}
