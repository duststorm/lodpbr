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

from Cluster import Cluster


index = 0

listEllipse     = []
listNovoSplat   = [] 
######################################################
# Class
######################################################

         
                
mousex=1
mousey=1


cluster = Cluster()

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

     Generates only one cluster
'''

BuildOneClustering = Draw.Create( 1 )
# Events
EVENT_BUILD_ONE_CLUSTRING = 1

'''
    Generates all possible cluster
'''

BuildAllClustering = Draw.Create( 2 )
# Events
EVENT_BUILD_ALL_CLUSTERING = 2


'''
    Choose how dissimilarity each other
'''


MenuDissimilarity = Draw.Create( 3 )
# Events
EVENT_DISSIMILARITY = 3

Seed = Draw.Create( 4)

EVENT_SEED = 6

Neihbors = Draw.Create( 5 )

EVENT_NEIGHBORS = 5

GetMesh = Draw.Create( 6 )

EVENT_GETMESH = 6

Threshold = Draw.Create( 0.0 )

EVENT_THRESHOLD = 7
######################################################
# GUI drawing
######################################################

def drawgui():

    global mousex, mousey, click, gs, mainTabs, subtabs,inpanel,rounded
    global background,border,idtrack,makeGeodesic
    #Events
    global EVENT_EXIT

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

    global BuildAllClustering , BuildOneClustering , retval , block , MenuDissimilarity
    global Seed, Neihbors, Threshold
    
    
    ds=goo.ScafFold(mainTabs.left+20, mainTabs.pane.top-270,400,230,7,5)

    GetMesh             = Draw.Button("GetMesh",               EVENT_GETMESH , ds.col1[0],ds.row[0], 120,ds.bheight[0])
    
    Seed                = Draw.Button("Seed",                  EVENT_SEED ,    ds.col1[0],ds.row[1], 120,ds.bheight[0])
    
    Neihbors            = Draw.Button("Neighbors",             EVENT_NEIGHBORS,ds.col1[0],ds.row[2], 120,ds.bheight[0])
    
    Threshold           = Draw.Number("Threshold  ",           EVENT_THRESHOLD,ds.col2[0],ds.row[3], 240, ds.bheight[0], Threshold.val, 0.25, 1,"Threshold")
    
    BuildOneClustering  = Draw.Button("Build one Clustering",  EVENT_BUILD_ONE_CLUSTRING ,ds.col3[1],ds.row[0], 120,ds.bheight[0])
    
    BuildAllClustering  = Draw.Button("Build all Clustering",  EVENT_BUILD_ALL_CLUSTERING,ds.col3[1],ds.row[1], 120,ds.bheight[0])
          
    name = "The Title %t|First Entry %x1|Second Entry %x2|Third Entry %x3|Fourty Entry %x4"
    
    MenuDissimilarity = Draw.Menu(name, EVENT_DISSIMILARITY, 60, 120, 200, 40, MenuDissimilarity.val, "Just a test menu.")

    
    #    
#    GerarNovoCentroENormal = Draw.Button("", EVENT_NOVOCENTROENORMAL,ds.col1[0],ds.row[2], 120,ds.bheight[0])
#    
#    EixoA =     Draw.Number("Eixo A  ",EVENT_EIXOA, ds.col2[1], ds.row[2], 240, ds.bheight[0], EixoA.val, 0.1, 10,"Tamanho - Eixo A")
    
#    EixoB =     Draw.Number("Eixo B  ",EVENT_EIXOB, ds.col2[1], ds.row[3], 240, ds.bheight[0], EixoB.val, 0.1, 10,"Tamanho - Eixo B")
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
        
    if (evt == EVENT_GETMESH):
        
        in_editmode = Window.EditMode()
        
        if in_editmode:
            Window.EditMode(0)
                      
        object = Blender.Object.GetSelected()
        me = object[0].getData(False, True)
        me.vertexColors = 1
        print "ENTROU"
        cluster.Mesh(me)
        
        if in_editmode:
           Window.EditMode(1)
                   
#    if (evt == EVENT_BUILD_ONE_CLUSTRING):
#        
#       in_editmode = Window.EditMode()
#        
#       if in_editmode:
#           Window.EditMode(0)
#       cluster.KClose_to_Seed()    
##       cluster.Similars()  
##       cluster.PaintMesh()
#            
#       
#       if in_editmode:
#           Window.EditMode(1)
#       
#    if ( evt == EVENT_BUILD_ALL_CLUSTERING ):
#        
#        in_editmode = Window.EditMode()
#                
#        if in_editmode:
#           Window.EditMode(0)
#                  
#        if in_editmode:
#           Window.EditMode(1)
#
#    if ( evt == EVENT_DISSIMILARITY ):
#        
#        in_editmode = Window.EditMode()
#                
#        if in_editmode:
#           Window.EditMode(0)
#           
#           
#           object = Blender.Object.GetSelected()
#        
#           me = object[0].getData(False, True)
#           me.vertexColors = 1
#            
#           nums = filter(lambda x: x.sel == 1, me.verts)
#            
#           print len(nums),"Vl"
#           print nums
#             
#                  
#        if in_editmode:
#           Window.EditMode(1)           
#    if (evt == EVENT_SEED):
#        
#        in_editmode = Window.EditMode()
#        
#        if in_editmode:
#            Window.EditMode(0)
#             
#        print "ENTROU SEED"             
#        cluster.Seed()
#        
#        if in_editmode:
#           Window.EditMode(1) 
#        
#    if (evt == EVENT_NEIGHBORS):
#        
#        in_editmode = Window.EditMode()
#        
#        if in_editmode:
#            Window.EditMode(0)
#            
#        cluster.Neighbors()
#        
#        if in_editmode:
#           Window.EditMode(1) 
#           
#    if (evt == EVENT_THRESHOLD):
#        cluster.Threshold(Threshold.val)
#        print cluster.mThreshold
                 
           
Draw.Register(drawgui, otherevents, buttonevents)