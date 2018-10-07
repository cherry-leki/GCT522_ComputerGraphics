* Source code (in code file)
- CameraPath_KCL.py	: The main code file. The python gui code is in it
- ButtonFunc.py		: It contains several codes related python gui buttons
- MatrixModule.py		: The createRotationMatrix and vectorAngle functions are in it


* Target Machine & Software
: Maya 2017, python 2.7


* How to use GUI
1. Execute the CameraPath_KCL.py
   ¡Ø If you do not use Atom, please change "__file__" in line 5 to absolute path of "code" folder.
2. Input values
 2-1. Register the target object
  2-1-1. Select the target object and click the add button next to the textScrollList of Target Object
   	¡Ø If you do not select the object that the type is "mesh", the error message is shown on history board
 2-2. Register the target curve
  2-2-1. Select the target curve and click the add button next to the textScrollList of Curve
   ¡Ø If you do not select the object that the type is "nurbsCurve", the error message is shown on history board
 2-3. Set the camera placement and distance
  2-3-1. Choose the camera direction: Right, Left, Front, Back
  2-3-2. Input the distance value on the textField next to the "Distance"
 2-4. Set the keyframes and interval length
  2-4-1. Input the number of keyframes on the textField next to the "Keyframes / Interval Length"
  2-4-2. Input the number of frames between keyframes on the textField next to the textField mentioned in 2-4-1
3. Click the "Place Camera" button to create and place camera to given direction and distance
   ¡Ø If you do not register target object and distance value, the error message is shown on history board
4. Click the "Follow Path" button to create a camera and move this camera along the curve
   ¡Ø If you do not register target object, target curve, keyframes value and interval length value, the error message is shown on history board


* How functions work
[ ButtonFunc.py ]
> function addTargetObj (targetObj)
   - Input
      - targetObj: The textScrollList of target object
   - Output
        None
   : Register the target object on the textScrollList of target object in the GUI

> function removeTargetObj (targetObj)
   - Input
      - targetObj: The textScrollList of target object
   - Output
        None
   : Remove the target object from the textScrollList of target object in the GUI

> function addCurve (targetCurve)
   - Input
      - targetCurve: The textScrollList of target curve
   - Output
        None
   : Register the target curve on the textScrollList of target curve in the GUI

> function removeCurve (targetCurve)
   - Input
      - targetCurve: The textScrollList of target curve
   - Output
        None
   : Remove the target curve from the textScrollList of target curve in the GUI

> function placeCamera (distance, targetObj, cameraPlace, list_cameraPlace)
   - Input
      - distance: The textField of distance
      - targetObj: The textScrollList of target object
      - cameraPlace: The selected menuItem on optionMenu of camera place
      - list_cameraPlace: The list of camera place menu items
   - Output: None
   : First, it gets values mentioned upper and saves them at local variables.
    The rotation angle is calculated by using camera place value and target rotation value in y axis.
     It calls "createTranslateMatrix" and "createRotationMatrix" in MatrixModule.py. For calculating camera position where we want, we move the camera as much as distance and rotate it following camera place angle. Then we rotate it how much target rotate and move it how much target move. So, we dot matrices ordered by camera distance¡æcamera direction¡ætarget rotation¡ætarget position (In text, we dot matrices left to right but in code we dot matrices right to left) by calling "calPosVector" in MatrixModule.py.
    Finally, it sets a camera on computed position and rotates it as much as computed angle

> function followPath (targetObj, targetCurve, keyframes, intervals)
   - Input
      - targetObj: The textScrollList of target object
      - targetCurve: The textScrollList of target curve
      - keyframes: The textField of keyframes
      - intervals: The textField of intervals
   - Output
   : First, it gets values mentioned upper and saves them at local variables.
     Then it calculates the camera position and rotation to look at the target at each keyframe using 'for' loop.
     For position, it places the camera at the position of (itr * (target's spans / keyframe)) on curve.
     For rotation, it sets two vectors: camera vector and normalized vector of camera's point to target object's point. Then it calls "vectorAngle" in MatrixModule.py. The calculated angle range is -90 to 270, so it contains correction code for angle range. The process of calculating angle is end, it rotates the camera as much as calculated angle.


[ MatrixModule.py ]
> function createRotationMatrix (rotRad, axis)
   - Input
      - rotRad: The radian angle value for rotation
      - axis: The string value of rotation axis. Only one axis is possible
   - Output
      - rotMat: The calculated 4x4 rotation matrix
   : Create the rotation matrix according to axis and radian angle(rotRad).

> function createTranslateMatrix (position)
   - Input
      - position: The 1x3 vector for translation
   - Output
      - posMat: The calculated 4x4 translation matrix
   : Create the translation matrix according to position

> function calPosVector(matrices, objPos)
   - Input
      - matrices: The list of matrices ordered right to left.
                    (ex: CBAx (x is position vector) -> [C, B, A])
      - objPos: The 1x3 vector of origin position of object to move
   - Output
      - posVec: The calculated 1x3 position vector
   : Calculate the position vector.
     Dot product is performed as much as matrices size. In the last, the dot product between matrices and object's position vector(objPos) is performed.

> function vectorAngle (cameraVector, posVector)
   - Input
      - cameraVector: The 1x3 vector of origin camera root
      - posVector: The 1x3 vector of camera's point to target object's point
   - Output
      - angle: The calculated degree of angle
   : Calculate the angle between two vectors.
    According to cameraVector and posVector, angle and orthogonal axis are computed using cosine law and cross product. These values are inputted into Maya's MQuaternion function. Then euler angle is computed using asEulerRotation function.