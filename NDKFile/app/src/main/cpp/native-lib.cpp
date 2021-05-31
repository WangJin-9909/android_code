#include <jni.h>
#include <string>
#include <dirent.h>
//#include <list>
//#include <iostream>
//#include <stdio.h>
//#include <vector>
#include <android/log.h>

using namespace std;
#define TAG "JNI_DEBUG_wangJin" // 这个是自定义的LOG的标识
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, TAG, __VA_ARGS__)  // 定义LOGV类型
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__) // 定义LOGF类型

void write_file(char *content) {
    FILE *file = NULL;
    file = fopen("/data/local/tmp/hello.txt", "a");    //创建文件
    if (file == NULL) {        //容错
        LOGD("文件创建失败%s", "222");
    }
    fwrite(content, 3, 1, file);            //往文件中写文件

    fclose(file);                    //关闭文件

}

void showAllFiles(string dir_name) {
    // check the parameter
    if (dir_name.empty()) {
        LOGE("dir_name is null !");
        return;
    }
    DIR *dir = opendir(dir_name.c_str());
    // check is dir ?
    if (NULL == dir) {
        LOGE("Can not open dir. Check path or permission!");
        return;
    }
    struct dirent *file;
    // read all the files in dir
    while ((file = readdir(dir)) != NULL) {
        // skip "." and ".."
        if (strcmp(file->d_name, ".") == 0 || strcmp(file->d_name, "..") == 0) {
            LOGV("ignore . and ..");
            continue;
        }
        if (file->d_type == DT_DIR) {
            string filePath = dir_name + "/" + file->d_name;
            showAllFiles(filePath); // 递归执行
        } else {
            // 如果需要把路径保存到集合中去，就在这里执行 add 的操作
           // LOGI("filePath: %s/%s", dir_name.c_str(), file->d_name);
           write_file(file->d_name);
        }
    }
    closedir(dir);
}



extern "C" JNIEXPORT void JNICALL
Java_com_example_ndkfile_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */, jstring dirPath_) {
    const char *dirPath = env->GetStringUTFChars(dirPath_, 0);
    showAllFiles(string(dirPath));
    env->ReleaseStringUTFChars(dirPath_, dirPath);

}
