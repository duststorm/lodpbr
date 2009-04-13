
#-*- coding: utf-8 -*-
BIG = 1e100

from Blender  import Scene, Draw, BGL, Window , Mesh ,Mathutils , Object
from Blender.Mathutils import *
from Blender.Object import *

from heapq import heappush, heappop

def sqrDist(q,p):
    """Distancia ao quadrado entre dois pontos
    """
    x,y,z = q[0]-p[0],q[1]-p[1],q[2]-p[2]
    return x*x+y*y+z*z
        
class Box: 
    """Representa um paralelepipedo."""
    
    def __init__(self, pmin = (-BIG,-BIG,-BIG), pmax=(BIG,BIG,BIG)):
        """Construtor: vertices minimo e maximo da caixa"""
        self.pmin = pmin
        self.pmax = pmax
        
    def sqrDist(self, p):
        """Retorna a distancia entre p e a caixa"""
        if p[2]<=self.pmin[2]:
            if p[0]<=self.pmin[0]:
                if p[1]<=self.pmin[1]:
                   return sqrDist(p,self.pmin)
                elif p[1] >= self.pmax[1]:
                   return sqrDist(p,(self.pmin[0],self.pmax[1],self.pmin[2]))
                else:
                   return sqrDist((p[0],0,p[2]),(self.pmin[0],0,self.pmin[2]))
            elif p[0]>=self.pmax[0]:
                if p[1]<=self.pmin[1]:
                   return sqrDist(p,(self.pmax[0],self.pmin[1],self.pmin[2]))
                elif p[1] >= self.pmax[1]:
                   return sqrDist(p,(self.pmax[0],self.pmax[1],self.pmin[2]))
                else:
                   return sqrDist((p[0],0,p[2]),(self.pmax[0],0,self.pmin[2]))
            else:
                if p[1]<=self.pmin[1]:
                   return sqrDist((0,p[1],p[2]),(0,self.pmin[1],self.pmin[2]))
                elif p[1] >= self.pmax[1]:
                   return sqrDist((0,p[1],p[2]),(0,self.pmax[1],self.pmin[2]))
                else:
                   return (self.pmin[2]-p[2])**2
        elif p[2]>=self.pmax[2]:
            if p[0]<=self.pmin[0]:
                if p[1]<=self.pmin[1]:
                   return sqrDist(p,(self.pmin[0],self.pmin[1],self.pmax[2]))
                elif p[1] >= self.pmax[1]:
                   return sqrDist(p,(self.pmin[0],self.pmax[1],self.pmax[2]))
                else:
                   return sqrDist((p[0],0,p[2]),(self.pmin[0],0,self.pmax[2]))
            elif p[0]>=self.pmax[0]:
                if p[1]<=self.pmin[1]:
                   return sqrDist(p,(self.pmax[0],self.pmin[1],self.pmax[2]))
                elif p[1] >= self.pmax[1]:
                   return sqrDist(p,(self.pmax[0],self.pmax[1],self.pmax[2]))
                else:
                   return sqrDist((p[0],0,p[2]),(self.pmax[0],0,self.pmax[2])) 
            else:
                if p[1]<=self.pmin[1]:
                   return sqrDist((0,p[1],p[2]),(0,self.pmin[1],self.pmax[2])) 
                elif p[1] >= self.pmax[1]:
                   return sqrDist((0,p[1],p[2]),(0,self.pmax[1],self.pmax[2])) 
                else:
                   return (p[2]-self.pmax[2])**2
        else:
            if p[0]<=self.pmin[0]:
                if p[1]<=self.pmin[1]:
                   return sqrDist((p[0],p[1],0),(self.pmin[0],self.pmin[1],0)) 
                elif p[1] >= self.pmax[1]:
                   return sqrDist((p[0],p[1],0),(self.pmin[0],self.pmax[1],0)) 
                else:
                   return (self.pmin[0]-p[0])**2
            elif p[0]>=self.pmax[0]:
                if p[1]<=self.pmin[1]:
                   return sqrDist((p[0],p[1],0),(self.pmax[0],self.pmin[1],0)) 
                elif p[1] >= self.pmax[1]:
                   return sqrDist((p[0],p[1],0),(self.pmax[0],self.pmax[1],0)) 
                else:
                   return (p[0]-self.pmax[0])**2
            else:
                if p[1]<=self.pmin[1]:
                   return (self.pmin[1] - p[1])**2
                elif p[1] >= self.pmax[1]:
                   return (p[1] - self.pmax[1])**2
                else:
                   return 0

        
                    
        if self.pmin[0]<=p[0]<=self.pmax[0] and self.pmin[1]<=p[1]<=self.pmax[1] and self.pmin[2]<=p[2]<=self.pmax[2]:
           return 0
        else:
           return min([sqrDist(p,self.pmin),sqrDist(p,self.pmax),
                      sqrDist(p,(self.pmin[0],self.pmax[1],self.pmax[2])),            
                      sqrDist(p,(self.pmin[0],self.pmin[1],self.pmax[2])),            
                      sqrDist(p,(self.pmin[0],self.pmax[1],self.pmin[2])),            
                      sqrDist(p,(self.pmax[0],self.pmin[1],self.pmin[2])),            
                      sqrDist(p,(self.pmax[0],self.pmin[1],self.pmax[2])),            
                      sqrDist(p,(self.pmax[0],self.pmax[1],self.pmin[2]))])
    
    def split(self,coord,value):
        """Retorna duas caixas obtidas seccionando a caixa por um plano 
        coord = value"""
        lmin = list(self.pmin)
        lmin[coord] = value
        lmax = list(self.pmax)
        lmax[coord] = value
        boxmin = Box(self.pmin,tuple(lmax))
        boxmax = Box(tuple(lmin),self.pmax)
        return (boxmin, boxmax)

