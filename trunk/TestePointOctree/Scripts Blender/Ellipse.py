import Blender
import math

from Blender.Mathutils import *
from math              import *

class Edge:
    def __init__ (self):
        self.source = 0.0
        self.target = 0.0
        
    def SetSource(self,v):
        self.source = v
    def SetTarget(self,v):
        self.target = v
        
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

class Ellipse:
    
    def __init__(self,pCenter,pA,pB,pAngle,pName):
        
        self.mListEdge   = []    
        self.mCenter = pCenter
        
        self.mEixoA  = Blender.Mathutils.Vector(0.0,0.0,0.0)
        self.mEixoB  = Blender.Mathutils.Vector(0.0,0.0,0.0)
                      
        self.mA      = pA
        self.mB      = pB
        
        self.mAindex      = 0
        self.mBindex      = 0
        
        self.mAngle  = pAngle
        
        self.mNormal = Blender.Mathutils.Vector(0.0,0.0,0.0)
        self.mName   = pName
    
    def Name(self):
        return self.mName
    """ quais pontos formam o eixo A no espaço de Blender """
    def setAIndex(self,pIndex):
        self.mAindex = pIndex
    """ quais pontos formam o eixo B no espaço de Blender """    
    def setBIndex(self,pIndex):
        self.mBindex = pIndex

    def AIndex(self):
        return self.mAindex
        
    def BIndex(self):
        return self.mBindex
        
    def A(self):
        return self.mA
    
    def B(self):
        return self.mB
    
    def SetCenter(self,pCenter):
        self.mCenter = pCenter
        
    def SetEixoA(self,pEixoA):
        self.mEixoA = pEixoA
                
    def SetEixoB(self,pEixoB):
        self.mEixoB = pEixoB
                
    def EixoA(self):
        return self.mEixoA
        
        
    def EixoB(self):
        return self.mEixoB
                    
                
    def Center(self):
        return self.mCenter
    
    def SetNormal(self,pNormal):
        self.mNormal = pNormal
        self.mNormal.normalize()
        #self.mEixoA = perpendicular(self.mNormal)
        #self.mEixoA.normalize()                 
        #self.mEixoB = Blender.Mathutils.CrossVecs(self.mNormal,self.mEixoA)
        #self.mEixoB.normalize()
        
    def Normal(self):
        return self.mNormal
    
       
    #! Return list of point in Boundaries 
    def CalculateBoundaries(self,steps,axis): 
            
      if steps == 0.0:
        steps = 1
    
      points = []  
        
     
      beta =  (-self.mAngle * 180 ) *  pi
      sinbeta = sin(beta)
      cosbeta = cos(beta)
     
      i = 0
      #i = -self.mA
      X = 0
      Y = 0
      u = Blender.Mathutils.Vector(0,0)
      while i < 360 :
      #while i < self.mA :
        alpha = (i / 180) * pi        
        sinalpha =  sin(alpha)
        cosalpha =  cos(alpha)
        
        #X = (self.mA * cosalpha * cosbeta - self.mB * sinalpha * sinbeta)
        X = self.mA * cosalpha 
        #X = i
        
        #Y = sqrt  ( (1 - ( (X*X) / (self.mA*self.mA) )  ) * (self.mB*self.mB) ) 
           
        #Y = (self.mA * cosalpha * sinbeta + self.mB * sinalpha * cosbeta)
        
        Y = self.mB * sinalpha
        
        factor = sqrt(X*X+Y*Y)
        
        angle_c = X/factor
        angle_s = Y/factor
        # Rotacionando o Eixo ...
        w = axis[0]*angle_c + axis[1]*angle_s

        Z = self.mCenter.z
        # Transladando o ponto até a borda da ellipse                    
        points.append(self.mCenter + (w*factor))
        #points.append(Blender.Mathutils.Vector(X,Y,0.0))
                                  
        i =  i + (360.0 / steps)
        #i += 0.1
      
      return points
  
    def Area(self):
        return (4*pi*self.mA*self.mB)
    
    def ResizeA(self,pA):
        self.mA = pA
        
    def ResizeB(self,pB):
        self.mB = pA
    
    def CalEdges(self):
      m = self.EixoA()
      m.normalize()
      v = self.EixoB()
      v.normalize()
      points = self.CalculateBoundaries(8, [m,v])
      e.SetSource(points[-1])
      e.SetTarget(points[0])
      self.mListEdge.append(e)
      for i in range(0,len(points)-1):
        e.SetSource(points[i])
        e.SetTarget(points[i+1])
        self.mListEdge.append(e)
          
      
      