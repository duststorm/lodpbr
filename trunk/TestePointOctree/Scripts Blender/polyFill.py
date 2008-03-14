import Blender
import math
import multiarray
import LinearAlgebra as la

import MergeOperator
from MergeOperator import *

import Ellipse
from Ellipse import Ellipse    

from math import *
from LinearAlgebra import *
from multiarray import *

Vector = Blender.Mathutils.Vector(256.0,1.0,1.0)

cov = [Blender.Mathutils.Vector(-1.0,-2.0,1.0),
       Blender.Mathutils.Vector(1.0,0.0,2.0),
       Blender.Mathutils.Vector(2.0,-1.0,3.0),
       Blender.Mathutils.Vector(2.0,-1.0,2.0)]

p = Merge(Blender.Mathutils.Vector(1.0,-1.0,2.0))

fel = p.CovarianceMatrix(cov)

print fel,'FELIPE'

a = array ([[1.5,0.5,0.75],[0.5,0.5,0.25],[0.75,0.25,0.5]])

#print la.eigenvalues(a)
#print la.eigenvectors(a)
# Outline of 5 points

#def calculateEllipse(x, y, a, b, angle, steps): 
#
#  if steps == 0.0:
#    steps = 8
#    
#  points = []
# 
#  beta =  (-angle * 180 ) *  pi
#  sinbeta = sin(beta)
#  cosbeta = cos(beta)
# 
#  i = 0
#   
#  while i < 360 :
#  
#    alpha = (i / 180) * pi        
#    sinalpha =  sin(alpha)
#    cosalpha =  cos(alpha)
# 
#    X = x + (a * cosalpha * cosbeta - b * sinalpha * sinbeta)
#    Y = y + (a * cosalpha * sinbeta + b * sinalpha * cosbeta)
# 
#    points.append(Vector(X, Y, 0.0));
#    i =  i + (360.0 / steps);
#  
#  return points;
 
e = Ellipse(0.0,0.0,0.0,2,1.5,60.0,"felipe")
    
print  Vector / 3 
    
polyline1 =  e.CalculateBoundaries(0.0)
print polyline1 
   # Make a new mesh and add the truangles into it
me= Blender.Mesh.New(e.Name())
me.verts.extend(polyline1)
me.edges.extend(me.verts[0],me.verts[-1])
for i in range(0,len(polyline1)-1):
    me.edges.extend(me.verts[i],me.verts[i+1])
me.faces.extend(me.verts[0],me.verts[1],me.verts[2]) # Add the faces, they reference the verts in polyline 1 and 2

scn = Blender.Scene.GetCurrent()
ob = scn.objects.new(me)

print ob.getLocation()

po = []
      
po.extend([1,2,3])
po.extend([2,3])

print Vector.x      

Blender.Redraw()