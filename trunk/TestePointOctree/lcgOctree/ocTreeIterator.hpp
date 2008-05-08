#ifndef OCTREEINTERATOR_HPP_
#define OCTREEINTERATOR_HPP_

//[C++ STL includes]
#include <vector>

//[Project includes]
#include "ocTreeNode.hpp"
#include "ocTreeInternalNode.hpp"

// @Tip Use dynamic_cast<OctreeLeafNode*> para tentar transformar OctreeNode em LeafNode
// se der errado retornará NULL


#define debug(msg)

template <class Real, class ItemPtr, class Refine>
class OctreeInternalNode;

template <class Real, class ItemPtr, class Refine>
class OctreeNode;


template <class Real, class ItemPtr, class Refine = OverflowRefine<Real,ItemPtr> >
class OctreeIterator {
    
    typedef OctreeNode<Real, ItemPtr, Refine> 			Node;         ///< Octree Node
    typedef OctreeInternalNode<Real, ItemPtr, Refine> 	InternalNode; ///< Internal OctreeNode
    typedef Node* 										NodePtr; 	  ///< Pointer to octree node
    
    typedef LAL::Point3<Real> 							Point3;
    typedef LAL::Vector3<Real> 							Vector3; 
    typedef Box_3<Real> 								Box3;          ///< Octant extent
    
    std::vector<NodePtr*> path; ///< Path from root to pointed node
    int pathLen; ///< Path length
    NodePtr root; ///< Root of octree 

public:
    
    /// Default constructor: null pointer
    OctreeIterator () : pathLen (-1), root(0) {};
    
    /// Constructor from a pointer to an octree node
    OctreeIterator (NodePtr r) : pathLen(0), root(r) {};
    
    /// Constructor from another iterator
    OctreeIterator (const OctreeIterator& i) {
        path = i.path;
        pathLen = i.pathLen;
        root = i.root;
    }
    
    /// Tells when an iterator cannot be dereferenced
    bool null () const { return root == 0 || pathLen < 0; }

    
    /// Level of the node inside the octree (Root is level 0)
    int level () const { return pathLen; }

    Point3 mean ( void ) const { 
    	if (pathLen > 1)
    		if ((*path[pathLen-1])->isLeaf()) 
    			return father()->mean(); 
    }

     
    /// Pointer to father node. Pre-condition: node is not root.
    InternalNode * father () const {
        assert (pathLen > 0);
        if (pathLen == 1)
            return (InternalNode*) root;
        else 
            return (InternalNode*) (*path [pathLen-2]);
    }

    /// Which son of its father is this node. Pre-condition: node is not root
    int sonIndex () const {
        int ison = path [pathLen-1] - father()->son;
        assert (ison >=0 && ison < 8);
        return ison;
    }
    
    /// Returns in x,y,z the coordinates of the minimum corner of the 
    /// box occupied by the node. The root node is assumed to be of size
    /// 1 and have min coords = (0,0,0)
  void coords (const Box3& world, Real& minx, Real& miny, Real& minz, Real& maxx, Real& maxy, Real& maxz) const 
  {

    minx = world.xmin();
    miny = world.ymin();
    minz = world.zmin();
    maxx = world.xmax();
    maxy = world.ymax();
    maxz = world.zmax();
	
    InternalNode* fatherNode = (InternalNode*) root;
    for (int i = 0; i < pathLen; ++i) 
    {
    	 int ison = path [i] - fatherNode->son;
    	 
    	 assert (ison >= 0 && ison < 8);
    	 
    	 if (ison & 1) minx = fatherNode->mean().x();
    	 else maxx = fatherNode->mean().x();
	  
    	 if (ison & 2) miny = fatherNode->mean().y();
    	 else maxy = fatherNode->mean().y();

    	 if (ison & 4) minz = fatherNode->mean().z();
    	 else maxz = fatherNode->mean().z();

    	 fatherNode = (InternalNode*) (*path [i]);
         }
  }
    
    /// Equality predicate
    bool operator== (const OctreeIterator& i) const {
        return null() && i.null() ||
               !null() && !i.null() && operator* () == *i;
    }

    /// Inequality predicate
    bool operator!= (const OctreeIterator& i) const {
        return ! operator== (i);
    }

    /// Dereferences an iterator
    NodePtr operator* () const {
        assert (!null());
        if (pathLen == 0) return root;
        return *path[pathLen-1];
    };

    /// Increments an iterator
    OctreeIterator& operator++ () 
    {
        assert (!null());
        debug ("PathLen="<< pathLen);
        if (pathLen == 0) {
            if (root->isLeaf()) {
                // Nowhere to go
                pathLen = -1;
                root = 0;
                debug ("Leaf root");
            }
            else {
                // Go down
                assert (path.size() == 0);
                path.push_back (((InternalNode*) root)->son);
                pathLen++;
                debug ("Down from root");
            }
        } 
        else {
            if ((*path[pathLen-1])->isLeaf ()) {
                /// Get sibling node if it exists
                debug ("leaf");
                do {
                    int i = sonIndex ();
                    debug ("sonindex=" << i);
                    if (i < 7) {
                        /// Node is not the last son - get sibling node
                        debug ("sibling");
                        path [pathLen-1]++;
                        break;
                    }
                    else {
                        /// Node is the last son - go up
                        debug ("up");
                        //assert (path.size () == pathLen);
                        pathLen--;
                        path.pop_back();
                        if (pathLen < 1) {
                            // Nowhere to go 
                            root = 0;
                            pathLen = -1;
                            break;
                        }
                    }
                } while (true);
            } 
            else 
            {
                /// Go down
                debug ("down");
                InternalNode * iNodePtr = (InternalNode*) *(path[pathLen-1]);
                path.push_back (iNodePtr->son);
                pathLen++;
                assert ((unsigned int)pathLen == path.size());
            }
        }        
    }
    
};

#endif /*OCTREEINTERATOR_HPP_*/
