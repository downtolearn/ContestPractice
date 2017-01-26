/*
Purpose: solve ACM contest problem socalcontest.org/current/prev_probs/fonebook.htm
*/

#include <iostream>
#include <iomanip>
#include <fstream>
//#include <sstream>
#include <string>
#include <vector>
#include <math.h>
using namespace std;

void fileLine_to_vector(string&, vector<string>&);
void input_to_vector(vector<string>&);

void vector_to_file(string&, vector<string>&);
void print_vector(vector<string>&);

bool compare_strings(string&, string&);

void quick_sort(vector<string>&);
	void pivot(vector<string>&, int&, int&);
		void swap(string&, string&);

	void number_to_word(string&);
		void nine_digit_num(string&);
			void three_digit_num(string&);

	void special_to_spaces(string&); // changes any special character to spaces

	void string_to_lower(string&); //this function makes a string all lower case
		void char_to_lower(char&);


int main(){

	//string inputFile = ("rawData.txt");
	//string outputFile = ("outputData.txt");
	vector<string> data; //data vector
	
	//read data into vector line by line
	//fileLine_to_vector(inputFile, data);
	input_to_vector(data);

	//**perform algorithm here**
	quick_sort(data);

	//write output to file
	//vector_to_file(outputFile, data);
	print_vector(data);
	
	return 0;
}

//reads from a file line by line into a vector
void fileLine_to_vector(string& filename, vector<string> &fileData){
	string data;
	ifstream fin;
	fin.open(filename.data());
	while(!fin.eof()){
		getline(fin, data); //reads a single line from the input file
		fileData.push_back(data);
	} 
	fin.close();
}

void input_to_vector(vector<string> &inputdata){
	//use getline and istringstream
	string temp;
	while(getline(cin, temp)){
		if(temp[temp.size()-1]=='\r'){
			temp.erase(temp.size()-1);
		}
		inputdata.push_back(temp);
	}
}

void vector_to_file(string& filename, vector<string> &data){
	ofstream fout;	
	fout.open(filename.data());
	for(int i=0; i<data.size(); i++)
	{
		fout << resetiosflags(ios::adjustfield);
		fout << setiosflags(ios::left);
		fout << setw(52) << data[i].substr(7, data[i].length()).c_str();
		fout << setw(3) << " ";
		fout << data[i].substr(0,3) << " " << data[i].substr(3,4); //phone number
		if(i != data.size()-1){
			fout << endl;
		}
	} 
	fout.close();
}

void print_vector(vector<string> &data){
	for(int i=0; i<data.size(); i++)
	{
		cout << resetiosflags(ios::adjustfield);
		cout << setiosflags(ios::left);
		cout << setw(52) << data[i].substr(7, string::npos).c_str();
		cout << setw(3) << ' ';
		cout << data[i].substr(0,3) << ' ' << data[i].substr(3,4); //phone number
		cout << endl;
	} 
}

void quick_sort(vector<string> &data){
	int left=0, right=data.size()-1;
	pivot(data,left,right);
}

void pivot(vector<string>& data, int& left, int& right){
  //** this is useful for debugging
  // cout << "\nleft: " << left << "\t\tpivot: " << (right+left)/2 << "\tright: " << right << endl;
  // print_vector(data);
  // cout << endl;
   
   //exit condition
    if((right+left)/2 >= data.size() || (right+left)/2 <= 0 || left >= right || right-left < 1) return;
	
	//initializations
    int L = left, R = right, Piv = (right+left)/2;
	string t1, t2, pivotElem = data[Piv].substr(7, data[Piv].length());
	
	//partitioning
	while(L <= R){
		t1 = data[L].substr(7, data[L].length());
		while(compare_strings(pivotElem, t1)){
			L++;
			t1 = data[L].substr(7, data[L].length());
		}
		t2 = data[R].substr(7, data[R].length());
		while(compare_strings(t2, pivotElem)){
			R--;
			t2 = data[R].substr(7, data[R].length());
		}
		if(L <= R){
			//cout << "data left:" << t1 << "\t\t data right:" << t2 << endl;
			swap(data[L],data[R]);
			L++;
			R--;
		}
	}

	//recursive step
	if(left < R){
	 pivot(data,left,R);
	}
	if(L < right){
	 pivot(data,L,right);
	}
	
}

void swap(string& c1, string& c2){
	string temp;
	temp = c1;
	c1 = c2;
	c2 = temp;
}

bool compare_strings(string& p1, string& p2){
	//prepare strings for comparison
	number_to_word(p1);
	number_to_word(p2);
	special_to_spaces(p1);
	special_to_spaces(p2);
	string_to_lower(p1);
	string_to_lower(p2);

	//cout << "p1:" << p1 << "\t\tp2:" <<p2<<endl;

	int spaces1=0, spaces2=0;
	//comparison logic
	for (int pos1 = 0; pos1 < p1.size();) {
		for (int pos2 = 0; pos2 < p2.size();) {
			//keep count of spaces
			if(p1[pos1]==' '){
				spaces1++;
			}else{
				spaces1=0;
			}
			if(p2[pos2]==' '){
				spaces2++;
			}else{
				spaces2=0;
			}

			//simple comparison logic using character values
    		if(p1[pos1] > p2[pos2] && spaces2<=1){
    			return true;
    		}
	       	else if(p1[pos1] < p2[pos2] && spaces1<=1){
    			return false;
    		}
			else if(p1[pos1] > p2[pos2] && spaces2 == spaces1){
		 		return true;
			}
			else {
				pos1++ ; pos2++;
			}
		}
    }
    return false;
}

