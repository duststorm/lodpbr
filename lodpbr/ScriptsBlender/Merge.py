import Blender
import math
import numpy.core.multiarray
#import LinearAlgebra as la
import Ellipse
import numpy.linalg as nu
#import scipy.linalg as sc

from Blender.Mathutils import Vector, Matrix ,Intersect, DotVecs, ProjectVecs, CrossVecs, LineIntersect
from Blender  import Scene, Draw, BGL, Window , Mesh ,Mathutils , Object

from numpy.linalg import eig, eigh
from numpy import *

#from scipy.linalg import eig, eigh
#from scipy import *

from math           import *
#from LinearAlgebra  import *
from numpy.core.multiarray     import *
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


class Error:
    def __init__(self,Ellipse,listEllipse):
        self.Ellipse = Ellipse
        self.ListEllipse = listEllipse
    def geomrtricError(self):
        dis_max = 0.0
        l = self.Ellipse.CalculateBoundaries(8,[self.Ellipse.EixoA(),self.Ellipse.EixoB()])
        for p in l:
            result = 9999999
            for ellipse in self.ListEllipse:
                q  = p - ( (ellipse.Normal() * (p - ellipse.Center() )) *ellipse.Normal())
#                print "Q --- ",q
#                print "P --- ",p
#                print "ellipse --- ",[ellipse.EixoA(),ellipse.EixoB()]
#                print "Ellipse --- ",[self.Ellipse.EixoA(),self.Ellipse.EixoB()]
                r = q - ellipse.Center()
                s = p - q
                A = (r * ellipse.EixoA())/(ellipse.A())
                B = (r * ellipse.EixoB())/(ellipse.B())
                if (A*A + B*B) > 1:
                    BA = B/A
                    Aline = sqrt(1.0/(1.0+(BA*BA)))
#                    print "Aline --- ",Aline
#                    print "A --- ",A
                    Dist = (1-(Aline/abs(A))) * sqrt(r*r)  + sqrt(s*s)
                else:
                    Dist = sqrt(s*s)
                if result < Dist:
                    result = Dist
            if result > dis_max:
                 dis_max = result     
        return dis_max            
                    
    def perpendicularError(self):
        lEpMin = []
        lEpMax = []
        for ellipse in self.ListEllipse:
            di = self.Ellipse.B() * sqrt(1.0 - (self.Ellipse.Normal()*ellipse.Normal()) * (self.Ellipse.Normal()*ellipse.Normal()) ) ;
            epMax = ( ( self.Ellipse.Center() - ellipse.Center() ) * self.Ellipse.Normal() )+di;
            epMin = ( ( self.Ellipse.Center() - ellipse.Center() ) * self.Ellipse.Normal() )-di;
            lEpMin.append(epMin);
            lEpMax.append(epMax);    
        epmax = max(lEpMax)
        epmin = min(lEpMin)
        ep = epmax - epmin
        return ep
    def newPerpendicularError(self):
        dist_max = 0.0
        for ellipse in self.ListEllipse:
#            if fabs(self.Ellipse.Normal()*ellipse.EixoB()) > 1e-6 :
#                factor = (self.Ellipse.Normal()*ellipse.EixoA()*ellipse.A()) / (self.Ellipse.Normal()*ellipse.EixoB()*ellipse.B())
#                factor2 = factor*factor
#                alfa = sqrt(1.0/(1.0+factor2))
#                beta = factor*alfa
#                ray = ellipse.EixoB()*alfa*ellipse.B() + ellipse.EixoA()*beta*ellipse.A()
#            else:
#                 ray = ellipse.EixoA()*ellipse.A()
##            if (   (ellipse.Center()-self.Ellipse.Center())*self.Ellipse.Normal()  ) * (ray * self.Ellipse.Normal()) < 0:
##                ray = -ray*ellipse.A()

            tn1 = (self.Ellipse.Normal()*ellipse.EixoB()*ellipse.B()) * (self.Ellipse.Normal()*ellipse.EixoB()*ellipse.B())
            tn2 = (self.Ellipse.Normal()*ellipse.EixoA()*ellipse.A()) * (self.Ellipse.Normal()*ellipse.EixoA()*ellipse.A())
            dist = fabs( (ellipse.Center()-self.Ellipse.Center()) * self.Ellipse.Normal() )+ sqrt( tn1+ tn2) 
            #fabs( ray* self.Ellipse.Normal() ) 
            if (dist > dist_max ):
                dist_max = dist
            
#            print "new per: Center EixoA,EixoB,normal,erro,",ellipse.Center(),ellipse.EixoA(),ellipse.EixoB(),ellipse.Normal(),dist
#            print "center,normal", self.Ellipse.Center(),self.Ellipse.Normal()        
        return dist_max
        

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
#     self.CalcularEixosAeB_alt()
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
   def CalcularEixosAeB_alt(self):
       
       alfa = 0
       beta = 0
       pmax = Blender.Mathutils.Vector(0.0,0.0,0.0)
       
       for i in self.mPontosPorjetos:
           pi = i - self.mCenter
           if (pi*pi) > alfa:
               alfa = (pi*pi)
               pmax = pi  
               
           uq = pmax.normalize()
           
       for i in self.mPontosPorjetos:
           pi = i - self.mCenter
           esc = pi * uq
           esc2 = esc*esc
           if (abs(alfa - esc2) > 0.0001 ):
               factor = ( alfa *  ((pi*pi) - esc2) )/(alfa-esc2)
               if (factor > beta):
                   beta = factor
           
       self.mEigenVector.append(uq)
       self.mEigenVector.append(CrossVecs(uq , self.mNormal))
       self.mEigenVector.append(self.mNormal)
                  
       self.mEigenValues.append(sqrt(alfa))
       self.mEigenValues.append(sqrt(beta))  
       self.mEigenValues.append(0.0)
                  
       self.mA = 1.0
       self.mB = 1.0   
            
   def CalcularEixosAeB(self):
       
       cov = self.CovarianceMatrix(self.mPontosPorjetos)
       #print cov, "MATRIX"
       #eigenvec = la.eigenvectors(cov)
       eigenvalue,eigenvec = nu.eig(cov)
       #print 'LA',eigenvec
       print 'NUMPY',eigenvalue,eigenvec
       #print len(eigenvec[0]) ,' PRIMEIRO ',eigenvec[0]
       self.mEigenVector = [Blender.Mathutils.Vector(eigenvec[:,0]),Blender.Mathutils.Vector(eigenvec[:,1]),Blender.Mathutils.Vector(eigenvec[:,2])]
       self.mEigenValues = [eigenvalue[0],eigenvalue[1],eigenvalue[2]]
       
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
       
       print 'NUMPY',eigenvec
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

