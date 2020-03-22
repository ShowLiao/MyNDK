#include <jni.h>
#include <string>

extern "C"
JNIEXPORT jstring

JNICALL
Java_com_example_show_myndk_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_show_myndk_MainActivity_intFromJNI(JNIEnv *env, jobject instance) {

    jint res = 4;
    return res;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_show_myndk_MainActivity_sendStream(JNIEnv *env, jobject instance, jobject in) {

    // TODO

}extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_show_myndk_MainActivity_strArray(JNIEnv *env, jobject instance, jintArray arr_) {

    jint *arr = env->GetIntArrayElements(arr_, NULL);

    if (NULL == arr)
        return env->NewStringUTF("");

    jsize length = env->GetArrayLength(arr_);

    jint sum = 0;
    for (int i=0; i<length; i++) {
        sum += arr[i];
    }

    env->ReleaseIntArrayElements(arr_, arr, 0);

    char str[3] ;
    jstring res;
    sprintf(str, "%d", sum);
    res = env->NewStringUTF(str);

    return res;
}

extern "C"
JNIEXPORT jintArray JNICALL
Java_com_example_show_myndk_MainActivity_getArray(JNIEnv *env, jobject instance, jintArray arr_) {

    jint *arr = env->GetIntArrayElements(arr_, NULL);

    if (NULL == arr)
        return NULL;
    jsize length = env->GetArrayLength(arr_);
    jintArray intarr = env->NewIntArray(length);
    jint *arrtmp = env->GetIntArrayElements(intarr, NULL);

    for (int i=0; i<length; i++) {
        arrtmp[i] = arr[i] + 100;
    }

    arr[2] = 100;

    env->ReleaseIntArrayElements(arr_, arr, 0);
    env->ReleaseIntArrayElements(intarr, arrtmp, 0);
    return intarr;
}
extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_example_show_myndk_MainActivity_getStringArray(JNIEnv *env, jobject instance) {

    char* days[] = {"Monday", "Thu", "Wednesday"};
    int length = 3;//sizeof(days);
    jobjectArray obj = env->NewObjectArray(length, env->FindClass("java/lang/String"), env->NewStringUTF(""));

    for (int i=0; i<length; i++) {
//        obj[i] = days[i];
        env->SetObjectArrayElement(obj, i, env->NewStringUTF(days[i]));
    }

    return obj;
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_example_show_myndk_MainActivity_createZoo(JNIEnv *env,
                                                    jobject thisObj,
                                                    jstring name,
                                                    jint size) {

    //Create the obj of the class Eddie
    jclass zooClass = env->FindClass("com/example/show/myndk/Zoo");
    jobject zooInfo = env->AllocObject(zooClass);

    //Get the Eddie class
    jfieldID nameField = env->GetFieldID(zooClass, "name", "Ljava/lang/String;");
    jfieldID sizeField = env->GetFieldID(zooClass, "size", "I");

    env->SetObjectField(zooInfo, nameField, name);
    env->SetIntField(zooInfo, sizeField, size);

    return zooInfo;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_show_myndk_MainActivity_printData(JNIEnv *env,
                                                   jobject thisObj,
                                                   jobject zooInfo) {

    // Find the user of the Java medthod to be called
    jclass zooClass = env->GetObjectClass(zooInfo);
    jmethodID methodId = env->GetMethodID(zooClass, "getZooInfo", "()Ljava/lang/String;");

    jstring result = (jstring)env->CallObjectMethod(zooInfo, methodId);
    return result;
}