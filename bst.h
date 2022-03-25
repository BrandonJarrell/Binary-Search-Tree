/***********************************************************************
 * Component:
 *    Assignment 09, Binary Search Tree (BST)
 *    Brother Kirby, CS 235
 * Author:
 *    Brandon Jarrell, Michael George
 * Summary:
 *    Create a binary search tree
 ************************************************************************/

#ifndef BST_H
#define BST_H
#include <cassert>

namespace custom
{
    /**************************************************
    * BST
    **************************************************/
    template <class T>
    class BST
    {
    public:
    
        // BST nested classes for iterator and BNode
        class iterator;
        class BNode;

        // Default constructor
        BST() :root(NULL), numElements(0){}

        // Copy constructor
        BST(const BST<T>& rhs) throw(const char*);

        // Destructor
        ~BST() { clear(); }

        // Boolean that comes up if the BST is empty
        bool empty() { return numElements == 0; }

        // Figures out how many nodes are in the BST
        int size() { return numElements; }

        // Purges the array of all elements
        void clear();

        // Add an element to the tree
        void insert(const T& t) throw (const char*);

        // Reference to the root node
        BNode* getRoot() { return root; }

        // Removes an element in the tree given an iterator to "it"
        void erase(iterator& it);

        // Returns an iterator with the position of an element in the tree
        iterator find(const T& t);

        // Iterators to the begin and end of BST
        iterator begin();
        iterator end() { return iterator(NULL); }
        iterator rbegin() 
        {
            // If root is not NULL
            if (root != NULL)
            {
                // Create a left node
                BNode* rightNode = root;

                // While leftNode is not NULL
                while (rightNode->pRight)
                {
                    // leftNode is equal to the node to its left
                    rightNode = rightNode->pRight;
                }

                // Return iterator to the first node of the binary tree
                return iterator(rightNode);
            }
            else
            {
                // Return iterator
                return iterator();
            }
        
        }
        iterator rend() { return iterator (NULL); }
        // Assignment operator
        BST<T>& operator=(const BST& rhs) throw(const char*);

        friend std::ostream& operator<<(std::ostream& out, BST <T>& tree)
        {
            out << "{ ";

            // Verify that the underlying node is not NULL
            if (tree.root != NULL)
            {
                out << tree.root;
            }

            out << " }";

            return out;
        }

        // Insertion operator for BNode
        friend std::ostream& operator<<(std::ostream& out, BNode* pNode)
        {
            // Verify that the underlying node is not NULL
            if (pNode != NULL)
            {
                out << pNode->pLeft;    // Go to the left sub-tree
                out << " " << pNode->data << " ";     // Go to the underlying node
                out << pNode->pRight;   // Go to tht right sub-tree
            }

            return out;
        }

    private:
        // Pointer to root binary node
        BNode* root;

        // Number of elements in the tree
        int numElements;
        
        void rotateRight(BNode* newNode)
        {
           BNode* RightRot = newNode->pLeft; // Selects the pLeft of the new node
           newNode->pLeft = RightRot->pRight;  // selects the pRIght of rotating node
           if (RightRot->pRight != NULL)
              RightRot->pRight->pParent = newNode;
           RightRot->pParent = newNode->pParent;
           if (newNode->pParent == NULL)  // if the new node doesnt have a parent
              root = RightRot;           // make that rotated node the root
           // else check if newNode is the pRight of its parent
           else if (newNode == newNode->pParent->pRight)
              newNode->pParent->pRight = RightRot;
           else // else, we know we are the pLeft of pParent
              newNode->pParent->pLeft = RightRot;
           RightRot->pRight = newNode;
           newNode->pParent = RightRot;
        }
        
        void rotateLeft(BNode * newNode)
        {
           BNode* LeftRot = newNode->pRight; // Selects the pRight of the new node
           newNode->pRight = LeftRot->pLeft; // selects the pLeft of rotating node
           if (LeftRot->pLeft != NULL)
              LeftRot->pLeft->pParent = newNode;
           LeftRot->pParent = newNode->pParent;
           if (newNode->pParent == NULL) // if the new node doesnt have a parent
              root = LeftRot;            // make that rotated node the root
           // else check if newNode is the pLeft of its parent
           else if (newNode == newNode->pParent->pLeft)
              newNode->pParent->pLeft = LeftRot;
           else // else, we know we are the pRight of pParent
              newNode->pParent->pRight = LeftRot;
           LeftRot->pLeft = newNode;
           newNode->pParent = LeftRot;
		}

