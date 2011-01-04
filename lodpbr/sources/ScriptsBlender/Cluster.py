from heapq import heappush, heappop

from Blender.Mathutils import *

import Ellipse
from Ellipse import Ellipse    

import Merge
from Merge import Merge, Error

from KDTree import *


BIGELLIPSE = False
MAX_ERROR = 0.5

class Cluster:
    def __init__(self):
        # get mesh
        self.mMesh = Mesh.New('Mesh') 
        #Vertice that begins the agglomeration
        # in (index of the vertice on mesh)
        """ Cluster Looping """  
              
        self.ListSeed = []
        
        """ End Cluster Looping """
        self.mSeed = None
        # List of the vertices similar to the seed
        self.mSimilar = []
        # Neighbors
        self.mNeighbors = []
        # Threshold
        self.mThreshold = 0.25       #
        
        self.tree = Kdtree(1)
        
    def Mesh(self,mesh):
        self.mMesh = mesh
        self.tree = Kdtree(1)
        for f in self.mMesh.faces:
             if f.sel == 1: self.mSeed = f
             self.tree.insert(f)
        k = []
        k = SeedExpansion(self.mSeed,0)
        print self.ListSeed,"List SEED"
        print "LEN DE KCLOSED" ,len(k_close)
        for f in k_close:
                f[1].col[0].r = 255
                f[1].col[0].g = 0
                f[1].col[0].b = 0
                f[1].col[1].r = 255
                f[1].col[1].g = 0
                f[1].col[1].b = 0
                f[1].col[2].r = 255
                f[1].col[2].g = 0
                f[1].col[2].b = 0                                
        self.mSeed.col[0].r = 0
        self.mSeed.col[0].g = 0
        self.mSeed.col[0].b = 255
        self.mSeed.col[1].r = 0
        self.mSeed.col[1].g = 0
        self.mSeed.col[1].b = 255
        self.mSeed.col[2].r = 0
        self.mSeed.col[2].g = 0
        self.mSeed.col[2].b = 255     
        self.KClose_to_Seed()    
    def Threshold(self,threshold):
        self.mThreshold = threshold
    def GetNeighbors(self):
        self.mNeighbors = []
        for f in self.mMesh.faces:
            if f.sel == 1:
             self.mNeighbors.append(f)
    def Seed(self):
        for f in self.mMesh.faces:
            if f.sel == 1:
             self.mSeed = f
    def EuclideanDistance(self,v,u):
        return sqrt(    (v.x - u.x) * (v.x - u.x) +
                        (v.y - u.y) * (v.y - u.y) +
                        (v.z - u.z) * (v.z - u.z) )
        