void special_to_spaces(string& s1){
	int counter=0;
	for(int i=0; i<s1.length(); i++){
		if(!(s1[i] >= 97 && s1[i] <= 122 || s1[i] >= 65 && s1[i] <= 90)){
			s1[i] = ' ';
		}
		if(counter>0){
			if(s1[i-1]>=65 && s1[i-1]<=90 && s1[i]>=65 && s1[i]<=90){
				s1.insert(s1.begin()+counter, ' ');
			}
		}
		counter++;
	}

}

void string_to_lower(string &data){
	for(int i=0; i<data.length(); i++){
		char_to_lower(data[i]);
	}
}

void char_to_lower(char &data){
	if(data >= 'A' && data <= 'Z'){
		data += 32;
	}
}

//converts and replaces the numbers in a string with their word equivalent
void number_to_word(string& num){
	string toWord, temp;
	int counter=0, index=0;
	bool flag = false;
	for(int i=0; i<num.length(); i++){
		if(num[i] >= 48 && num[i] <= 57){
			temp = num[i];
			toWord.append(temp);
			counter++;
			if(!flag){
				index=i;
				flag=true;
			}
		}
	}
	if(counter>=1){		
		nine_digit_num(toWord);
		if(index!=0){
			temp = " ";
			temp.append(toWord);
			num.replace(index-1,counter+2,temp);
		}
		else{
			num.replace(index,counter+1,toWord);
		}
	}	
}

//converts up to a 9 digit number as a string to it's word equivalent
void nine_digit_num(string& num){
	//pass in a number from the range 0-999,999,999
	string thousand = "thousand ";
	string million = "million ";

	string word;
	int length = num.length();

	while(num.length()<9){
		num.insert(0, "0");
	}
	string millions = num.substr(0,3);
	string thousands = num.substr(3,3);
	string hundreds = num.substr(6,3);

	//temp = three_digit_num(millions); //checks the millions place
	three_digit_num(millions);
	if(millions != "zero "){
		word.append(millions);
		word.append(million);
	}
	//temp = three_digit_num(thousands); //checks the thousands place
	three_digit_num(thousands);
	if(thousands != "zero "){	
		word.append(thousands);
		word.append(thousand);
	}
	three_digit_num(hundreds);
	word.append(hundreds); //checks the hundreds place
	
	//this is what happends with multiple zeros
	if(millions == "zero " && thousands == "zero " && hundreds == "zero "){
		word.clear();
		while(length > 0){
			word.insert(0,hundreds);
			length--;
		}
	}

	num.resize(word.size());
	num = word;
}

//converts up to a 3 digit number to it's word equivalent
void three_digit_num(string& number){
	string onesNames[] = {"zero ", "one ", "two ", "three ", "four ", "five ", "six ", "seven ", "eight ", "nine "};
	string teensNames[] = {"ten ", "eleven ", "twleve ", "thirteen ", "fourteen ", "fifteen ", "sixteen ", "seventeen ", "eighteen ", "nineteen "};
	string tensNames[] = {"ten ", "twenty ", "thirty ", "fourty ", "fifty ", "sixty ", "seventy ", "eighty ", "ninety "}; 
	string hundred = "hundred ";

	string word;

	if(number.length()==3 && number[0]!='0'){ //if the number is 3 digits
		word.append(onesNames[number[0]-48]);
		word.append(hundred);
		if(number[1]=='1'){
			word.append("and ");
			word.append(teensNames[number[2]-48]);
		}
		else if(number[1] > '1'){
			word.append("and ");
			word.append(tensNames[number[1]-49]);
		}
		else if(number[1]=='0'&&number[2]!='0'){
			word.append("and ");
		}
		if(number[1]!='1'&&number[2]!='0'){
			word.append(onesNames[number[2]-48]);
		}
	}
	else if(number.length()==3 && number[0]=='0'){ //if the number is 3 digits with a leading zero
		if(number[1]=='0'){ //if the number is 3 digits with two leading zeros
			word.append(onesNames[number[2]-48]);
		}
		else if(number[1]=='1'){
			word.append(teensNames[number[2]-48]);
		}
		else{
			word.append(tensNames[number[1]-49]);
			if(number[2]!= '0'){
				word.append(onesNames[number[2]-48]);
			}
		}
	}
	else if(number.length()==2 && number[0]!='0'){ //if the number is 2 digits
		if(number[0]=='1'){
			word.append(teensNames[number[1]-48]);
		}
		else if(number[0]!='0'){
			word.append(tensNames[number[0]-49]);
		}
		if(number[0]!='1' && number[1]!='0'){
			word.append(onesNames[number[1]-48]);
		}
	}
	else if(number.length()==2 && number[0]=='0'){ //if the number is 2 digits with leading zero
		word.append(onesNames[number[1]-48]);
	}
	else if(number.length()==1){ //if the number is 1 digit
		word.append(onesNames[number[0]-48]);
	}
	number.resize(word.size());
	number = word;
}
