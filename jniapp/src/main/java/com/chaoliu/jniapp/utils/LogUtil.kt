package com.chaoliu.jniapp.utils

import android.util.Log

/**
 * Created by glumes on 28/02/2018
 */
class LogUtil {

    companion object {

        var TAG: String = "NativeMethod"

        fun d(msg: String) {
            d(msg, tag = TAG)
        }

        fun d(msg: String, tag: String = TAG) {
            Log.d(tag, msg)
        }

        fun i(msg: String) {
            i(msg, tag = TAG)
        }

        fun i(msg: String, tag: String = TAG) {
            Log.i(tag, msg)
        }

        fun e(msg: String) {
            e(msg, tag = TAG)
        }

        fun e(msg: String, tag: String = TAG) {
            Log.e(tag, msg)
        }
    }
}