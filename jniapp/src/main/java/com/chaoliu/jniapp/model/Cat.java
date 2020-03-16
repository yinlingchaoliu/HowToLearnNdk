package com.chaoliu.jniapp.model;

import com.chaoliu.jniapp.utils.LogUtil;

/**
 * @Author glumes
 */

public class Cat extends Animal {


    public Cat(String name) {
        super(name);
        LogUtil.d("Cat Construct call....");
    }

    @Override
    public String getName() {
        return "My name is " + this.name;
    }

}