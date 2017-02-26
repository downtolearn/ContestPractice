#include <iostream>
#include <sstream>
#include <vector>

using namespace std;


struct Card{
        int value;
        char suit;
        bool isStart;

        Card(int v, char s, bool b){
                value = v;
                suit = s;
                isStart = b;
        }
        Card(){};
        ~Card(){};
};

void get_data(vector< vector<Card> >&, vector<string>&);
void print_data(vector< vector<Card> >&, vector<string>&, vector<int>&);
void sortCards(vector<Card>&);

int char_to_value(char);
int value_to_real(int);
char value_to_char(int);

int get_hand_score(vector<Card>&, string&);
int get_pairs(vector<Card>&);
int get_hand_15(vector<Card>&);
int get_flush(vector<Card>&,string&);
int get_run(vector<Card>&);
int get_nobs(vector<Card>&);

int main(){
        vector< vector<Card> > hands;
        vector<string> handTypes;
        vector<int> scores;
        int score=0;

        //get the hands
        get_data(hands, handTypes);
        //sort the cards in each hand
        for(int i = 0; i < hands.size(); i++){
                sortCards(hands[i]);
        }

        //get the score of each hand
        for(int i=0; i<hands.size(); i++){
                score = get_hand_score(hands[i],handTypes[i]);
                scores.push_back(score);
        }
        //print the hands and scores
        print_data(hands, handTypes, scores);
}

int get_hand_score(vector<Card>& cards, string& type){
        int score=0;
        score += get_pairs(cards);
        score += get_hand_15(cards);
        score += get_flush(cards, type);
//      score += get_run(cards);
        score += get_nobs(cards);
        return score;
}

int get_pairs(vector<Card>& cards){
        int score =0;
        for(int i=0; i < cards.size()-1; i++){
                for(int j=i+1; j < cards.size();j++){
                        if(cards[i].value==cards[j].value){
                                score += 2;
                        }
                }
        }
        return score;
}

int get_hand_15(vector<Card>& cards){
        int temp=0, temp2=0, score=0, total=15;
        for(int start=0; start < cards.size(); start++){
                temp = value_to_real(cards[start].value);
                total -= temp;
                if(total < 0){
                        for(int i=0; i<start; i++){
                                temp2 = value_to_real(cards[i].value);
                                if(total + temp2==0){
                                        total += temp2;
                                        score+=2;
                                        break;
                                }
                        }
                }
        }
        return score;
}

int get_flush(vector<Card>& cards,string& type){
        if(type == "c"){return 0;}
        int score = 0;
        int values[]={0,0,0,0};
        char suits[] ={'H','S','D','C'};
        for(int i=0; i<cards.size(); i++){
                for(int p=0; p<4; p++){
                        if(suits[p] == cards[i].suit){
                                values[p]+=1;
                                break;
                        }
                }

        }
        for(int i=0; i<4; i++){
                if(values[i]==4){
                        score+=4;
                        break;
                }
                else if(values[i]==5){
                        score+=5;
                        break;
                }
        }
        return score;
}

/*
//left off, this is wrong
int get_run(vector<Card>& cards){
        int score =0, run=0, mutiplier=1;
        vector<Card> real (cards.begin(), cards.end());
        for(int i=1; i<cards.size()-1; i++){
                if(cards[i].value == cards[i+1].value+1 && cards[i].value == cards[i-1].value-1){
                        run+=1;
                }
                else if(cards[i].value == cards[i+1].value+1|| cards[i].value == cards[i-1].value && multiplier != 3 && multiplier!=2){
                        multiplier+=1;
                }
                else if(cards[i].value==cards[i+1].value && cards[i]==cards.[i-1].value){
                        if(multiplier==2){multiplier+=1;}
                        else{multiplier+=2;}
                }
        }
        if(multiplier
        switch(run){
                case 0; score = 0;
                case 1; score = 3;
                case 2; score = 4;
                case 3; score = 5;
        }
        return score*multiples;
}
*/

int get_nobs(vector<Card>& cards){
        int score =0;
        for(int i = 0; i<cards.size()-1; i++){
                if(cards[i].value == 11 && cards[i].suit == cards[4].suit){
                        score+=1;
                        break;
                }
        }
        return score;
}

void sortCards(vector<Card>& cards){

        bool swap = true;

        while(swap){
                swap = false;

                for(int i = 1; i < cards.size(); i++){
                        if(cards[i-1].value > cards[i].value){
                                Card temp;
                                temp = cards[i];
                                cards[i] = cards[i-1];
                                cards[i-1] = temp;
                                swap = true;
                        }
                }
        }
}

int char_to_value(char c){
        switch(c){
                case 'A': return 1;
                case 'K': return 13;
                case 'Q': return 12;
                case 'J': return 11;
                case 'T': return 10;
                default: return (c - '0');
        }
}

int value_to_real(int value){
        if(value >= 10){return 10;}
        else{return value;}
}

char value_to_char(int value){
        switch(value){
                case 13: return 'K';
                case 12: return 'Q';
                case 11: return 'J';
                case 10: return 'T';
                case 1: return 'A';
                default: return (char) value + '0';
        }
}

void get_data(vector< vector<Card> >& hands, vector<string>& handTypes){
        string temp;
        string handTemp;
        vector<Card> cards;
        while(getline(cin, temp)){
                istringstream iss (temp);
                iss >> handTemp;
                handTypes.push_back(handTemp);


                for(int i = 0; i < 4; i++){
                        iss >> handTemp;
                        Card newCard(char_to_value(handTemp[0]), handTemp[1], false);
                        cards.push_back(newCard);
                }

                iss >> handTemp;
                Card start(char_to_value(handTemp[0]), handTemp[1], true);
                cards.push_back(start);
                hands.push_back(cards);
                cards.clear();
        }

}


void print_data(vector< vector<Card> >& hands, vector<string>& handTypes, vector<int>& scores){
        for(int i = 0; i < hands.size(); i++){
                if(handTypes[i] == "h"){
                        cout << "Hand ";
                }
                else{
                        cout << "Crib ";
                }
                for(int j = 0; j < hands[i].size(); j++){
                        cout << value_to_char(hands[i][j].value) << hands[i][j].suit << " ";
                }

                cout << "= " << scores[i] << endl;
        }
}
