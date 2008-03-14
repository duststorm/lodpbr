#!BPY

"""
Name: 'Blender Cookie Cutter'
Blender: 234
Group: 'Mesh'
Tooltip: 'Projects a closed edgeloop on a mesh'
"""

###################################################################
#                                                                 #
# Blender Cookie Cutter                                           #
#                                                                 #
# v. 0.0.1 (C) July 2004 Wim Van Hoydonck                         #
#                                                                 #
# Released under the Blender Artistic Licence (BAL)               #
# see www.blender.org                                             #
#                                                                 #
# Works in Blender 2.33 and higher                                #
#                                                                 #
# this script can be found online at:                             #
# http://users.pandora.be/tuinbels/scripts/slice.py               #
#                                                                 #
# email: tuinbels@hotmail.com                                     #
#                                                                 #
###################################################################
#                                                                 #
# WARNING:    This script is not finished and has some bugs, use  #
#             it at your own risk!                                #
#                                                                 #
###################################################################
# History                                                         #
# V: 0.0.1 - 03-08-04 - First public release and a rewrite of a   #
#                       script I coded more than 1 year ago...    #
#    0.0.2 - 08-08-04 - Name change: Cookie Cutter, thanks theeth!#
#                     - Added closed curves as cutter, open curves#
#                       are a problem since the API doesn't have  #
#                       a method to determine if a curve is open  #
#                       or closed.                                #
#                                                                 #
###################################################################

import Blender
from Blender import *
from math import *
from Blender.Draw import *
from Blender.BGL import *

print "    -------------------------"
print "    - Slice script V. 0.0.1 -"
print "    -------------------------"

# a small number
Epsilon = 0.000001

# program (GUI) parameters

# alter value to change startup default
# 1 = x, 2 = y , 3 = z
direction = Create(3)
# if you only want verts added (and some faces removed)...
vertsonly = Create(0)

BL_VERSION = Blender.Get('version')
if (BL_VERSION<=223):
	import Blender210

#=================================#
# vector and matrix manipulations #
#=================================#

# vector substration
def vecsub(a, b):
	return [a[0] - b[0], a[1] - b[1], a[2] - b[2]]

# vector addition
def vecadd(a, b):
	return [a[0] + b[0], a[1] + b[1], a[2] + b[2]]

# vector crossproduct
def veccross(x, y):
	v = [0, 0, 0]
	v[0] = x[1]*y[2] - x[2]*y[1]
	v[1] = x[2]*y[0] - x[0]*y[2]
	v[2] = x[0]*y[1] - x[1]*y[0]
	return v

# vector dotproduct
def vecdot(x, y):
	return x[0]*y[0] + x[1]*y[1] + x[2]*y[2]

# vector length
def length(v):
	return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2])

# vector multiplied by constant s
def vecmul(a, s):
	return[a[0]*s, a[1]*s, a[2]*s]

# vector divided by constant s
def vecdiv(a, s):
	if s!=0.0:
            s = 1.0/s
	return vecmul(a, s)

# matrix(4x3) vector multiplication
def mulmatvec4x3(a, b):
	# a is vector, b is matrix
	r = [0, 0, 0]
	r[0] = a[0]*b[0][0] + a[1]*b[1][0] + a[2]*b[2][0] + b[3][0]
	r[1] = a[0]*b[0][1] + a[1]*b[1][1] + a[2]*b[2][1] + b[3][1]
	r[2] = a[0]*b[0][2] + a[1]*b[1][2] + a[2]*b[2][2] + b[3][2]
	return r

# matrix(3x3) vector multiplication
def mulmatvec3x3(a, b):
	# a is vector, b is matrix
	r = [0, 0, 0]
	r[0] = a[0]*b[0][0] + a[1]*b[0][1] + a[2]*b[0][2]
	r[1] = a[0]*b[1][0] + a[1]*b[1][1] + a[2]*b[1][2]
	r[2] = a[0]*b[2][0] + a[1]*b[2][1] + a[2]*b[2][2]
	return r

# midpoint between two vertices/vectors
def mid(a, b):
	return vecdiv(vecadd(a, b), 2)

# Normalization of a vector
def Normalize(a):
	lengte = length(a)
	return vecdiv(a, lengte)

# calculate normal from 3 verts
def Normal(v0, v1, v2):
	return veccross(vecsub(v0, v1),vecsub(v0, v2))

# calculate normal from 4 verts
# found in the blender sources in arithb.c 
# (bl-blender\blender\source\blender\blenlib\intern\arithb.c)
def Normal4(v0, v1, v2, v3):
	return veccross(vecsub(v0, v2),vecsub(v1, v3))

# check if edge is parallel to plane
# if this returns 0, the edge is parallel to the plane
def Parallel(N, p1, p2):
	return vecdot(N, vecsub(p1, p2))

# see if a number is odd or even by dividing it by 2 and subsequently
# multiplying it back with 2, and if the two numbers are equal,
# the original number was even, otherwise it was odd
# e.g.	if x=5, this gives 4 (5/2 = 2, 2*2 = 4)
# 		if x=4, this gives 4 (4/2 = 2, 2*2 = 4)
# it returns 0 if x is even
# else it returns 1

# is there a builtin method/function for this??

def odd_even(x):
	x1 = x/2
	x1 = x1*2
	if x1 == x:
		return 0
	elif x1 != x:
		return 1

#======================#
# Bezier interpolation #
#======================#

