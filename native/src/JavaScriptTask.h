#include <include/cef_runnable.h>
#include <include/cef_v8.h>
#include <jni.h>
#include <vector>
class JavaScriptTask : public CefTask
{
public: 
	JavaScriptTask(CefFrame * frame);	
	int AddRef(void);
	int Release(void);
	int GetRefCt(void);
private :
	CefFrame * frame_;
	CefString jsCode_;
	CefString scriptUrl_;
	int startLine_;
};