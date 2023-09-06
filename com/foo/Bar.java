package com.foo;

public class Bar {
    public native static String pong(String arg);

    static {
        System.loadLibrary("ping_pong");
    }

    public static void main(String[] args) {
        System.out.println(pong("ping") + " from c++...");
    }
}