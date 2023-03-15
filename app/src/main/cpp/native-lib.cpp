#include <jni.h>
#include <string>
#include <unistd.h>

#include <android/log.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

//---------------------------------------------------------------------------
// Defines and Macros
//---------------------------------------------------------------------------
#include <string.h>
#include <thread>         // std::thread
//---------------------------------------------------------------------------
// Typedefs
//---------------------------------------------------------------------------
#include "pedapp.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"
//#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include <opencv2/videoio/videoio.hpp>

#include "pedapp.hpp"
#include <iostream>
#include <fstream>

#define TAG "NativeLib"

using namespace std;
using namespace cv;

std::ifstream infile;
static bool threadFlag = true;

int initFile = 0;

#define TAG "Native-LOG"


#define  LOGV(...)  __android_log_print(ANDROID_LOG_VERBOSE,    TAG, __VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,       TAG, __VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,      TAG, __VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,       TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,      TAG, __VA_ARGS__)



unsigned char *Buffer=         new unsigned char [1920*1080*3];
unsigned char *inputImage  =   new unsigned char [1344*1024*2];

extern "C" JNIEXPORT jstring JNICALL
Java_com_aitl_pddemo_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
void pdthread(jlong matAddr){

    // get Mat from raw address
    Mat &mat = *(Mat *) matAddr;

    pedapp_Init();

    for(int i=0;i<1000 && (threadFlag == true);i++){
        if(initFile == 0)
        {
            infile.open("/sdcard/data/newfile.yuv", ios::in|ios::binary);
            initFile = 1;
            LOGD("/sdcard/data/newfile.yuv file open \n");
        }

        if(infile.eof())
        {
            //return false;
            LOGD("newfile.yuv END of File\n");
        }

        LOGD("Runnint in th native api %d \n",i);

        LOGD("Reading the Frame\n");
        infile.read ((char *)inputImage, 1280*806*2);
        pedapp_Process(inputImage,Buffer);
        LOGD("After Process  the Frame\n");

        cv::Mat Output(1080, 1920, CV_8UC3,Buffer);
        //memcpy(mat.ptr(),Output.ptr(),(1080*1920*3));
        // cv::imwrite("outputimage_1.jpg",Output);
        //outpuvideo.write(Output);
        LOGD("After Process output imwrite the Frame\n");

        sleep(1);

    }

    //return 0;

}


extern "C" JNIEXPORT jstring JNICALL
Java_com_aitl_pddemo_MainActivity_startPDThread(
        JNIEnv* env,
        jobject /* this */,
        jlong matAddr) {

    std::string startPDThread = "startPDThread from C++";

    threadFlag = true;

    std::thread first (pdthread, matAddr);     // spawn new thread that calls foo()
    //std::thread second (bar,0);  // spawn new thread that calls bar(0)

    //main, foo and bar now execute concurrently

    // synchronize threads:
    first.detach();                // pauses until first finishes
    //second.join();

    return env->NewStringUTF(startPDThread.c_str());
}


extern "C" JNIEXPORT jstring JNICALL
Java_com_aitl_pddemo_MainActivity_stopPDThread(
        JNIEnv* env,
        jobject /* this */) {
    std::string stopPDThread = "stopPDThread from C++";

    threadFlag = false;


    return env->NewStringUTF(stopPDThread.c_str());
}

extern "C" JNIEXPORT void JNICALL
Java_com_aitl_pddemo_MainActivity_adaptiveThresholdFromJNI(JNIEnv *env,
         jobject instance,
         jlong matAddr) {

    // get Mat from raw address
    Mat &mat = *(Mat *) matAddr;

    clock_t begin = clock();

    cv::adaptiveThreshold(mat, mat, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY_INV, 21, 5);

    // log computation time to Android Logcat
    double totalTime = double(clock() - begin) / CLOCKS_PER_SEC;
    //LOGD(ANDROID_LOG_INFO, TAG, "adaptiveThreshold computation time = %f seconds\n",totalTime);


}
