#include"jni.h"
#include "jni.h"
#include <stdio.h>


const char *classPathName = "cn/createqy/t1";

/**
 native 函数的实现
**/
jclass m;
jint myadd(JNIEnv *env, jobject thiz, jint a, jint b)
{
	printf("asd");
	return 10;
}
jint speak(JNIEnv* env,jobject obj, jint a, jstring str)
{
	printf("nihao");
	return 0;
}

jint JNI_OnLoad(JavaVM *vm, void *resolved)
{
	JNINativeMethod jnm[] =
	{
		{(char*)"add",(char*)"(II)I",myadd},
	{(char*)"speak",(char*)"(ILjava/lang/String;)I",speak}
	};



	JNIEnv* env = NULL;

	if (vm->GetEnv((void**)&env, JNI_VERSION_1_6) != JNI_OK)
	{
		return JNI_ERR;
	}
	jclass j = env->FindClass("cn/createqy/t1");

	if (env->RegisterNatives(j, jnm, 2) < 0)//只有执行这个命令后才能使用env
	{

		return JNI_ERR;
	}
	env->DeleteLocalRef(j);
	return JNI_VERSION_1_6;

}


/*
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void *resolved)
{
	JNINativeMethod  jnm[] =
	{
		(char*)"add",(char*)"(II)I",myadd
	};
	JNIEnv* env = NULL;
	jint result = -1;
	if (vm->GetEnv((void**)&env, JNI_VERSION_1_6)!=JNI_OK)
	{
		return JNI_ERR;
	}
	jclass j = env->FindClass("cn/createqy/t1");
	if (0 > env->RegisterNatives(j, jnm, 1))
	{
		return JNI_ERR;
	}
	return JNI_VERSION_1_6;
}*/