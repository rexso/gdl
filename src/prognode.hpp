/***************************************************************************
                          prognode.hpp  -  the node used for the running program
                             -------------------
    begin                : July 22 2002
    copyright            : (C) 2002 by Marc Schellens
    email                : m_schellens@users.sf.net
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef prognode_hpp__
#define prognode_hpp__

#include "dnode.hpp"

//#include "GDLInterpreter.hpp"

    enum RetCode {
        RC_OK=0,
        RC_BREAK,
        RC_CONTINUE,
        RC_RETURN, 
        RC_ABORT, // checked as retCode >= RC_RETURN
    };

class ProgNode;
typedef ProgNode* ProgNodeP;

class BreakableNode;

// the nodes the programs are made of
class ProgNode
{
protected:
  static DInterpreter* interpreter;

private:
  int ttype;
  std::string text;

protected:
  bool keepRight;

  ProgNodeP breakTarget;
  
  ProgNodeP down;
  ProgNodeP right;

  static void AdjustTypes(std::auto_ptr<BaseGDL>& a, 
			  std::auto_ptr<BaseGDL>& b);

  BaseGDL*   cData;           // constant data
  DVar*      var;             // ptr to variable 

  DLibFun*   libFun;
  DLibPro*   libPro;

  union {
    int        initInt;    // for c-i not actually used
    int        numBranch;  // number of branches in switch/case statements
    int        nDot;       // nesting level for tag access
    int        arrayDepth; // dimension to cat
    int        proIx;      // Index into proList
    int        funIx;      // Index into funList
    int        varIx;      // Index into variable list
    int        targetIx;   // Index into label list
    int        structDefined; // struct contains entry with no tag name
    int        compileOpt; // for PRO and FUNCTION nodes
  };

private:
  // from DNode (see there)
  int lineNumber;
  ArrayIndexListT* arrIxList; // ptr to array index list
  int labelStart; // for loops to determine if to bail out
  int labelEnd; // for loops to determine if to bail out

  // disable usage
  ProgNode( const ProgNode& p) {}

public:
  ProgNode();

  ProgNode( const RefDNode& refNode);

  static ProgNodeP NewProgNode( const RefDNode& refNode);

  virtual ~ProgNode();
  
  void SetNodes( const ProgNodeP right, const ProgNodeP down);

  virtual BaseGDL* Eval();
  virtual BaseGDL* EvalNC(); // non-copy
  virtual void     Run();

  bool ConstantNode();

  ProgNodeP getFirstChild() const
  {
    return down;
  }
  ProgNodeP GetFirstChild() const
  {
    return getFirstChild();
  }
  void SetFirstChild( ProgNodeP d)
  {
    down = d;
  }
  ProgNodeP getNextSibling() const
  {
    return right;
  }
  ProgNodeP GetLastSibling() const
  {
	ProgNodeP act = const_cast<ProgNodeP>(this);
	while(!act->KeepRight() && act->GetNextSibling() != NULL) act = act->GetNextSibling();
    return act;
  }
  ProgNodeP GetNextSibling() const
  {
    return getNextSibling();
  }
  void SetNextSibling( ProgNodeP r)
  {
    right = r;
  }

  ProgNodeP StealNextSibling()
  {
    ProgNodeP n = right;
    right = NULL;
    return n;
  }
  ProgNodeP StealFirstChild()
  {
    ProgNodeP n = down;
    down = NULL;
    return n;
  }

  bool KeepRight() const { return keepRight;}
  
  virtual void KeepRight( ProgNodeP r)
  {
//   if( right != NULL)
	//assert( right == NULL);
	//assert( r != NULL);
	right = r;
	keepRight = true;
// if( r != NULL)
// std::cout << "KeepRight: " << getText() <<"   r: " << r->getText() <<  std::endl;
// else
// std::cout << "KeepRight: " << getText() <<"   r: NULL" <<  std::endl;
  }
  void SetRight( ProgNodeP r)
  {
	assert( right == NULL);
	right = r;
  }
  
	void SetAllBreak( ProgNodeP target)
	{
		if( this->getType() == GDLTokenTypes::BREAK)
			breakTarget = target;
		else
		{
			if( down != NULL)
				{
					down->SetAllBreak( target);
				}
		}
		
		if( right != NULL && !keepRight)
		{
			right->SetAllBreak( target);
		}
	}

  int getType() { return ttype;}
  void setType( int t) { ttype=t;}
  std::string getText() { return text;}
  void setText(const std::string t) { text = t;}
  int getLine() const { return lineNumber;}
  void setLine( int l) { lineNumber = l;}
  void SetGotoIx( int ix) { targetIx=ix;}

  ProgNodeP BreakTarget() const { return breakTarget;}
  
  bool LabelInRange( const int lIx)
  {
// 	std::cout << "LabelInRange: " << ((lIx >= labelStart) && (lIx < labelEnd)) << "     " << lIx << "   [" << labelStart << "," << labelEnd << ")" << std::endl;
	return (lIx >= labelStart) && (lIx < labelEnd);
  }
  
  friend class GDLInterpreter;
  friend class DInterpreter;

friend class NSTRUCNode;
friend class ASSIGNNode;
friend class ASSIGN_REPLACENode;
friend class PCALL_LIBNode;//: public CommandNode
friend class MPCALLNode;//: public CommandNode
friend class MPCALL_PARENTNode;//: public CommandNode
friend class PCALLNode;//: public CommandNode

  friend class KEYDEF_Node;
  friend class KEYDEF_REFNode;
  friend class KEYDEF_REF_CHECKNode;
  friend class KEYDEF_REF_EXPRNode;
  friend class REFNode;
  friend class REF_CHECKNode;
  friend class REF_EXPRNode;
  friend class ParameterNode;

};



class DefaultNode: public ProgNode
{
public:
  DefaultNode(): ProgNode()  {}  

  DefaultNode( const RefDNode& refNode): ProgNode( refNode) 
  {
    if( refNode->GetFirstChild() != RefDNode(antlr::nullAST))
      {
	down = NewProgNode( refNode->GetFirstChild());
      }
    if( refNode->GetNextSibling() != RefDNode(antlr::nullAST))
      {
	right = NewProgNode( refNode->GetNextSibling());
      }
  }
};



class BreakableNode: public ProgNode
{
protected:
	void SetAllBreak( ProgNodeP target)
	{
		// down: do NOT descent into own loop tree here
		
		if( right != NULL && !keepRight)
		{
				right->SetAllBreak( target);
		}
	}

public:
  BreakableNode(): ProgNode()  {}

  BreakableNode( const RefDNode& refNode): ProgNode( refNode)
  {
    if( refNode->GetFirstChild() != RefDNode(antlr::nullAST))
      {
		down = NewProgNode( refNode->GetFirstChild());
      }
    if( refNode->GetNextSibling() != RefDNode(antlr::nullAST))
      {
		right = NewProgNode( refNode->GetNextSibling());
      }
  }
};



class FORNode: public BreakableNode
{
  public:
  FORNode(): BreakableNode()  {}

  FORNode( const RefDNode& refNode): BreakableNode( refNode)
  {}
};



class FOR_STEPNode: public BreakableNode
{
  public:
  FOR_STEPNode(): BreakableNode()  {}

  FOR_STEPNode( const RefDNode& refNode): BreakableNode( refNode)
  {}
};



class FOREACHNode: public BreakableNode
{
  public:
  FOREACHNode(): BreakableNode()  {}

  FOREACHNode( const RefDNode& refNode): BreakableNode( refNode)
  {}
};



class WHILENode: public BreakableNode
{
  public:
  WHILENode(): BreakableNode()  {}

  WHILENode( const RefDNode& refNode): BreakableNode( refNode)
  {}
};



class REPEATNode: public BreakableNode
{
  public:
  REPEATNode(): BreakableNode()  {}

  REPEATNode( const RefDNode& refNode): BreakableNode( refNode)
  {}
};



class CASENode: public BreakableNode
{
	ProgNodeP GetStatementList()
	{
		return down->GetNextSibling();
	}
	
	void KeepRight( ProgNodeP r)
	{
		assert( down != NULL);
		right = r;
		keepRight = true;
		// down is expr
		ProgNodeP csBlock = GetStatementList();
		while( csBlock != NULL)
		{
			if( csBlock->getType() == GDLTokenTypes::ELSEBLK)
				{
					ProgNodeP statementList = csBlock->GetFirstChild();
					if( statementList != NULL)
					{
							statementList->GetLastSibling()->KeepRight( right);
					}
				}
			else
				{
					// keep expr in case of empty statement
					ProgNodeP statementList = csBlock->GetFirstChild()->GetNextSibling();
					if( statementList != NULL)
					{
							statementList->GetLastSibling()->KeepRight( right);
					}
				}
			csBlock = csBlock->GetNextSibling();
		}
		GetStatementList()->SetAllBreak( right);
	}

public:
  CASENode(): BreakableNode()  {}

  CASENode( const RefDNode& refNode): BreakableNode( refNode)
  {
    assert( down != NULL);
	
	ProgNodeP statementList = this->GetStatementList();
	statementList->SetAllBreak( right);

    // down is expr
    ProgNodeP csBlock = GetStatementList();

	while( csBlock != NULL)
	{
		if( csBlock->getType() == GDLTokenTypes::ELSEBLK)
			{
				ProgNodeP statementList = csBlock->GetFirstChild();
				if( statementList != NULL)
				{
						statementList->GetLastSibling()->KeepRight( right);
				}
			}
		else
			{
				// keep expr in case of empty statement
				ProgNodeP statementList = csBlock->GetFirstChild()->GetNextSibling();
				if( statementList != NULL)
				{
						statementList->GetLastSibling()->KeepRight( right);
				}
			}
		
// 		if( csBlock->GetNextSibling() == NULL)
// 		{
// 				csBlock->KeepRight( right);
// 				break;
// 		}
		
		csBlock = csBlock->GetNextSibling();
	}
  }
};



class SWITCHNode: public BreakableNode
{
	ProgNodeP GetStatementList()
	{
		return down->GetNextSibling();
	}

  void KeepRight( ProgNodeP r)
  {
	right = r;
	keepRight = true;
    ProgNodeP csBlock = GetStatementList();
	ProgNodeP lastStatementList = NULL;
	while( csBlock != NULL)
	{
		if( csBlock->getType() == GDLTokenTypes::ELSEBLK)
			{
				ProgNodeP statementList = csBlock->GetFirstChild();
				if( statementList != NULL)
				{
					lastStatementList = statementList;
				}
			}
		else
			{
				// keep expr in case of empty statement
				ProgNodeP statementList = csBlock->GetFirstChild()->GetNextSibling();
				if( statementList != NULL)
				{
					lastStatementList = statementList;
				}
			}
		csBlock = csBlock->GetNextSibling();
	}
	if( lastStatementList != NULL)
		lastStatementList->GetLastSibling()->KeepRight( right);
	GetStatementList()->SetAllBreak( right);
 } 
	
public:
  SWITCHNode(): BreakableNode()  {}

  SWITCHNode( const RefDNode& refNode): BreakableNode( refNode)
  {
    assert( down != NULL);

	ProgNodeP statementList = this->GetStatementList();
	statementList->SetAllBreak( right);
 
    // down is expr
    ProgNodeP csBlock = GetStatementList();

	ProgNodeP lastStatementList = NULL;

	while( csBlock != NULL)
	{
		if( csBlock->getType() == GDLTokenTypes::ELSEBLK)
			{
				ProgNodeP statementList = csBlock->GetFirstChild();
				if( statementList != NULL)
				{
					if( lastStatementList != NULL)
						lastStatementList->GetLastSibling()->KeepRight( statementList);
						
					lastStatementList = statementList;
				}
			}
		else
			{
				// keep expr in case of empty statement
				ProgNodeP statementList = csBlock->GetFirstChild()->GetNextSibling();
				if( statementList != NULL)
				{
					if( lastStatementList != NULL)
						lastStatementList->GetLastSibling()->KeepRight( statementList);
						
					lastStatementList = statementList;
				}
			}
		if( csBlock->GetNextSibling() == NULL)
		{
				if( lastStatementList != NULL)
					lastStatementList->GetLastSibling()->KeepRight( right);
				break;
		}
		csBlock = csBlock->GetNextSibling();
	}
  }

};



class BLOCKNode: public ProgNode
{
  void KeepRight( ProgNodeP r)
  {
//  	if( r == NULL)
//   	assert( r != NULL);

//  	if( r == NULL)
// 		return;
		
// diconnection of s1 leads to right != NULL		
// 	if( right != NULL)
// 		assert( right != NULL);
	// 	must recursively set dependents here
     if( down != NULL)
		down->GetLastSibling()->KeepRight( r);

// if( r != NULL)
// std::cout << "BLOCK KeepRight("<<getLine()<<"): " << getText() <<"   r: " << r->getText() <<  std::endl;
// 	else
// std::cout << "BLOCK KeepRight("<<getLine()<<"): " << getText() <<"   r: NULL" <<  std::endl;
	
	right = r;
	keepRight = true;
 }

public:
  BLOCKNode(): ProgNode()  {}

  BLOCKNode( const RefDNode& refNode): ProgNode( refNode)
  {
    if( refNode->GetFirstChild() != RefDNode(antlr::nullAST))
      {
		down = NewProgNode( refNode->GetFirstChild());
      }
    if( refNode->GetNextSibling() != RefDNode(antlr::nullAST))
      {
		right = NewProgNode( refNode->GetNextSibling());
     
		// first statement
		if( down != NULL)
			down->GetLastSibling()->KeepRight( right);
      }
  }

};



class IFNode: public ProgNode
{
  void KeepRight( ProgNodeP r)
  {
// 	assert( r != NULL);
// 	assert( right == NULL);
	
	// 	must recursively set dependents here
    if( down != NULL && r != NULL)
        {
// 			ProgNodeP s1 = down->GetNextSibling(); // skip expr
			right = r;
			down->GetLastSibling()->KeepRight( right);
			keepRight = true;
        }
  }
public:
  IFNode(): ProgNode()  {}

  IFNode( const RefDNode& refNode): ProgNode( refNode)
  {
		if( refNode->GetFirstChild() != RefDNode(antlr::nullAST))
		{
			down = NewProgNode( refNode->GetFirstChild());
		}
		if( refNode->GetNextSibling() != RefDNode(antlr::nullAST))
		{
			right = NewProgNode( refNode->GetNextSibling());
		}

        // first alternative
        if( down != NULL && right != NULL)
        {
			ProgNodeP s1 = down->GetNextSibling(); // skip expr
			s1->GetLastSibling()->KeepRight( right);
        }
  }
};



class IF_ELSENode: public ProgNode
{
  void KeepRight( ProgNodeP r)
  {
//   	assert( r != NULL);
// 	assert( right == NULL);

// if( r != NULL)
// std::cout << "IF_ELSE KeepRight: " <<right<<"   " << getText() <<"   r: " << r->getText() <<  std::endl;
// else
// std::cout << "IF_ELSE KeepRight: " <<right<<"   " << getText() <<"   r: NULL"  <<  std::endl;
	
	// 	must recursively set dependents here
    if( down != NULL && r != NULL)
        {
			//IF expr s1 s2
			// first alternative
			ProgNodeP s1 = down->GetNextSibling(); // skip expr
			// 2nd alternative
			ProgNodeP s2 = s1->GetNextSibling();
			
//         s1->ProgNode::KeepRight( right); // disconnect s2
        s1->KeepRight( r); // disconnect s2
			
		s2->GetLastSibling()->SetRight( r);
	//         s2->KeepRight( right);

		right = s2;
        }
  }

public:
  IF_ELSENode(): ProgNode()  {}

  IF_ELSENode( const RefDNode& refNode): ProgNode( refNode)
  {
    if( refNode->GetFirstChild() != RefDNode(antlr::nullAST))
      {
	down = NewProgNode( refNode->GetFirstChild());
      }
    if( refNode->GetNextSibling() != RefDNode(antlr::nullAST))
      {
	right = NewProgNode( refNode->GetNextSibling());
      }

    assert( down != NULL);
        
        {
			//IF expr s1 s2
			// first alternative
			ProgNodeP s1 = down->GetNextSibling(); // skip expr
			// 2nd alternative
			ProgNodeP s2 = s1->GetNextSibling();
			
         s1->KeepRight( right); // disconnect s2
			
    	s2->GetLastSibling()->SetRight( right);
	//         s2->KeepRight( right);

		right = s2;
        }
  }
};

//#undef UNDEF
//#ifdef UNDEF
class EnvBaseT;

class ParameterNode: public DefaultNode
{
public:
  ParameterNode( const RefDNode& refNode): DefaultNode( refNode) {}
  virtual void Parameter( EnvBaseT* actEnv);
};

class KEYDEF_REFNode: public ParameterNode
{
public:
  KEYDEF_REFNode( const RefDNode& refNode): ParameterNode( refNode) {}
  void Parameter( EnvBaseT* actEnv);
};

class KEYDEF_REF_EXPRNode: public ParameterNode
{
public:
  KEYDEF_REF_EXPRNode( const RefDNode& refNode): ParameterNode( refNode) {}
  void Parameter( EnvBaseT* actEnv);
};

class KEYDEF_REF_CHECKNode: public ParameterNode
{
public:
  KEYDEF_REF_CHECKNode( const RefDNode& refNode): ParameterNode( refNode) {}
  void Parameter( EnvBaseT* actEnv);
};

class KEYDEFNode: public ParameterNode
{
public:
  KEYDEFNode( const RefDNode& refNode): ParameterNode( refNode) {}
  void Parameter( EnvBaseT* actEnv);
};

class REF_EXPRNode: public ParameterNode
{
public:
  REF_EXPRNode( const RefDNode& refNode): ParameterNode( refNode) {}
  void Parameter( EnvBaseT* actEnv);
};

class REF_CHECKNode: public ParameterNode
{
public:
  REF_CHECKNode( const RefDNode& refNode): ParameterNode( refNode) {}
  void Parameter( EnvBaseT* actEnv);
};

class REFNode: public ParameterNode
{
public:
  REFNode( const RefDNode& refNode): ParameterNode( refNode) {}
  void Parameter( EnvBaseT* actEnv);
};



class CommandNode: public DefaultNode
{
public:
  CommandNode( const RefDNode& refNode): DefaultNode( refNode) {}
};
class ASSIGNNode: public CommandNode
{
public:
  ASSIGNNode( const RefDNode& refNode): CommandNode( refNode) {}
  void Run();
};
class ASSIGN_ARRAYEXPR_MFCALLNode: public CommandNode
{
public:
  ASSIGN_ARRAYEXPR_MFCALLNode( const RefDNode& refNode): CommandNode( refNode) {}
  void Run();
};
class ASSIGN_REPLACENode: public CommandNode
{
public:
  ASSIGN_REPLACENode( const RefDNode& refNode): CommandNode( refNode) {}
  void Run();
};
class PCALL_LIBNode: public CommandNode
{
public:
  PCALL_LIBNode( const RefDNode& refNode): CommandNode( refNode) {}
  void Run();
};
class MPCALLNode: public CommandNode
{
public:
  MPCALLNode( const RefDNode& refNode): CommandNode( refNode) {}
  void Run();
};
class MPCALL_PARENTNode: public CommandNode
{
public:
  MPCALL_PARENTNode( const RefDNode& refNode): CommandNode( refNode) {}
  void Run();
};
class PCALLNode: public CommandNode
{
public:
  PCALLNode( const RefDNode& refNode): CommandNode( refNode) {}
  void Run();
};
class DECNode: public CommandNode
{ public:
  DECNode( const RefDNode& refNode): CommandNode( refNode){}
  void Run();
};
class INCNode: public CommandNode
{ public:
  INCNode( const RefDNode& refNode): CommandNode( refNode){}
  void Run();
};
// class FOR_INITNode: public CommandNode
// { public:
//   FOR_INITNode( const RefDNode& refNode): CommandNode( refNode){}
//   void Run();
// };
// class FORNode: public CommandNode
// { public:
//   FORNode( const RefDNode& refNode): CommandNode( refNode){}
//   void Run();
// };
// class FOR_STEPNode: public CommandNode
// { public:
//   FOR_STEPNode( const RefDNode& refNode): CommandNode( refNode){}
//   void Run();
// };


// class ARRAYDEFNode: public CommandNode
// {
// public:
//   /*virtual*/ RetCode   Run();
// 
// };
//#endif

#endif
