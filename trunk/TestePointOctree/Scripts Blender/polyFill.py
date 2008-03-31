import Blender
import math
import multiarray
import LinearAlgebra as la

from Blender  import Scene, Draw, BGL, Window , Mesh ,Mathutils , Object
from Blender.Mathutils import *
from Blender.Object import *

import Ellipse
from Ellipse import Ellipse    

from math import *
from LinearAlgebra import *
from multiarray import *

#Vector = Blender.Mathutils.Vector(256.0,1.0,1.0)
#
#cov = [Blender.Mathutils.Vector(-1.0,-2.0,1.0),
#       Blender.Mathutils.Vector(1.0,0.0,2.0),
#       Blender.Mathutils.Vector(2.0,-1.0,3.0),
##       Blender.Mathutils.Vector(2.0,-1.0,2.0)]
#
##p = Merge(Blender.Mathutils.Vector(1.0,-1.0,2.0))
#
##fel = p.CovarianceMatrix(cov)
#
#print fel,'FELIPE'

a = array ([[ 1.32749402 , 0.03042916 ,-0.41181601,],[ 0.03042916 , 0.50236605 ,-0.00943975],[-0.41181601 ,-0.00943975 , 0.12775381]])  
#a = array ([[1.5,0.5,0.75],[0.5,0.5,0.25],[0.75,0.25,0.5]])


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
 
e = Ellipse(Vector(0.0,0.0,0.0),1.0,1.5,45.0,"EllipseFelipe" )
    
    
polyline1 =  e.CalculateBoundaries(8,[Vector(1.0,0.0,0.0),Vector(0.0,1.0,0.0)])
 
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

b = []

c =  la.eigenvectors(a)
d = la.eigenvalues(a)

opa = Vector(c[1][0])

print c[0], 'Mas por que'
print c[1][0], 'Mas por que v1' , opa.magnitude
print c[1][1], 'Mas por que v2'
print c[1][2], 'Mas por que v3'



b =  [Vector(c[1][0]),Vector(c[1][1]),Vector(c[1][2])]

print b,'Felipe b '


g = [d[0],d[1],d[2]]

print g ,"values"
print la.eigenvectors(a)

ve = Vector(0,232,151)

m = Matrix(ve,[5,6,7],[8,9,10])
 
print max(2,6)

Blender.Redraw()