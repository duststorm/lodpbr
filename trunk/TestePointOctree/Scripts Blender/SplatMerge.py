################################################################################
# Importing modules
################################################################################

import Blender
import bpy

from Blender  import Scene, Draw, BGL, Window , Mesh ,Mathutils , Object
from Blender.Mathutils import *
from Blender.Object import *

from sets import Set as set

import math
from math import *
import goo


import Ellipse
from Ellipse import Ellipse    

index = 0

listEllipse     = []
listNovoSplat   = [] 
######################################################
# Class
######################################################


mousex=1
mousey=1

rounded=[1,1,1,1]
idtrack=[0,0]

background=[0.7,0.7,0.7,0.0]
border=[0.0,0.0,0.0]
lowpane=[0.65,0.65,0.55]
black=[0.0,0.0,0.0]

maincol=[0.7,0.8,0.7]
formcol=[0.90,0.9,0.50]
facecol=[0.50,0.65,0.75]
strutcol=[0.50,0.60,0.7]
hubcol=[0.50,0.55,0.65]
helpcol=[0.59,0.59,0.59]

green0=[0.65,0.75,0.65]
green1=[0.6,0.7,0.6]
green2=[0.55,0.65,0.55]
green3=[0.5,0.6,0.5]
green4=[0.45,0.55,0.45]
green5=[0.40,0.50,0.40]
green6=[0.35,0.45,0.35]
green7=[0.30,0.40,0.30]
palegreen=[0.7,0.9,0.7]

'''    Tab Principal  -
    mainTitles    - Label da  abas
    mainColours - Core da abas
    mainPageID  - Identificador de evento da aba
'''
mainTitles=["Main"]
mainColours=[maincol,facecol,strutcol,hubcol,helpcol]
mainPageID=Draw.Create(2)

mainTabs=goo.Tabs( len( mainTitles ), mainTitles, mainColours, border, black, mainPageID)

# Events
EVENT_EXIT = 0

'''    Tab Face -
'''



# Pega o centro e a normal dos Splats Selecionados
getSplat = Draw.Create( 1 )
# Events
EVENT_GETSPLAT = 1

# Gera um novo Splat na posição (0,0,0)
GerarSplat = Draw.Create( 2 )
# Events
EVENT_GERARSPLAT = 2

#Gerar novo Centro e nova Normal

GerarNovoCentroENormal = Draw.Create( 2 )
# Events
EVENT_NOVOCENTROENORMAL = 3

#tamanho do eixo A
EixoA  = Draw.Create(1.0)
#Events 
EVENT_EIXOA = 4

#tamanho do eixo A
EixoB  = Draw.Create(1.5)
#Events 
EVENT_EIXOB = 5
######################################################
# GUI drawing
######################################################

def drawgui():

    global mousex, mousey, click, gs, mainTabs, subtabs,inpanel,rounded
    global background,border,idtrack,makeGeodesic
    #Events
    global EVENT_CENTERFACE, EVENT_EXIT

    gs=goo.GuiSpace(background)

    click=goo.ClickTracker()

    if gs.width<350:

        gs.width=350

    if gs.height<500:

        gs.height=500

    lowline=80

    lp=goo.Panel(5, 5, 120, lowline-10, background, border,rounded)
    Draw.Button("EXIT", EVENT_EXIT, lp.left+10, lp.base+10,lp.width-20,lp.height-20 )

    xstart=5
    mainTabs.drawtabs(xstart, lowline, gs.width-xstart-5, gs.height-lowline-10, 50, click)

    if mainTabs.pageid.val == 0:
        facecontrols()

    if mainTabs.pageid.val == 1:
        pass
        
    

def facecontrols():

    global GerarNovoCentroENormal, truncateF, original ,EixoA , EixoB
    global estrelarMais , identar , getSplat , truncMais, GerarSplat

    ds=goo.ScafFold(mainTabs.left+20, mainTabs.pane.top-270,400,230,7,5)


    getSplat          = Draw.Button("Get Splats", EVENT_GETSPLAT,ds.col1[0],ds.row[0], 120,ds.bheight[0])
    
    GerarSplat        = Draw.Button("Gerar Splat", EVENT_GERARSPLAT,ds.col2[1],ds.row[0], 120,ds.bheight[0])
#    
    GerarNovoCentroENormal = Draw.Button("Novo Centro e Normal", EVENT_NOVOCENTROENORMAL,ds.col1[0],ds.row[2], 120,ds.bheight[0])
#    
    EixoA =     Draw.Number("Eixo A  ",EVENT_EIXOA, ds.col2[1], ds.row[2], 240, ds.bheight[0], EixoA.val, 0.1, 10,"Tamanho - Eixo A")
    
    EixoB =     Draw.Number("Eixo B  ",EVENT_EIXOB, ds.col2[1], ds.row[3], 240, ds.bheight[0], EixoB.val, 0.1, 10,"Tamanho - Eixo B")
