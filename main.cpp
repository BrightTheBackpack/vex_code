controller Controller = controller();
brain Brain;
motor Left = motor(PORT1, false ) //set gear ratio later
motor Right = motor(PORT2, false ) //set gear ratio later
motor Arm = motor(PORT3, false ) //set gear ratio later
array Position = [0, 0, 0]
accelerometer AccelX = accelerometer(Brain.ThreeWirePort.A)//make sure to set which port were using
drivetrain DriveTrain = drivetrain(Left, Right, 300, 320, 320, mm, 1)
void axis3Changed() {
    int axis = Controller.Axis3.position();
    if (axis > 0) {
        //move robot forward
        drive(forward, axis)

    } else if (axis < 0) {
        //move robot backward
        drive(reverse, axis)

    } else if(axis == 0) {
        //stop robot. i think i want something to check if the previous input was a low or high, and based on that, breaktype break or coast respectively
        DriveTrain.stop(brake)
    }

}

void axis4Changed() {
    int axis = Controller.Axis4.position();
    if (axis > 0) {
        //turn robot right
        drive(right, axis)

    } else if (axis < 0) {
        //turn robot left
        drive(left, axis)
    } 

}

void arm1() {
    if (Controller.ButtonX.pressing()) {
        //move arm up, assuming up is postiive speed
        arm(forward, 100, 10)
    } else if (Controller.ButtonB.pressed()) {
        //move arm down
        arm(reverse, 100, 10)
    }
}

void drive(dir, speed){
    if (dir == "forward") {
        DriveTrain.drive(forward, speed, rpm);
    } else if (dir == "reverse") {
        DriveTrain.drive(reverse, speed, rpm);
    } else if (dir == "left") {
        DriveTrain.turnFor(left, speed, degrees);
    } else if (dir == "right") {
        DriveTrain.turnFor(right, speed, degrees);
    }
}
void arm(dir = forward, speed = 100, distance = 100) {
    if (dir == "forward") {
        arm.setVelocity(speed, rpm);
        Arm.spinFor(forward, distance);
    } else if (dir == "reverse") {
          arm.setVelocity(speed, rpm);
        Arm.spinFor(reverse, distance);
    } 
}
void accelerometer(axis) {
    if (axis == "x"){
        double value = AccelX.accelration();
    }

}
int main() {
    vexcodeInit();

    Controller.Axis3.changed(axis3Changed);
    Controller.Axis4.changed(axis4Changed);
    Controller.ButtonX.pressed(arm1);//have buttons for all the way up? and then make a joystick for precision control
    Controller.ButtonB.pressed(arm1);
    AccelX.changed(accelerometer("x"));
 
}