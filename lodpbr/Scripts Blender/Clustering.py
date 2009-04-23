################################################################################
# Importing modules
################################################################################

import Blender
import bpy

from Blender  import Scene, Draw, BGL, Window , Mesh ,Mathutils , Object
from Blender.Mathutils import *
from Blender.Object import *

from sets import Set as set

#import Cluster
#from Cluster import *

import math
from math import *
import goo

import Ellipse
from Ellipse import Ellipse    

import KDTree
from KDTree import *

index = 0

listEllipse     = []
listNovoSplat   = [] 
######################################################
# Class
######################################################


BIGELLIPSE = False
MAX_ERROR = 0.5

class Cluster:
    def __init__(self):
        # get mesh
        self.mMesh = Mesh.New('Mesh') 
        #Vertice that begins the agglomeration
        # in (index of the vertice on mesh)
        """ Cluster Looping """  
              
        self.ListSeed = []
        
        """ End Cluster Looping """
        self.mSeed = None
        # List of the vertices similar to the seed
        self.mSimilar = []
        # Neighbors
        self.mNeighbors = []
        # Threshold
        self.mThreshold = 0.25       #
        
        self.tree = Kdtree(1)
        
    def Mesh(self,mesh):
        self.mMesh = mesh
        self.tree = Kdtree(1)
        for f in self.mMesh.faces:
             if f.sel == 1: self.mSeed = f
             self.tree.insert(f)
        k = []
        k = self.SeedExpansion(self.mSeed,0)
        print self.ListSeed,"List SEED"
        print "LEN DE KCLOSED" ,len(k_close)
        for f in k_close:
                f[1].col[0].r = 255
                f[1].col[0].g = 0
                f[1].col[0].b = 0
                f[1].col[1].r = 255
                f[1].col[1].g = 0
                f[1].col[1].b = 0
                f[1].col[2].r = 255
                f[1].col[2].g = 0
                f[1].col[2].b = 0                                
        self.mSeed.col[0].r = 0
        self.mSeed.col[0].g = 0
        self.mSeed.col[0].b = 255
        self.mSeed.col[1].r = 0
        self.mSeed.col[1].g = 0
        self.mSeed.col[1].b = 255
        self.mSeed.col[2].r = 0
        self.mSeed.col[2].g = 0
        self.mSeed.col[2].b = 255     
        self.KClose_to_Seed()    
    def Threshold(self,threshold):
        self.mThreshold = threshold
    def GetNeighbors(self):
        self.mNeighbors = []
        for f in self.mMesh.faces:
            if f.sel == 1:
             self.mNeighbors.append(f)
    def Seed(self):
        for f in self.mMesh.faces:
            if f.sel == 1:
             self.mSeed = f
    def EuclideanDistance(self,v,u):
        return sqrt(    (v.x - u.x) * (v.x - u.x) +
                        (v.y - u.y) * (v.y - u.y) +
                        (v.z - u.z) * (v.z - u.z) )
        
