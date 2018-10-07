* Source code (in code file)
- CameraPath_KCL.py	: The main code file. The code related python gui is in it
- ButtonFunc.py		: It contains several codes related python gui buttons
- MatrixModule.py		: The createRotationMatrix and vectorAngle functions are in it


* Target Machine & Software
: Maya 2017, python 2.7


* How to use GUI
1. Execute the CameraPath_KCL.py
2. Input values
 2-1. Register the target object
  2-1-1. Select the target object and click the add button next to the textScrollList of Target Object
   	『 If you do not select the object that the type is "mesh", the error message is shown on history board
 2-2. Register the target curve
  2-2-1. Select the target curve and click the add button next to the textScrollList of Curve
   『 If you do not select the object that the type is "nurbsCurve", the error message is shown on history board
 2-3. Set the camera placement and distance
  2-3-1. Choose the camera direction: Right, Left, Front, Back
  2-3-2. Input the distance value on the textField next to the "Distance"
 2-4. Set the keyframes and interval length
  2-4-1. Input the number of keyframes on the textField next to the "Keyframes / Interval Length"
  2-4-2. Input the number of frames between keyframes on the textField next to the textField mentioned in 2-4-1
3. Click the "Place Camera" button to create and place camera to given direction and distance
   『 If you do not register target object and distance value, the error message is shown on history board
4. Click the "Follow Path" button to create a camera and move this camera along the curve
   『 If you do not register target object, target curve, keyframes value and interval length value, the error message is shown on history board



* How functions work
[ ButtonFunc.py ]
> function addTargetObj (targetObj)
   - Input	: The textScrollList of target object
   - Output: None
   : Register the target object on the textScrollList of target object in the GUI

> function removeTargetObj (targetObj)
   - Input: The textScrollList of target object
   - Output: None
   : Remove the target object from the textScrollList of target object in the GUI

> function addCurve (targetCurve)
   - Input: The textScrollList of target curve
   - Output: None
   : Register the target curve on the textScrollList of target curve in the GUI

> function removeCurve (targetCurve)
   - Input: The textScrollList of target curve
   - Output: None
   : Remove the target curve from the textScrollList of target curve in the GUI

[ MatrixModule.py ]
> function 