
package com.gittopper.puzzle;

import android.os.Bundle;
import android.app.Activity;
import android.util.Log;

public class PuzzleActivity extends Activity
{
    private static String LOGTAG = "PuzzleActivity";
    protected PuzzleView graphicsView;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        Log.i(LOGTAG, "Creating New Puzzle View");
        graphicsView = new PuzzleView(getApplication());
        setContentView(graphicsView);
    }

    @Override protected void onPause()
    {
        super.onPause();
        graphicsView.onPause();
    }

    @Override protected void onResume()
    {
        super.onResume();
        graphicsView.onResume();
    }
}
