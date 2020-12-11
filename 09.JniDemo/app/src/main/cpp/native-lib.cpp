#include <jni.h>
#include <string>
#include <android/log.h>

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_jnidemo_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "C++中无法catch 空指针问题";
    return env->NewStringUTF(hello.c_str());
}
extern "C" JNIEXPORT void JNICALL
Java_com_example_jnidemo_MainActivity_test(
        JNIEnv *env,
        jobject /* this */) {
    //2020.12.11空指针测试
    char *ret = NULL;
    try{

        *ret = 1;
    }catch (...){
        __android_log_print( ANDROID_LOG_DEBUG, "WANGJIN","----FAIL---");
    }



}
