import Blender
import math
#import multiarray
#import LinearAlgebra as la
import Ellipse
import numpy as nu
import scipy.linalg as sc

from Blender.Mathutils import Vector, Matrix ,Intersect, DotVecs, ProjectVecs, CrossVecs, LineIntersect
from Blender  import Scene, Draw, BGL, Window , Mesh ,Mathutils , Object

from numpy.linalg import eig, eigh
from numpy import *

from scipy.linalg import eig, eigh
from scipy import *

from math           import *
#from LinearAlgebra  import *
#from multiarray     import *
from Ellipse        import Ellipse

EPSILON = 0.001

def perpendicular(v):
 
 # select the shortest of projections of axes on v
 # (the closest to perpendicular to v),
 # and project it to the plane defined by v
 if abs(v.x) < abs(v.y): # x < y
     
   if abs(v.x) < abs(v.z):  # x < y && x < z
     t = Blender.Mathutils.Vector(1.0 - (v.x * v.x),-v.x * v.y,-v.x * v.z);
     return t
   
 else: #  y <= x
 
   if abs(v.y) < abs(v.z): # // y <= x && y < z
     t = Blender.Mathutils.Vector( -v.y * v.x, 1.0 - v.y * v.y, -v.y * v.z)
     return t
 # z <= x && z <= y
 t = Blender.Mathutils.Vector(-v.z * v.x, -v.z * v.y, 1.0 - v.z * v.z)
 return t;

class Merge:
       
   def __init__(self,listEllipse):
         
     self.listEllipse     = listEllipse
     self.mCenter         = Blender.Mathutils.Vector(0.0,0.0,0.0)
     self.mNormal         = Blender.Mathutils.Vector(0.0,0.0,0.0)
     
     self.mEigenVector    = []
     self.mEigenValues    = []
     
     self.mA                = 0.0
     self.mB                = 0.0
               
     self.mPontosPorjetos = []
     self.CalcularCentroProgressiveSplatting()
     self.CalcularPointosPojetados()
     self.CalcularEixosAeB()
   
#    def __init__(self,pCenter,pNormal):
#        
#      self.listEllipse    = []
#      self.mEigenVector   = []
#      self.mEigenValues   = []
#      self.PontosPorjetos = []
#      self.mCenter        = pCenter
#      self.mNormal        = pNormal
#      self.CalcularCentroProgressiveSplatting()
#      self.CalcularPointosPojetados()
   def A(self):
       return self.mA
   
   def B(self):
       return self.mB
       
   def Center(self):
       return self.mCenter
   
   def Normal(self):
       return self.mNormal
     
   def EigenVectors (self):
       return self.mEigenVector
   
   def EigenValues (self):
       return self.mEigenValues
   
   def PontosProjetados(self):
       return self.mPontosPorjetos
   def project_point_plane(self,point, norm, pop):
       """Give the projected point on the plane (norm, pop).
       point: point to project (Blender.Mathutils.Vector object).
       norm: normal vector of the plane (Blender.Mathutils.Vector object).
       pop: a point that belong to the plane (Blender.Mathutils.Vector object).
       return: the projected point (Blender.Mathutils.Vector object), or None if invalid norm.
       """
       if norm.length > EPSILON:
           return point - ( (DotVecs(point - pop, norm)*norm)  * (1/(norm.magnitude*norm.magnitude)))#ProjectVecs(point - pop, norm)
       
   def CalcularPointosPojetados(self):
       
       listPoints = []
       
       for i in self.listEllipse:
           m = i.EixoA()
           m.normalize()
           i.Normal().normalize()
           v = i.EixoB()
           v.normalize()
           listPoints = i.CalculateBoundaries(8,[m,v])
           for j in listPoints:
               self.mPontosPorjetos.append(self.project_point_plane(j,self.mNormal,self.mCenter))
               
         
   #! Dado dois splats calcular seu centro e normal
   def CalcularCentroProgressiveSplatting(self):
               
       lSomaCenterAreas = Blender.Mathutils.Vector(0.0,0.0,0.0)
       lSomaNormalAreas = Blender.Mathutils.Vector(0.0,0.0,0.0)
       lSomaAreas       = 0.0
       
       for i in self.listEllipse:
           lSomaCenterAreas += i.Area() * i.Center()
           lSomaNormalAreas += i.Area() * i.Normal()
           lSomaAreas       += i.Area()          
             
       self.mCenter = lSomaCenterAreas / lSomaAreas
       self.mNormal = lSomaNormalAreas / lSomaAreas
       
   #! Usando um amostra de 8 pontos que representa a borda das elipses , calcular os AutoValores e AutoVetores    
   def CalcularEixosAeB(self):
       
       cov = self.CovarianceMatrix(self.mPontosPorjetos)
       
       #print cov, "MATRIX"
             
       #eigenvec = la.eigenvectors(cov)
       eigenvec = sc.eig(cov)
       
       #print 'LA',eigenvec
       print 'NUMPY',eigenvec
       
       #print len(eigenvec[0]) ,' PRIMEIRO ',eigenvec[0]
                                   
       self.mEigenVector = [Blender.Mathutils.Vector(eigenvec[1][0]),Blender.Mathutils.Vector(eigenvec[1][1]),Blender.Mathutils.Vector(eigenvec[1][2])]
             
       self.mEigenValues = [eigenvec[0][0],eigenvec[0][1],eigenvec[0][2]]
       
       for i in range(len(self.mEigenValues)-1):
           for j  in range(1,len(self.mEigenValues)):
               if self.mEigenValues[i] < self.mEigenValues[j]:
                   tmp = self.mEigenValues[i]
                   self.mEigenValues[i] = self.mEigenValues[j]
                   self.mEigenValues[j] = tmp
                   tmpv = self.mEigenVector[i]
                   self.mEigenVector[i] = self.mEigenVector[j]
                   self.mEigenVector[j] = tmpv
               
       self.mEigenVector[0].normalize()
       self.mEigenVector[1].normalize()      
       self.mNormal.normalize()
       m = Matrix(self.mEigenVector[0],self.mEigenVector[1],self.mNormal)
       #m.transpose()
       #m.invert()
       lplano = []
       lp = []
       
       for i in self.mPontosPorjetos:
           v = m*i
           c = m*self.mCenter
           lplano.append( ((v.x - c.x )*(v.x - c.x ))/(self.mEigenValues[0]) + ((v.y - c.y )*(v.y - c.y ))/(self.mEigenValues[1]) )
           lp.append(v)
       
