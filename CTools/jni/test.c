#include "jni.h"
#include "My_Opencv.h"

My_Opencv *mine=NULL;

void input_Image(JNIEnv* env, jobject obj, jstring primary_image,jstring match_image)
{
	const char * image1=env->GetStringUTFChars(primary_image, 0);
	const char * image2=env->GetStringUTFChars(match_image, 0);
	mine = new My_Opencv(image1, image2);
	env->ReleaseStringUTFChars(primary_image, image1);
	env->ReleaseStringUTFChars(match_image, image2);
	
	
}
jfloat get_sample(JNIEnv* env, jobject obj)
{
	return mine->get_sample();
}
jint get_x(JNIEnv* env, jobject obj)
{
	if (mine != NULL)
	{
		return mine->get_x();
	}
	else
		return -1;
}
jint get_y(JNIEnv* env, jobject obj)
{
	if (mine != NULL)
	{
		return mine->get_y();
	}
	else
		return -1;
}
void debug_show_Image(JNIEnv* env, jobject obj)
{
	if (mine != NULL)
	{
		mine->Debug_Show_Image();
	}
	
}
void Image_Cap(JNIEnv* env, jobject obj,jint x, jint y, jint width, jint height, jstring read_path, jstring save_path)
{
	const char *path1= env->GetStringUTFChars(read_path, 0);
	const char *path2=env->GetStringUTFChars(save_path, 0);
	My_Opencv::Image_Cap(x, y, width, height, path1, path2);
	env->ReleaseStringUTFChars(read_path, path1);
	env->ReleaseStringUTFChars(save_path, path2);
}



jint JNI_OnLoad(JavaVM *vm, void *resolved)
{
	JNINativeMethod jnm[] =
	{
		{(char*)"input_Image",(char*)"(Ljava/lang/String;Ljava/lang/String;)V",input_Image},
		{(char*)"get_sample",(char*)"()F",get_sample},
		{(char*)"get_x",(char*)"()I",get_x},
		{(char*)"get_y",(char*)"()I",get_y},
		{(char*)"debug_show_Image",(char*)"()V",debug_show_Image},
		{(char*)"Image_Cap",(char*)"(IIIILjava/lang/String;Ljava/lang/String;)V",Image_Cap },
	
	
	};



	JNIEnv* env = NULL;

	if (vm->GetEnv((void**)&env, JNI_VERSION_1_6) != JNI_OK)
	{
		return JNI_ERR;
	}
	jclass j = env->FindClass("cn/createqy/autoScripts/Detection");

	if (env->RegisterNatives(j, jnm, 6) < 0)//只有执行这个命令后才能使用env
	{

		return JNI_ERR;
	}
	env->DeleteLocalRef(j);
	return JNI_VERSION_1_6;

}


