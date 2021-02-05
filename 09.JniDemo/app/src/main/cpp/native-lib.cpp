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
    char *ret = (char *)malloc(4);

    char **m ;
    m = (char**)malloc(sizeof(char *) * 100000); //行数

    long i=0;
    for( i=0;i<1000000000000 ;i++ )
    {
        m[i]= (char*)malloc(sizeof(char)*1000); //为每行申请空间

    }
    strcpy( m[0], "hello" );
    m[0][0]= 'H' ;





    //__android_log_print( ANDROID_LOG_DEBUG, "+++++++++++++++++++++++++++++++++++++++++++++++WANGJIN","sizeof(ret) = %d", sizeof(ret));
    try{

       // *ret = 1;
    }catch (...){
        __android_log_print( ANDROID_LOG_DEBUG, "WANGJIN","----FAIL---");
    }



}