def BezInterpolation(p0,p1,p2,p3,t):
	# t in range [0,1]
	c = vecmul(vecsub(p1,p0),3)
	b = vecsub(vecmul(vecsub(p2,p1),3), c)
	a = vecsub(vecsub(vecsub(p3, p0), c), b)
	p = vecadd(vecadd( vecadd( vecmul( a,t*t*t ), vecmul(b,t*t) ), vecmul(c,t) ), p0 )
	
	return p

#==================================#
# From local to global coordinates #
#==================================#

def GlobalPosition(P, Obj):
	if (BL_VERSION<=223):
		m = Obj.matrix
	else:
		m = Obj.getMatrix()
	return mulmatvec4x3(P, m)

#==================================#
# From global to local coordinates #
#==================================#

def LocalPosition(P, Obj):
	if (BL_VERSION<=223):
		m = Blender210.getObject(Obj.name).inverseMatrix
	else:
		m = Obj.getInverseMatrix()
	return mulmatvec4x3(P, m)

#===========================#
# Position wrt Bounding Box #
#===========================#
# aligned to world coordinate system (wcs)
 
def BoundingBox_wcs(vertco, lenfa, lim, dirs):
	inb, ob0, ob1, ob2, ob3 = 0, 0, 0, 0, 0
	
	for V in vertco:

		if dirs.val == 1:
			if (V[1] < lim[0]):			# y-coord smaller than ymin
				ob0 += 1
			if (V[1] > lim[1]):			# y-coord bigger than ymax
				ob1 += 1
			if (V[2] < lim[2]):			# z-coord smaller than zmin
				ob2 += 1
			if (V[2] > lim[3]):			# z-coord bigger than zmax
				ob3 += 1

		elif dirs.val == 2:
			if (V[0] < lim[0]):			# x-coord smaller than xmin
				ob0 += 1
			if (V[0] > lim[1]):			# x-coord bigger than xmax
				ob1 += 1
			if (V[2] < lim[2]):			# z-coord smaller than zmin
				ob2 += 1
			if (V[2] > lim[3]):			# z-coord bigger than zmax
				ob3 += 1

		elif dirs.val == 3:
			if (V[0] < lim[0]):			# x-coord smaller than xmin
				ob0 += 1
			if (V[0] > lim[1]):			# x-coord bigger than xmax
				ob1 += 1
			if (V[1] < lim[2]):			# y-coord smaller than ymin
				ob2 += 1
			if (V[1] > lim[3]):			# y-coord bigger than ymax
				ob3 += 1

	if (ob0==lenfa):	# face on lim0-side of slice
		return 0
	elif (ob1==lenfa):	# face on lim1-side of slice
		return 0
	elif (ob2==lenfa):	# face on lim2-side of slice	
		return 0
	elif (ob3==lenfa):	# face on lim3-side of slice	
		return 0
	else:				# face not on 1 side of slice
		return 1

#================#
# Get slice data #
#================#

