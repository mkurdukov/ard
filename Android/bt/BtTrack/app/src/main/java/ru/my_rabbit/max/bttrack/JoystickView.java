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

        if (context instanceof JoystickListener)
            joystickCallback = (JoystickListener) context;
    }

    public JoystickView(Context context, AttributeSet attrs) {
        super(context, attrs);
        getHolder().addCallback(this);
        setOnTouchListener(this);
        if (context instanceof JoystickListener)
            joystickCallback = (JoystickListener) context;
    }

    public JoystickView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        getHolder().addCallback(this);
        setOnTouchListener(this);
        if (context instanceof JoystickListener)
            joystickCallback = (JoystickListener) context;
    }

    public JoystickView(Context context, AttributeSet attrs, int defStyleAttr, int defStyleRes) {
        super(context, attrs, defStyleAttr, defStyleRes);
        getHolder().addCallback(this);
        setOnTouchListener(this);
        if (context instanceof JoystickListener)
            joystickCallback = (JoystickListener) context;
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
    JoystickListener joystickCallback;

    private void setupDimensions() {
        centerX = getWidth() / 2;
        centerY = getHeight() / 2;
        baseRadius = Math.min(getWidth(), getHeight()) / 3;
        hatRadius = Math.min(getWidth(), getHeight()) / 5;
    }

    private void drawJoystick(float newX, float newY) {
        if (getHolder().getSurface().isValid()) {
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
    public boolean onTouch(View v, MotionEvent e) {
        if (v.equals(this)) {

            float x, y;
            if (e.getAction() != e.ACTION_UP) {
                float ds = (float) Math.sqrt(Math.pow(e.getX() - centerX, 2) + Math.pow(e.getY() - centerY, 2));
                if (ds < baseRadius) {
                    drawJoystick(e.getX(), e.getY());
                    x = (e.getX() - centerX) / baseRadius;
                    y = (e.getY() - centerY) / baseRadius;
                } else {

                    float ratio = baseRadius / ds;

                    float constrainedX = centerX + (e.getX() - centerX) * ratio;

                    float constrainedY = centerY + (e.getY() - centerY) * ratio;

                    drawJoystick(constrainedX, constrainedY);
                    x = (constrainedX - centerX) / baseRadius;
                    y = (constrainedY - centerY) / baseRadius;
                }
            } else {
                drawJoystick(centerX, centerY);
                x = y = 0;
            }
            RobustDirection direction = RobustDirection.STOP;
            if(x >= -0.5 && x <= 0.5 && y < -0.5 && y >= -1)
                direction = RobustDirection.FORWARD;
            else if(x >= -0.5 && x <= 0.5 && y > 0.5 && y <= 1)
                direction = RobustDirection.BACK;
            else if(x >= -1 && x < -0.5 && y >= -0.5 && y <= 0.5)
                direction = RobustDirection.LEFT;
            else if (x > 0.5 && x <= 1 && y >= -0.5 && y <= 0.5)
                direction = RobustDirection.RIGHT;

            joystickCallback.onJoystickMoved(x, y, direction, getId());
        }


        return true;
    }
}
