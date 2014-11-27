#ifndef PARSERCLASSES_H_
#define PARSERCLASSES_H_
/*
All code written by :
Jason Liu 301224956
Daryl Seah 301222124

Modified by:
Choong Jin Ng 301226977
Steven Luu    301150253
*/

// Last edited: 25 Nov 2014, 9.34pm

//Use only the following libraries:
#include <string>
#include "lexemesTypes.h"

using namespace std;

//Declare your variables for storing delimiters here:

//typedef for custom data type defined in header file "lexemesTypes.h"
typedef ensc251::LexemeType TokenClass;

//Token class for a doubly-linked list of string tokens
class Token

{
private:
	Token *next; //Next pointer for doubly linked list
	Token *prev; //Previous pointer for doubly linked list
	string stringRep; //Token value
    TokenClass stringClass; //Token class (to which class this token belongs to, for e.g. identifier, keywords...etc)
	string stringType; // Under class, what type of string is it (e.g int, bool, class, union)
    TokenClass identifier_value; //type of identifier --- Jin: StringType is suppose to do this. Also, we may have to check for class, unions and structures
	//Allow TokenList class to access Token member variables marked private
	friend class TokenList;

public:
	//Default Constructor, pointers initialized to NULL
	Token() : next(NULL), prev(NULL) { }

	//Constructor with string initialization, pointers initialized to NULL
	Token(const string &stringRep) : next(NULL), prev(NULL), stringRep(stringRep) { }

	//Returns the Token's *next member
	Token* getNext ( ) const
	{
		return next;
	}

	//Sets the Token's *next member
	void setNext(Token* next)
	{
		this->next = next;
	}

	//Returns the Token's *prev member
	Token* getPrev ( ) const
	{
		return prev;
	}

	//Sets the Token's *prev member
	void setPrev (Token* prev )
	{
		this->prev = prev;
	}

	//Returns a reference to the Token's stringRep member variable
	const string& getStringRep ( ) const
	{
		return stringRep;
	}

	//Sets the token's stringRep variable
	void setStringRep (const string& stringRep )
	{
		this->stringRep = stringRep;
	}

	//Returns a reference to the Token's stringClass member variable
	const TokenClass getStringClass ( ) const
	{
		return stringClass;
	}

	//Sets the token's stringClass variable
	void setStringClass (const TokenClass& stringClass)
	{
		this->stringClass = stringClass;
	}

	// Returns a reference to the Token's stringType member variable
	const string getStringType() const
	{
		return stringType;
	}

	// Sets the token's stringType variable
	void setStringType(const string& stringType)
	{
		this->stringType = stringType;
	}
	//Return the Token's identifier value
	const TokenClass getID_value()const
	{
		return identifier_value;
	}

	//Sets the Token's identifier value
	void setID_value(const TokenClass& ID_value)
	{
		this->identifier_value = ID_value;
	}
};

//A doubly-linked list class consisting of Token elements
class TokenList 
{
private:
	Token *head; //Points to the head of the token list (doubly linked)
	Token *tail; //Points to the tail of the function list (doubly linked)

public:
	//Default Constructor, Empty list with pointers initialized to NULL
	TokenList() : head(NULL), tail(NULL) { }

	//Returns a pointer to the head of the list
	Token* getFirst() const
	{
		return head;
	}

	//Returns a pointer to the tail of the list
	Token* getLast() const
	{
		return tail;
	}

	//Creates a new token for the string input, str
	//Appends this new token to the TokenList
	//On return from the function, it will be the last token in the list
	void append(const string &str); //example comment

	//Appends the token to the TokenList if not null
	//On return from the function, it will be the last token in the list
	void append(Token *token);

    //Removes the token from the linked list if it is not null
	//Deletes the token
	//On return from function, head, tail and the prev and next Tokens (in relation to the provided token) may be modified.
	void deleteToken(Token *token);

	//Input: a pointer to a token
	//Output: it won't return anything, but within function, it should set the token class (i.e. token->stringClass)
	//Note: one can invoke this function before adding token to the token list
	void setTokenClass(Token *token);

	//Input: a pointer to a token
	//Output: it won't return anything, but within function, it should set the token class (i.e. token->stringClass)
	//NOTE: DOES NOT DO ANYTHING RIGHT NOW
	void setTokenType(Token *token);
};

//A class for tokenizing a string of C++  code into tokens
class Tokenizer 
{
private:
	/*State tracking variables for processing a single string*/
	bool processingInlineComment; //True if processing an In-line comment //
	bool processingBlockComment;  //True if processing a Block Comment /* */
	bool processingIncludeStatement; //True if processing an include statement <> ""
	bool processingFloat; //True if processing a number
	bool complete; //True if finished processing the current string

	size_t offset; //Current position in string
	size_t tokenLength; //Current token length
	string *str; //A pointer to the current string being processed

	//Include any helper functions here
	//e.g. trimming whitespace, comment processing
	void trimwhitespace() 
	{
		if (offset == str->length())
		{
			complete = true;
			return;
		}

		while ((str->at(offset) == ' ' || str->at(offset) == '\t') && offset < str->length())
		{
			offset++;
			if (offset == str->length()) {
				complete = true;
				return;
			}
		}
	} // end of trimwhitespace

	bool isnumber(const char d)
	{
		if (d > 47 && d < 58) //uses ascii values
		{
			return true;
		}
		return false;
	} // end of isnumber

	//Computes a new tokenLength for the next token
	//Modifies: size_t tokenLength, and bool complete
	//(Optionally): may modify offset
	//Does NOT modify any other member variable of Tokenizer
	void prepareNextToken();

public:
	//Default Constructor- YOU need to add the member variable initializers.
	Tokenizer() : processingInlineComment(false), processingBlockComment(false), processingIncludeStatement(false)
		,processingFloat(false), complete(false)
	{
		str = NULL;
		offset = 0;
		tokenLength = 0;
	}

	//Sets the current string to be tokenized
	//Resets all Tokenizer state variables
	//Calls Tokenizer::prepareNextToken() as the last statement before returning.
	void setString(string *str);

	//Returns true if all possible tokens have been extracted from the current string (string *str)
	bool isComplete() const
	{
		return complete;
	}

	//Returns the next token. Hint: consider the substr function
	//Updates the tokenizer state
	//Updates offset, resets tokenLength, updates processingABC member variables
	//Calls Tokenizer::prepareNextToken() as the last statement before returning.
	string getNextToken();
};


#endif /* PARSERCLASSES_H_ */