def SliceData(Slice, dirs):
 
	vertglobx, vertgloby, vertglobz = [], [], []
	edge, edgelist, norlist, svertlist, endnorlist, des = [], [], [], [], [], []
	i, j, place, samedir = 0, 0, 0, 0
	limits, edgelist, vertlist = [], [], []
	vertexlimits = []

	# parameters for curves
	maxControlPoints = 100		# maximum 100 handles per curve
	maxcurves = 1				# maximum 1 curve
	closedcurve = 1				# closed curve (for the moment)

	# convert direction to a vector
	if dirs.val == 1:
		direc = [1, 0, 0]
	elif dirs.val == 2:
		direc = [0, 1, 0]
	elif dirs.val == 3:
		direc = [0, 0, 1]

	# get object type
	slicetype = Slice.getType()
	if slicetype == 'Curve':
		print "slice is curve ..."

		# curve number
		curveno = maxcurves - 1
		cdata = Slice.getData()
		cdresolu = cdata.getResolu()
		cdloc = cdata.getLoc()

		# get coordinates of control points
		pointcoords = []
		
		for i in range(0,maxControlPoints):
		
			try:
				pointdata = cdata.getControlPoint(curveno,i)
				pointcoords.append(pointdata)

			except:
				AttributeError
				break 

		# number of handles
		nohandles = len(pointcoords)
		
		pointcoords2 = []
		
		# make vectors of the pointcoords list
		for i in range(nohandles):
			vec0, vec1, vec2 = [], [], []
			
			vec0.append(pointcoords[i][0])
			vec0.append(pointcoords[i][1])
			vec0.append(pointcoords[i][2])
			
			vec0g = GlobalPosition(vec0, Slice)

			vec1.append(pointcoords[i][3])
			vec1.append(pointcoords[i][4])
			vec1.append(pointcoords[i][5])

			vec1g = GlobalPosition(vec1, Slice)
			
			vec2.append(pointcoords[i][6])
			vec2.append(pointcoords[i][7])
			vec2.append(pointcoords[i][8])

			vec2g = GlobalPosition(vec2, Slice)
			
			pointcoords2.append(vec0g)
			pointcoords2.append(vec1g)
			pointcoords2.append(vec2g)
			
		# sort vectors in groups of four, for easier use with BezInterpolation
		segments = []
		nosegments = nohandles
		
		for i in range(nosegments):
			segment = []
			
			p0 = pointcoords2[3*i + 1]
			p1 = pointcoords2[int(fmod(3*i + 2, len(pointcoords2)))]
			p2 = pointcoords2[int(fmod(3*i + 3, len(pointcoords2)))]
			p3 = pointcoords2[int(fmod(3*i + 4, len(pointcoords2)))]
			
			segment.append(p0)
			segment.append(p1)
			segment.append(p2)
			segment.append(p3)
			
			segments.append(segment)
			
		# get the coordinates of the bezier interpolation and add them to a list
		
		for i in range(nosegments):
			p0, p1, p2, p3 = segments[i][0], segments[i][1], segments[i][2], segments[i][3]
			for j in range(0,cdresolu):
				jf = float(j)		# convert j to float
				t = jf/cdresolu
				
				coords = BezInterpolation(p0,p1,p2,p3,t)
				
				svertlist.append(coords)
		len_faces = len(svertlist)

		print svertlist

		for i in range(len_faces):
			vertglobx.append(svertlist[i][0])
			vertgloby.append(svertlist[i][1])
			vertglobz.append(svertlist[i][2])

		vertglobx.sort(), vertgloby.sort(), vertglobz.sort()

	elif slicetype == 'Mesh':
		print "slice is mesh ..."
		
		SliceMesh = NMesh.GetRawFromObject(Slice.name)
		len_faces = len(SliceMesh.faces)
		print 'slice has',len_faces, "edges and", len(SliceMesh.verts) ,"verts"
		
		# calculate the global position of every vertex in Slice, 
		# and apppend the x, y and z coordinate in different lists

		for oface in SliceMesh.faces:
			# assuming every "face" has 2 verts and 1 edge...

			ve0 = GlobalPosition(oface.v[0].co, Slice)
			ve1 = GlobalPosition(oface.v[1].co, Slice)
	
			vertlist.append(ve0), vertlist.append(ve1)

			vertglobx.append(ve0[0]), vertglobx.append(ve1[0])
			vertgloby.append(ve0[1]), vertgloby.append(ve1[1])
			vertglobz.append(ve0[2]), vertglobz.append(ve1[2])

		# sort the lists in ascending order (van klein naar groot) to find the limits

		vertglobx.sort(), vertgloby.sort(), vertglobz.sort()	

		# append the coordinates of the first face/edge to s(orted)vertlist and delete them

		svertlist.append(vertlist[0]), svertlist.append(vertlist[1])
		del vertlist[0:2]

		# in the next loops the list of verts is sorted to be able to 
		# calculate the normals pointing outside
		for i in range(0, len_faces-2):
			j = 0
			for j in range(0, len(vertlist)):
				if vertlist[j] == svertlist[-1]:
					odd_or_even = odd_even(j)
					if odd_or_even == 0: # even
						svertlist.append(vertlist[j+1])
						del vertlist[j+1]
						del vertlist[j]
					elif odd_or_even == 1: # odd
						svertlist.append(vertlist[j-1])
						del vertlist[j]
						del vertlist[j-1]
					break
				else:
					continue
		print svertlist
	# calculate a normal with the first 3 verts (=Nor) and see if it is in the same direction as dirs
	# if dirs and Nor are in the same direction, svertlist should be reversed otherwise the 
	# normals are calculated inside instead of outside
	# don't ask me why, but it is like that
	Nor = Normalize(Normal(svertlist[0], svertlist[1], svertlist[2]))

	samedir = vecadd(Nor, direc)

	if length(samedir) != 0:
		svertlist.reverse()

	# calculate the normals

	for i in range(0, len_faces):
		nor = veccross(direc, vecsub(svertlist[int(fmod(i+1, len_faces))], svertlist[i]))
		norlist.append(Normalize(nor))

	# calculate the normals of the edges in the direction of the edges, normal to the plane in
	# which the slice is located and normal to the normals in norlist (pointing away from the edge)
	for i in range(0, len_faces):
		endnorlist.append(Normalize(veccross(direc, norlist[i])))
		endnorlist.append(Normalize(veccross(norlist[i], direc)))

	# collect limits(minima and maxima) of the edgeloop, they were sorted
	if dirs.val == 1:
		limits.append(vertgloby[0]), limits.append(vertgloby[-1])
		limits.append(vertglobz[0]), limits.append(vertglobz[-1])
	elif dirs.val == 2:
		limits.append(vertglobx[0]), limits.append(vertglobx[-1])
		limits.append(vertglobz[0]), limits.append(vertglobz[-1])
	elif dirs.val == 3:
		limits.append(vertglobx[0]), limits.append(vertglobx[-1])
		limits.append(vertgloby[0]), limits.append(vertgloby[-1])

	# these lists are not needed any more
	del vertglobx, vertgloby, vertglobz

	# distance in direction of normal of the edge wrt the wcs
	# or the offset of the edge in the direction of the normal of the edge
	for i in range(0, len(norlist)):
		des.append(vecdot(svertlist[i], norlist[i]))

	# limits (wrt wcs) for every edge of slice
	for i in range(0, len_faces):
		if direction.val == 1:
			ymin = min(svertlist[i][1], svertlist[int(fmod(i+1, len_faces))][1])
			ymax = max(svertlist[i][1], svertlist[int(fmod(i+1, len_faces))][1])
			zmin = min(svertlist[i][2], svertlist[int(fmod(i+1, len_faces))][2])
			zmax = max(svertlist[i][2], svertlist[int(fmod(i+1, len_faces))][2])
			vertexlimits.append([ymin, ymax, zmin, zmax])
		elif direction.val == 2:
			xmin = min(svertlist[i][0], svertlist[int(fmod(i+1, len_faces))][0])
			xmax = max(svertlist[i][0], svertlist[int(fmod(i+1, len_faces))][0])
			zmin = min(svertlist[i][2], svertlist[int(fmod(i+1, len_faces))][2])
			zmax = max(svertlist[i][2], svertlist[int(fmod(i+1, len_faces))][2])
			vertexlimits.append([xmin, xmax, zmin, zmax])
		else:
			xmin = min(svertlist[i][0], svertlist[int(fmod(i+1, len_faces))][0])
			xmax = max(svertlist[i][0], svertlist[int(fmod(i+1, len_faces))][0])
			ymin = min(svertlist[i][1], svertlist[int(fmod(i+1, len_faces))][1])
			ymax = max(svertlist[i][1], svertlist[int(fmod(i+1, len_faces))][1])
			vertexlimits.append([xmin, xmax, ymin, ymax])

	return limits, norlist, svertlist, endnorlist, des, vertexlimits