class Kdtree:
    """Uma classe kdtree simples para pontos 3D"""
    
    def __init__(self, capacity):
        """Construtor.
        root � um n� da kd-tree que pode ter um dos seguintes formatos:
           n� interno: [discriminante filho1 filho2] 
           n� folha: [ponto ponto ... ponto] (no m�ximo capacity pontos)
        capacity � a capacidade m�xima do bucket."""
        
        self.root = []
        self.capacity = capacity
        self.count = 0
        
    def isleaf (self,node): 
        """Retorna true sse node � um n� folha"""
        return len(node)==0 or type(node[0]) not in (float,int)

    def insert (self, p):
        """Insere um ponto p na kd-tree"""
        
        def ins (node, level):
            """Faz inser��o recursiva de p num n� de n�vel leve"""
            
            def split():
                """Parte o n� de acordo com a mediana"""
                coord = level % 3
                discriminantes = [q.cent[coord] for q in node]
                discriminantes.sort()
                discr = discriminantes[(len(discriminantes)+1)/2]
                son0 = []
                son1 = []
                for q in node:
                    if q.cent[coord]<discr: son0.append(q)
                    else: son1.append(q)
                node[:] = [discr, son0, son1]
                
            if self.isleaf(node):
               if len(node) < self.capacity: node.append (p)
               else: 
                  node.append(p)
                  split()
            else:
               coord = level%3
               if p.cent[coord]<node[0]: ins(node[1],level+1)
               else: ins(node[2],level+2)
           
        ins(self.root, 0)
        self.count += 1
        
    def kClosest(self,p,k_close,k):
        """Retorna a a lista (k_close) dos objetos mais proximos do objeto p """         
        
        def insert_point(q,k_close,k):
            """ insere o objeto q na lista dos k mais proximos e
                retorna sua distancia a p """
            heappush(k_close,(q))
            if len(k_close) > k:
                heappop(k_close)
            return -(k_close[0][0])
                    
        def find_kclose(node,p,smallestDist,k_close,k,level,box):
            """Busca a partir de node os k pontos mais proximos de p.
            smallestDist tem uma estimativa do k-esimo ponto mais 
            proximo encontrado ate agora.
            k e o numero de pontos mais proximos a serem encontrados
            Retorna uma lista de tuplas (-d,q) onde q é o ponto 
            e d é sua distancia a p.
            d e negativo para rapida consulta na lista, sendo a cabeca
            o k-esimo ponto mais proximo encontrado """
            
            if self.isleaf(node):
                 for q in node:
                    dist = sqrDist(q.cent,p.cent)
                    if (dist < smallestDist) or (len(k_close) < k) : 
                        smallestDist = insert_point((-dist,q),k_close,k)
            else:
                if box.sqrDist(p.cent) > smallestDist:
                   return k_close
                coord = level%3
                son0box,son1box = box.split(coord,node[0])
                dist0,dist1 = son0box.sqrDist(p.cent),son1box.sqrDist(p.cent)
                if dist0<dist1:
                    find_kclose(node[1],p,smallestDist,k_close,k,level+1,son0box)
                    if len(k_close) > 0 :smallestDist = -k_close[0][0]
                    find_kclose(node[2],p,smallestDist,k_close,k,level+1,son1box)
                else:
                    find_kclose(node[2],p,smallestDist,k_close,k,level+1,son1box)
                    if len(k_close) > 0 :smallestDist = -k_close[0][0]
                    find_kclose(node[1],p,smallestDist,k_close,k,level+1,son0box)
                    
        assert(self.count>0)
        return find_kclose(self.root,p,BIG,k_close,k,0,Box())


            
    def closest (self, p):
        """Acha o ponto mais perto de p. Assume-se que a kd-tree tem
        ao menos um ponto."""
        
        def find(node,smallestDist,level,box):
            """Busca a partir de node o ponto mais proximo de p.
            smallestDist tem uma estimativa do ponto mais proximo
            encontrado ate agora.
            Retorna uma tupla (d,q) onde q � o ponto mais proximo
            e d � sua distancia a p."""
            
            if self.isleaf(node):
                return min([(sqrDist(q.cent,p.cent),q) for q in node])
            else:
                if box.sqrDist(p.cent) > smallestDist:
                   return (BIG,())
                coord = level%3
                son0box,son1box = box.split(coord,node[0])
                dist0,dist1 = son0box.sqrDist(p.cent),son1box.sqrDist(p.cent)
                if dist0<dist1:
                    dist0,q = find(node[1],smallestDist,level+1,son0box)
                    if dist0<smallestDist: smallestDist = dist0
                    dist1,r = find(node[2],smallestDist,level+1,son1box)
                else:
                    dist1,r = find(node[2],smallestDist,level+1,son1box)
                    if dist1<smallestDist: smallestDist = dist1
                    dist0,q = find(node[1],smallestDist,level+1,son0box)
                if dist0<dist1:
                    return (dist0,q)
                else:
                    return (dist1,r)
                    
        assert(self.count>0)
        return find(self.root,BIG,0,Box())

