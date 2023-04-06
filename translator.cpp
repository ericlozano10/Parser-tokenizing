#include<iostream>
#include<fstream>
#include<string>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include "scanner.cpp"

using namespace std;


/* INSTRUCTION:  copy your parser.cpp here
      cp ../ParserFiles/parser.cpp .
   Then, insert or append its contents into this file and edit.
   Complete all ** parts.
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

//=================================================
// File translator.cpp written by Group Number: **
//=================================================

// ----- Additions to the parser.cpp ---------------------

// ** Declare Lexicon (i.e. dictionary) that will hold the content of lexicon.txt
// Make sure it is easy and fast to look up the translation.
// Do not change the format or content of lexicon.txt 
//  Done by: ** 
map<string,string> lexicon;//mapping to hold words from file
string japWord;//holds string japanese word from file read
string engWord;//holds string english word from file
string saved_E_word;//saves english word
ifstream file;//lexicon file
ofstream tfile;//translated file
int size = 47;//lines in file
// ** Additions to parser.cpp here:
//    getEword() - using the current saved_lexeme, look up the English word
//                 in Lexicon if it is there -- save the result   
//                 in saved_E_word
//  Done by: Eric Lozano 
//    gen(line_type) - using the line type,
//                     sends a line of an IR to translated.txt
//                     (saved_E_word or saved_token is used)
//  Done by: Eric Lozano

//Purpose: This function is meant to search for the english word in the mapping by using an iterator. 
//If the Japanese word has an English translation then save to E word else save the japanese word itself.
void getEword()
{
  map<string,string>::iterator eng = lexicon.find(saved_lexeme);//iterate through the mapping and find saved_lexeme 
  if(eng != lexicon.end())//if english word does not equal the end of iteration value then translation exist
    {
      saved_E_word = eng->second;//save the 2nd values of the mapping remember saved as a table format
    }
  else
    {
      saved_E_word = saved_lexeme;//save the jap word itself
    }
}

//Purpose: Recieves a string from left factored rules. If the string is Tense/Past word  save current token.
//Otherwise, save the English translation. Display result to trannslation.txt file.
void gen(string line_type)
{
  string store;//holds save token
  if (line_type == "TENSE")// string equals tense enter if
    {
      store = tokenName[saved_token] + '\n';//save token name value into store
    }
  else
    {
      store = saved_E_word;// save english word into store
    }
  tfile<<line_type<<": "<<store<<endl;//display result to translator.txt
}

// ----- Changes to the parser.cpp content ---------------------

// ** Comment update: Be sure to put the corresponding grammar 
//    rule with semantic routine calls
//    above each non-terminal function 

// ** Each non-terminal function should be calling
//    getEword and/or gen now.
// ----- RDP functions - one per non-term -------------------

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// ** Be sure to put the name of the programmer above each function

// Grammar: <tense> := VERBPAST  | VERBPASTNEG | VERB | VERBNEG
// Done by: Joshua Manlutac
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
// Done by: Joshua Manlutac
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
// Done by: Joshua Manlutac
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
// Done by: Joshua Manlutac
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

// Grammar: <after object> ::= <verb> #getEword# #gen(ACTION)# <tense> #gen(TENSE)# PERIOD 
//| <noun> #getEword# DESTINATION #gen(TO)# <verb> #getEword# #gen(ACTION)# <tense> #gen(TENSE)# PERIOD

// Done by: Joshua Manlutac
void afterObject()
{
  cout<<"Processing <afterObject>"<<endl;
  switch(next_token())
    {
      //noun is called and can  be Word 1 or Pronoun 
    case WORD1:
    case PRONOUN:
      noun();
      getEword();
      match(DESTINATION);
      gen("TO");
      verb();
      getEword();
      gen("ACTION");
      tense();
      gen("TENSE");
      match(PERIOD);
      break;
      //verb is word2
    case WORD2:
      verb();
      getEword();
      gen("ACTION");
      tense();
      gen("TENSE");
      match(PERIOD);
      break;
    default:
      syntaxerror2(saved_lexeme, "afterObject");
    }
}

// Grammar:<after noun> ::= <be> #gen(DESCRIPTION)# #gen(TENSE)# PERIOD  
//| DESTINATION #gen(TO)# <verb> #getEword# #gen(ACTION)# <tense> #gen(TENSE)# PERIOD 
//| OBJECT #gen(OBJECT)# <after object>

// Done by: Joshua Manlutac
void afterNoun()
{  
  cout<<"Processing <afterNoun>"<<endl;
  switch(next_token())
    {
      //be can be is or was
    case IS:
    case WAS:
      be();
      gen("DESCRIPTION");
      gen("TENSE");
      match(PERIOD);
      break;
      //destination is itself only
    case DESTINATION:
      match(DESTINATION);
      gen("TO");
      verb();
      getEword();
      gen("ACTION");
      tense();
      gen("TENSE");
      match(PERIOD);
      break;
      //object is itself only
    case OBJECT:
      match(OBJECT);
      gen("OBJECT");
      afterObject();
      break;
    default:
      syntaxerror2(saved_lexeme, "afterNoun");
    }
}

// Grammar:<after subject> ::= <verb> #getEword# #gen(ACTION)# <tense> #gen(TENSE)# PERIOD | <noun> #getEword# <after noun>

// Done by: Joshua Manlutac
void afterSubject()
{
  cout<<"Processing <afterSubject>"<<endl;
  switch(next_token())
    {
      //verb is word 2  
    case WORD2:
      verb();
      getEword();
      gen("ACTION");
      tense();
      gen("TENSE");
      match(PERIOD);
      break;
      //noun is word1 or pronoun
    case WORD1:
    case PRONOUN:
      noun();
      getEword();
      afterNoun();
      break;
    default:
      syntaxerror2(saved_lexeme, "afterSubject");      
    }
}

// Grammar: <s> ::= [CONNECTOR #getEword# #gen(CONNECTOR)#] <noun> #getEword# SUBJECT #gen(ACTOR)# <after subject>
// Done by: Joshua Manlutac
void s()
{
  cout<<"Processing<s>.."<<endl;
  
  switch(next_token())
    {
      //can only be connector
    case CONNECTOR:
      match(CONNECTOR);
      getEword();
      gen("CONNECTOR");
      noun();
      getEword();
      match(SUBJECT);
      gen("ACTOR");
      afterSubject();
      break;
      //originally thought it was word1 or pronoun but did not work tried default and worked.
    default:
      noun();
      getEword();
      match(SUBJECT);
      gen("ACTOR");
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
// ---------------- Driver ---------------------------

// The final test driver to start the translator
// Done by:  Eric Lozano
int main()
{

  //** opens the lexicon.txt file and reads it into Lexicon
  //** closes lexicon.txt 

  file.open("lexicon.txt", ios::in);//open and read file

  for(int i = 0; i < size; i++)//loop size stimes
    {
      file>>japWord;//save word in row 1 column 1 to japword 
      file>>engWord;//save english word in row 1 column 2 to engword
      lexicon[japWord] = engWord;//refrence mapping at wherever japwword is located add english word in there.
    }
  tfile.open("translated.txt", ios::out);//open translated.txt file.
  //** opens the output file translated.txt

  cout << "Enter the input file name: ";
  cin >> filename;
  fin.open(filename.c_str());

  //** calls the <story> to start parsing
  story();
  //** closes the input file 
  fin.close();
  //** closes traslated.txt
  tfile.close();
}// end
//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions
