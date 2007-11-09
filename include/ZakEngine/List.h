#ifndef _LIST_H_
#define _LIST_H_

#include <windows.h>
#include <memory.h>
#include "ZakEngine/defines.h"
#include "ZakEngine/Node.h" 


namespace zak {

template <class LIST_TYPE>

// Doubly linked list 
class ZAKENGINE_API List 
{
public:
	// Get Previous Node of a certain Node
	Node<LIST_TYPE> *Previous(Node<LIST_TYPE> *pNode) 
	{
		if (pNode) {
			if (pNode->GetPreviousNode() != NULL)
				return (m_pActualNode = pNode->GetPreviousNode());
			else
				return NULL;
		} else
			return NULL;
	}

	// Move to the next node
	Node<LIST_TYPE> *Next(Node<LIST_TYPE> *pNode) 
	{
		if (pNode) {
			if (pNode->GetNextNode() != NULL)
				return (m_pActualNode = pNode->GetNextNode());
			else
				return NULL;
		} else
			return NULL;
	}

	// Move the m_pActualNode to the first position
	void MoveToFirst(void)
	{
		m_pActualNode = m_pFirstNode;
	}

	// Move the m_pActualNode to the last position
	void MoveToLast(void)
	{
		m_pActualNode = m_pLastNode;
	}

	bool MoveToNext(void) 
	{
		if (m_pActualNode = Next(m_pActualNode))
			return true;
		else
			return false;
	}

	bool MoveToPrevious(void) 
	{
		if (m_pActualNode = Previous(m_pActualNode))
			return true;
		else
			return false;
	}


	// search for an element
	bool SearchForElement(const LIST_TYPE &Element)
	{
		Node<LIST_TYPE> *pNode = m_pFirstNode;
		while (pNode != NULL) {
			if (pNode->GetElement() == Element) {
				m_pActualNode = pNode;
				return true;
			}
			pNode = pNode->GetNextNode();
		}
		return false;
	}

	// insert a Node Next to m_pActualNode, use zakSearchForElement
	// to find the Node.
	bool InsertCurrent(const LIST_TYPE &Element)
	{
		Node<LIST_TYPE> *pNode, *pTmp;

		pNode = new Node<LIST_TYPE>;
		if (pNode != NULL) { 
			if (m_pActualNode != NULL) {
				pNode->SetNextNode(m_pActualNode->GetNextNode());
				pNode->SetPreviousNode(m_pActualNode);
				pNode->SetElement(Element);
				pTmp = m_pActualNode->GetNextNode();
				if (pTmp != NULL) pTmp->SetPreviousNode(pNode);
				m_pActualNode->SetNextNode(pNode);
				m_lCount++;
				return true;
			}
			else {
				if (InsertFront(Element)) {
					m_pFirstNode = pNode;
					return true;
				}
				else
					return false;
			}
		}
		else
			return false;
	}

	// delete the Node in the m_pActualNode position in the list,
	// use zakSearchForElement before to find the Node
	// at the end m_pActualNode = NULL, you're warned.
	bool DeleteCurrent(void)
	{
		Node<LIST_TYPE> *pNextNode, *pPrevNode;
		if (m_pActualNode != NULL) {
			pNextNode = m_pActualNode->GetNextNode();
			pPrevNode = m_pActualNode->GetPreviousNode();
			if (pNextNode != NULL)
				pNextNode->SetPreviousNode(pPrevNode);
			else
				m_pLastNode = pPrevNode;
			if (pPrevNode != NULL)
				pPrevNode->SetNextNode(pNextNode);
			else
				m_pFirstNode = pNextNode;
			m_pActualNode->SetNextNode(NULL);
			delete m_pActualNode;
			m_pActualNode = NULL;
			m_lCount--;
			return true;
		}
		return false;
	}

	// Insert an element to the front
	bool InsertFront(const LIST_TYPE &Element)
	{
		Node<LIST_TYPE> *pNode;

		pNode = new Node<LIST_TYPE>;

		if (pNode != NULL) {
			pNode->SetNextNode(m_pFirstNode);
			pNode->SetElement(Element);
			if (m_pFirstNode != NULL) 
				m_pFirstNode->SetPreviousNode(pNode);
			
			if (IsEmpty()) m_pLastNode = pNode;
			
			
			m_pFirstNode = pNode;
			m_lCount++;
			return true;
		} 
		else 
			return false;
	}

	// Insert an element to the back
	bool zakInsertBack (const LIST_TYPE &Element)
	{
		Node<LIST_TYPE> *pNode;

		pNode = new Node<LIST_TYPE>;

		if (pNode != NULL) {
			pNode->SetNextNode(NULL);
			pNode->SetPreviousNode(m_pLastNode);
			pNode->SetElement(Element);

			if (IsEmpty()) {
				m_pFirstNode = pNode;
				m_pLastNode = pNode;
			} else {
				m_pLastNode->SetNextNode(pNode);
				m_pLastNode = pNode;
			}
			
			m_lCount++;
			return true;
		} 
		else
			return false;
	}

	// Extract the first element from the list
	bool ExtractFront(LIST_TYPE &Element)
	{
		Node<LIST_TYPE> *pNode;

		if (!IsEmpty()) {
			Element = m_pFirstNode->GetElement();
			pNode = m_pFirstNode;
			m_pFirstNode = m_pFirstNode->GetNextNode();
			
			if (m_pFirstNode)
				m_pFirstNode->SetPreviousNode(NULL);

			pNode->SetNextNode(NULL);

			delete pNode;

			m_lCount--;

			if (IsEmpty()){
				m_pFirstNode = NULL;
				m_pLastNode = NULL;
			}
			return true;
		} 
		else
			return false;
	}

	// Extract the last element from the list
	bool ExtractBack(LIST_TYPE &Element)
	{
		Node<LIST_TYPE>  *pNode;

		if (!IsEmpty()) {
			Element = m_pLastNode->GetElement();

			pNode = m_pLastNode->GetPreviousNode();

			if (pNode != NULL)
				pNode->SetNextNode(NULL);
			
			delete m_pLastNode;

			m_lCount--;

			if (IsEmpty()) {
				m_pFirstNode = NULL;
				m_pLastNode = NULL;
			} else
				m_pLastNode = pNode;

			return true;
		} else
			return false;
	}

	// Get Count of elements
	long GetCount()
	{
		return m_lCount;
	}

	// Return if the list is empty
	bool IsEmpty()
	{
		return (GetCount() == 0);
	}

	// Delete all Nodes
	void Clear()
	{
		if (m_pFirstNode != NULL) 
			delete m_pFirstNode;
		m_pFirstNode = NULL;
		m_pLastNode = NULL;
		m_lCount = 0;
	}

	
	// Return the first element
	bool GetFirst(LIST_TYPE &Element)
	{
		if (m_pFirstNode != NULL) {
			Element = m_pFirstNode->GetElement();
			return true;
		} else 
			return false;
	}		

	// Return the current element from m_pActualNode
	bool GetCurrent(LIST_TYPE &Element)
	{
		if (m_pActualNode != NULL) {
			Element = m_pActualNode->GetElement();
			return true;
		}
		else
			return false;
	}

	// Return the Last Element
	bool GetLast(LIST_TYPE &Element)
	{
		if (m_pLastNode != NULL) {
			Element = m_pLastNode->GetElement();
			return true;
		} else 
			return false;
	}

	// Constructor
	List()
	{
		m_lCount = 0;
		m_pFirstNode = NULL;
		m_pLastNode = NULL;
	}

	// Destructor
	~List()
	{
		if (m_pFirstNode != NULL) 
			delete m_pFirstNode;
	}

private:
	Node<LIST_TYPE> *m_pFirstNode;	 // pointer lo first
	Node<LIST_TYPE> *m_pLastNode;	 // pointer to last
	Node<LIST_TYPE> *m_pActualNode; // pointer to actual node
	long m_lCount;					 // Node Count

};

} // end namespace

#endif // _LIST_H_