#a very simple test
if __name__ == '__main__':
    tree = Kdtree(1)
    from random import random
    from time import *
    l = []
    for i in range(2):
        p = (100*random(),100*random(),100*random())
        tree.insert(p)
        l.append(p)
   
    p = (0,0,0)
    t0 = clock()
    heap = []
    for q in l:
        heappush(heap,(sqrDist(p,q),q))
    print heappop(heap)
    print heappop(heap)     
    #print clock()-t0
    #t0 = clock()
    #print tree.closest(p)
    #print clock()-t0
    k_close = []
    print "----"
    print tree.kClosest(p, k_close, 2)


# -*- coding: utf-8 -*-
#BIG = 1e100
#
#from heapq import heappush, heappop
#
#
#
#def sqrDist(q,p):
#    """Distancia ao quadrado entre dois pontos
#    """
#    x,y,z = q[0]-p[0],q[1]-p[1],q[2]-p[2]
#    return x*x+y*y+z*z
#        
#class Box: 
#    """Representa um paralelepipedo."""
#    
#    def __init__(self, pmin = (-BIG,-BIG,-BIG), pmax=(BIG,BIG,BIG)):
#        """Construtor: vertices minimo e maximo da caixa"""
#        self.pmin = pmin
#        self.pmax = pmax
#        
#    def sqrDist(self, p):
#        """Retorna a distancia entre p e a caixa"""
#        if p[2]<=self.pmin[2]:
#            if p[0]<=self.pmin[0]:
#                if p[1]<=self.pmin[1]:
#                   return sqrDist(p,self.pmin)
#                elif p[1] >= self.pmax[1]:
#                   return sqrDist(p,(self.pmin[0],self.pmax[1],self.pmin[2]))
#                else:
#                   return sqrDist((p[0],0,p[2]),(self.pmin[0],0,self.pmin[2]))
#            elif p[0]>=self.pmax[0]:
#                if p[1]<=self.pmin[1]:
#                   return sqrDist(p,(self.pmax[0],self.pmin[1],self.pmin[2]))
#                elif p[1] >= self.pmax[1]:
#                   return sqrDist(p,(self.pmax[0],self.pmax[1],self.pmin[2]))
#                else:
#                   return sqrDist((p[0],0,p[2]),(self.pmax[0],0,self.pmin[2]))
#            else:
#                if p[1]<=self.pmin[1]:
#                   return sqrDist((0,p[1],p[2]),(0,self.pmin[1],self.pmin[2]))
#                elif p[1] >= self.pmax[1]:
#                   return sqrDist((0,p[1],p[2]),(0,self.pmax[1],self.pmin[2]))
#                else:
#                   return (self.pmin[2]-p[2])**2
#        elif p[2]>=self.pmax[2]:
#            if p[0]<=self.pmin[0]:
#                if p[1]<=self.pmin[1]:
#                   return sqrDist(p,(self.pmin[0],self.pmin[1],self.pmax[2]))
#                elif p[1] >= self.pmax[1]:
#                   return sqrDist(p,(self.pmin[0],self.pmax[1],self.pmax[2]))
#                else:
#                   return sqrDist((p[0],0,p[2]),(self.pmin[0],0,self.pmax[2]))
#            elif p[0]>=self.pmax[0]:
#                if p[1]<=self.pmin[1]:
#                   return sqrDist(p,(self.pmax[0],self.pmin[1],self.pmax[2]))
#                elif p[1] >= self.pmax[1]:
#                   return sqrDist(p,(self.pmax[0],self.pmax[1],self.pmax[2]))
#                else:
#                   return sqrDist((p[0],0,p[2]),(self.pmax[0],0,self.pmax[2])) 
#            else:
#                if p[1]<=self.pmin[1]:
#                   return sqrDist((0,p[1],p[2]),(0,self.pmin[1],self.pmax[2])) 
#                elif p[1] >= self.pmax[1]:
#                   return sqrDist((0,p[1],p[2]),(0,self.pmax[1],self.pmax[2])) 
#                else:
#                   return (p[2]-self.pmax[2])**2
#        else:
#            if p[0]<=self.pmin[0]:
#                if p[1]<=self.pmin[1]:
#                   return sqrDist((p[0],p[1],0),(self.pmin[0],self.pmin[1],0)) 
#                elif p[1] >= self.pmax[1]:
#                   return sqrDist((p[0],p[1],0),(self.pmin[0],self.pmax[1],0)) 
#                else:
#                   return (self.pmin[0]-p[0])**2
#            elif p[0]>=self.pmax[0]:
#                if p[1]<=self.pmin[1]:
#                   return sqrDist((p[0],p[1],0),(self.pmax[0],self.pmin[1],0)) 
#                elif p[1] >= self.pmax[1]:
#                   return sqrDist((p[0],p[1],0),(self.pmax[0],self.pmax[1],0)) 
#                else:
#                   return (p[0]-self.pmax[0])**2
#            else:
#                if p[1]<=self.pmin[1]:
#                   return (self.pmin[1] - p[1])**2
#                elif p[1] >= self.pmax[1]:
#                   return (p[1] - self.pmax[1])**2
#                else:
#                   return 0
#
#        
#                    
#        if self.pmin[0]<=p[0]<=self.pmax[0] and self.pmin[1]<=p[1]<=self.pmax[1] and self.pmin[2]<=p[2]<=self.pmax[2]:
#           return 0
#        else:
#           return min([sqrDist(p,self.pmin),sqrDist(p,self.pmax),
#                      sqrDist(p,(self.pmin[0],self.pmax[1],self.pmax[2])),            
#                      sqrDist(p,(self.pmin[0],self.pmin[1],self.pmax[2])),            
#                      sqrDist(p,(self.pmin[0],self.pmax[1],self.pmin[2])),            
#                      sqrDist(p,(self.pmax[0],self.pmin[1],self.pmin[2])),            
#                      sqrDist(p,(self.pmax[0],self.pmin[1],self.pmax[2])),            
#                      sqrDist(p,(self.pmax[0],self.pmax[1],self.pmin[2]))])
#    
#    def split(self,coord,value):
#        """Retorna duas caixas obtidas seccionando a caixa por um plano 
#        coord = value"""
#        lmin = list(self.pmin)
#        lmin[coord] = value
#        lmax = list(self.pmax)
#        lmax[coord] = value
#        boxmin = Box(self.pmin,tuple(lmax))
#        boxmax = Box(tuple(lmin),self.pmax)
#        return (boxmin, boxmax)
#
#class Kdtree:
#    """Uma classe kdtree simples para pontos 3D"""
#    
#    def __init__(self, capacity):
#        """Construtor.
#        root � um n� da kd-tree que pode ter um dos seguintes formatos:
#           n� interno: [discriminante filho1 filho2] 
#           n� folha: [ponto ponto ... ponto] (no m�ximo capacity pontos)
#        capacity � a capacidade m�xima do bucket."""
#        
#        self.root = []
#        self.capacity = capacity
#        self.count = 0
#        
#    def isleaf (self,node): 
#        """Retorna true sse node � um n� folha"""
#        return len(node)==0 or type(node[0]) not in (float,int)
#
#    def insert (self, p):
#        """Insere um ponto p na kd-tree"""
#        
#        def ins (node, level):
#            """Faz inser��o recursiva de p num n� de n�vel leve"""
#            
#            def split():
#                """Parte o n� de acordo com a mediana"""
#                coord = level % 3
#                discriminantes = [q[coord] for q in node]
#                discriminantes.sort()
#                discr = discriminantes[(len(discriminantes)+1)/2]
#                son0 = []
#                son1 = []
#                for q in node:
#                    if q[coord]<discr: son0.append(q)
#                    else: son1.append(q)
#                node[:] = [discr, son0, son1]
#                
#            if self.isleaf(node):
#               if len(node) < self.capacity: node.append (p)
#               else: 
#                  node.append(p)
#                  split()
#            else:
#               coord = level%3
#               if p[coord]<node[0]: ins(node[1],level+1)
#               else: ins(node[2],level+2)
#           
#        ins(self.root, 0)
#        self.count += 1
#    def kClosest(self,p,k_close,k):
#        
#        def insert_point(p,k_close,k):
#            heappush(k_close,(p))
#            if len(k_close) > k:
#                heappop(k_close)
#            return -(k_close[0][0])
#                    
#        def find_kclose(node,p,smallestDist,k_close,k,level,box):
#            """Busca a partir de node os k pontos mais proximo de p.
#            smallestDist tem uma estimativa do k-esimo ponto mais 
#            proximo encontrado ate agora.
#            k e o numero de pontos mais proximo a ser encontrado
#            Retorna uma lista de tupla (-d,q) onde q � o ponto 
#            e d � sua distancia a p.
#            d e negativo para rapida consulta na lista, sendo a cabeca
#            o k-esimo ponto mais proximo encontrado """
#            
#            if self.isleaf(node):
#                 for q in node:
#                    dist = sqrDist(q,p)
#                    if (sqrDist(q,p) < smallestDist) or (len(close) < k) : 
#                        smallestDist = insert_point((-dist,q),k_close,k)
#            else:
#                if box.sqrDist(p) > smallestDist:
#                   pass
#                coord = level%3
#                son0box,son1box = box.split(coord,node[0])
#                dist0,dist1 = son0box.sqrDist(p),son1box.sqrDist(p)
#                if dist0<dist1:
#                    find_kclose(node[1],p,smallestDist,k_close,k,level+1,son0box)
#                    find_kclose(node[2],p,smallestDist,k_close,k,level+1,son1box)
#                else:
#                    find_kclose(node[2],p,smallestDist,k_close,k,level+1,son1box)
#                    find_kclose(node[1],p,smallestDist,k_close,k,level+1,son0box)
#                return k_close    
#                    
#        assert(self.count>0)
#        return find_kclose(self.root,p,BIG,k_close,k,0,Box())
#
#
#            
#    def closest (self, p):
#        """Acha o ponto mais perto de p. Assume-se que a kd-tree tem
#        ao menos um ponto."""
#        
#        def find(node,smallestDist,level,box):
#            """Busca a partir de node o ponto mais proximo de p.
#            smallestDist tem uma estimativa do ponto mais proximo
#            encontrado ate agora.
#            Retorna uma tupla (d,q) onde q � o ponto mais proximo
#            e d � sua distancia a p."""
#            
#            if self.isleaf(node):
#                return min([(sqrDist(q,p),q) for q in node])
#            else:
#                if box.sqrDist(p) > smallestDist:
#                   return (BIG,())
#                coord = level%3
#                son0box,son1box = box.split(coord,node[0])
#                dist0,dist1 = son0box.sqrDist(p),son1box.sqrDist(p)
#                if dist0<dist1:
#                    dist0,q = find(node[1],smallestDist,level+1,son0box)
#                    if dist0<smallestDist: smallestDist = dist0
#                    dist1,r = find(node[2],smallestDist,level+1,son1box)
#                else:
#                    dist1,r = find(node[2],smallestDist,level+1,son1box)
#                    if dist1<smallestDist: smallestDist = dist1
#                    dist0,q = find(node[1],smallestDist,level+1,son0box)
#                if dist0<dist1:
#                    return (dist0,q)
#                else:
#                    return (dist1,r)
#                    
#        assert(self.count>0)
#        return find(self.root,BIG,0,Box())
#
##a very simple test
#if __name__ == '__main__':
#    tree = Kdtree(1)
#    from random import random
#    from time import *
#    l = []
#    for i in range(2):
#        p = (100*random(),100*random(),100*random())
#        tree.insert(p)
#        l.append(p)
#   
#    p = (0,0,0)
#    t0 = clock()
#    heap = []
#    for q in l:
#        heappush(heap,(sqrDist(p,q),q))
#    print heappop(heap)
#    print heappop(heap)     
#    #print clock()-t0
#    #t0 = clock()
#    #print tree.closest(p)
#    #print clock()-t0
#    k_close = []
#    print "----"
#    print tree.kClosest(p, k_close, 2)
