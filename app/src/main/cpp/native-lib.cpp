#include <jni.h>
#include <string>

/**
 *
 * Use after free，使用已释放的内存；
 * Heap buffer overflow，使用超出了申请空间的堆内存；
 * Stack buffer overflow，使用超出了申请空间的栈内存；
 * Global buffer overflow，使用超出了全局空间内存；
 * Use after return，使用在函数内部分配但已跳出函数的内存；
 * Use after scope，使用了超出作用域的内存；
 * Initialization order bugs，一些和变量初始化有关的问题；
 * Memory Leaks，内存泄漏(android上不支持)。
 *
 */

extern "C" JNIEXPORT jstring JNICALL
Java_com_panda_asam_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "xxxx";

    // Use after free：使用已释放的内存
//    int *array = new int[100];
//    delete [] array;
//    int a = array[2];
//    hello.operator+=(a);

    // Heap buffer overflow：使用超出了申请空间的堆内存
//    int *array = new int[1];
//    array[0] = 0;
//    int res = array[1100];  // BOOM
//    delete [] array;
//    hello.operator+=(res);

    // Stack buffer overflow：使用超出了申请空间的栈内存
//    int stack_array[100];
//    stack_array[1] = 0;
//    int s = stack_array[(rand() % (1000-100))+ 100];
//    hello.operator+=(s);

    // 不接入AddressSanitizer的情况下，模拟数组越界，因为"C++数组越界不检查"，
    // 一般来说，会打印出一个不确定的整数，直到在打印某个元素的时候，出现了 “segmentation fault”.
    // 所以这里循环的上限很大
    int *ptr;
    ptr = (int*) malloc(2);
    for (int i=0; i< 10000000; i++)
    {
        ptr[i] = i;
    }

    return env->NewStringUTF(hello.c_str());
}
