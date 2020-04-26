由于JNIEnv是与线程绑定的，就像 Android 的 Looper 也是和线程绑定一样，每一个 Looper 会对应一个线程。因此要在子线程中调用 Java 的方法，需要得到当前线程的 JNIEnv 实例。
