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
import polyhedronBuild 
#from polyhedronBuild import Polyhedron
t = 0.0

######################################################
# Class
######################################################

class tetrahedron:
    def vertices(self):
        l = [[0.626107 ,0.626107  ,-0.683949 ],
              [0.192501 ,-0.992133 , -0.683949],
              [-0.992132,0.192501  ,-0.683949 ],
              [-0.057841,-0.057841 , 0.683949 ]]
        
    def faces(self):
        l = [[3,3,0,1],
             [3,1,2,3],
             [3,2,0,3],
             [3,1,2,0]] 


class Vertex:
    def __init__(self,v,s,t):
        self.vert = v
        self.source = s
        self.target = t
        self.index = 0

class VertexFigure:
    def __init__(self):
        self.vertice   = 0
        # list of Vertex
        self.verts     = []

class Truncation:
    def __init__(self):
        # lista de Vertices da nova Face
        self.truc                     = False
        #factor multiplication
        self.factor     = 0.0
        # vertices de um face , podem ter mais de 4
        self.verts                    =[]
        #indexVectors
        self.index                    =[]
        #vertices do centro da face
        self.centerVerts              = None
        # index do centro da face
        self.indexCenterVerts         = None
        #direcao normal da face - usado no procedimento stella
        self.directionCenterVerts     = None
        #vertice originais
        self.originalVerts            = []
        #novos Vertices adicionados
        self.newVerts                 = []


    def sort(self):

        aux  = self.verts[0]

        oldVerts = self.verts

        newVerts = []

        newVerts.append (  oldVerts[0] )

        del oldVerts[0]

        while len(oldVerts) != 0:
            for v in  oldVerts :
                if  (v.source == aux.target) and ( v.target == aux.source ):
                     newVerts.append (v)
                     aux = v
                     del oldVerts[oldVerts.index(v)]
            for v in  oldVerts :
                if  (v.source == aux.source):
                     newVerts.append (v)
                     aux = v
                     del oldVerts[oldVerts.index(v)]

        self.verts = newVerts

       
    def length (self,v1,v2):
        
        x = v1.target.x - v2.target.x
        y = v1.target.y - v2.target.y
        z = v1.target.z - v2.target.z
        
        return sqrt (x*x + y*y + z*z)
    
    def sortNew(self):
        
        aux  = self.verts[0]

        oldVerts = self.verts

        newVerts = []

        newVerts.append (  oldVerts[0] )

        del oldVerts[0]
        
        while len (oldVerts) != 0:
            l = map ( lambda x : self.length(aux, x),oldVerts)
            index = l.index (min (l))
            newVerts.append (oldVerts[index])
            aux = oldVerts[index]
            del oldVerts[index]

        self.verts = newVerts

            
    def centerFace (self):

        resultx = 0.0
        resulty = 0.0
        resultz = 0.0

        totalArea = 0.0
        tempArea = 0.0

        lenV =  len(self.verts)

        print lenV

        for i in range(0,  lenV  - 2 ):
            tempArea = TriangleArea(self.newVerts[i],self.newVerts[i + 1],self.newVerts[lenV - 1])

            print tempArea , 'CArvalho'
            
            totalArea = totalArea + tempArea

            resultx = resultx + tempArea * (self.newVerts[i].x + self.newVerts[i + 1].x + self.newVerts[lenV - 1].x) / 3.0
            resulty = resulty + tempArea * (self.newVerts[i].y + self.newVerts[i + 1].y + self.newVerts[lenV - 1].y) / 3.0
            resultz = resultz + tempArea * (self.newVerts[i].z + self.newVerts[i + 1].z + self.newVerts[lenV - 1].z) / 3.0

        x = resultx / totalArea
        y = resulty / totalArea
        z = resultz / totalArea

        return (Blender.Mathutils.Vector(x,y,z))







