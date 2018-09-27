import maya.cmds as cmds

# List
list_country = ['Korea (South)', 'United States', 'Afghanistan', 'Albania', 'Algeria', 'Andorra', 'Angola', 'Antigua & Deps', 'Argentina', 'Armenia', 'Australia', 'Austria', 'Azerbaijan', 'Bahamas', 'Bahrain', 'Bangladesh', 'Barbados', 'Belarus', 'Belgium', 'Belize', 'Benin', 'Bhutan', 'Bolivia', 'Bosnia Herzegovina', 'Botswana', 'Brazil', 'Brunei', 'Bulgaria', 'Burkina', 'Burundi', 'Cambodia', 'Cameroon', 'Canada', 'Cape Verde', 'Central African Rep', 'Chad', 'Chile', 'China', 'Colombia', 'Comoros', 'Congo', 'Congo {Democratic Rep}', 'Costa Rica', 'Croatia', 'Cuba', 'Cyprus', 'Czech Republic', 'Denmark', 'Djibouti', 'Dominica', 'Dominican Republic', 'East Timor', 'Ecuador', 'Egypt', 'El Salvador', 'Equatorial Guinea', 'Eritrea', 'Estonia', 'Ethiopia', 'Fiji', 'Finland', 'France', 'Gabon', 'Gambia', 'Georgia', 'Germany', 'Ghana', 'Greece', 'Grenada', 'Guatemala', 'Guinea', 'Guinea-Bissau', 'Guyana', 'Haiti', 'Honduras', 'Hungary', 'Iceland', 'India', 'Indonesia', 'Iran', 'Iraq', 'Ireland {Republic}', 'Israel', 'Italy', 'Ivory Coast', 'Jamaica', 'Japan', 'Jordan', 'Kazakhstan', 'Kenya', 'Kiribati', 'Korea North', 'Korea South', 'Kosovo', 'Kuwait', 'Kyrgyzstan', 'Laos', 'Latvia', 'Lebanon', 'Lesotho', 'Liberia', 'Libya', 'Liechtenstein', 'Lithuania', 'Luxembourg', 'Macedonia', 'Madagascar', 'Malawi', 'Malaysia', 'Maldives', 'Mali', 'Malta', 'Marshall Islands', 'Mauritania', 'Mauritius', 'Mexico', 'Micronesia', 'Moldova', 'Monaco', 'Mongolia', 'Montenegro', 'Morocco', 'Mozambique', 'Myanmar, {Burma}', 'Namibia', 'Nauru', 'Nepal', 'Netherlands', 'New Zealand', 'Nicaragua', 'Niger', 'Nigeria', 'Norway', 'Oman', 'Pakistan', 'Palau', 'Panama', 'Papua New Guinea', 'Paraguay', 'Peru', 'Philippines', 'Poland', 'Portugal', 'Qatar', 'Romania', 'Russian Federation', 'Rwanda', 'St Kitts & Nevis', 'St Lucia', 'Saint Vincent & the Grenadines', 'Samoa', 'San Marino', 'Sao Tome & Principe', 'Saudi Arabia', 'Senegal', 'Serbia', 'Seychelles', 'Sierra Leone', 'Singapore', 'Slovakia', 'Slovenia', 'Solomon Islands', 'Somalia', 'South Africa', 'South Sudan', 'Spain', 'Sri Lanka', 'Sudan', 'Suriname', 'Swaziland', 'Sweden', 'Switzerland', 'Syria', 'Taiwan', 'Tajikistan', 'Tanzania', 'Thailand', 'Togo', 'Tonga', 'Trinidad & Tobago', 'Tunisia', 'Turkey', 'Turkmenistan', 'Tuvalu', 'Uganda', 'Ukraine', 'United Arab Emirates', 'United Kingdom', 'United States', 'Uruguay', 'Uzbekistan', 'Vanuatu', 'Vatican City', 'Venezuela', 'Vietnam', 'Yemen', 'Zambia', 'Zimbabwe']
list_status = ['Single', 'In a relationship', 'Engaged', 'Married']
list_attr = []

# Show Info Dialog
def showDialog(*args):
    messages= 'Hello everyone! \n\n'
    messages += 'My name is ' + cmds.textField(name, query=True, text=True)
    messages += " and I'm from " + cmds.optionMenu(country, query=True, value=True) + '.\n'
    
    if cmds.checkBox(optionCheck, query=True, value=True):
        messages += "I am " + cmds.radioCollection(gender, query=True, select=True)
        messages += " and now I'm " + cmds.optionMenu(status, query=True, value=True) + '.\n'
    messages += "\n :D \n"
    cmds.confirmDialog(title="Hey", message=messages)

# Close Window
def closeWindow(*args):
    cmds.deleteUI(window, window=True)