#===============#
# Get Mesh data #
#===============#

def MeshData(Obj, m):

# get the indices of the faces of ObjMesh
# get per face the vertex indices
# get per face the global coordinates of the verts

	idx = []
	for i in range(0, len(m.faces)):
		idx.append(i)

	lenface, vertglob, vertidx = [], [], []

	totverts = len(m.verts)

	for i in idx:
		fvertidx, Ve = [], []
		fa = m.faces[i]
		lenface.append(len(fa))
		for v in fa.v:
			Ve.append(GlobalPosition(v.co, Obj))
			fvertidx.append(v.index)
		vertidx.append(fvertidx)
		vertglob.append(Ve)

	return idx, lenface, vertidx, vertglob, totverts

#========================================#
# Append existing faces / make new faces #
#========================================#

def FaceAppend(me, vertindex):

	nf = NMesh.Face()
	for vi in vertindex:
		nf.v.append(me.verts[vi])
	me.faces.append(nf)

def FaceMake(me, vl):
	idx = len(me.verts)
	  
 	if len(vl) <= 4:
		nf = NMesh.Face()
		for i in range(len(vl)):
			nf.v.append(me.verts[vl[i]])
		me.faces.append(nf)
	else:
		nf = NMesh.Face()
		nf.v.append(me.verts[vl[0]])
		nf.v.append(me.verts[vl[1]])
		nf.v.append(me.verts[vl[2]])
		nf.v.append(me.verts[vl[3]])
		me.faces.append(nf)

		nf = NMesh.Face()
		nf.v.append(me.verts[vl[3]])
		nf.v.append(me.verts[vl[4]])
		nf.v.append(me.verts[vl[0]])
		me.faces.append(nf)

#	elif len(vl) == 5:
#		nf = NMesh.Face()
#		nf.v.append(me.verts[vl[0]])
#		nf.v.append(me.verts[vl[1]])
#		nf.v.append(me.verts[vl[2]])
#		nf.v.append(me.verts[vl[3]])
#		me.faces.append(nf)

#		nf = NMesh.Face()
#		nf.v.append(me.verts[vl[3]])
#		nf.v.append(me.verts[vl[4]])
#		nf.v.append(me.verts[vl[0]])
#		me.faces.append(nf)

#====================#
# Edge Intersections #
#====================#

def EdgeIntersect(p1,p2,p3,p4,dirs):

	x1,y1,z1 = p1[0],p1[1],p1[2]
	x2,y2,z2 = p2[0],p2[1],p2[2]
	x3,y3,z3 = p3[0],p3[1],p3[2]
	x4,y4,z4 = p4[0],p4[1],p4[2]

	if dirs.val == 1:									# x-direction
		Den = (z4-z3)*(y2-y1) - (y4-y3)*(z2-z1)			# denominator
		ua = ((y4-y3)*(z1-z3) - (z4-z3)*(y1-y3)) / Den
		ub = ((y2-y1)*(z1-z3) - (z2-z1)*(y1-y3)) / Den
		# intersectionpoint...
		xint = x3 + ub*(x4-x3)
		yint = y1 + ua*(y2-y1)
		zint = z1 + ua*(z2-z1)

	elif dirs.val == 2:									# y-direction
		Den = (z4-z3)*(x2-x1) - (x4-x3)*(z2-z1)
		ua = ((x4-x3)*(z1-z3) - (z4-z3)*(x1-x3)) / Den
		ub = ((x2-x1)*(z1-z3) - (z2-z1)*(x1-x3)) / Den
		# intersectionpoint...
		xint = x1 + ua*(x2-x1)
		yint = y3 + ub*(y4-y3)
		zint = z1 + ua*(z2-z1)

	elif dirs.val == 3:									# z-direction
		Den = (y4-y3)*(x2-x1) - (x4-x3)*(y2-y1)
		ua = ((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3)) / Den
		ub = ((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3)) / Den
		# intersectionpoint...
		xint = x1 + ua*(x2-x1)
		yint = y1 + ua*(y2-y1)
		zint = z3 + ub*(z4-z3)

	return ua,ub,[xint,yint,zint]

#===========#
# Positions # 
#===========#

def Distance(P, N, d0):
	# distance from a vertex to the plane, measured perpendicular to the plane
	# and corrected for the offset (d0) of the plane wrt the wcs
	return vecdot(P, N) - d0

def FacePosition(vertco, N, d0):
	# checks on which side every vertex of a face is wrt the planenormal
	# np=0 : face totally on positive (=normalside) side of plane, no intersection
	# nn=0 : face totally on negative side of plane, no intersection
	# else : face has vertices on both sides of plane, so intersection with plane
	np, nn, nz = 0, 0, 0

	for V in vertco:

		d = Distance(V, N, d0)

		if d>0:
			np += 1
		elif d<0:
			nn += 1
		else:
			nz += 1 

	if np==0:
		return -1
	if nn==0:
		return 1
	return 0

#=================#
# Splitting faces #
#=================#

def Split(Obj, MeshNew, V, Vidx, N, d0, everts, newvidx, newvcoo, totverts, dirs):

	d = []
 
	vp = []
	vn = []

	for i in range(0,len(V)):
		d.append(Distance(V[i], N, d0))
 	# print d

	for i in range(len(d)):
		# print i
		dim1 = d[int(fmod(i-1, len(d)))]
		Vim1 = V[int(fmod(i-1, len(d)))]
		# print dim1, Vim1
		
		if abs(d[i]) < Epsilon:
					
			vp.append(Vidx[i])
			vn.append(Vidx[i])
		else:
			if abs(dim1) < Epsilon:
				if d[i] > 0:
					vp.append(Vidx[i])
				else:
					vn.append(Vidx[i])
			else:
				if d[i]*dim1 > 0:
					# print "i", i
					if d[i] > 0:
						vp.append(Vidx[i])
					else:
						vn.append(Vidx[i])
					# print vn, vp
				
				else:
					Den = vecdot(vecsub(Vim1,V[i]),N)
					
    				      
					Vi = []    
					Vi.append (- ((Vim1[0]*V[i][1]-Vim1[1]*V[i][0])*N[1]+(Vim1[0]*V[i][2]-Vim1[2]*V[i][0])*N[2]+(V[i][0]-Vim1[0])*d0)/Den)
					Vi.append (- ((Vim1[1]*V[i][0]-Vim1[0]*V[i][1])*N[0]+(Vim1[1]*V[i][2]-Vim1[2]*V[i][1])*N[2]+(V[i][1]-Vim1[1])*d0)/Den)
					Vi.append (- ((Vim1[2]*V[i][0]-Vim1[0]*V[i][2])*N[0]+(Vim1[2]*V[i][1]-Vim1[1]*V[i][2])*N[1]+(V[i][2]-Vim1[2])*d0)/Den)
					ViL = LocalPosition(Vi, Obj)
					# print "Vi", Vi
					# print "vil", ViL
					
# is the intersectionpoint between the points of the current edge of the slice
# and making sure to get no float division errors (den == 0)
# den = denominator, num = numerator
					if dirs.val == 1:# or dirs.val == 2: #  x-direction
						den, num = everts[1][1] - everts[0][1], Vi[1] - everts[0][1]
						if den == 0:
							den, num = everts[1][2] - everts[0][2], Vi[2] - everts[0][2]
						u_a = num/den
					
					elif dirs.val == 2:
						den, num = everts[1][0] - everts[0][0], Vi[0] - everts[0][0]
						if den == 0:
							den, num = everts[1][2] - everts[0][2], Vi[2] - everts[0][2]
						u_a = num/den
				
					elif dirs.val == 3: # z-direction
						den, num = everts[1][0] - everts[0][0], Vi[0] - everts[0][0]
						if den == 0:
							den, num = everts[1][1] - everts[0][1], Vi[1] - everts[0][1]
						u_a = num/den
					# print "u_a", u_a
# if next line is positive, the calculated intersectionpoint doesn't lie within the boundaries of the sliceedge,
# with no valid intersectionpoints as a result

					if u_a > 1 or u_a < 0:
#						print u_a
						# return 0 for vlp and vln
						return [0, 0, newvidx, newvcoo]
# good intersectionpoint, see if it already exist, if not, add a new vertex to MeshNew
					else:
						# first new vertex always has to be added to MeshNew
						if newvidx == []: # no new verts exist yet
							ViLl = NMesh.Vert(ViL[0],ViL[1],ViL[2])
							MeshNew.verts.append(ViLl)
							# and add it to newvidx and newvcoo
							nvidx = totverts
							newvidx.append(nvidx)
							newvcoo.append(ViL)
							#append the vertexindex of the new vert to vp and vn instead of its coordinates
							vp.append(nvidx)
							vn.append(nvidx)
					
						else:
							dist = []
							tlr = 0
							for j in range(len(newvidx)): 
								dist.append(length(vecsub(ViL, newvcoo[j])))
							for k in range(len(dist)):
								if dist[k] < Epsilon:
									# use newvidx[k] as vert
									vp.append(newvidx[k])
									vn.append(newvidx[k])
									break # get out of closest loop
								else:
									tlr += 1
							if tlr == len(newvidx):
								nvidx = totverts + len(newvidx)
								ViLl = NMesh.Vert(ViL[0],ViL[1],ViL[2])
								MeshNew.verts.append(ViLl)
								newvidx.append(nvidx)
								newvcoo.append(ViL)
								vp.append(nvidx)
								vn.append(nvidx)
				
						if (d[i]>0):
							vp.append(Vidx[i])
						else:
							vn.append(Vidx[i])

	return [vp, vn, newvidx, newvcoo]

#############################################################
# quick sort between faces that are not intersected and     #
# faces that are probably intersected                       #
#############################################################