class Polyhedron:

    def __init__(self):

        in_editmode = Window.EditMode()

        mCopy = None
        #Novas Faces
        self.truncation   = []
        #NewVertices
        self.newVertices  = []
        self.centerVerts  = []
        #direcao de crescimento
        self.direction    = []
        # Vertex Figure
        self.vertexFigure = []
        #Vertices Originais
        self.copyVertices = []
        #Faces Originais
        self.copyFaces    = []
        #indices dos vertices Originais
        self.originalVertices = []
        

        if in_editmode:
            Window.EditMode(0)

        object = Blender.Object.GetSelected()
        self.mesh = object[0].getData(False, True)

        self.copy()

        if in_editmode:
            Window.EditMode(1)
            
    def newFaceVertices(self,face):

        newV = []
        newF = []

        cent = face.cent

        newV =  [ v.co for v in face.verts]

        newF.extend( [ v  for v in  self.newVertices if (v.source in newV) and  (v.target in newV)  ] )

        return newF
    
    def truncate(self,factor):
        
        in_editmode = Window.EditMode()
        if in_editmode:
            Window.EditMode(0)

        # Para cada vertice do polyhedron , adicioana-se os novos vertices e a direção em
        # que ele será inserido na aresta
        
        for e in self.mesh.edges:
            self.newVertices.append(  Vertex (e.v1.co.copy(),e.v1.co.copy(),e.v2.co.copy()) )
            self.newVertices.append(  Vertex (e.v2.co.copy(),e.v2.co.copy(),e.v1.co.copy())  )

        # Vertices da nova Face criada aparti do corte de um vertice
            
        for v in  self.mesh.verts:
           t = Truncation()
           t.truc = True
           t.factor = (factor)
           for vf in  self.newVertices:
                 if v.co == vf.source:
                     t.verts.append(vf)
           t.sortNew()
           t.centerVerts = vf.source
           self.truncation.append(t)

        for f in  self.mesh.faces:
            t = Truncation()
            t.truc = False
            t.originalVerts.extend(f.verts)
            t.verts.extend (self.newFaceVertices(f))
            t.sort()
            t.centerVerts = f.cent
            t.directionCenterVerts = f.no
            t.factor = (factor)
            self.truncation.append(t)

        self.mesh.verts = None

        # Cria a nova malha com os novos vertices 
        for t in self.truncation:
            if t.truc == True:
                for vt in range ( 0, len(t.verts) ):
                    self.mesh.verts.extend(  t.verts[vt].source.x + (t.verts[vt].source.x-t.verts[vt].target.x)*(t.factor) , t.verts[vt].source.y + (t.verts[vt].source.y-t.verts[vt].target.y)*(t.factor) , t.verts[vt].source.z + (t.verts[vt].source.z-t.verts[vt].target.z)*(t.factor) )
                    t.newVerts.append(self.mesh.verts[-1].co.copy())
                    t.verts[vt].index = self.mesh.verts[-1].index
                    #Reconstruir as faces antigas com os novos Vertices 
                    for tm in self.truncation:
                        if tm.truc == False:
                            for tmv in tm.verts:
                                if (tmv.source == t.verts[vt].source) and (tmv.target == t.verts[vt].target):
                                    tmv.index = self.mesh.verts[-1].index
                                    tm.newVerts.append(self.mesh.verts[-1].co.copy())
                
                self.mesh.verts.extend (t.centerFace())
                t.indexCenterVerts = self.mesh.verts[-1].index 
                self.mesh.faces.extend ( self.mesh.verts[t.verts[0].index], self.mesh.verts[t.verts[-1].index],self.mesh.verts[-1] )
                t.directionCenterVerts =  t.verts[0].source - self.mesh.verts[-1].co 
                t.directionCenterVerts.normalize() 
                for v in range ( 0, len(t.verts)-1 ):
                    self.mesh.faces.extend ( self.mesh.verts[t.verts[v].index], self.mesh.verts[t.verts[v+1].index],self.mesh.verts[-1] )
                         

        for t in self.truncation:
            if t.truc == False:
               self.mesh.verts.extend (t.centerVerts)
               t.indexCenterVerts = self.mesh.verts[-1].index
               self.mesh.faces.extend ( self.mesh.verts[t.verts[0].index], self.mesh.verts[t.verts[-1].index],self.mesh.verts[-1] )
               for j in range (0, len(t.verts) -1 ):
                   self.mesh.faces.extend ( self.mesh.verts[t.verts[j].index], self.mesh.verts[t.verts[j+1].index],self.mesh.verts[-1] )
        if in_editmode:
         Window.EditMode(1)
                               
    def truncSize(self,factor):
        
        in_editmode = Window.EditMode()
        if in_editmode:
            Window.EditMode(0)
                               
        for t in self.truncation:
            t.newVerts = []
            if t.truc == True:
                for v in t.verts:    
                    self.mesh.verts[v.index].co[0] = v.source.x + (v.source.x-v.target.x)*factor#(-0.5)
                    self.mesh.verts[v.index].co[1] = v.source.y + (v.source.y-v.target.y)*factor#(-0.5)
                    self.mesh.verts[v.index].co[2] = v.source.z + (v.source.z-v.target.z)*factor#(-0.5)
                    t.newVerts.append(self.mesh.verts[v.index].co.copy())
                vr = t.centerFace()
                self.mesh.verts[t.indexCenterVerts].co[0] = vr.x    
                self.mesh.verts[t.indexCenterVerts].co[1] = vr.y
                self.mesh.verts[t.indexCenterVerts].co[2] = vr.z
        
                    
        if in_editmode:
            Window.EditMode(1)
                        
            
    def copy(self):
        
        for v in self.mesh.verts:
            self.copyVertices.append([v.co[0],v.co[1],v.co[2]])
        for f in self.mesh.faces:
            lfaces = []
            for v in f.verts:
                lfaces.append (v.index)    
            self.copyFaces.append (lfaces)
            

    def original(self):

        in_editmode = Window.EditMode()
        if in_editmode:
             Window.EditMode(0)

        self.mesh.verts = None
        self.mesh.verts.extend(self.copyVertices)
        self.mesh.faces.extend(self.copyFaces)
        self.truncation = []

        #NewVertices
        self.newVertices  = []
        self.centerVerts  = []
        #direcao de crescimento
        self.direction    = []
        # Vertex Figure
        self.vertexFigure = []
        #Vertices Originais
        self.copyVertices = []
        #Faces Originais
        self.copyFaces    = []
        #indices dos vertices Originais
        self.originalVertices = []
        self.truncation   = []

        if in_editmode:
            Window.EditMode(1)


    def stella(self,factor):

        in_editmode = Window.EditMode()
        if in_editmode:
             Window.EditMode(0)

        lenCV =  len (self.centerVerts)
        if len(self.truncation) > 0:
            for t in self.truncation:
                self.mesh.verts[t.indexCenterVerts].co[0] = self.mesh.verts[t.indexCenterVerts].co[0] + t.directionCenterVerts.x*factor#(-0.5)
                self.mesh.verts[t.indexCenterVerts].co[1] = self.mesh.verts[t.indexCenterVerts].co[1] + t.directionCenterVerts.y*factor#(-0.5)
                self.mesh.verts[t.indexCenterVerts].co[2] = self.mesh.verts[t.indexCenterVerts].co[2] + t.directionCenterVerts.z*factor#(-0.5)
                        
        for i in range (1,lenCV+1):
            self.mesh.verts[-i].co[0] = self.centerVerts[lenCV-i].co[0] + self.direction[lenCV-i][0]*factor#(-0.5)
            self.mesh.verts[-i].co[1] = self.centerVerts[lenCV-i].co[1] + self.direction[lenCV-i][1]*factor#(-0.5)
            self.mesh.verts[-i].co[2] = self.centerVerts[lenCV-i].co[2] + self.direction[lenCV-i][2]*factor#(-0.5)

        if in_editmode:
            Window.EditMode(1)


    def centerFace(self):

        in_editmode = Window.EditMode()

        if in_editmode:
             Window.EditMode(0)

        self.centerVerts   = []
        self.direction  = []

        faces = self.mesh.faces
        lenAux = len (faces)

        for i in range(0,len(faces)):
            self.mesh.verts.extend (  faces[i].cent  )
            self.direction.append(faces[i].no)


            for j in range (0, faces[i].__len__() -1 ):
                self.mesh.faces.extend ( faces[i].verts[j], faces[i].verts[j+1],self.mesh.verts[ -1 ] )

            self.mesh.faces.extend ( faces[i].verts[j+1], faces[i].verts[0],self.mesh.verts[ -1 ] )
            self.centerVerts.append( self.mesh.verts[-1] )

        for i in range(0,lenAux):
            self.mesh.faces.delete ( i , [0] )

