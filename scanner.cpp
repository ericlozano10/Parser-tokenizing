#include<iostream>
#include<fstream>
#include<string>
using namespace std;

/* Look for all **'s and complete them */

//=====================================================
// File scanner.cpp written by: Group Number: 11
//=====================================================

// --------- Two DFAs ---------------------------------

// WORD DFA 
// Done by: Eric Lozano
// RE:(vowel | vowel n | consonant vowel | consonant vowel n |consonant-pair vowel | consonant-pair vowel n)^+              

bool word (string s)
{

  int state = 0;
  int charpos = 0;
  /* replace the following to do the word dfa  */
  while (s[charpos] != '\0') 
    {
      if(state == 0)//state 0 can terminate if its an immediate vowel or it can be the starting point
	{
	  if(s[charpos] == 'b' ||s[charpos] == 'g' ||s[charpos] == 'h' ||s[charpos] == 'k' ||
	     s[charpos] == 'm' ||s[charpos] == 'n' ||s[charpos] == 'p' ||s[charpos] == 'r')
	    {
	      state = 1;//qy or consonant-y pair
	    }
	  else if(s[charpos] == 'd' ||s[charpos] == 'w' ||s[charpos] == 'z' ||s[charpos] == 'y' ||s[charpos] == 'j')
	    {
	      state = 2;//qsa or non-starting consonant-vowel state
	    }
	  else if(s[charpos] == 't')
	    {
	      state = 3;//from q0 to qt state we get there by 't'
	    }
	  else if(s[charpos] == 's')
	    {
	      state = 4;//from q0 to qs state we get there by 's'
	    }
	  else if(s[charpos] == 'c')
	    {
	      state = 5;//from q0 to qc state we get there by 'c'
	    }
	  else if(s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' || s[charpos] == 'E')
            {
              state = 0;//state q0 or q6? on a vowel
            }
	  else//invalid state
	    {
	      return false;
	    }
	}
      else if(state == 1)//qy and reached by consonant-y pair
	{
	  if(s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' || s[charpos] == 'E')
            {
              state = 6;//q0q1 on a vowel state
            }
	  else if(s[charpos] == 'y')
	    {
	      state = 2;//qsa
	    }
	  else
	    {
	      return false;
	    }
	}
      else if(state == 2)//state qsa and we get here by "dwyzj"
	{
	  if(s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' || s[charpos] == 'E')
	    {
	      state = 6;//q6 on a vowel
	    }
	  else
	    {
	      return false;
	    }
	}
      else if(state == 3)//get here by a 't' this state is qt
	{
	   if(s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' || s[charpos] == 'E')
	    {
	      state = 6;//q6
	    }
	   else if(s[charpos] == 's')
	     {
	       state = 2;//qsa
	     }
	  else
	    {
	      return false;
	    }
	}
      else if(state == 4)//this state is q4 reached by an s
	{
	  if(s[charpos] == 'h')
	    {
	      state = 2;//qsa
	    }
	  else if(s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' || s[charpos] == 'E')
	    {
	      state = 6;//q0q1
	    }
	  else
	    {
	      return false;
	    }
	}
      else if (state == 5)//q5 atate and reched by c
	{
	  if(s[charpos] == 'h')
            {
              state = 2;//qsa
            }
          else
            {
              return false;
            }
	}
      else if(state == 6)//q0q1
	{
	  if(s[charpos]== 'h')
	    {
	      state == 3;//qt
	    }
	  else if(s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' || s[charpos] == 'E')
            {
              state = 6;//q0q1
            }
	  else if(s[charpos] == 'b' ||s[charpos] == 'g' ||s[charpos] == 'h' ||s[charpos] == 'k' ||
             s[charpos] == 'm' ||s[charpos] == 'p' ||s[charpos] == 'r')
	    {
	      state = 1;//qy
	    }
	  else if(s[charpos] == 'n')
	    {
	      state = 7;//qoqy
	    }
	  else if(s[charpos] == 't')
	    {
	      state = 3;//qt
	    }
	  else if(s[charpos] == 's')
	    {
	      state = 4;//qs
	    }
	  else if(s[charpos] == 'c')
	    {
	      state = 5;//qc
	    }
	  else if(s[charpos] == 'd' ||s[charpos] == 'w' ||s[charpos] == 'z' ||s[charpos] == 'y' ||s[charpos] == 'j')
	    {
	      state = 2;//qsa
	    }
	  else
	    {
	      return false;
	    }
	}
      else if(state == 7)//q0qy
	{
	  if(s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' || s[charpos] == 'E')
	    {
	      state = 6;//q0q1
	    }
	  else if(s[charpos] == 'b' ||s[charpos] == 'g' ||s[charpos] == 'h' ||s[charpos] == 'k' ||
		  s[charpos] == 'm' ||s[charpos] == 'n' ||s[charpos] == 'p' ||s[charpos] == 'r')
            {
              state = 1;//qy
            }
	  else if(s[charpos] == 't')
	    {
	      state = 3;//qt
	    }
	  else if(s[charpos] == 's')
	    {
	      state = 4;//qs
	    }
	  else if(s[charpos] == 'c')
	    {
	      state = 5;//qc
	    }
	  else if(s[charpos] == 'd' ||s[charpos] == 'w' ||s[charpos] == 'z' ||s[charpos] == 'y' ||s[charpos] == 'j')
	    {
	      state = 2;//qsa
	    }
	  else
	    {
	      return false;
	    }
	}
      charpos++;
    }//end of while

  // where did I end up????
  //well our state 0 is our starting point and final state but if it ends in a vowel or E/I we can end the DFA as well.
  //state 6 and state 7 are lso final states.
  if (state == 0 || state == 6 || state == 7) return(true);  // end in a final state
   else return(false);
}

// PERIOD DFA 
// Done by: Eric Lozano
bool period (string s)
{
  int charpos = 0;
  // complete this **
  while(s[charpos]!= '\0')//if string i snot null enter
    {
      if(s[charpos] == '.')//if string is a period enter
	{
	  return true;
	}
      else
	{
	  return false;
	}
      charpos++;//increment
    }
}

// ------ Three  Tables -------------------------------------

// TABLES Done by: Joshua Manlutac

// ** Update the tokentype to be WORD1, WORD2, PERIOD, ERROR, EOFM, etc.
enum tokentype {WORD1, WORD2, PERIOD,ERROR,EOFM,VERB,VERBNEG,VERBPAST,VERBPASTNEG,IS,WAS,OBJECT,SUBJECT,DESTINATION,PRONOUN,CONNECTOR};

// ** For the display names of tokens - must be in the same order as the tokentype.
string tokenName[30] = {"WORD1", "WORD2", "PERIOD","ERROR","EOFM","VERB","VERBNEG","VERBPAST","VERBPASTNEG","IS","WAS","OBJECT","SUBJECT","DESTINATION","PRONOUN","CONNECTOR"};

// ** Need the reservedwords table to be set up here. 
// ** Do not require any file input for this. Hard code the table.
// ** a.out should work without any additional files.
string resrvWords[19][2] = {{"masu","VERB"}, {"masen","VERBNEG"}, {"mashita","VERBPAST"}, {"masendeshita","VERBPASTNEG"}, {"desu","IS"}, {"deshita","WAS"}, {"o","OBJECT"}, {"wa","SUBJECT"}, {"ni","DESTINATION"}, {"watashi","PRONOUN"}, {"anata","PRONOUN"}, {"kare","PRONOUN"}, {"kanojo","PRONOUN"}, {"sore","PRONOUN"}, {"mata","CONNECTOR"}, {"soshite","CONNECTOR"}, {"shikashi","CONNECTOR"}, {"dakara","CONNECTOR"}, {"eofm","EOFM"}};

// ------------ Scaner and Driver ----------------------- 

ifstream fin;  // global stream for reading from the input file

// Scanner processes only one word each time it is called
// Gives back the token type and the word itself
// ** Done by: Eric Lozano & Joseph Aaron
int scanner(tokentype& tt, string& w)
{
  // ** Grab the next word from the file via fin
  // 1. If it is eofm, return right now.   
  /*  **
  2. Call the token functions (word and period) 
     one after another (if-then-else).
     Generate a lexical error message if both DFAs failed.
     Let the tokentype be ERROR in that case.
  3. If it was a word,
     check against the reservedwords list.
     If not reserved, tokentype is WORD1 or WORD2
     decided based on the last character.

  4. Return the token type & string  (pass by reference)
  */

  fin>>w;//read from file
  if(word(w))//if dfa accepts string word enter if
    {
      bool resrv = false;//flag
      
      for(int i = 0; i < 19; i++)//loop table times
	{
	  if(w == resrvWords[i][0])//if string w equals row i at column 0 enter if
	    {
	      //same logic for all if statements
	      //if string w equals row i at column 1 enter if
	      if(resrvWords[i][1] == "VERB")
		{
		  tt = VERB;
		}
	      else if(resrvWords[i][1] == "VERBNEG")
		{
		 tt = VERBNEG;
		}
	      else if(resrvWords[i][1] == "VERBPAST")
                {
		  tt = VERBPAST;
                }
	      else if(resrvWords[i][1] == "VERBPASTNEG")
		{
		  tt = VERBPASTNEG;
		}
	      else if(resrvWords[i][1] == "IS")
		{
		  tt = IS;
		}
	      else if(resrvWords[i][1] == "WAS")
		{
		  tt = WAS;
		}
	      else if(resrvWords[i][1] == "OBJECT")
		{
		  tt = OBJECT;
		}
	      else if(resrvWords[i][1] == "SUBJECT")
		{
		  tt = SUBJECT;
		}
	      else if(resrvWords[i][1] == "DESTINATION")
		{
		  tt = DESTINATION;
		}
	      else if(resrvWords[i][1] == "PRONOUN")
		{
		  tt = PRONOUN;
		}
	      else if(resrvWords[i][1] == "CONNECTOR")
		{
		  tt = CONNECTOR;
		}
	      else if(resrvWords[i][1] == "EOFM")
		{
		  tt = EOFM;
		}
	      resrv = true;//if we have a match flag up
	      break;//loop break
	    }
	}
      //if not a reserver word enter if check last position for I or E
      if(resrv != true)
	{
	  //check if w ends in I or E
	  if(w[w.length() - 1] == 'I' || w[w.length() - 1] == 'E')
	    {
	      tt = WORD2;
	    }
	  else
	    {
	      tt = WORD1;//must end in e or i
	    }
	}
    }
  else if(period(w))//check fot dfa period in string w
    {
      tt = PERIOD;
    }
  else if(w == "eofm")//check for string w
    {
      tt = EOFM;
    }
  else//error
    {
      cout<<"Lexical Error: "<<w<<" is not a valid token."<<endl;
      tt = ERROR;
    }
  return 0;
}//the end of scanner



