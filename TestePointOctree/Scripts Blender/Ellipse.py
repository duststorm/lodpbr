import Blender
import math
import multiarray
import LinearAlgebra as la

from Blender.Mathutils import *
from math              import *
from LinearAlgebra     import *
from multiarray        import *


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
        
        self.mCenter = pCenter
        
        self.mEixoA  = Blender.Mathutils.Vector(0.0,0.0,0.0)
        self.mEixoB  = Blender.Mathutils.Vector(0.0,0.0,0.0)
                      
        self.mA      = pA
        self.mB      = pB
        
        self.mAngle  = pAngle
        
        self.mNormal = Blender.Mathutils.Vector(0.0,0.0,0.0)
        self.mName   = pName
    
    def Name(self):
        return self.mName
    
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
        self.mEixoA = perpendicular(self.mNormal)
        self.mEixoA.normalize()                 
        self.mEixoB = Blender.Mathutils.CrossVecs(self.mNormal,self.mEixoA)
        self.mEixoB.normalize()
        
    def Normal(self):
        return self.mNormal
    
       
    #! Return list of point in Boundaries 
    def CalculateBoundaries(self,steps,axis): 
            
      if steps == 0.0:
        steps = 8
    
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
        
        
                
        print X, 'X'
        print Y, 'Y'     
        print X*X,'X*X'
        print Y*Y,'Y*Y'
        print sqrt(X*X+Y*Y),'tamanho'
        
        factor = sqrt(X*X+Y*Y)
        
        angle_c = X/factor
        angle_s = Y/factor
               
        w = axis[0]*angle_c + axis[1]*angle_s

        Z = self.mCenter.z
                            
        points.append(self.mCenter + (w*factor))
        #points.append(Blender.Mathutils.Vector(X,Y,0.0))
                                  
        i =  i + (360.0 / steps)
        #i += 0.1
      
      return points
  
    def Area(self):
        return (pi*self.mA*self.mB)
    
    def ResizeA(self,pA):
        self.mA = pA
        
    def ResizeB(self,pB):
        self.mB = pA
    
        
      