### Cluster Looping

    def SeedExpansion(self, seed,idCluster):
        """ Expande um semente , e gera um cluster quando passa no teste de agregacao """
        listOpen = []
        listClose = []
        listCluster = []
        mCurrentEllipse = seed
        heappush((0.0,seed))
        
        """ Enquanto tiver pontos a serem explorados na vizinhanca da semente """                
        while len(listOpen) > 0:  
   
            target = heappop(listOpen)
            cost      = target[0]   
            ellipse  = target[1]

            """ Se o ponto ja foi expandido , tirar proximo elemento ta lista aberta """
            if   (ellipse.mLastClusterID == idCluster) and (ellipse.mLastClusterCost < cost) :
                continue
            """ inclui apenas as ellipses para uma futura agregacao """
            listClose.append(ellipse)
            """ dado criterio de agregacao .. saber se para e gera um Ellipse"""
            if  self.Aggregation(close) == True:
                if  BIGELLIPSE:
                    listClose.append(mCurrentEllipse);
                    #mCurrentEllipse = MakeEllipse(listClose);
            
                else:
                    listCluster.extend(listClose)
                    #mCurrentEllipse = MakeEllipse(listCluster)

                if  mCurrentEllipse.mError > MAX_ERROR :
                    while  len(listClose) > 0 :
                        temp = listClose.pop()
                        if  temp.mClusterID == -1:
                            self.ListSeed.append(temp)
                    while  len(listOpen) > 0:
                        temp = open.pop();
                        if  temp.mClusterID == -1:
                            self.ListSeed.append(temp)
                ## mCurrentEllipse.mError < MAX_ERROR 
                else:
                    #UpdateAggregationCoditions()
                    listCluster.extend(listClose)
                    while  len(listClose):
                        temp = listClose.pop()
                        if temp.mError > mCurrentEllipse.mError: 
                            temp.mError = mCurrentEllipse.mError
                            temp.mClusterID = idCluster
                            

            kNeighbor = [] 
            kNeighbor = self.tree.kClosest(self.mSeed,20)
                  
            for i in  kNeighbor: 
           
                """  Se nao estiver em um cluster ou seu costo do novo caminho desde a semente é melhor """
                if  ( i[1].mLastClusterID != idCluster) or (i[0] < i.mLastClusterCost) :
                             """ Se custo for melhor que um Threshold , poe na lista aberto para futura expanssao"""
                             if  i[0] < MAX_COST:
                                 i[1].mLastClusterCost = i[0]
                                 i[1].mLastClusterID   = idCluster
                                 heappush((i[0],i))
                                 """  Senao acrescenta-o a  lista de semente"""
                             else:
                                if  i[1].mLastClusterID == -1:
                                    self.ListSeed.append(i)

        return listCluster   
                
    def Aggregation(self,cluster):
         """ Testa se a lista cluster forma um cluster de acordo com os criterios abaixo """ 
         if len(listCluster) >=  50 or self.Error(istCluster) > self.mThreshold:
                pass           
    def UpdateAggregationCoditions(self,cluster):
        pass            
    def Error(self):
        return 0
    
    def KClose_to_Seed(self):
        k_close = []
        k_close = self.tree.kClosest(self.mSeed,2000)
        print "LEN DE KCLOSED" ,len(k_close)
        for f in k_close:
                f[1].col[0].r = 255
                f[1].col[0].g = 0
                f[1].col[0].b = 0
                f[1].col[1].r = 255
                f[1].col[1].g = 0
                f[1].col[1].b = 0
                f[1].col[2].r = 255
                f[1].col[2].g = 0
                f[1].col[2].b = 0                                
        self.mSeed.col[0].r = 0
        self.mSeed.col[0].g = 0
        self.mSeed.col[0].b = 255
        self.mSeed.col[1].r = 0
        self.mSeed.col[1].g = 0
        self.mSeed.col[1].b = 255
        self.mSeed.col[2].r = 0
        self.mSeed.col[2].g = 0
        self.mSeed.col[2].b = 255
                                
    def Similars(self):
        self.mSimilars = []
        for f in self.mNeighbors:
         for f in self.mNeighbors:
            print self.EuclideanDistance(f.v[0].co,self.mSeed.co) , "v1"
            if self.EuclideanDistance(f.v[0].co,self.mSeed.co) < self.mThreshold:
                self.mSimilar.append(f.v[0])
            print self.EuclideanDistance(f.v[1].co,self.mSeed.co) , "v2"    
            if self.EuclideanDistance(f.v[1].co,self.mSeed.co) < self.mThreshold:
                self.mSimilar.append(f.v[1])
            print self.EuclideanDistance(f.v[2].co,self.mSeed.co), "v3"
            if self.EuclideanDistance(f.v[2].co,self.mSeed.co) < self.mThreshold:
                self.mSimilar.append(f.v[2]) 
#            if DotVecs(f.v[0].co,self.mSeed.no) > self.mThreshold:
#                self.mSimilar.append(f.v[0])
#            if DotVecs(f.v[1].no,self.mSeed.no) > self.mThreshold:
#                self.mSimilar.append(f.v[1])
#            if DotVecs(f.v[2].no,self.mSeed.no) > self.mThreshold:
#                self.mSimilar.append(f.v[2])        
                 
    def PaintMesh(self):
        map (lambda f: self.PaintVerts(f),self.mNeighbors)
        
    def Update(self):
        pass
               
    def PaintVerts(self,face):
        for v in self.mSimilar:
            if face.v[0].index == self.mSeed.index:
                face.col[0].r = 0
                face.col[0].g = 0
                face.col[0].b = 255
                continue
            if face.v[0].index == v.index:
                face.col[0].r = 255
                face.col[0].g = 0
                face.col[0].b = 0
                continue
            elif face.v[1].index == v.index:
                face.col[1].r = 255
                face.col[1].g = 0
                face.col[1].b = 0
                continue
            elif face.v[2].index == v.index:
                face.col[2].r = 255
                face.col[2].g = 0
                face.col[2].b = 0
                continue
            else:
               continue
