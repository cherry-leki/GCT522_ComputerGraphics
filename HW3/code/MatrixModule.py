import numpy as np
import maya.OpenMaya as om

''' Create a rotation matrix '''
def createRotationMatrix(rotRad, axis):
    # Rotation Matrix
    rotAxisSwitch = {
        "x": [[1, 0, 0, 0],
              [0, np.cos(rotRad), -np.sin(rotRad), 0],
              [0, np.sin(rotRad),  np.cos(rotRad), 0],
              [0, 0, 0, 1]],
        "y": [[ np.cos(rotRad), 0, np.sin(rotRad), 0],
              [0, 1, 0, 0],
              [-np.sin(rotRad), 0, np.cos(rotRad), 0],
              [0, 0, 0, 1]],
        "z": [[np.cos(rotRad), -np.sin(rotRad), 0, 0],
              [np.sin(rotRad),  np.cos(rotRad), 0, 0],
              [0, 0, 1, 0],
              [0, 0, 0, 1]]
    }
    rotMat = rotAxisSwitch.get(axis, 0)

    return rotMat

''' Create a translate matrix '''
def createTranslateMatrix(position):
    # Translate Matrix
    posMat = [[1, 0, 0, position[0]],
              [0, 1, 0, position[1]],
              [0, 0, 1, position[2]],
              [0, 0, 0, 1]]

    return posMat

''' Calculate a position vector '''
def calPosVector(matrices, objPos):
    posVec = np.eye(4)

    for mat in matrices:
        posVec = np.dot(posVec, mat)
        
    posVec = np.dot(posVec, np.transpose(objPos))

    return posVec

''' Calculate the angle between two vectors '''
def vectorAngle(cameraVector, posVector):
    # Calculate the angle
    angle = np.arccos(np.dot(cameraVector, posVector))
    orthoAxis = np.cross(cameraVector, posVector)

    q = om.MQuaternion(angle, om.MVector(orthoAxis[0], orthoAxis[1], orthoAxis[2]))
    euler = q.asEulerRotation()
    angle = np.rad2deg(euler.y)

    return angle
