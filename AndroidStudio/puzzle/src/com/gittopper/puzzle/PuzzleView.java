/* Copyright (c) 2013-2017, ARM Limited and Contributors
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge,
 * to any person obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

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
    protected int[] value = new int [1];
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
            EGLContext context = egl.eglCreateContext(display, eglConfig, EGL10.EGL_NO_CONTEXT, attrib_list);
            return context;
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
                case MotionEvent.ACTION_POINTER_2_DOWN:
                    NativeLibrary.dragStart((int)pc0.x, (int)pc0.y, (int)pc1.x, (int)pc1.y);
                    break;
                case MotionEvent.ACTION_MOVE:
                    NativeLibrary.drag((int)pc0.x, (int)pc0.y, (int)pc1.x, (int)pc1.y);
                    break;
                case MotionEvent.ACTION_UP:
                case MotionEvent.ACTION_POINTER_2_UP:
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
                NativeLibrary.init(width, height, asset_manager);
            }

            public void onSurfaceCreated(GL10 gl, EGLConfig config)
            {
            }
        }
}