def FirstSort(m, dir, m_idx, m_vertcoord, m_lenface, m_vertidx, limits, normals, offset, limv):

# a first quick global check to see weather a face is intersected by the mesh,
# if not, it is appended to the new mesh

	pr_f = [] # processed faces
	e_idx_all = []
	FPgl = []
	for i in m_idx:
		
# calculate the position of a face wrt to limits of the slice
		fpB = BoundingBox_wcs(m_vertcoord[i], m_lenface[i], limits, dir)

		if fpB == 0:
			FaceAppend(m, m_vertidx[i])
			pr_f.append(i)
		else:

# calculate position of a face wrt to limits of every edge of the slice
			e_idx = []
			for j in range(0, len(limv)):
				fpBB = BoundingBox_wcs(m_vertcoord[i], m_lenface[i], limv[j], dir)
				if fpBB == 1:
					e_idx.append(j)

			if len(e_idx) == 0:
				FaceAppend(m, m_vertidx[i])
				pr_f.append(i)
			else:


				FPlo = [] # faceposition local
				for k in range(len(e_idx)):
					FPlo.append(FacePosition(m_vertcoord[m_idx[i]], normals[e_idx[k]], offset[e_idx[k]]) )

				nz = 0 # non-zero
				for l in range(len(FPlo)):
					if FPlo[l] != 0: 
						nz += 1

				if nz == len(FPlo):
					FaceAppend(m, m_vertidx[m_idx[i]])
					pr_f.append(i)

				else:
					e_idx_all.append(e_idx)
					FPgl.append(FPlo)

	m_idx_2 = []
	for i in m_idx:
		if i not in pr_f:
			m_idx_2.append(i)

	return e_idx_all, FPgl, m_idx_2

#############################################################
# creating the new object                                   #
#############################################################

def main():

	if BL_VERSION <= 223:
		selected_obs = Object.GetSelected()
	elif 223 < BL_VERSION < 228:
		selected_obs = Object.getSelected()
	else:
		selected_obs = Object.GetSelected()

	if (len(selected_obs)!=2):
		msg = "ERROR: You must select exactly two objects"
	else:
		Slice = selected_obs[0] 	# "Cookie Cutter"
		Obj = selected_obs[1] 		# "Lijdend" voorwerp

	MeshNew = NMesh.GetRaw()   # new mesh

	if BL_VERSION<=223:
		ObjMesh = Obj.data
	else:
		ObjMesh = Obj.getData()

	print ""
	print "lets start..."
	print ""

#
# get data about the edgeloop
#
	limits, normals, verts, endnormals, offset, limv = SliceData(Slice, direction)
	# print verts
#
# get data about the mesh
#
	m_idx, m_lenface, m_vertidx, m_vertcoord, totverts = MeshData(Obj, ObjMesh)
	
	# print m_idx
#
# append all verts of ObjMesh to MeshNew
#
	for v in ObjMesh.verts:
		MeshNew.verts.append(v)
#
# appending faces of mesh to new mesh that definately do not intersect
#
	e_idx_gl, FP_gl, m_idx_2 = FirstSort(MeshNew, direction, m_idx, m_vertcoord, m_lenface, m_vertidx, limits, normals, offset, limv)
	# print e_idx_gl, FP_gl

# if their are FP_gl with 2 or more entries, and 1 of them is not equal to zero (1 or -1),
# remove that entry and its respective entry in e_idx_gl
# this happens with slices with sharp corners
# it also has some influence on the Split function, so more code was needed there

	for i in range(0,len(FP_gl)):
		if len(FP_gl[i]) > 1:
			for j in range(len(FP_gl[i])):
				if FP_gl[i][j] == -1 or FP_gl[i][j] == 1:

					dFP_gl = [ FP_gl[i][int(fmod(j-1, len(FP_gl[i])))] ]
					de_idx_gl =  [ e_idx_gl[i][int(fmod(j-1, len(FP_gl[i])))] ]

					FP_gl[i], e_idx_gl[i] = dFP_gl, de_idx_gl
					break

# if there are now faces (i) in m_idx_2 that have a FPgl[i] with length == 1 and the entry is 0, use split function 
# to split the faces
# this works good for faces that have dimensions that are smaller than the dimensions of the edges of the slice

#
# indices of new verts and its respective local coordinates, these lists are input AND output of Slice, so they get
# updated every time a new vertex is added to the new mesh
#
	newvidx, newvcoo = [], []
#
# keep track of processed faces
#
	pr_f = []

#
# splitting some faces...
#
	#	print "FP_gl, e_idx_gl:", FP_gl, e_idx_gl
	for i in range(0,len(m_idx_2)):
		if len(e_idx_gl[i]) == 1 and FP_gl[i] == [0]:

			# a little bit more variables than the original Split function, but it works :)
			output = Split(Obj, MeshNew, m_vertcoord[m_idx_2[i]], m_vertidx[m_idx_2[i]], normals[e_idx_gl[i][0]], offset[e_idx_gl[i][0]], [verts[e_idx_gl[i][0]], verts[int(fmod(e_idx_gl[i][0]+1, len(verts) ))]], newvidx, newvcoo, totverts, direction)
			# print output

			vlp, vln, newvidx, newvcoo = output[0], output[1], output[2], output[3]
			if vlp != 0 and vln != 0 and vertsonly.val == 0:
				FaceMake(MeshNew, vlp)
				FaceMake(MeshNew, vln)
				pr_f.append(m_idx_2[i])

	m_idx_3 = []
	e_idx_gl3 = []

