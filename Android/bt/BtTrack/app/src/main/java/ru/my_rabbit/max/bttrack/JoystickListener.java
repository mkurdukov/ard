package ru.my_rabbit.max.bttrack;

/**
 * Created by mkurdukov on 09/09/2017.
 */

public interface JoystickListener

{
    void onJoystickMoved(float xPercent, float yPercent, RobustDirection direction, int source);
}