        // Methods for deleting a node/binary tree (parent and children)
        void deleteNode(BNode* pNode, bool right)
        {
            // Create a node, if right is true, pNext is equal to pNode's right child,
            // else pNext is equal to pNode's left child
            BNode* pNext = (right ? pNode->pRight : pNode->pLeft);

            // If pNode is not equal to root
            if (pNode != root)
            {
                // If the parent of left child is equal to pNode
                if (pNode->pParent->pLeft == pNode)
                {
                    // The parent of the left child is equal to pNext
                    pNode->pParent->pLeft = pNext;
                }
                else
                {
                    // The parent of the right child is equal to pNext
                    pNode->pParent->pRight = pNext;
                }
            }
            else
            {
                // Root node is equal to pNext
                root = pNext;
                // the pNext parent is set to NULL
                pNext->pParent = NULL;
            }

            // Delete pNode
            delete pNode;
            pNode = NULL;
        }
        void deleteBinaryTree(BNode* pNode)
        {
            if (pNode == NULL)
            {
                return;
            }

            // Delete all the children
            deleteBinaryTree(pNode->pLeft);
            deleteBinaryTree(pNode->pRight);

            // Delete pNode
            delete pNode;

            // Assign pNode to NULL
            pNode = NULL;
        }

        // Method for copying a binary tree
        BNode* copyBinaryTree(BNode* src)
        {
            if (src == NULL)
            {
                return NULL;
            }

            // Allocate a new node
            BNode* dest = new BNode(src->data);

            // Copy the left sub-trees
            dest->pLeft = copyBinaryTree(src->pLeft);
            if (dest->pLeft != NULL)
            {
                dest->pLeft->pParent = dest;
            }

            // Copy the right sub-trees
            dest->pRight = copyBinaryTree(src->pRight);
            if (dest->pRight != NULL)
            {
                dest->pRight->pParent = dest;
            }

            return dest;    // Return the copy node
        }

    };

    /**************************************************
    * BST:: copy constructor
    **************************************************/
    template <class T>
    BST<T>::BST(const BST<T>& rhs) throw(const char*)
    {
        try
        {
            // Copy root
            this->root = copyBinaryTree(rhs.root);
            // Copy numElements
            this->numElements = rhs.numElements;
        }
        catch (std::bad_alloc)
        {
            throw "ERROR: Unable to allocate a node";
        }
    }
   
    /**************************************************
    * BST:: erase()
    **************************************************/
    template <class T>
    void BST<T>::erase(iterator& it)
    {   // CASE 1 if it is a leaf
        if (it.p->pRight == NULL && it.p->pLeft == NULL)  
        {    // then investigate further
            // two if statements to know if it is the pLeft or pRight of pParent && not NULL
            if (it.p->pParent == NULL && it.p->pParent->pRight == it.p)
                it.p->pParent->pRight = NULL;  // Assign the pointers when removing a BNode 
            if(it.p->pParent!= NULL && it.p->pParent->pLeft == it.p) // to the correct BNodes
               it.p->pParent->pLeft = NULL;
            deleteNode (it.p, false);  // Delete

            return;
        }
        //  CASE 2 if the pLeft is a child
        if(it.p->pRight == NULL && it.p->pLeft != NULL)  
        {   // then investigate further
            it.p->pLeft->pParent = it.p->pParent;
            // two if statements to know if it is the pLeft or pRight of pParent && not NULL
            if (it.p->pParent != NULL && it.p->pParent->pRight == it.p)
                it.p->pParent->pRight = it.p->pLeft; // Assign the pointers when removing a BNode 
            if (it.p->pParent != NULL && it.p->pParent->pLeft == it.p) // to the correct BNodes
                it.p->pParent->pLeft = it.p->pLeft;

            deleteNode(it.p, false); // Delete

            return;
		  }  
        // CASE 2 if the pRight is a child
        if (it.p->pRight == NULL && it.p->pLeft != NULL)
        {   // then investigate further
            it.p->pLeft->pParent = it.p->pParent;
            // two if statements to know if it is the pLeft or pRight of pParent && not NULL
            if (it.p->pParent != NULL && it.p->pParent->pRight == it.p)  
                it.p->pParent->pRight = it.p->pRight;// Assign the pointers when removing a BNode
            if (it.p->pParent != NULL && it.p->pParent->pLeft == it.p) // to the correct BNodes
                it.p->pParent->pLeft = it.p->pRight;

            deleteNode(it.p, true);

            return;
        }
        // CASE 3 if there are two children
        else if( it.p->pRight != NULL && it.p->pLeft != NULL)
        {
            // New node is set equal to it.p 
            BNode* successor = it.p;

            // If right child of successor exists
            if (successor->pRight != NULL)
            {
                // Successor is equal to the right child of successor
                successor = successor->pRight;

                // While Left child exist
                while (successor->pLeft != NULL)
                {
                    // Successor is equal to its left child node
                    successor = successor->pLeft;
                }

                // "it.p"'s data is equal to successor's data
                it.p->data = successor->data;

                // Set left child equal to NULL
                successor->pParent->pLeft = NULL;

                // If successor's right child
                if (successor->pRight != NULL)
                {
                    // The parent of right child is the parent of successor
                    successor->pRight->pParent = successor->pParent;
                    // The parent of left child is the right child
                    successor->pParent->pLeft = successor->pRight;
                    // Set right child equal to NULL
                    successor->pRight=NULL;
                }

                // Delete successor and then set it equal to NULL
                delete successor;
                successor = NULL;
            }
        }
	 }