#
# remove faces in pr_f
#
	for i in range(len(m_idx_2)):
		if m_idx_2[i] not in pr_f:
			m_idx_3.append(m_idx_2[i])
			e_idx_gl3.append(e_idx_gl[i])
	del m_idx_2

#
# calculate all valid intersections of the slice edges with edges of the faces
#
	pr_f = []
	for i in range(len(m_idx_3)):		# for every remaining face...
		newvidx2 = []

		# print face index number
		print ""
		print "face..." # , m_idx_3[i]
		# print e_idx_gl3

		dpf = [] # distances per face
		for j in e_idx_gl3[i]:			# for every slice-edge

			dse = []
			for k in range(len(m_vertcoord[m_idx_3[i]])):
				d = Distance(m_vertcoord[m_idx_3[i]][k], normals[j], offset[j])
				dse.append(d)
				# dse (distance to slice edge) is afstanden van alle verts v/1 face tot 1 slice edge
			dpf.append(dse)


		# preliminary -per face- vertex list
		pfvl = []
		nmvidx = [] # new mesh vertex index
	
		for j in range(len(dpf)):				# face tov alle edges

			psevl = [] # preliminary -per slice edge- vertex list
			nmfvidx = []

			for k in range(len(dpf[j])):		# face tov 1 edge
				mvk, mvkp1 = m_vertcoord[m_idx_3[i]][k], m_vertcoord[m_idx_3[i]][int(fmod(k+1,len(m_vertcoord[m_idx_3[i]])))]		# mesh vertex k and mesh vertex k+1 
				svj, svjp1 = verts[e_idx_gl3[i][j]], verts[int(fmod(e_idx_gl3[i][j]+1, len(verts)))]								# slice vertex j and slice vertex j+1
#				inter = []

				dse, dsep1 = dpf[j][k] ,dpf[j][int(fmod(k+1, len(dpf[j])))]    # distance per slice edge of current vertex (mvk) and dse of the next vertex (mvkp1)

				if abs(dse) < Epsilon:
					print "facepoint on slice edge."
					psevl.append(0)		# vertex on edge, add a zero (0)
					nmfvidx.append(0)
				else:
					if dse * dsep1 > 0:
						# print "no intersection."

						psevl.append(-1)		# no intersection, add a minus one (-1)
						nmfvidx.append(-1)

					elif dse * dsep1 < 0:
						# print "possible intersection:"

						ua, ub, intcoord = EdgeIntersect(svj, svjp1, mvk, mvkp1, direction)
						# print "ua ub:", ua, ub

						if 0 < ua < 1 and 0 < ub < 1:
							# print "     -> zekers wel een intersection."
							# print "intersectionpoint = ", intcoord
							psevl.append(1)		# definately an intersection, add a plus one (1)
							
							# print "ua, ub:", ua, ub
							# convert point to local coordinates
							intcoordL = LocalPosition(intcoord, Obj)

							# check if vert already exists, if not add a new vert to MeshNew, else use an already existing one...
							# copied from the Split function
							dist = []
							for m in range(len(newvidx)):
								dist.append(length(vecsub(intcoordL, newvcoo[m])))

							tlr = 0		# teller
							for n in range(len(dist)):
								if dist[n] < Epsilon:
									# use newvidx[n] as vert
									nmfvidx.append(newvidx[n])
									break
								else:
									tlr += 1
							# none of the new verts is close enough to the intersectionpoint
							if tlr == len(newvidx):
								nvidx = totverts + len(newvidx)
								VertNew = NMesh.Vert(intcoordL[0],intcoordL[1],intcoordL[2])
								MeshNew.verts.append(VertNew)
								# update the coords and index lists
								newvidx.append(nvidx)
								newvcoo.append(intcoordL)
								newvidx2.append(nvidx)
								# print nvidx
								nmfvidx.append(nvidx)
						else:
							# print "     -> geen intersection."
							psevl.append(-1)
							nmfvidx.append(-1)

			pfvl.append(psevl)
			nmvidx.append(nmfvidx)
		# test if face has no valid intersections (there are some left, near sharp corners of slice...)

		# print pfvl
		ttest = 0
		for j in range(len(pfvl)):
			inttest = 0
			lengte = len(pfvl[j])
			for k in range(lengte):
				if pfvl[j][k] == -1:
					inttest += 1
			if inttest == lengte:
				ttest += 1

		if ttest == len(pfvl):
			FaceAppend(MeshNew, m_vertidx[m_idx_3[i]])
			pr_f.append(m_idx_3[i])
			# print m_idx_3[i]
			# print "no intersections"
		else:
                    if vertsonly.val == 0:
			# there are still some cases where the above code is not capable of detecting intersections,
			# and I still don't know how (or where in the script) to solve it ...
			# print "wooooot, intersections"
			# print "pfvl", pfvl

			# determine number of needed vertexlists, from number of ones (and zeros) in pfvl			
			
			if len(pfvl) == 1:  # don't know if this _can_ happen here, just in case it does
				print "this shouldn't happen here...something went wrong"
			else:
				noei = 0		# number of edge intersections				

				vl0, vl1, vl2, vl3, vl4, vlists = [], [], [], [], [], []

				inters = 0
				totinters, noei = [], 0
				einters = []
				for j in range(len(pfvl[0])):		# pfvl[j] are all of equal (face) length
					# print j						# 0,1,2,3
					facelen = len(pfvl[0])
				
					switch = 0
					noipe = 0						# number of intersections per edge
					esubinters = []
					for k in range(len(pfvl)):		# 0,1 als noei = 2

						if pfvl[k][j] == 1:
							noipe += 1
							noei += 1
							# print k, j, "is een"
							esubinters.append(nmvidx[k][j])
					totinters.append(noipe)
					einters.append(esubinters)

 				# print "einters", einters
 				# print "totinters", totinters, noei
 				# print "nmvidx", nmvidx

				lenmaxeinters = len(max(einters))
				# print "lenmaxeinters", lenmaxeinters

				# now comes the creation of face vertex lists with the info gathered above...
				# create some vertexlists...
				vl00 = [[],[],[],[],[],[],[],[]]	# vertex lists 00

				# create vertex lists...
				pinters = 0		# passed intersections
				for j in range(len(pfvl[0])): # 0,1,2,3
					v0 = m_vertidx[m_idx_3[i]][j]
					# print j
					# print "v0", v0
					# print m_vertcoord[m_idx_3[i]][j]
					if noei == 2 and lenmaxeinters == 1:	# two intersections in different edges
						# print noei, lenmaxeinters
						if totinters[j] == 0:		# no intersection
							vl00[int(fmod(pinters, noei))].append(v0)
							# print "no intersection"
						elif totinters[j] >= 0:		# intersection
							if totinters[j] == 1:
								vl00[int(fmod(pinters, noei))].append(v0)
								vl00[int(fmod(pinters, noei))].append(einters[j][0])
								pinters += 1
								# print "passed intersections", pinters
								vl00[int(fmod(pinters, noei))].append(einters[j][0])
					#if noei == 2 and lenmaxeinters == 2:	# two intersections in same edge
					#	if totinters[j] == 0:
					#		vl00[int(fmod(pinters, noei))].append(v0)
					#	elif totinters[j] >= 0:
					#		vl00[int(fmod(pinters, noei))].append(v0)
					#		vl00[int(fmod(pinters, noei))].append(einters[j][0])
					#		vl00[int(fmod(pinters, noei))].append(einters[j][1])
							# pinters += 1

				# create faces from vertex lists...
				vl = []
				for j in range(len(vl00)):
					if vl00[j] != []:
						vl = vl00[j]
						FaceMake(MeshNew, vl)


	# create the meshobject in blender
	ObNew = NMesh.PutRaw(MeshNew)

	ObNew.LocX, ObNew.LocY, ObNew.LocZ = Obj.LocX, Obj.LocY, Obj.LocZ
	ObNew.RotX, ObNew.RotY, ObNew.RotZ = Obj.RotX, Obj.RotY, Obj.RotZ
	ObNew.SizeX, ObNew.SizeY, ObNew.SizeZ = Obj.SizeX, Obj.SizeY, Obj.SizeZ