### Cluster Looping

    def SeedExpansion(self, seed,idCluster):
        """ Expande um semente , e gera um cluster quando passa no teste de agregacao """
        listOpen = []
        listClose = []
        listCluster = []
        mCurrentEllipse = seed
        heappush((0.0,seed))
        
        """ Enquanto tiver pontos a serem explorados na vizinhanca da semente """                
        while len(listOpen) > 0:  
   
            target = heappop(listOpen)
            cost      = target[0]   
            ellipse  = target[1]

            """ Se o ponto ja foi expandido , tirar proximo elemento ta lista aberta """
            if   (ellipse.mLastClusterID == idCluster) and (ellipse.mLastClusterCost < cost) :
                continue
            """ inclui apenas as ellipses para uma futura agregacao """
            listClose.append(ellipse)
            """ dado criterio de agregacao .. saber se para e gera um Ellipse"""
            if  self.Aggregation(close) == True:
                if  BIGELLIPSE:
                    listClose.append(mCurrentEllipse);
                    #mCurrentEllipse = MakeEllipse(listClose);
            
                else:
                    listCluster.extend(listClose)
                    #mCurrentEllipse = MakeEllipse(listCluster)

                if  mCurrentEllipse.mError > MAX_ERROR :
                    while  len(listClose) > 0 :
                        temp = listClose.pop()
                        if  temp.mClusterID == -1:
                            self.ListSeed.append(temp)
                    while  len(listOpen) > 0:
                        temp = open.pop();
                        if  temp.mClusterID == -1:
                            self.ListSeed.append(temp)
                ## mCurrentEllipse.mError < MAX_ERROR 
                else:
                    #UpdateAggregationCoditions()
                    listCluster.extend(listClose)
                    while  len(listClose):
                        temp = listClose.pop()
                        if temp.mError > mCurrentEllipse.mError: 
                            temp.mError = mCurrentEllipse.mError
                            temp.mClusterID = idCluster
                            

            kNeighbor = [] 
            kNeighbor = self.tree.kClosest(self.mSeed,20)
                  
            for i in  kNeighbor: 
           
                """  Se nao estiver em um cluster ou seu costo do novo caminho desde a semente � melhor """
                if  ( i[1].mLastClusterID != idCluster) or (i[0] < i.mLastClusterCost) :
                             """ Se custo for melhor que um Threshold , poe na lista aberto para futura expanssao"""
                             if  i[0] < MAX_COST:
                                 i[1].mLastClusterCost = i[0]
                                 i[1].mLastClusterID   = idCluster
                                 heappush((i[0],i))
                                 """  Senao acrescenta-o a  lista de semente"""
                             else:
                                if  i[1].mLastClusterID == -1:
                                    self.ListSeed.append(i)

        return listCluster   
                
    def Aggregation(self,cluster):
         """ Testa se a lista cluster forma um cluster de acordo com os criterios abaixo """ 
         if len(listCluster) >=  50 or self.Error(istCluster) > self.mThreshold:
                pass           
    def UpdateAggregationCoditions(self,cluster):
        pass            
    def Error(self):
        return 0
    
    def KClose_to_Seed(self):
        k_close = []
        k_close = self.tree.kClosest(self.mSeed,2000)
        print "LEN DE KCLOSED" ,len(k_close)
        for f in k_close:
                f[1].col[0].r = 255
                f[1].col[0].g = 0
                f[1].col[0].b = 0
                f[1].col[1].r = 255
                f[1].col[1].g = 0
                f[1].col[1].b = 0
                f[1].col[2].r = 255
                f[1].col[2].g = 0
                f[1].col[2].b = 0                                
        self.mSeed.col[0].r = 0
        self.mSeed.col[0].g = 0
        self.mSeed.col[0].b = 255
        self.mSeed.col[1].r = 0
        self.mSeed.col[1].g = 0
        self.mSeed.col[1].b = 255
        self.mSeed.col[2].r = 0
        self.mSeed.col[2].g = 0
        self.mSeed.col[2].b = 255
                                
    def Similars(self):
        self.mSimilars = []
        for f in self.mNeighbors:
         for f in self.mNeighbors:
            print self.EuclideanDistance(f.v[0].co,self.mSeed.co) , "v1"
            if self.EuclideanDistance(f.v[0].co,self.mSeed.co) < self.mThreshold:
                self.mSimilar.append(f.v[0])
            print self.EuclideanDistance(f.v[1].co,self.mSeed.co) , "v2"    
            if self.EuclideanDistance(f.v[1].co,self.mSeed.co) < self.mThreshold:
                self.mSimilar.append(f.v[1])
            print self.EuclideanDistance(f.v[2].co,self.mSeed.co), "v3"
            if self.EuclideanDistance(f.v[2].co,self.mSeed.co) < self.mThreshold:
                self.mSimilar.append(f.v[2]) 
#            if DotVecs(f.v[0].co,self.mSeed.no) > self.mThreshold:
#                self.mSimilar.append(f.v[0])
#            if DotVecs(f.v[1].no,self.mSeed.no) > self.mThreshold:
#                self.mSimilar.append(f.v[1])
#            if DotVecs(f.v[2].no,self.mSeed.no) > self.mThreshold:
#                self.mSimilar.append(f.v[2])        
                 
    def PaintMesh(self):
        map (lambda f: self.PaintVerts(f),self.mNeighbors)
        
    def Update(self):
        pass
               
    def PaintVerts(self,face):
        for v in self.mSimilar:
            if face.v[0].index == self.mSeed.index:
                face.col[0].r = 0
                face.col[0].g = 0
                face.col[0].b = 255
                continue
            if face.v[0].index == v.index:
                face.col[0].r = 255
                face.col[0].g = 0
                face.col[0].b = 0
                continue
            elif face.v[1].index == v.index:
                face.col[1].r = 255
                face.col[1].g = 0
                face.col[1].b = 0
                continue
            elif face.v[2].index == v.index:
                face.col[2].r = 255
                face.col[2].g = 0
                face.col[2].b = 0
                continue
            else:
               continue



#######################################################
         
                
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