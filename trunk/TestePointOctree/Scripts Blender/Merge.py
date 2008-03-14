import Blender
import math
import multiarray
import LinearAlgebra as la
import Ellipse

from math           import *
from LinearAlgebra  import *
from multiarray     import *
from Ellipse        import Ellipse

class Merge:
        
    def __init__(self,listEllipse):
           
      self.listEllipse = listEllipse
      self.mCenter     = Blender.Mathutils.Vector(0.0,0.0,0.0)
      self.mNormal     = Blender.Mathutils.Vector(0.0,0.0,0.0)
      self.mEigenVector = []
      self.mEigenValues = []
      self.CalcularCentroProgressiveSplatting()
     
    def __init__(self,pCenter,pNormal):
        
      self.listEllipse  = []
      self.mEigenVector = []
      self.mEigenValues = []
      self.mCenter      = pCenter
      self.mNormal      = pNormal
      self.CalcularCentroProgressiveSplatting()
        
    def Center(self):
        return self.mCenter
    
    def Normal(self):
        return self.mNormal
      
    def EigenVector (self):
        return self.mEigenVector
    
    def EigenValues (self):
        return self.mEigenValues

    #! Dado dois splats calcular seu centro e normal
    def CalcularCentroProgressiveSplatting(self):
                
        lSomaCenterAreas = 0.0 
        lSomaNormalAreas = 0.0
        lSomaAreas       = 0.0
        
        for i in self.listEllipse:
            lSomaCenterAreas += i.Area() * i.GetCenter()
            lSomaNormalAreas += i.Area() * i.GetNormal()
            lSomaAreas       += i.Area()           
               
        self.mCenter = lSomaCenterAreas / lSomaAreas
        self.mNormal = lSomaNormalAreas / lSomaAreas
        
    #! Usando um amostra de 8 pontos que representa a borda das elipses , calcular os AutoValores e AutoVetores    
    def CalcularEixosAeB(self):
        
        points = []
        
        for i in self.listEllipse:
            points.extend(i.CalculateBoundaries(8))
          
        cov = CovarianceMatrix(points)
        
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
        