# Control 3D Object    
def control3DObject(*args):
    controlAttr = cmds.textField(attrName, query=True, text=True)
    if not controlAttr:
        cmds.delete()
        cmds.deleteUI("attribute")
        attrScroll = cmds.scrollLayout("attribute", p="myControllerFrame")
        cmds.polySphere(name='mySphere')
        global list_attr
        list_attr = []
        return
    if not cmds.objExists('mySphere'):
        cmds.polySphere(name='mySphere')
    
    
    translateMinMax = [-20, 20]
    rotateMinMax = [-360, 360]
    scaleMinMax = [-20, 20]
    attrType = [translateMinMax, rotateMinMax, scaleMinMax]
    fieldRangeType = []
    
    if controlAttr.find('translate') > -1:
        fieldRangeType=attrType[0]
    elif controlAttr.find('rotate') > -1:
        fieldRangeType=attrType[1]
    elif controlAttr.find('scale') > -1:
        fieldRangeType=attrType[2]
        
    try:
        if controlAttr not in list_attr:
            cmds.attrFieldSliderGrp(at=('%s.'+controlAttr) % 'mySphere', p="attribute", fieldMinValue=fieldRangeType[0], fieldMaxValue=fieldRangeType[1])
            list_attr.append(controlAttr)
    except:
        cmds.confirmDialog(message="The Attribute Does not Exist!") 

# Enable or disable Additional Info
def optionCheck(*args):
    enable = cmds.checkBox(optionCheck, query=True, value=True)
    if enable:
        cmds.radioButton(female, edit=True, enable=True)
        cmds.radioButton(male, edit=True, enable=True)
        cmds.optionMenu(status, edit=True, enable=True)
    else:
        cmds.radioButton(female, edit=True, enable=False)
        cmds.radioButton(male, edit=True, enable=False)
        cmds.optionMenu(status, edit=True, enable=False)
    


# Window Setting
windowName="Self Introduction"
windowSize = [505, 400]
    
window = cmds.window(title=windowName, widthHeight=windowSize, sizeable=False)


''' MainLayout '''
cmds.columnLayout("mainColumn", adjustableColumn=True)


''' About Me Layout '''
cmds.columnLayout("aboutMe", p="mainColumn", columnAlign='center', height=60, backgroundColor=[1, 1, 1])
cmds.text("", height=2.5)
cmds.text("About Me", p="aboutMe", width=500, height=55, backgroundColor=[0.8, 0.8, 0.8], fn="boldLabelFont")


''' Info Layout '''
cmds.frameLayout("I am...", p="mainColumn")
cmds.columnLayout("iAmRC", rs=10)


''' Basic Info Layout '''
cmds.rowColumnLayout("BasicInfo", numberOfColumns=2, columnWidth=[(1,100),(2,400)], p="iAmRC")

# Name part
cmds.text(label="Name: ", p="BasicInfo", align='center')
name = cmds.textField("nameOfTextField")

# Country part
cmds.text(label="Country: ", p="BasicInfo", align='center')
country = cmds.optionMenu("countryItem")
for c in list_country:
    cmds.menuItem(c)


''' Additional Info Layout '''
cmds.rowColumnLayout("AdditionalInfo", numberOfColumns=2, columnWidth=[(1,100),(2,400)], p="iAmRC")

# Print Option part
cmds.text(label="Print Option: ", p="AdditionalInfo", align='center')
optionCheck = cmds.checkBox("Show optional information", changeCommand=optionCheck)

# Gender part
cmds.text(label="Gender: ", p="AdditionalInfo", align='center')
gender = cmds.radioCollection()
cmds.rowLayout(numberOfColumns=2)
female=cmds.radioButton("female", enable=False)
male=cmds.radioButton("male", enable=False)
cmds.setParent( '..' )
cmds.radioCollection(gender, edit=True, select=female)

# Status part
cmds.text(label="Status: ", p="AdditionalInfo", align='center')
status=cmds.optionMenu("statusItem", enable=False)
for s in list_status:
    cmds.menuItem(s)
    
# Buttons part
cmds.rowLayout("buttons", p="mainColumn", numberOfColumns=2, columnWidth=[350,150], h=50)
cmds.button(label="Show", p="buttons", w=350, h=30, command=showDialog)
cmds.button(label="Cancel", p="buttons", w=150, h=30, command=closeWindow)


''' My Controller Layout '''
cmds.frameLayout("myControllerFrame", label="My Controller", p="mainColumn", collapsable=True, collapse=True)
cmds.rowLayout("controller", p="myControllerFrame", numberOfColumns=3, columnWidth3=[100, 220, 180])
cmds.text(label="Attribute: ", p="controller", align='center', w=100)
attrName = cmds.textField("attrOfTextField", p="controller", w=220)
cmds.button(label="Apply", p="controller", w=180, command=control3DObject)
attrScroll = cmds.scrollLayout("attribute", p="myControllerFrame")


# Show Window    
cmds.showWindow(window)