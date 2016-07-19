//Osama Mohamed Mostafa AbdelMageid Ghozlan
//13p6040

#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <ctime>
using namespace std;

enum TokenType{IF, THEN, ELSE, END, REPEAT, UNTIL, READ, WRITE, IDENTIFIER, NUMBER, COMMENT, NONE, OPERATOR, WHITESPACE, LEFTPARAN, RIGHTPARAN, ASSIGNMENT};
enum State{Start, In_Comm, In_Num, In_ID, Assign, Done, Error, Other};
static State curStt = Start;
static string inputBuffer = "";
static int curChar = 0;
static bool end = 0;
TokenType int2TT(int t);
string findTokenType(TokenType t);

const string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

class Token{
	public:
	TokenType TokenType;	
	string stringVal;
	Token(void);
	Token(int TokenType,string stringVal);
	void getType(){
		if( this->stringVal == "if" )
			this->TokenType = IF;

		else if(this->stringVal == "then")
			this->TokenType = THEN;

		else if(this->stringVal == "else")
			this->TokenType = ELSE;

		else if(this->stringVal == "end")
			this->TokenType = END;

		else if(this->stringVal == "read")
			this->TokenType = READ;

		else if(this->stringVal == "write")
			this->TokenType = WRITE;

		else if(this->stringVal == "repeat")
			this->TokenType = REPEAT;

		else if(this->stringVal == "until")
			this->TokenType = UNTIL;
	}
	
	void print(){
		cout << this->stringVal  << '\t' << findTokenType(this->TokenType) <<endl;
	}
	
	string toString(){
		return this->stringVal  + '\t' + findTokenType(this->TokenType);
	}
	
};

Token::Token(void){}


Token::Token(int TokenType,string stringVal){
		this->TokenType = int2TT(TokenType);
		this->stringVal = stringVal;
		if(this->TokenType == IDENTIFIER){
			this->getType();
		}
	}

static vector <Token*> currLine;

//Gets TokenType corresponding to an int value
TokenType int2TT(int x){
	if(x == 0){
		return IF;
	}else if(x == 1){
		return THEN;
	}else if(x == 2){
		return ELSE;
	}else if(x == 3){
		return END;
	}else if(x == 4){
		return REPEAT;
	}else if(x == 5){
		return UNTIL;
	}else if(x == 6){
		return READ;
	}else if(x == 7){
		return WRITE;
	}else if(x == 8){
		return IDENTIFIER;
	}else if(x == 9){
		return NUMBER;
	}else if(x == 10){
		return COMMENT;
	}else if(x == 11){
		return NONE;
	}else if(x == 12){
		return OPERATOR;
	}else if(x == 13){
		return WHITESPACE;
	}else if(x == 14){
		return LEFTPARAN;
	}else if(x == 15){
		return RIGHTPARAN;
	}else if(x == 16){
		return ASSIGNMENT;
	}
	
}

//Get Token representing input Character	
TokenType charToToken(char c){
		TokenType TokenType;
		switch(c){
			
		case ':':
			TokenType = ASSIGNMENT;
			break;	

		case '=':
			TokenType = OPERATOR;
			break;

		case '<':
			TokenType = OPERATOR;
			break;

		case '+':
			TokenType = OPERATOR;
			break;

		case '-':
			TokenType = OPERATOR;
			break;

		case '*':
			TokenType = OPERATOR;
			break;

		case '/':
			TokenType = OPERATOR;
			break;

		case '(':
			TokenType = LEFTPARAN;
			break;

		case ')':
			TokenType = RIGHTPARAN;
			break;

		case ';':
			TokenType = OPERATOR;
			break;

		default:
			TokenType = NONE;
		}

		return TokenType;
	}

//Get TokenType representing Current State
TokenType stateToTokenType(State state){
		TokenType TokenType;
		switch(state){

		case Assign:
			TokenType = OPERATOR;
			break;

		case In_ID:
			TokenType = IDENTIFIER;
			break;

		case In_Num:
			TokenType = NUMBER;
			break;
			
		case Start:
			TokenType = WHITESPACE;
			break;	

		default:
			TokenType = NONE;
		}

		return TokenType;
	}


//Check if character is a number
bool isDigit(char c){
	return (c >= '0' && c <='9');
}

//Check if character is an alphabet letter
bool isLetter(char c){
	return (c >= 'a' && c<='z') || (c >= 'A' && c<='Z');
}

//Check if character is a Whitespace
bool isWhiteSpace(char c){
	return (c == '\t' || c == '\n' || c == ' ');
}


//Check if character is an Operator
bool isOperator(char c){
	if (c == '+' || c == '-' || c == '*'
		|| c == '/'|| c == '='|| c == '<'
		||c == ';'){
			return 1;
	}
	return 0;
}

//Converts string into character array
char* str2char(string s){
	char* temp = new char[s.size()];
	for(int i = 0; i < s.size(); i++){
		temp[i] = s.at(i);
	}
	return temp;
}


//Get string value for State enum
string findState(State s){
	map<State,string> temp;
	temp[Start] = "Start";
	temp[In_Comm] = "In Comment";
	temp[In_Num] = "In Number";
	temp[In_ID] = "In Identifier";
	temp[Assign] = "Assignment";
	temp[Done] = "Done";
	temp[Error] = "Error";
	temp[Other] = "Other";
	return temp[s];
}

