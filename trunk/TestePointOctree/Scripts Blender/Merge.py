import Blender
import math
import multiarray
import LinearAlgebra as la
import Ellipse

from Blender.Mathutils import Vector, Intersect, DotVecs, ProjectVecs, CrossVecs, LineIntersect

from math           import *
from LinearAlgebra  import *
from multiarray     import *
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
            return point - ProjectVecs(point - pop, norm)
        
    def CalcularPointosPojetados(self):
        
        listPoints = []
        
        for i in self.listEllipse:
            m = Blender.Mathutils.Vector(perpendicular(i.Normal()))
            m.normalize()
            i.Normal().normalize()
            v = CrossVecs(i.Normal(),m)
            v.normalize()
            listPoints = i.CalculateBoundaries(0,[m,v])
            
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
        print cov, "MATRIX"
        eigenvec = la.eigenvectors(cov)
        eigenval = la.eigenvalues(cov)
        
        print [eigenvec(0),eigenvec(1),eigenvec(2)] ,"TAMANHO DOS EIGENVECTOR"
        
        self.mEigenVector.append([eigenvec[0][0],eigenvec[0][1],eigenvec[0][2]])
        self.mEigenVector.append([eigenvec[1][0],eigenvec[1][1],eigenvec[1][2]])
        self.mEigenVector.append([eigenvec[2][0],eigenvec[2][1],eigenvec[2][2]])
        
        self.mEigenValues.append([eigenval[0][0],eigenval[0][1],eigenval[0][2]]) 
        self.mEigenValues.append([eigenval[1][0],eigenval[1][1],eigenval[1][2]])
        self.mEigenValues.append([eigenval[2][0],eigenval[2][1],eigenval[2][2]])
         
                
    #! Calcular  a Matrix de Covariancia de um conjuntos de pontos
    def CovarianceMatrix(self,points):
       
        correlationXX = 0.0
        correlationYY = 0.0
        correlationZZ = 0.0
        correlationXY = 0.0
        correlationXZ = 0.0
        correlationYZ = 0.0
                             
        N = 1.0/len(points) 

        for i in points:
          correlationXX += ((i.x - self.mCenter.x) * (i.x - self.mCenter.x)) 
          correlationYY += ((i.y - self.mCenter.y) * (i.y - self.mCenter.y))
          correlationZZ += ((i.z - self.mCenter.z) * (i.z - self.mCenter.z))

          correlationXY += ((i.x - self.mCenter.x) * (i.y - self.mCenter.y))
          correlationXZ += ((i.x - self.mCenter.x) * (i.z - self.mCenter.z))
          correlationYZ += ((i.y - self.mCenter.y) * (i.z - self.mCenter.z))
                         
            
        return array([[(N*correlationXX), (N*correlationXY) , (N*correlationXZ)],
                      [(N*correlationXY), (N*correlationYY) , (N*correlationYZ)],
                      [(N*correlationXZ), (N*correlationYZ) , (N*correlationZZ)]])    
        