#    estrelarMais     = Draw.Button("Estrelar (+)", EVENT_ESTRELARMAIS,ds.col1[0],ds.row[3], 120,ds.bheight[0])
#
#    identar          = Draw.Button("Identar  (-)", EVENT_IDENTAR,ds.col1[0],ds.row[4], 120,ds.bheight[0])
#    
#    truncateF        = Draw.Button("Truncar", EVENT_TRUNCATEF,ds.col2[1],ds.row[2], 120,ds.bheight[0])
#
#    truncMais        = Draw.Button("Truncar Mais  (+)", EVENT_TRUNCMAIS,ds.col2[1],ds.row[3], 120,ds.bheight[0])
#
#    truncMenos       = Draw.Button("Truncar Menos (-)", EVENT_TRUNMENOS,ds.col2[1],ds.row[4], 120,ds.bheight[0])



def otherevents(evt, val):

    global mousex,mousey

    if (evt== Draw.ESCKEY and not val):
        Draw.Exit()

    if (evt== Draw.QKEY and not val):
        Draw.Exit()

    if (evt==Draw.MOUSEX):
        mousex=val-gs.left

    if (evt==Draw.MOUSEY):
        mousey=val-gs.base

    if (evt==Draw.LEFTMOUSE):

        click.clickcheck(mousex,mousey)

        Draw.Register(drawgui, otherevents, buttonevents)

def buttonevents(evt):
    
    global index, listEllipse ,listNovoSplat
    
    if ( evt == EVENT_EXIT ):
        Draw.Exit()
        
    if (evt == EVENT_NOVOCENTROENORMAL):
        
        SomaArea         = 0
        SomaAreaCentro   = Blender.Mathutils.Vector(0.0,0.0,0.0)
        SomaAreaNormal   = Blender.Mathutils.Vector(0.0,0.0,0.0)
        listSelecionados = []
        
        in_editmode = Window.EditMode()
        
        if in_editmode:
            Window.EditMode(0)

        object = Blender.Object.GetSelected()
        
        
                
        for i in object:
            
            for j in listEllipse:
                if j.Name() == i.getName():
                    print 'Vamprito'
                    j.SetCenter(i.getData(False, True).verts[-1].co)
                    j.SetNormal(i.getData(False, True).faces[0].no)
                    listSelecionados.append(j)
                    
        print len(listSelecionados), '=='     
        for i in listSelecionados: 
            
            print i.Name(),i.Center(),'==' 
            print i.Name(),i.Normal(), '=='
            print i.Area(), '=='
            SomaArea         += i.Area()
            SomaAreaCentro   += i.Area() * i.Center()
            SomaAreaNormal   += i.Area() * i.Normal()
        
        me= Blender.Mesh.New('FElipe')
       
        me.verts.extend([SomaAreaCentro/SomaArea])
        me.verts[-1].no = SomaAreaNormal/SomaArea
        me.edges.extend(me.verts[0],me.verts[-1])
        #Vertex do Centro
      
        scn = Blender.Scene.GetCurrent()
        ob = scn.objects.new(me,listEllipse[-1].Name())
        
        if in_editmode:
            Window.EditMode(1)
        
    if (evt == EVENT_GERARSPLAT):
        
       in_editmode = Window.EditMode()
        
       if in_editmode:
           Window.EditMode(0)
            
       listEllipse.append( Ellipse(Vector(0.0,0.0,0.0),EixoA.val,EixoB.val,60.0,"Ellipse"+str(index)) )
       
       index += 1
       
       polyline1 =  listEllipse[-1].CalculateBoundaries(0.0)
       # Make a new mesh and add the truangles into it
       me= Blender.Mesh.New(listEllipse[-1].Name())
       
       me.verts.extend(polyline1)
       me.edges.extend(me.verts[0],me.verts[-1])
       #Vertex do Centro
       me.verts.extend(0.0,0.0,0.0)
       me.faces.extend(me.verts[-1],me.verts[-2],me.verts[0]) # Add the faces, they reference the verts in polyline 1 and 2
       
       for i in range(0,len(polyline1)-1):
           me.edges.extend(me.verts[i],me.verts[i+1])
           me.faces.extend(me.verts[i],me.verts[i+1],me.verts[-1]) # Add the faces, they reference the verts in polyline 1 and 2

       scn = Blender.Scene.GetCurrent()
       ob = scn.objects.new(me,listEllipse[-1].Name())
       
       print ob.name,'olha o nome'
       ob.setName(listEllipse[-1].Name())
       print ob.name,'olha o nome',listEllipse[-1].Name()
       if in_editmode:
           Window.EditMode(1)
       
    if ( evt == EVENT_GETSPLAT ):
        
        in_editmode = Window.EditMode()
        
        if in_editmode:
            Window.EditMode(0)

        object = Blender.Object.GetSelected()
        
#        for i in object:
#            print '-------------------------'
#            print i.getLocation(),'Centro do Blender'
#            print i.getData(False, True).faces[0].no,'Normal'       
#            print i.getData(False, True).verts[-1].co,  'Meu Centro'
#            print i.getName()
#        for j in listEllipse:
#            print j.Name(),j.Center(),'==' 
#            print j.Name(),j.Normal(), '=='
        print '##############################'    
        if in_editmode:
            Window.EditMode(1)


Draw.Register(drawgui, otherevents, buttonevents)