//Get string value for TokenType enum
string findTokenType(TokenType t){
	map<TokenType,string> temp;
	temp[IF] = "Reserved Word: if";
	temp[THEN] = "Reserved Word: then";
	temp[ELSE] = "Reserved Word: else";
	temp[END] = "Reserved Word: end";
	temp[REPEAT] = "Reserved Word: repeat";
	temp[UNTIL] = "Reserved Word: until";
	temp[READ] = "Reserved Word: read";
	temp[WRITE] = "Reserved Word: write";
	temp[COMMENT] = "Comment";
	temp[OPERATOR] = "Operator";
	temp[NONE] = "None";
	temp[WHITESPACE] = "Whitespace";
	temp[NUMBER] = "Number";
	temp[IDENTIFIER] = "Identifier";
	temp[LEFTPARAN] = "Left Paranthesis";
	temp[RIGHTPARAN] = "Right Paranthesis";
	temp[ASSIGNMENT] = "Assignment";
	return temp[t];
}


//Get next character
char nextChar(string s){
		char c = s.at(curChar++);
		inputBuffer = inputBuffer + c;
		return c;
	}

//Get previous character
void prevChar(){
		curChar--;
		inputBuffer = inputBuffer.substr(0,inputBuffer.size() - 1);
	}

//Check end of data	
bool hasMoreChars(string s){
		end = !(curChar < s.size());
		return !end;
	}

Token* getNextToken(string s, State state){
		TokenType T = NONE;
		while(state != Done && !end){
			if(hasMoreChars(s)){
				char c = nextChar(s);
				//cout<< "Next Char "<< curChar << " " << c << " "<< findState(stateTransition(c,state)) <<endl;
			
				switch(state){
				case Start:
					if(isDigit(c)){ state = In_Num;
            		}else if (isOperator(c)){ state = Done; T = OPERATOR;
					}else if (isLetter(c)){ state = In_ID;
					}else if (isWhiteSpace(c)){state = Start; inputBuffer = ""; T = WHITESPACE;
					}else if (c == ':'){state = Assign;
					}else if (c == '{'){state = In_Comm; inputBuffer = "";
					}else{T = charToToken(c); state = Done;	}
				break;					

				case In_Comm:
					if(c == '}'){ state = Start; T = COMMENT;
					}else{ state = In_Comm;}
				break;
				
				case In_ID:
						if(isLetter(c)){ state = In_ID; T = IDENTIFIER;					
						}else if(isDigit(c)){ prevChar(); state = Done; T = NONE;
						}else{ prevChar(); state = Done; T = IDENTIFIER;}
					break;

				case In_Num:
					if(isDigit(c)){ state = In_Num; T = NUMBER;
					}else if(isLetter(c)){prevChar(); curStt = Done; T = NONE;
					}else{prevChar(); state = Done; T = NUMBER;}
				break;


				case Assign:
					if(c == '='){ state = Assign; T = ASSIGNMENT;
					}else{prevChar(); state = Done; }
				break;
				
				default:
					break;
				}	
			}
		}
		Token* Token2;
		if(state == Done){
			Token2 = new Token(T,inputBuffer);
		}else if(!inputBuffer.empty()){
			Token2 = new Token(stateToTokenType(state), inputBuffer);
		}
		state = Start;
		inputBuffer = "";
		return Token2;
	}
	
	//Split input into tokens
	vector <Token*> scan(string s, State curStt){
		vector <Token*> allTokens;
		Token* token = getNextToken(s,curStt);
		while(!end){
			if(token->TokenType != COMMENT)
				allTokens.push_back(token);
				token = getNextToken(s,curStt);
		}

		return allTokens;
	}

//Print tokens
void printTokens(vector <Token*> v){
	for (int i = 0; i < v.size(); i++)
    	v[i]->print();
}

void printTT(vector <Token*>& v, vector<string> str, int idx,State s){
			v = scan(str[idx],s);
			printTokens(v);
	}



void identify(char* arr, int size, char* &num, char* &res, char* &op){
	for(int j = 0; j < size; j++){
		num[j] = res[j] = op[j] = ' ';
	}
	
	for(int i = 0; i < size; i++){
		if(isDigit(arr[i])){
			num[i] = arr[i];
		}else if(isLetter(arr[i])){
			res[i] = arr[i];
		}else if(isOperator(arr[i])){
			op[i] = arr[i];
		}else{}
	}
}

int main(){

	ofstream outputFile ("output.txt", ios::app); 
	ifstream inputFile ("input.txt");
	string line;
	vector <string> input;
  	if (inputFile.is_open()){	
    while(getline (inputFile,line) )
    	{input.push_back(line);}
    	inputFile.close();}
    int sz = input.size();
	State s = Start;
	int w;
	cout <<  currentDateTime() <<endl;
	cout << "Input Lines: " << sz <<endl;
	cin >> w;
	stringstream ss;
	ss << (w);
	w--;	
	vector<Token*> v = scan(input[w],s);
	if (outputFile.is_open()){
		outputFile << "Line " + ss.str() + ": " + '\n';
		for (int i = 0; i < v.size(); i++){
			cout << "Line " + ss.str() <<": "<<v[i]->toString() <<endl;
  			outputFile << v[i]->toString() + '\n';
		}}if(w == (sz-1)){
  				outputFile << "----------------End of File---------------" <<endl;
		}outputFile.close();
	return 0;

}
