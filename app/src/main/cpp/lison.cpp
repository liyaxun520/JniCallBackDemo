#include <jni.h>
#include <pthread.h>   //引入线程
#include<android/log.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "native-activity", __VA_ARGS__))

JavaVM *g_jvm ;
jobject g_obj;
#define NUMTHREADS 10

//当动态库被加载时这个函数被系统调用
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved)
{
    JNIEnv* env = NULL;
    jint result = -1;

    //获取JNI版本
    if (vm->GetEnv((void**)&env, JNI_VERSION_1_4) != JNI_OK)
    {
        LOGE("GetEnv failed!");
        return result;
    }

    return JNI_VERSION_1_4;
}

extern "C"
JNIEXPORT void JNICALL Java_com_lison_jnicallbackdemo_JniCall_start(JNIEnv *env, jobject jniObject){

    jclass jniClass = env->GetObjectClass(jniObject);
    if(jniClass == NULL){
        return;
    }

    //执行method01
    jmethodID methodId = env->GetMethodID(jniClass,"callMethod01", "()V");
    //执行回调方法
    env->CallVoidMethod(jniObject,methodId); //参数1   方法所在的对象  2 方法id  3

    //执行method02
    jmethodID methodId02 = env->GetMethodID(jniClass,"callMethod02","(Ljava/lang/String;Ljava/lang/String;I)I");
    env->CallIntMethod(jniObject,methodId02,env->NewStringUTF("lison"),env->NewStringUTF("is"),30);
 };


void *thread_fun(void* arg){
    JNIEnv *env;
    jclass cls;
    jmethodID mid;

    //Attach主线程
    if(g_jvm->AttachCurrentThread(&env, NULL) != JNI_OK)
    {
        LOGE("%s: AttachCurrentThread() failed", __FUNCTION__);
        return NULL;
    }
    //找到对应的类
    cls = env->GetObjectClass(g_obj);
    if(cls == NULL)
    {
        LOGE("FindClass() Error.....");
        goto error;
    }
    //再获得类中的方法
    mid = env->GetStaticMethodID(cls, "fromJNI", "(I)V");
    if (mid == NULL)
    {
        LOGE("GetMethodID() Error.....");
        goto error;
    }
    //最后调用java中的静态方法
    env->CallStaticVoidMethod( cls, mid ,(int)arg);
    error:
    //Detach主线程
    if(g_jvm->DetachCurrentThread() != JNI_OK){
        LOGE("%s: DetachCurrentThread() failed", __FUNCTION__);
    }
    pthread_exit(0);
}
extern "C"
JNIEXPORT void JNICALL Java_com_lison_jnicallbackdemo_JniCall_mainThread
        (JNIEnv *env, jobject obj){
    int i;
    pthread_t pt[NUMTHREADS];
    for(i;i<NUMTHREADS;i++){
        pthread_create(&pt[i],NULL, &thread_fun, (void *)i);
    }
};


extern "C"
JNIEXPORT void JNICALL Java_com_lison_jnicallbackdemo_JniCall_setJNIEnv
        (JNIEnv *env, jobject obj){
    env->GetJavaVM(&g_jvm);
    //不能直接赋值(g_obj = obj)
    g_obj = env->NewGlobalRef(obj);

};

