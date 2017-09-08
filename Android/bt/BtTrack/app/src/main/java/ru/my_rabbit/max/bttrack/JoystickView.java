package ru.my_rabbit.max.bttrack;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.PorterDuff;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;

//http://www.instructables.com/id/A-Simple-Android-UI-Joystick/ step 4

public class JoystickView extends SurfaceView implements SurfaceHolder.Callback, View.OnTouchListener {

    public JoystickView(Context context) {
        super(context);

        getHolder().addCallback(this);
        setOnTouchListener(this);
    }

    public JoystickView(Context context, AttributeSet attrs) {
        super(context, attrs);
        getHolder().addCallback(this);
        setOnTouchListener(this);
    }

    public JoystickView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        getHolder().addCallback(this);
        setOnTouchListener(this);
    }

    public JoystickView(Context context, AttributeSet attrs, int defStyleAttr, int defStyleRes) {
        super(context, attrs, defStyleAttr, defStyleRes);
        getHolder().addCallback(this);
        setOnTouchListener(this);
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        setupDimensions();
        drawJoystick(centerX, centerY);
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {

    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {

    }

    float centerX;
    float centerY;
    float baseRadius;
    float hatRadius;

    private void setupDimensions(){
        centerX = getWidth() / 2;
        centerY = getHeight() / 2;
        baseRadius = Math.min(getWidth(), getHeight())/3;
        hatRadius = Math.min(getWidth(), getHeight())/5;
    }

    private void drawJoystick(float newX, float newY)
    {
        if(getHolder().getSurface().isValid())
        {
            Canvas c = this.getHolder().lockCanvas();
            Paint colors = new Paint();
            c.drawColor(Color.TRANSPARENT, PorterDuff.Mode.CLEAR);
            colors.setARGB(255, 50, 50, 50);
            c.drawCircle(centerX, centerY, baseRadius, colors);
            colors.setARGB(255, 0, 0, 255);
            c.drawCircle(newX, newY, hatRadius, colors);
            getHolder().unlockCanvasAndPost(c);
        }
    }

    @Override
    public boolean onTouch(View v, MotionEvent event) {
        if(v.equals(this)){
            if(event.getAction() == event.ACTION_UP){
                drawJoystick(event.getX(), event.getY());
            } else {
                drawJoystick(centerX, centerY);
            }

        }


        return true;
    }
}
