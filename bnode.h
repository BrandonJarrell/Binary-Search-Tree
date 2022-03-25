/***********************************************************************
 * Module:
 *    Bnode
 * Author:
 *    Brandon Jarrell, Michael George
 * Summary:
 *    This program will implement a pair: two values
 ************************************************************************/

#ifndef Bnode
#define Bnode

#include <iostream>  // for ISTREAM and OSTREAM
template <class T>
class BNode
{
   private:

   public:
      T data;
      BNode <T>* pLeft;
      BNode <T>* pRight;
      BNode <T>* pParent;

      BNode() { pLeft = NULL; pRight = NULL; pParent = NULL; }
      BNode(T t) { data = t; pLeft = NULL; pRight = NULL; pParent = NULL; }
};

/***********************************************************************
 * addLeft() (adds a node using a BNode *)
 ************************************************************************/
 template <class T>
 void addLeft(BNode <T>* pNode, BNode <T> * pAdd)
 {
    if(pAdd != NULL)   // If it points to nothing, 
    {
        pAdd->pParent = pNode;  // make the rhs nodes's parent point to the lhs node
    }

    pNode->pLeft = pAdd;    // lhs node's pLeft point to the rhs

    return;
 }

 /***********************************************************************
 * addLeft() (adds a node using T)
 ************************************************************************/
template <class T>
void addLeft(BNode <T> * pNode, T t)
{
   BNode <T>* pAdd = new BNode<T>(t); // Make a node, give it a value
   pAdd->pParent = pNode;           // Make that node point to its parent
   pNode->pLeft = pAdd;            // point this node's pLeft point to that node
   
   return;
}

 /***********************************************************************
 * addRight (adds a node using a BNode *)
 ************************************************************************/
template <class T>
void addRight(BNode <T>* pNode, BNode <T> * pAdd)
{
   if(pAdd != NULL)   // If it points to nothing, 
   {
      pAdd->pParent = pNode;  // make the rhs nodes's parent point to the lhs node
   }

   pNode->pRight = pAdd;   // lhs node's pRight point to the rhs

   return;
}

/***********************************************************************
 * addRight (adds a node using T)
 ************************************************************************/
template <class T>
void addRight(BNode <T>* pNode, T t)
{
   BNode <T>* pAdd = new BNode <T>(t); // Make a node, give it a value
   pAdd->pParent = pNode;              // point this node's pRight point to that node
   pNode->pRight = pAdd;            // Make that node point to its parent
   return;
}

 /***********************************************************************
 * sizeBTree
 ************************************************************************/
template <class T>
int sizeBTree(const BNode <T> * pRoot)
{
    if (pRoot == NULL)      // If there are no roots to the tree
    {
       return 0;            // Return 0 for the size of the tree
    }
    else                    // Otherwise
    {
       // Make the size of the tree equal to the size both roots together
       // plus one
       return sizeBTree(pRoot->pLeft) + 1 + sizeBTree(pRoot->pRight);
    }
}

/***********************************************************************
 * copyBTree
 ************************************************************************/
 template <class T>
 BNode <T>* copyBTree(const BNode <T>* pSrc)
 {
    // If there's nothing, do nothing
    if (pSrc == NULL)
    {
       return NULL;
    }

    // Allocate a new node
    BNode <T>* destination = new BNode <T>(pSrc->data);

    // Copy over the left sub-trees
    destination->pLeft = copyBTree(pSrc->pLeft);
    if (destination->pLeft != NULL)
    {
       destination->pLeft->pParent = destination;
    }

    // Copy over the right sub-trees
    destination->pRight = copyBTree(pSrc->pRight);
    if (destination->pRight != NULL)
    {
       destination->pRight->pParent = destination;
    }

    // Return the new node allocated here
    return destination;
 }

 /***********************************************************************
 * deleteBTree()
 ************************************************************************/
 template <class T>
 void deleteBTree(BNode <T>*& pNode)
 {
    // If there's nothing, do nothing
    if (pNode == NULL)
    {
       return;
    }

    // delete the roots
    deleteBTree(pNode->pLeft);
    deleteBTree(pNode->pRight);

    // delete itself
    delete pNode;

    pNode = NULL;
 }

 /***********************************************************************
 * Insertion operator <<
 ************************************************************************/
 template <class T>
 std::ostream & operator << (std::ostream & out, BNode <T> * pNode)
{
    // Check to see if the underlying node is not NULL
    if (pNode != NULL)
    {
       std::cout << pNode->pLeft;           // Check the left sub-tree
       std::cout << pNode->data << " ";     // Visit the underlying node
       std::cout << pNode->pRight;          // Check the right sub-tree
    }

    // Return the ostream
    return out;
}

#endif //  Bnode