    /**************************************************
    * BST:: clear()
    **************************************************/
    template <class T>
    void BST<T>::clear()
    {
        // If there are any Elements
        if (numElements > 0)
        {
            // Delete them
            deleteBinaryTree(root);

            root = NULL;
        }

        // Zero out numElements
        numElements = 0;
    }

    /**************************************************
    * BST:: insert()
    **************************************************/
    template <class T>
    void BST<T>::insert(const T& t) throw (const char*)
    {
        try
	    {
		   // Allocate newNode
		   BNode* newNode = new BNode(t);

		   // If there aren't any elements
		   if (numElements == 0)
		   {
			   // Assign newNode to the root node
			   root = newNode;
			   // Increase numElements by one
			   numElements++;
			   root->setBlack();
			   return;
		   }
		   else
		   {
			   // Create a new node
			   BNode* pNext = root;

			   while (pNext)
			   {
				   // If t element is <= pNext data
				   if (t <= pNext->data)
				   {
					   // If the left child is NULL
					   if (pNext->pLeft == NULL)
					   {
						   // Left child is equal to newNode
						   pNext->pLeft = newNode;
						   // Parent is equal to pNext node
						   newNode->pParent = pNext;
						   // Set pNext equal to NULL
						   pNext = NULL;
					   }
					   else
					   {
						   // pNext is equal to the left child
						   pNext = pNext->pLeft;
					   }
				   }
				   else
				   {
					   // If the right child is NULL
					   if (pNext->pRight == NULL)
					   {
						   // Right child is equal to newNode
						   pNext->pRight = newNode;
						   // Parent is equal to pNext node
						   newNode->pParent = pNext;
						   // Set pNext equal to NULL
						   pNext = NULL;
					   }
					   else
					   {
						   // pNext is equal to the right child
						   pNext = pNext->pRight;
					   }
				   }
			   }
			
		   }

		   // Increae numElements by one
		   numElements++;

		
	       //redblack balancing
		
		   BNode* temp;
		   newNode->setRed();
		
         // while the parent of the new node is red rebalance
	       while(newNode != root && newNode->pParent->isRed == true)  
		    {
			   
			   if (newNode->pParent == newNode->pParent->pParent->pLeft)
			   {
				   temp = newNode->pParent->pParent->pRight;
				
				   //case 1
				   if(temp != NULL && temp->isRed == true)
				   {
					   newNode->pParent->setBlack();
					   temp->setBlack();
					   newNode->pParent->pParent->setRed();
					   newNode = newNode->pParent->pParent;
					
				   }
                   //case 2
				   else 
				   {
				       if(newNode == newNode->pParent->pRight)
				       {
					       newNode = newNode->pParent;
					       rotateLeft(newNode);
				       }
				    //case 3
				       newNode->pParent->setBlack();
				       newNode->pParent->pParent->setRed();
				       rotateRight(newNode->pParent->pParent);
					
	
				   }
	
			   }
               //case 4
			   else
			   {
				   temp = newNode->pParent->pParent->pLeft;
				   if(temp != NULL && temp->isRed == true)
				   {
					   newNode->pParent->setBlack();
					   temp->setBlack();
					   newNode->pParent->pParent->setRed();
					   newNode = newNode->pParent->pParent;
					
				   }
                   //case 5
				   else 
				   {
	   		         if(newNode == newNode->pParent->pLeft)
			         {
				         newNode = newNode->pParent;
				         rotateRight(newNode);	
				      }
                      //case 6
					   newNode->pParent->setBlack();
					   newNode->pParent->pParent->setRed();
					   rotateLeft(newNode->pParent->pParent);
				   }		
			   }
		    }
		    root->setBlack();

		    // if the root moved out from under us, find it again.
		    while (root->pParent != NULL)
			   root = root->pParent;	   
	    }
       catch (const std::bad_alloc)
       {
          throw "ERROR: Unable to allocate a node";
       }
    }

