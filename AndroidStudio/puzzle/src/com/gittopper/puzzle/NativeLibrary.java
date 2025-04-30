
package com.gittopper.puzzle;
import android.content.res.AssetManager;

public class NativeLibrary
{
    static
    {
        System.loadLibrary("native");
    }
    public static native void init(int width, int height, AssetManager assetManager);
    public static native void dragStart(int x1, int y1, int x2, int y2);
    public static native void drag(int x1, int y1, int x2, int y2);
    public static native void moveStart(int x, int y);
    public static native void move(int x, int y);
    public static native void dragStop();
    public static native void step();
}
