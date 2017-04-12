package com.example.t.velengestest;

/**
 * Created by T on 2017-04-12.
 */

import android.app.Activity;
import android.support.v4.view.GestureDetectorCompat;
import android.support.v4.view.MotionEventCompat;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.ScaleGestureDetector;
import android.view.View;

public class VelGesture {
    private native void DoubleTap();
    private native void Scroll(float distanceX, float distanceY, float positionX, float positionY);
    private native void Scale(float scaleFactor);
    private native void Move(float distanceX, float distanceY);

    private GestureDetectorCompat TapScrollDetector;
    private ScaleGestureDetector ScaleDetector;

    public VelGesture(Activity activity)
    {
        TapScrollDetector = new GestureDetectorCompat(activity, new TapScrollListener());
        ScaleDetector = new ScaleGestureDetector(activity.getApplicationContext(), new ScaleListener());
    }

    static int INVALID_POINTER_ID = -100;
    private int TwoFingerPtrID = INVALID_POINTER_ID;

    public View.OnTouchListener TwoFingerGestureListener = new View.OnTouchListener()
    {
        private float LastTouchX, LastTouchY;

        @Override
        public boolean onTouch(View v, MotionEvent event)
        {
            TapScrollDetector.onTouchEvent(event);
            ScaleDetector.onTouchEvent(event);

            final int action = MotionEventCompat.getActionMasked(event);

            switch (action)
            {
                case MotionEvent.ACTION_DOWN:
                {
                    break;
                }

                case MotionEvent.ACTION_MOVE:
                {
                    if(TwoFingerPtrID != INVALID_POINTER_ID)
                    {
                        final float x = MotionEventCompat.getX(event, TwoFingerPtrID); //TODO depr funcs
                        final float y = MotionEventCompat.getY(event, TwoFingerPtrID);

                        final float dx = x - LastTouchX;
                        final float dy = y - LastTouchY;

                        LastTouchX = x;
                        LastTouchY = y;
                        Move(dx, dy);
                    }
                    break;
                }
                case MotionEvent.ACTION_POINTER_DOWN: {
                    // detected two fingers, start the drag
                    TwoFingerPtrID = MotionEventCompat.getActionIndex(event);
                    final float x = MotionEventCompat.getX(event, TwoFingerPtrID);
                    final float y = MotionEventCompat.getY(event, TwoFingerPtrID);

                    // Remember where we started (for dragging)
                    LastTouchX = x;
                    LastTouchY = y;
                    break;
                }
                case MotionEvent.ACTION_UP:
                {
                    TwoFingerPtrID = INVALID_POINTER_ID;
                    break;
                }
                case MotionEvent.ACTION_CANCEL:
                {
                    TwoFingerPtrID = INVALID_POINTER_ID;
                    break;
                }
                case MotionEvent.ACTION_POINTER_UP:
                {
                    TwoFingerPtrID = INVALID_POINTER_ID;
                    break;
                }
            }
            return true;
        }
    };



    class TapScrollListener extends GestureDetector.SimpleOnGestureListener
    {
        public boolean onDoubleTap (MotionEvent event)
        {
            DoubleTap();
            return true;
        }

        public boolean onScroll (MotionEvent e1, MotionEvent e2, float distanceX, float distanceY)
        {
            if(TwoFingerPtrID == INVALID_POINTER_ID)
            {
                Scroll(distanceX, distanceY, e2.getX(), e2.getY());
            }
            return true;
        }
    }

    private class ScaleListener extends ScaleGestureDetector.SimpleOnScaleGestureListener
    {
        @Override
        public boolean onScale(ScaleGestureDetector detector)
        {
            Scale(detector.getScaleFactor());
            return true;
        }
    }

}

