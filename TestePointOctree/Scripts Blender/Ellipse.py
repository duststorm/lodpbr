import Blender
import math
import multiarray
import LinearAlgebra as la

from Blender.Mathutils import *
from math              import *
from LinearAlgebra     import *
from multiarray        import *

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
        
        angle_s = X/factor
        angle_x = Y/factor
               
        w = axis[0]*angle_s + axis[1]*angle_x

        Z = self.mCenter.z
                            
        points.append(self.mCenter + w*factor)
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
    
        
      