#        self.mesh.verts[-1].co[0] = self.mesh.verts[-1].co[0] + self.mesh.verts[-1].co[0]*0.5
#        self.mesh.verts[-1].co[1] = self.mesh.verts[-1].co[1] + self.mesh.verts[-1].co[1]*0.5
#        self.mesh.verts[-1].co[2] = self.mesh.verts[-1].co[2] + self.mesh.verts[-1].co[2]*0.5
        if in_editmode:
            Window.EditMode(1)







poly = None



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

'''	Tab Principal  -
	mainTitles    - Label da  abas
	mainColours - Core da abas
	mainPageID  - Identificador de evento da aba
'''
mainTitles=["Main","Help"]
mainColours=[maincol,facecol,strutcol,hubcol,helpcol]
mainPageID=Draw.Create(2)

mainTabs=goo.Tabs( len( mainTitles ), mainTitles, mainColours, border, black, mainPageID)

# Events
EVENT_EXIT = 1

'''	Tab Face -
'''


# Criar vertice no Centro da Face
getMesh = Draw.Create( 0 )
# Events
EVENT_GETMESH = 9

# Criar vertice no Centro da Face
createCenterFace = Draw.Create( 0 )
# Events
EVENT_CENTERFACE = 3

''' Estrelar +
'''
estrelarMais = Draw.Create( 0 )
# Events
EVENT_ESTRELARMAIS = 4

