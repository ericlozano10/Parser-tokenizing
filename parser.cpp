#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include "scanner.cpp"

using namespace std;

/* INSTRUCTION:  Complete all ** parts.
   You may use any method to connect this file to scanner.cpp
   that you had written.  
  e.g. You can copy scanner.cpp here by:
          cp ../ScannerFiles/scanner.cpp .  
       and then append the two files into one: 
          cat scanner.cpp parser.cpp > myparser.cpp
*/

//=================================================
// File parser.cpp written by Group Number: 11
//=================================================

// ----- Four Utility Functions and Globals -----------------------------------


string saved_lexeme; //global variable used to hold current string being used
tokentype saved_token; //global variable used to hold current token
bool available_token = false; // global boolean used to show if there is a token being held to determine the next_token()

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
//    to display syntax error messages as specified by me.  

// Type of error: Failed match between token_type and saved_lexeme, corresponds to match function
// Done by: Joshua Manlutac 
void syntaxerror1(tokentype expected_token, string saved_lexeme)
{    
  cout << "SYNTAX ERROR: Expected " << tokenName[expected_token] << " but found " << saved_lexeme << endl; 
  exit(1); //end program due to error
}
// Type of error: Default error message in RDP/parser functions
// Done by: Joshua Manlutac 
void syntaxerror2(string saved_lexeme, string parser_function) 
{
  cout << "SYNTAX ERROR: Unexpected " << saved_lexeme << " found in " << parser_function << endl;
  exit(1); //end program due to error
}

// ** Need the updated match and next_token with 2 global vars
// saved_token and saved_lexeme

// Purpose: Update saved_token and/or return it from the function
// Done by: Joshua Manlutac
tokentype next_token()
{
  if(!available_token) //means there is no current token being used, run scanner to get new saved_token
    {
      scanner(saved_token, saved_lexeme);
      cout << "Scanner called using word: " << saved_lexeme << endl;
      available_token = true;
    }
  return saved_token; //returns current saved_token
}

// Purpose: Checks if next_token() and expected_token are the same 
// Done by: Joshua Manlutac
bool match(tokentype expected_token) 
{
  if(next_token() != expected_token)//will run syntaxerror1 if there is a mismatch
    {
      available_token = false;
      syntaxerror1(expected_token, saved_lexeme);
      return false;
    }
  else //otherwise display match and prepare for new token
    {
      cout << "Matched " << tokenName[expected_token] << endl;
      available_token = false;
      return true;
    }
}

// ----- RDP functions - one per non-term -------------------

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// ** Be sure to put the name of the programmer above each function

// Grammar: <tense> := VERBPAST  | VERBPASTNEG | VERB | VERBNEG
// Done by: Eric Lozano
void tense()
{
  cout<<"Processing <tense>"<<endl;
  switch(next_token())//call next token 
    {
    //find verb marker tense
    //match verb marker and break once matched
    case VERBPAST:
      match(VERBPAST);
      break;
    case VERBPASTNEG:
      match(VERBPASTNEG);
      break;
    case VERB:
      match(VERB);
      break;
    case VERBNEG:
      match(VERBNEG);
      break;
    default:
      syntaxerror2(saved_lexeme, "tense");
    }
}

// Grammar: <be> ::=   IS | WAS
// Done by: Eric Lozano
void be()
{
  cout<<"Processing <be>"<<endl;
  
  switch (next_token())
    {
    //match verb markers for be
    case IS:
      match(IS);
      break;
    case WAS:
      match(WAS);
      break;
    default:
      syntaxerror2(saved_lexeme, "be");
    }
}

// Grammar: <verb> ::= WORD2
// Done by: Eric Lozano
void verb()
{
  cout<<"Processing <verb>"<<endl;
  
  switch (next_token()) 
    {
    //matched verbs that end in vowel I and E in other word word2
    case WORD2:
      match(WORD2);
      break;
    default:
      syntaxerror2(saved_lexeme, "verb");
    }
}

// Grammar: <noun> ::= WORD1 | PRONOUN
// Done by: Eric Lozano
void noun()
{
  cout<<"Processing <noun>"<<endl;
  
  switch(next_token())
    {
    //match noun can be Word 1 or pronoun
    case WORD1:
      match(WORD1);
      break;
    case PRONOUN:
      match(PRONOUN);
      break;
    default:
      syntaxerror2(saved_lexeme, "noun");
    }
}

// Grammar: <after object> ::= <verb> <after verb> | <noun> DESTINATION <verb> <tense> PERIOD
// Done by: Eric Lozano
void afterObject()
{
  cout<<"Processing <afterObject>"<<endl;
  switch(next_token())
    {
    //noun is called and can  be Word 1 or Pronoun 
    case WORD1:
    case PRONOUN:
      noun();
      match(DESTINATION);
      verb();
      tense();
      match(PERIOD);
      break;
    //verb is word2
    case WORD2:
      verb();
      tense();
      match(PERIOD);
      break;
    default:
      syntaxerror2(saved_lexeme, "afterObject");
    }
}

// Grammar: <after noun> ::= <be> PERIOD  | DESTINATION <verb> <tense>PERIOD | OBJECT <after object>
// Done by: Eric Lozano
void afterNoun()
{  
  cout<<"Processing <afterNoun>"<<endl;
  switch(next_token())
    {
    //be can be is or was
    case IS:
    case WAS:
      be();
      match(PERIOD);
      break;
    //destination is itself only
    case DESTINATION:
      match(DESTINATION);
      verb();
      tense();
      match(PERIOD);
      break;
    //object is itself only
    case OBJECT:
      match(OBJECT);
      afterObject();
      break;
    default:
      syntaxerror2(saved_lexeme, "afterNoun");
    }
}

// Grammar: <after subject> ::= <verb> <tense> PERIOD | <noun> <after noun>
// Done by: Eric Lozano
void afterSubject()
{
  cout<<"Processing <afterSubject>"<<endl;
  switch(next_token())
    {
    //verb is word 2  
    case WORD2:
      verb();
      tense();
      match(PERIOD);
      break;
    //noun is word1 or pronoun
    case WORD1:
    case PRONOUN:
      noun();
      afterNoun();
      break;
    default:
      syntaxerror2(saved_lexeme, "afterSubject");      
    }
}

// Grammar: <s> ::= [CONNECTOR] <noun> SUBJECT <after subject>
// Done by: Eric Lozano
void s()
{
  cout<<"Processing<s>.."<<endl;
  
  switch(next_token())
    {
    //can only be connector
    case CONNECTOR:
      match(CONNECTOR);
      noun();
      match(SUBJECT);
      afterSubject();
      break;
    //originally thought it was word1 or pronoun but did not work tried default and worked.
    default:
      noun();
      match(SUBJECT);
      afterSubject();
      break;
    }
}

// Grammar: <story> ::= <s> { <s> }
// Done by: Eric Lozano
void story()
{

  cout<<"Processing <story>"<< endl;
  s();//call s function
  while(true)
    {
      if(next_token() == EOFM)//if next token returns and is equal to EOFM
	{
	  cout<<endl;
	  cout<<"Successfully parsed <story>."<<endl;
	  break;
	}
      s();// call s function again
    }
}

string filename;

//----------- Driver ---------------------------

// The new test driver to start the parser
// Done by:  Eric Lozano
int main()
{
  string filename;
  string ch;
  cout << "Enter the input file name: ";
  cin >> filename;
  fin.open(filename.c_str());

  //** calls the <story> to start parsing
  //** closes the input file 
  story();
  fin.close();
}// end
//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions
