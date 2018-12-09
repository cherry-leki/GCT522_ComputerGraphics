from functools import partial as ft
import maya.cmds as cmds
import maya.mel as mel
import os
from os.path import basename

''' Funtion Part '''
# For Exporting Source Animation Data File
def exportSrcAni(*args):
    blendNodeName = cmds.textField(srcBlendNode, q=True, text=True)
    fileName = cmds.textField(srcFileName, q=True, text=True)
    frame = cmds.textField(srcFrames, q=True, text=True)
    mel.eval("FRRBlendExport -bn " + blendNodeName +
                            " -bfn " + fileName +
                            " -f " + frame)

# For Exporting Source Animation Data File
def exportSrcROE(*args):
    blendNodeName = cmds.textField(srcROEBlendNode, q=True, text=True)
    fileName = cmds.textField(srcROEFileName, q=True, text=True)
    frame = cmds.textField(srcROEFrames, q=True, text=True)
    mel.eval("FRRBlendExport -bn " + blendNodeName +
                            " -bfn " + fileName +
                            " -f " + frame)

# For Exporting Target CV List File
def exportTrgCV(*args):
    fileName = cmds.textField(trgFileName, q=True, text=True)
    mel.eval("FRRCtrlListExport -cln " + fileName)

# For Exporting Target Range Of Expression File
# Import Ctrl List file
def importTrgCV(*args):
    datFilter = "*.dat"
    file_path = cmds.fileDialog2(ff=datFilter, dialogStyle=1,
                                fileMode=1, caption="Import Target ROE file")
    file_path = file_path[0]
    fileName = file_path.split("/")
    fileName = fileName[-1]
    cmds.textField(trgROECtrlList, edit=True, tx=fileName)
# Export Target Range of Expression File
def exportTrgROE(*args):
    ctrlListName = cmds.textField(trgROECtrlList, q=True, text=True)
    fileName = cmds.textField(trgROEFileName, q=True, text=True)
    frame = cmds.textField(trgROENumOfSets, q=True, text=True)
    mel.eval("FRRCVExport -cln " + ctrlListName +
                        " -cfn " + fileName +
                        " -f " + frame)

# For Exporting Final Retargeting Result File
# Import Source ROE File
def importSrcROE(*args):
    datFilter = "*.dat"
    file_path = cmds.fileDialog2(ff=datFilter, dialogStyle=1,
                                fileMode=1, caption="Import Source ROE file")
    file_path = file_path[0]
    fileName = file_path.split("/")
    fileName = fileName[-1]
    cmds.textField(srcROEFile, edit=True, tx=fileName)
# Import Target ROE File
def importTrgROE(*args):
    datFilter = "*.dat"
    file_path = cmds.fileDialog2(ff=datFilter, dialogStyle=1,
                                fileMode=1, caption="Import Target ROE file")
    file_path = file_path[0]
    fileName = file_path.split("/")
    fileName = fileName[-1]
    cmds.textField(trgROEFile, edit=True, tx=fileName)
# Import Source Data File
def importSrcAni(*args):
    datFilter = "*.dat"
    file_path = cmds.fileDialog2(ff=datFilter, dialogStyle=1,
                                fileMode=1, caption="Import Source Animation file")
    file_path = file_path[0]
    fileName = file_path.split("/")
    fileName = fileName[-1]
    cmds.textField(srcAniFile, edit=True, tx=fileName)
# Export Final Target Data File
def exportFinalResult(*args):
    srcROEFileName = cmds.textField(srcROEFile, q=True, text=True)
    trgROEFileName = cmds.textField(trgROEFile, q=True, text=True)
    srcAniFileName = cmds.textField(srcAniFile, q=True, text=True)
    resultFileName = cmds.textField(finalDataFile, q=True, text=True)
    mel.eval("FRRTraining -bfn " + srcROEFileName +
                        " -cfn " + trgROEFileName +
                        " -sfn " + srcAniFileName +
                        " -ffn " + resultFileName)

# For Importing Final Result FileName
# Import Ctrl List File
def importTrgCVFile(*args):
    datFilter = "*.dat"
    file_path = cmds.fileDialog2(ff=datFilter, dialogStyle=1,
                                fileMode=1, caption="Import Target Ctrl List file")
    file_path = file_path[0]
    fileName = file_path.split("/")
    fileName = fileName[-1]
    cmds.textField(ctrlListFile, edit=True, tx=fileName)
# Import Final Result File
def importFinalResultFile(*args):
    datFilter = "*.dat"
    file_path = cmds.fileDialog2(ff=datFilter, dialogStyle=1,
                                fileMode=1, caption="Import Final Result file")
    file_path = file_path[0]
    fileName = file_path.split("/")
    fileName = fileName[-1]
    cmds.textField(finalResultFile, edit=True, tx=fileName)
# Import Final Result
def importFinalResult(*args):
    trgCVFileName = cmds.textField(ctrlListFile, q=True, text=True)
    resultFileName = cmds.textField(finalResultFile, q=True, text=True)
    mel.eval("FRRCVImport -cln " + trgCVFileName +
                        " -ffn " + resultFileName)


''' GUI Part '''
''' Window Setting '''
windowName = "Facial Retargeting To Frame"
window = cmds.window(title=windowName, sizeable=False)