''' Estrelar -
'''
identar = Draw.Create( 0 )
# Events
EVENT_IDENTAR = 5


''' Truncar +
'''
truncMais = Draw.Create( 0 )
# Events
EVENT_TRUNCMAIS = 6

''' Truncar -
'''
truncMenos = Draw.Create( 0 )
# Events
EVENT_TRUNMENOS = 11

truncateF = Draw.Create ( 1 )
# Events
EVENT_TRUNCATEF = 8

original = Draw.Create ( 1 )
# Events
EVENT_ORIGINAL = 7

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

    global createCenterFace, truncateF, original
    global estrelarMais , identar , getMesh , truncMais, truncMenos

    ds=goo.ScafFold(mainTabs.left+20, mainTabs.pane.top-270,400,230,7,5)


    getMesh          = Draw.Button("Get Mesh", EVENT_GETMESH,ds.col1[0],ds.row[0], 120,ds.bheight[0])
    orignal          = Draw.Button("Original", EVENT_ORIGINAL,ds.col2[1],ds.row[0], 120,ds.bheight[0])
    
    createCenterFace = Draw.Button("Center", EVENT_CENTERFACE,ds.col1[0],ds.row[2], 120,ds.bheight[0])
    
    estrelarMais     = Draw.Button("Estrelar (+)", EVENT_ESTRELARMAIS,ds.col1[0],ds.row[3], 120,ds.bheight[0])

    identar          = Draw.Button("Identar  (-)", EVENT_IDENTAR,ds.col1[0],ds.row[4], 120,ds.bheight[0])
    
    truncateF        = Draw.Button("Truncar", EVENT_TRUNCATEF,ds.col2[1],ds.row[2], 120,ds.bheight[0])

    truncMais        = Draw.Button("Truncar Mais  (+)", EVENT_TRUNCMAIS,ds.col2[1],ds.row[3], 120,ds.bheight[0])

    truncMenos       = Draw.Button("Truncar Menos (-)", EVENT_TRUNMENOS,ds.col2[1],ds.row[4], 120,ds.bheight[0])



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
    global poly ,t
    

    if ( evt == EVENT_EXIT ):
        Draw.Exit()

    if (evt == EVENT_GETMESH):
        poly = Polyhedron()
        
    if ( evt == EVENT_TRUNCATEF ):
        poly.truncate(-0.05)
        
    if ( evt == EVENT_TRUNCMAIS):
       t = t - 0.05
       poly.truncSize(t)
           
    if (evt == EVENT_TRUNMENOS):
        t = t + 0.05
        poly.truncSize(t)
               
    if( evt == EVENT_ORIGINAL ):
        poly.original()
        
    if ( evt == EVENT_CENTERFACE):
        poly.centerFace()
    
    if( evt == EVENT_ESTRELARMAIS ):
        poly.stella(0.25)

    if (evt == EVENT_IDENTAR ):
        poly.stella(-0.25)

Draw.Register(drawgui, otherevents, buttonevents)