#############################################################
# Graphics                                                  #
#############################################################

def draw():
	global direction, vertsonly

	BGL.glClearColor(0.5, 0.5, 0.5, 0.0)
	BGL.glClear(BGL.GL_COLOR_BUFFER_BIT)
	BGL.glColor3f(0.0, 0.0, 0.0)
	BGL.glRectf(2, 2, 380, 220)
	BGL.glColor3f(0.48, 0.4, 0.57)
	BGL.glRectf(4, 40, 378, 213)
	BGL.glColor3f(0.0, 0.0, 0.0)
	BGL.glRectf(3, 162, 380, 168)

	# buttons
	Button("CUT", 3, 300, 10, 70, 25)
	Button("Exit", 1, 330, 180, 40, 18)
	# menu to choose projection direction
	menuname = "direction to project%t|X-direction%x1|Y-direction%x2|Z-direction%x3"
	direction = Menu(menuname, 2, 10, 10, 140, 25, direction.val)
        # toggle to only add verts and not add any faces
	vertsonly = Toggle("Only add verts", 2, 165, 10 ,120, 25, vertsonly.val, "adds verts only")

	# text
	BGL.glColor3f(1,1,1)
	BGL.glRasterPos2d(8, 196)
	Text("Cookie Cutter V. 0.0.2")
	BGL.glRasterPos2d(8, 179)
	Text("by Wim <tuinbels> Van Hoydonck")
	BGL.glRasterPos2d(8, 148)
	Text("1 - Create a CLOSED Mesh or Bezier Curve EdgeLoop ")
	BGL.glRasterPos2d(8, 128)
	Text("      (eg. Add->Mesh->Circle or Add->Curve->Bezier Circle)")
	BGL.glRasterPos2d(8, 108)
	Text("2 - Select the Mesh to be Cut and the EdgeLoop")
	BGL.glRasterPos2d(8, 88)
	Text("      (Mesh Dark Purple, EdgeLoop Light Purple)")
	BGL.glRasterPos2d(8, 68)
	Text("3 - Choose the direction to project (X, Y or Z)")
	BGL.glRasterPos2d(8, 48)
	Text("4 - Push the 'CUT' button")


def event(evt, val): 
	if (evt== QKEY and not val):
		Exit()
	if (evt==CKEY and not val):
		main()
		Redraw()

def bevent(evt):
	if   (evt== 1):
		Exit()
	elif (evt== 3):
		main()
		Redraw()

Register(draw, event, bevent)
