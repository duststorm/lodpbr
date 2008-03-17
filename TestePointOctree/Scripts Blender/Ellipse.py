import Blender
import math
import multiarray
import LinearAlgebra as la

from math           import *
from LinearAlgebra  import *
from multiarray     import *

class Ellipse:
    
    def __init__(self,pCenter,pA,pB,pAngle,pName):
        
        self.mCenter = pCenter
              
        self.mA      = pA
        self.mB      = pB
        
        self.mAngle  = pAngle
        
        self.mNormal = Blender.Mathutils.Vector(0.0,0.0,0.0)
        self.mName   = pName
    
    def Name(self):
        return self.mName
    
    def SetCenter(self,pCenter):
        self.mCenter = pCenter
        
    def Center(self):
        return self.mCenter
    
    def SetNormal(self,pNormal):
        self.mNormal = pNormal
        
    def Normal(self):
        return self.mNormal
      
    
    #! Return list of point in Boundaries 
    def CalculateBoundaries(self,steps): 
            
      if steps == 0.0:
        steps = 8
    
      points = []  
        
     
      beta =  (-self.mAngle * 180 ) *  pi
      sinbeta = sin(beta)
      cosbeta = cos(beta)
     
      i = 0
       
      while i < 360 :
      
        alpha = (i / 180) * pi        
        sinalpha =  sin(alpha)
        cosalpha =  cos(alpha)
     
        X = self.mCenter.x + (self.mA * cosalpha * cosbeta - self.mB * sinalpha * sinbeta)
        Y = self.mCenter.y + (self.mA * cosalpha * sinbeta + self.mB * sinalpha * cosbeta)
     
        points.append(Blender.Mathutils.Vector(X, Y, 0.0));
        
        i =  i + (360.0 / steps);
      
      return points
  
    def Area(self):
        return (pi*self.mA*self.mB)
    
    def ResizeA(self,pA):
        self.mA = pA
        
    def ResizeB(self,pB):
        self.mB = pA
    
        
      