''' Main Layout '''
cmds.columnLayout("mainLayout", w=300)

''' Export Source Animation Data File '''
cmds.frameLayout("exportSource", l="Export Source Animation Data File",
                p="mainLayout", nch=2, cll=True, w=270)
cmds.rowColumnLayout("exportSourceList", p="exportSource", nc=2, cw=[(1,100), (2,150)])
cmds.text(l="FileName:")
srcFileName = cmds.textField("srcFileNameTxtField", tx="humanSourceAnimation.dat")
cmds.text(l="BlendNode:")
srcBlendNode = cmds.textField("srcBlendNodeTxtField", tx="targetBlend")
cmds.text(l="Frames:")
srcFrames = cmds.textField("srcFramesTxtField", tx="360")
cmds.button(l="Export Source Animation Data", w=250, c=exportSrcAni)

cmds.separator(style='none', height=5, p="mainLayout")

''' Export Range of Expression File '''
cmds.frameLayout("exportSrcROE", l="Export Range of Expression File",
                p="mainLayout", nch=2, cll=True, w=270)
cmds.rowColumnLayout("exportROEList", p="exportSrcROE", nc=2, cw=[(1,100), (2,150)])
cmds.text(l="FileName:")
srcROEFileName = cmds.textField("srcROEFileNameTxtField", tx="humanROE.dat")
cmds.text(l="BlendNode:")
srcROEBlendNode = cmds.textField("srcROEBlendNodeTxtField", tx="targetBlend")
cmds.text(l="Frames:")
srcROEFrames = cmds.textField("srcROEFramesTxtField", tx="36")
cmds.button(l="Export Source ROE", w=250, c=exportSrcROE)

cmds.separator(style='none', height=5, p="mainLayout")

''' Export Target CV List File '''
cmds.frameLayout("exportTarget", l="Export Target CV List File",
                p="mainLayout", nch=2, cll=True, w=270)
cmds.rowColumnLayout("exportTargetList", p="exportTarget", nc=2, cw=[(1,100), (2,150)])
cmds.text(l="FileName:")
trgFileName = cmds.textField("trgFileNameTxtField", tx="kokoCtrlList.dat")
cmds.button(l="Export Target CV List", w=250, c=exportTrgCV)

cmds.separator(style='none', height=5, p="mainLayout")

''' Export Target Range Of Expression File '''
cmds.frameLayout("exportTrgROE", l="Export Range of Expression File",
                p="mainLayout", nch=2, cll=True, w=270)
cmds.rowColumnLayout("exportTrgROEList", p="exportTrgROE", nc=2, cw=[(1,100), (2,150)])
cmds.text(l="Ctrl List:")
cmds.button(l="Import File", c=importTrgCV)
cmds.separator(style='none')
trgROECtrlList = cmds.textField("trgROECtrlListTxtField", tx="kokoCtrlList.dat")
cmds.text(l="FileName:")
trgROEFileName = cmds.textField("trgROEFileNameTxtField", tx="kokoROE.dat")
cmds.text(l="# of Sets:")
trgROENumOfSets = cmds.textField("trgROENumOfSetsTxtField", tx="36")
cmds.button(l="Export Target ROE", w=250, c=exportTrgROE)

cmds.separator(style='none', height=5, p="mainLayout")

''' Export Final Retargeting Result File '''
cmds.frameLayout("finalResult", l="Export Final Retargeting Result File",
                p="mainLayout", nch=2, cll=True, w=270)
cmds.rowColumnLayout("finalResultList", p="finalResult", nc=2, cw=[(1,100), (2,150)])
cmds.text(l="Source ROE File:")
cmds.button(l="Source ROE Import", c=importSrcROE)
cmds.separator(style='none')
srcROEFile = cmds.textField("srcROEFileTxtField")
cmds.text(l="Target ROE File:")
cmds.button(l="Target ROE Import", c=importTrgROE)
cmds.separator(style='none')
trgROEFile = cmds.textField("trgROEFileTxtField")
cmds.text(l="Source Data File:")
cmds.button(l="Source Animation Import", c=importSrcAni)
cmds.separator(style='none')
srcAniFile = cmds.textField("srcAniTxtField")
cmds.text(l="Final Data File:")
finalDataFile = cmds.textField("finalDataFileTxtField", tx="kokoFinalResult.dat")
cmds.button(l="Export Final Result", w=250, c=exportFinalResult)

cmds.separator(style='none', height=5, p="mainLayout")

''' Import Final Result File '''
cmds.frameLayout("importFinalFile", l="Import Final Result File",
                p="mainLayout", nch=2, cll=True, w=270)
cmds.rowColumnLayout("importFinalFileList", p="importFinalFile", nc=2, cw=[(1,100), (2,150)])
cmds.text(l="Ctrl List:")
cmds.button(l="Import file", c=importTrgCVFile)
cmds.separator(style='none')
ctrlListFile = cmds.textField("ctrlListFileTxtField")
cmds.text(l="Final Result File:")
cmds.button(l="Import file", c=importFinalResultFile)
cmds.separator(style='none')
finalResultFile = cmds.textField("finalResultFileTxtField")
cmds.button(l="Import Final Result", w=250, c=importFinalResult)

cmds.separator(style='none', height=5, p="mainLayout")

# Show window
cmds.showWindow(window)