#        in_editmode = Window.EditMode()
#        
#        if in_editmode:
#            Window.EditMode(0)
#
#        object = Blender.Object.GetSelected()
#        
#        me = Blender.Mesh.New('felipe')
#        me.verts.extend(lp)
#       #Vertex do Centro
#        scn = Blender.Scene.GetCurrent()
#        ob = scn.objects.new(me,'oi')
#                  
#
#        print '##############################'    
#        if in_editmode:
#            Window.EditMode(1)

       
           
       d = max(lplano)
       
       self.mA = sqrt( d / (self.mEigenValues[0]))
       self.mB = sqrt( d / (self.mEigenValues[1]))
               
   #! Calcular  a Matrix de Covariancia de um conjuntos de pontos
   def CovarianceMatrix(self,points):
     
       correlationXX = 0.0
       correlationYY = 0.0
       correlationZZ = 0.0
       correlationXY = 0.0
       correlationXZ = 0.0
       correlationYZ = 0.0
       
       print len(points) ,' PRIMEIRO ',points      
                           
       N = 1.0/len(points)


       for i in points:
         correlationXX += ((i.x - self.mCenter.x) * (i.x - self.mCenter.x))
         correlationYY += ((i.y - self.mCenter.y) * (i.y - self.mCenter.y))
         correlationZZ += ((i.z - self.mCenter.z) * (i.z - self.mCenter.z))

         correlationXY += ((i.x - self.mCenter.x) * (i.y - self.mCenter.y))
         correlationXZ += ((i.x - self.mCenter.x) * (i.z - self.mCenter.z))
         correlationYZ += ((i.y - self.mCenter.y) * (i.z - self.mCenter.z))
                       
           
#       return array([[(N*correlationXX), (N*correlationXY) , (N*correlationXZ)],
#                     [(N*correlationXY), (N*correlationYY) , (N*correlationYZ)],
#                     [(N*correlationXZ), (N*correlationYZ) , (N*correlationZZ)]])    
       # PORRA era so mudar a porra do array para array do numpy ou seja [ [] ,[] ] 2x2 
       # para [(),()]
       return array([ ( (N*correlationXX), (N*correlationXY) , (N*correlationXZ) ),
                      ( (N*correlationXY), (N*correlationYY) , (N*correlationYZ) ),
                      ( (N*correlationXZ), (N*correlationYZ) , (N*correlationZZ) ) ])    