    /**************************************************
    * BST :: Assignment Operator
    **************************************************/
    template <class T>
    BST<T>& BST<T>::operator=(const BST<T>& rhs) throw(const char*)
    {
        // Copy root
        this->root = this->copyBinaryTree(rhs.root);
        // copy numElements
        this->numElements = rhs.numElements;

        // Return the copy
        return *this;
    }

    /**************************************************
    * Iterator
    **************************************************/
    template <class T>
    class BST<T> ::iterator
    {
    public:
        // Constructors, destructors, and assignment operator
        iterator() : p(NULL) {}
        iterator(BNode* p) : p(p) { this->p = p; }
        iterator(const iterator & rhs) { *this = rhs; }
        iterator & operator = (const iterator & rhs)
        {
            p = rhs.p;
            return *this;
        }

         
        // equals, not equals operator
        bool operator != (const iterator & rhs) const { return rhs.p != this->p; }
        bool operator == (const iterator & rhs) const { return rhs.p == this->p; }

        // dereference operators
        T & operator * ()       
        { 
            if (p != NULL)
                return p->data; 
            else
                throw "ERROR: Cannot dereference NULL pointer";
        }
        const T & operator * () const 
        { 
            if (p != NULL)
                return p->data; 
            else
                throw "ERROR: Cannot dereference NULL pointer";
        }

        iterator& operator --();                // Prefix Decrement
        iterator& operator --(int postfix);     // Postfix Decrement
        iterator& operator ++();                // Prefix Increment
        iterator& operator ++(int postfix);     // Postfix Increment


        BNode* p;
    };

    /**************************************************
    * BST:: find()
    **************************************************/
    template <class T>
    typename BST<T>::iterator BST<T>::find(const T& t)
    {
        iterator it = begin();
        
        while(it != end())
        {
            if(*it == t)
                return it;
            ++it;
        }

        return end();
    }

    /**************************************************
    * BST :: begin()
    **************************************************/
    template <class T>
    typename BST<T>::iterator BST<T>::begin()
    {
        // If root is not NULL
        if (root != NULL)
        {
            // Create a left node
            BNode* leftNode = root;

            // While leftNode is not NULL
            while (leftNode->pLeft)
            {
                // leftNode is equal to the node to its left
                leftNode = leftNode->pLeft;
            }
            // Return iterator to the first node of the binary tree
            return iterator(leftNode);
        }
        else
        {
            // Return iterator
            return iterator();
        }
    }


    /**************************************************
    * BST ITERATOR :: DECREMENT PREFIX
    *     advance by one. 
    * Author:      Br. Helfrich
    * Performance: O(log n) though O(1) in the common case
    *************************************************/
   template <class T>
   typename BST <T> :: iterator & BST <T> :: iterator :: operator -- ()
   {
      // do nothing if we have nothing
      if (NULL == p)
         return *this;

      // if there is a left node, take it
      if (NULL != p->pLeft)
      {
         // go left
         p = p->pLeft;

         // jig right - there might be more right-most children
         while (p->pRight)
            p = p->pRight;
         return *this;
      }

      // there are no left children, the right are done
      assert(NULL == p->pLeft);
      BNode * pSave = p;

      // go up
      p = p->pParent;

      // if the parent is the NULL, we are done!
      if (NULL == p)
         return *this;

      // if we are the right-child, got to the parent.
      if (pSave == p->pRight)
         return *this;

      // we are the left-child, go up as long as we are the left child!
      while (NULL != p && pSave == p->pLeft)
      {
         pSave = p;
         p = p->pParent;
      }

      return *this;
   }

