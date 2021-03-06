// Copyright (c) 2010 Lime Wire, LLC. All rights reserved. Use of this source
// Copyright (c) 2013 Agitech http://agitech.net, LLC. All rights reserved. Use of this source
// Contributor Nassim MOUALEK nmoualek@agitech.net, agitechs@gmail.com
// code is governed by a BSD-style license that can be found in the LICENSE file.

/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class org_limewire_cef_CefV8Value_N */

#ifndef _Included_org_limewire_cef_CefV8Value_N
#define _Included_org_limewire_cef_CefV8Value_N
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_limewire_cef_CefV8Value_N
 * Method:    N_Destroy
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_limewire_cef_CefV8Value_1N_N_1Destroy
  (JNIEnv *, jobject);

/*
 * Class:     org_limewire_cef_CefV8Value_N
 * Method:    N_IsUndefined
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_limewire_cef_CefV8Value_1N_N_1IsUndefined
  (JNIEnv *, jobject);

/*
 * Class:     org_limewire_cef_CefV8Value_N
 * Method:    N_IsNull
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_limewire_cef_CefV8Value_1N_N_1IsNull
  (JNIEnv *, jobject);

/*
 * Class:     org_limewire_cef_CefV8Value_N
 * Method:    N_IsBool
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_limewire_cef_CefV8Value_1N_N_1IsBool
  (JNIEnv *, jobject);

/*
 * Class:     org_limewire_cef_CefV8Value_N
 * Method:    N_IsInt
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_limewire_cef_CefV8Value_1N_N_1IsInt
  (JNIEnv *, jobject);

/*
 * Class:     org_limewire_cef_CefV8Value_N
 * Method:    N_IsDouble
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_limewire_cef_CefV8Value_1N_N_1IsDouble
  (JNIEnv *, jobject);

/*
 * Class:     org_limewire_cef_CefV8Value_N
 * Method:    N_IsString
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_limewire_cef_CefV8Value_1N_N_1IsString
  (JNIEnv *, jobject);

/*
 * Class:     org_limewire_cef_CefV8Value_N
 * Method:    N_IsObject
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_limewire_cef_CefV8Value_1N_N_1IsObject
  (JNIEnv *, jobject);

/*
 * Class:     org_limewire_cef_CefV8Value_N
 * Method:    N_IsArray
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_limewire_cef_CefV8Value_1N_N_1IsArray
  (JNIEnv *, jobject);

/*
 * Class:     org_limewire_cef_CefV8Value_N
 * Method:    N_IsFunction
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_limewire_cef_CefV8Value_1N_N_1IsFunction
  (JNIEnv *, jobject);

/*
 * Class:     org_limewire_cef_CefV8Value_N
 * Method:    N_GetBoolValue
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_limewire_cef_CefV8Value_1N_N_1GetBoolValue
  (JNIEnv *, jobject);

/*
 * Class:     org_limewire_cef_CefV8Value_N
 * Method:    N_GetIntValue
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_limewire_cef_CefV8Value_1N_N_1GetIntValue
  (JNIEnv *, jobject);

/*
 * Class:     org_limewire_cef_CefV8Value_N
 * Method:    N_GetDoubleValue
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_org_limewire_cef_CefV8Value_1N_N_1GetDoubleValue
  (JNIEnv *, jobject);

/*
 * Class:     org_limewire_cef_CefV8Value_N
 * Method:    N_GetStringValue
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_limewire_cef_CefV8Value_1N_N_1GetStringValue
  (JNIEnv *, jobject);

/*
 * Class:     org_limewire_cef_CefV8Value_N
 * Method:    N_HasValue
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_org_limewire_cef_CefV8Value_1N_N_1HasValue__Ljava_lang_String_2
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_limewire_cef_CefV8Value_N
 * Method:    N_HasValue
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_org_limewire_cef_CefV8Value_1N_N_1HasValue__I
  (JNIEnv *, jobject, jint);

/*
 * Class:     org_limewire_cef_CefV8Value_N
 * Method:    N_DeleteValue
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_org_limewire_cef_CefV8Value_1N_N_1DeleteValue__Ljava_lang_String_2
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_limewire_cef_CefV8Value_N
 * Method:    N_DeleteValue
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_org_limewire_cef_CefV8Value_1N_N_1DeleteValue__I
  (JNIEnv *, jobject, jint);

/*
 * Class:     org_limewire_cef_CefV8Value_N
 * Method:    N_GetValue
 * Signature: (Ljava/lang/String;)Lorg/limewire/cef/CefV8Value;
 */
JNIEXPORT jobject JNICALL Java_org_limewire_cef_CefV8Value_1N_N_1GetValue__Ljava_lang_String_2
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_limewire_cef_CefV8Value_N
 * Method:    N_GetValue
 * Signature: (I)Lorg/limewire/cef/CefV8Value;
 */
JNIEXPORT jobject JNICALL Java_org_limewire_cef_CefV8Value_1N_N_1GetValue__I
  (JNIEnv *, jobject, jint);

/*
 * Class:     org_limewire_cef_CefV8Value_N
 * Method:    N_SetValue
 * Signature: (Ljava/lang/String;Lorg/limewire/cef/CefV8Value;)Z
 */
JNIEXPORT jboolean JNICALL Java_org_limewire_cef_CefV8Value_1N_N_1SetValue__Ljava_lang_String_2Lorg_limewire_cef_CefV8Value_2
  (JNIEnv *, jobject, jstring, jobject);

/*
 * Class:     org_limewire_cef_CefV8Value_N
 * Method:    N_SetValue
 * Signature: (ILorg/limewire/cef/CefV8Value;)Z
 */
JNIEXPORT jboolean JNICALL Java_org_limewire_cef_CefV8Value_1N_N_1SetValue__ILorg_limewire_cef_CefV8Value_2
  (JNIEnv *, jobject, jint, jobject);

/*
 * Class:     org_limewire_cef_CefV8Value_N
 * Method:    N_GetKeys
 * Signature: ()[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_org_limewire_cef_CefV8Value_1N_N_1GetKeys
  (JNIEnv *, jobject);

/*
 * Class:     org_limewire_cef_CefV8Value_N
 * Method:    N_GetUserData
 * Signature: ()Ljava/lang/Object;
 */
JNIEXPORT jobject JNICALL Java_org_limewire_cef_CefV8Value_1N_N_1GetUserData
  (JNIEnv *, jobject);

/*
 * Class:     org_limewire_cef_CefV8Value_N
 * Method:    N_GetArrayLength
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_limewire_cef_CefV8Value_1N_N_1GetArrayLength
  (JNIEnv *, jobject);

/*
 * Class:     org_limewire_cef_CefV8Value_N
 * Method:    N_GetFunctionName
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_limewire_cef_CefV8Value_1N_N_1GetFunctionName
  (JNIEnv *, jobject);

/*
 * Class:     org_limewire_cef_CefV8Value_N
 * Method:    N_GetFunctionHandler
 * Signature: ()Lorg/limewire/cef/CefV8Handler;
 */
JNIEXPORT jobject JNICALL Java_org_limewire_cef_CefV8Value_1N_N_1GetFunctionHandler
  (JNIEnv *, jobject);

/*
 * Class:     org_limewire_cef_CefV8Value_N
 * Method:    N_ExecuteFunction
 * Signature: (Lorg/limewire/cef/CefV8FunctionParams;)Z
 */
JNIEXPORT jboolean JNICALL Java_org_limewire_cef_CefV8Value_1N_N_1ExecuteFunction
  (JNIEnv *, jobject, jobject);

#ifdef __cplusplus
}
#endif
#endif
