package com.gittopper.puzzle;

import android.content.Context;
import android.content.res.AssetManager;
import android.opengl.GLSurfaceView;
import android.view.MotionEvent;
import android.util.Log;

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLContext;
import javax.microedition.khronos.egl.EGLDisplay;
import javax.microedition.khronos.opengles.GL10;

class PuzzleView extends GLSurfaceView
{
    public PuzzleView(Context context)
    {
        super(context);
        setEGLContextFactory(new ContextFactory());
        setEGLContextClientVersion(2);
        super.setEGLConfigChooser(8 , 8, 8, 8, 16, 0);
        AssetManager assetManager = context.getAssets();
        setRenderer(new Renderer(assetManager));
    }

    private static class ContextFactory implements GLSurfaceView.EGLContextFactory
    {
        public EGLContext createContext(EGL10 egl, EGLDisplay display, EGLConfig eglConfig)
        {
            final int EGL_CONTEXT_CLIENT_VERSION = 0x3098;
            int[] attrib_list = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL10.EGL_NONE };
            return egl.eglCreateContext(display, eglConfig, EGL10.EGL_NO_CONTEXT, attrib_list);
        }

        public void destroyContext(EGL10 egl, EGLDisplay display, EGLContext context)
        {
            egl.eglDestroyContext(display,  context);
        }
    }

    boolean moveStarted = false;
    public boolean onTouchEvent(final MotionEvent e) {
        if (e.getPointerCount() > 1)
        {
            moveStarted = false;
            Log.i("received ", Integer.toString(e.getPointerCount()));
            int itemPointerId0 = e.getPointerId(0);
            int pointerIndex0 = e.findPointerIndex(itemPointerId0);
            MotionEvent.PointerCoords pc0 = new MotionEvent.PointerCoords();
            e.getPointerCoords(pointerIndex0, pc0);

            int itemPointerId1 = e.getPointerId(1);
            int pointerIndex1 = e.findPointerIndex(itemPointerId1);
            MotionEvent.PointerCoords pc1 = new MotionEvent.PointerCoords();
            e.getPointerCoords(pointerIndex1, pc1);
            switch(e.getAction())
            {
                case MotionEvent.ACTION_DOWN:
                    NativeLibrary.dragStart((int)pc0.x, (int)pc0.y, (int)pc1.x, (int)pc1.y);
                    break;
                case MotionEvent.ACTION_MOVE:
                    NativeLibrary.drag((int)pc0.x, (int)pc0.y, (int)pc1.x, (int)pc1.y);
                    break;
                case MotionEvent.ACTION_UP:
                    NativeLibrary.dragStop();
                    break;
            }
        }else if (e.getPointerCount() == 1) {
            float x = e.getX();
            float y = e.getY();
            switch (e.getAction()) {
                case MotionEvent.ACTION_DOWN:
                    NativeLibrary.moveStart((int) x, (int) y);
                    moveStarted = true;
                    break;
                case MotionEvent.ACTION_MOVE:
                    if (moveStarted)
                    {
                        NativeLibrary.move((int) x, (int) y);
                    }
                    break;
                case MotionEvent.ACTION_UP:
                    moveStarted = false;
                    NativeLibrary.dragStop();
                    break;
            }
        }

        return true;
    }
        private static class Renderer implements GLSurfaceView.Renderer
        {
            AssetManager asset_manager;
            Renderer(AssetManager assetManager){
                asset_manager = assetManager;
            }
            public void onDrawFrame(GL10 gl)
            {
                NativeLibrary.step();
            }

            public void onSurfaceChanged(GL10 gl, int width, int height)
            {
                NativeLibrary.onSurfaceChanged(width, height, asset_manager);
            }

            public void onSurfaceCreated(GL10 gl, EGLConfig config)
            {
            }
        }
}