   /**************************************************
    * BST ITERATOR :: DECREMENT POSTFIX
    *     advance by one. 
    *************************************************/
   template <class T>
   typename BST <T> :: iterator & BST <T> :: iterator :: operator -- (int postfix)
   {
	 iterator tmp(*this);

	 // do nothing if we have nothing
      if (NULL == p)
         return tmp;

      // if there is a left node, take it
      if (NULL != p->pLeft)
      {
         
		 // go left
         p = p->pLeft;

         // jig right - there might be more right-most children
         while (p->pRight)
            p = p->pRight;
         return tmp;
      }

      // there are no left children, the right are done
      assert(NULL == p->pLeft);
      BNode * pSave = p;

      // go up
      p = p->pParent;

      // if the parent is the NULL, we are done!
      if (NULL == p)
         return tmp;

      // if we are the right-child, got to the parent.
      if (pSave == p->pRight)
         return tmp;

      // we are the left-child, go up as long as we are the left child!
      while (NULL != p && pSave == p->pLeft)
      {
         pSave = p;
         p = p->pParent;
      }

      return tmp;  
	}

   /**************************************************
    * BST ITERATOR :: INCREMENT PREFIX
    *     advance by one. 
    *************************************************/
   template <class T>
   typename BST <T> ::iterator& BST <T> ::iterator :: operator ++ ()
   {
   //fixed increment method because old one cause errors with map    
   BNode* pParent;
    
      if (p != NULL) // only call this if p does not point to null, if it does return
      {
            if (p->pRight != NULL)  
            {
                p = p->pRight;
        
                while (p->pLeft != NULL) // go to the farthest left of the right subtree
                {
                    p = p->pLeft;
                }
            }
            else
            {
                pParent = p->pParent;
                while (pParent != NULL && p == pParent->pRight) //go to the parent until it is NULL
                {
                    p = pParent;
                    pParent = pParent->pParent;
                }
            p = pParent;
            }
      
      }
     
     
    
      
      return *this;
   }


   /**************************************************
   * BST ITERATOR :: INCREMENT POSTFIX
   *     advance by one. 
   *************************************************/
   template <class T>
   typename BST <T> ::iterator& BST <T> ::iterator :: operator ++ (int postfix)
   {
      
   //this does have some issues but isn't used so was left unchanged

	  iterator tmp(*this);
      //if there is a right child
	  if(p->pRight) 
     {
          
		  p = p->pRight;
          while(p->pLeft)
          {
                p = p->pLeft;
          }
          return tmp;
     }
      //if there is no right child and we are left
      if(p->pRight == NULL && p->pParent->pLeft == p)
      {
          
		  p = p->pParent;
		  return tmp;
      }
      //no right child and we are right
      if(p->pRight == NULL && p->pParent->pRight == p)
      {
            
			while (p->pParent != NULL && p->pParent->pRight == p)
				p = p->pParent;
            p = p->pParent;
			return tmp;
      }        
   }




    
   /**************************************************
   * BNode
   **************************************************/
   template <class T>
   class BST<T>::BNode
   {
      private:
         BNode* currentNode;

         
         
         void verifyRB(int depth)
         {
		 }

         void verifyBST()
         {

		 }
        
        
      public:  
         T data;

         BNode * pLeft;
         BNode * pRight;
         BNode * pParent;

         void setBlack() {    isRed = false;   }
         void setRed() {    isRed = true;     }
         void setLeft(BNode* currnetNode) { this->pLeft = currentNode; }
         void setRight(BNode * currentNode){ this->pRight = currentNode; }
        
         bool isRed;

         

         // Both are set to default to red = true, not sure what the right one is
         BNode() { pLeft = NULL; pRight = NULL; pParent = NULL; isRed = true; }
         BNode(T t) { data = t; pLeft = NULL; pRight = NULL; pParent = NULL; isRed = true; }

         
   };
}; // namespace custom END

#endif // BST_H
