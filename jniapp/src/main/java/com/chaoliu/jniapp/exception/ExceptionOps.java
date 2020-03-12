package com.chaoliu.jniapp.exception;


/**
 * @Author chentong
 */
public class ExceptionOps  {

    /**
     * 由 Native 来调用该函数，由于 除数为 0 ，引发异常，在 Native 代码中清除这次异常
     *
     * @return
     */
    public int operation() {
        return 2 / 0;
    }

    /**
     * Native 调用  Java 方式时，导致异常了并不会立即终止 Native 方法的执行
     *
     * @throws NullPointerException
     */
    private void callback() throws NullPointerException {
        throw new NullPointerException("CatchThrow.callback by Native Code");
    }

}
