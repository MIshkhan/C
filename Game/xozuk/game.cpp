#include <iostream>
#include <ncurses.h>
#include <string>
#include <vector>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <unistd.h>
#include "game.hpp"
using namespace std;

const char* game::address = "f.txt";

void print_menu(const vector<string>& page) {
	clear();
	for(int i(0); i<page.size(); i++){
		for(int j(0); j<page[i].size(); j++)
            printw("%c", page[i][j]);
		printw("\n");	
	}
}

int menu(){
 begin:	
	int x = 6;
	int y = 20;
	int state = 0;     
	vector<string> page;
	page.push_back("*****************************************");
	page.push_back("*                                       *");
	page.push_back("*                       -----------     *");
	page.push_back("*      (\\____/)        | P I G G Y |    *");
	page.push_back("*      / @__@ \\         -----------     *");
	page.push_back("*     (  (oo)  )                        *");
	page.push_back("*      `-.~~.-'     -> SINGLE   GAME    *");
	page.push_back("*       /   \\                           *");
	page.push_back("*     @/     \\_        FRIENDLY GAME    *");
	page.push_back("*    (/ /   \\ \\)                        *");
	page.push_back("*     WW`----'WW       EXIT             *");
	page.push_back("*                                       *");	
	page.push_back("*****************************************");
	clear();	
	char c;//for getch
	while(true){
		print_menu(page);
		c = getch();
		switch(c){
			case 66:{ // up
				if(x < 10){
					page[x+2][y] = page[x][y];
					page[x+2][y+1] = page[x][y+1];
					page[x][y] = ' ';
					page[x][y+1] = ' ';
					x+=2;
				}else{
					page[x-4][y] = page[x][y];
					page[x-4][y+1] = page[x][y+1];
					page[x][y] = ' ';
					page[x][y+1] = ' ';					
					x-=4;
				}
				break;
			}
			case 65:{ //down
				if(x > 6){
					page[x-2][y] = page[x][y];
					page[x-2][y+1] = page[x][y+1];
					page[x][y] = ' ';
					page[x][y+1] = ' ';
					x-=2;
				}else{
					page[x+4][y] = page[x][y];
					page[x+4][y+1] = page[x][y+1];
					page[x][y] = ' ';
					page[x][y+1] = ' ';					
					x+=4;
				}
				break;
			}
			case '\n':{ //enter
				switch(state){
					case 0:{
						switch(x){
							case 6:{ return 0; } // for single
							case 8:{
								state = 1;
								x = 6;
								page[6] = ("*      `-.~~.-'     -> PLAYER 1         *");
								page[8] = ("*     @/     \\_        PLAYER 2         *");
								break;
							}
							case 10:{ return 3;	} // for exit
						}
						break;
					}
					case 1:{
					   switch(x){
							case 6:{	return 1;	} // for player 1
							case 8:{	return 2;	} // for player 2
							case 10:{ goto begin;}
				       }
				       break;
					}
				}				
			}			
		}		
	}
}

void game::start(){  
 begin:   	
    fstream f;
    initscr();  
    current_player.turn = menu();
    
    if(current_player.turn == 1 || current_player.turn == 0) {
        f.open(address, ios::out); // cleaning file
        f.close();
        current_player.turn == 1 ? updateCards(getShuffledCards(), getCardsFromBoard() , 1) : updateCards(getShuffledCards(), getCardsFromBoard() , 0);
    }   
    printInfo();
    ostringstream ss;
    ss << current_player.turn;      
    switch(current_player.turn){
        case 0:{ // Game with Computer
            halfdelay(15);
            while(true) { 
                if(isGameOver()) { endwin(); goto begin;} // Game Over -> Go to Menu
                chooseCard();  // me
                printInfo(); 
                getch();
                chooseCardForComp();// computer
                printInfo();            
            }
            break;
        }
        case 1: case 2:{ // Game with human
            halfdelay(2);
            do {           
                printInfo();
                usleep(500000);
                f.open(address, ios::in);
                string data;
                getline(f, data); // player's name
                f.close(); 
                if(data.find("Player_")!=std::string::npos && isGameOver()) { endwin(); goto begin;} // Game Over -> Go to Menu
                if(!data.compare("Player_"+ss.str())){ 
                    chooseCard();
                }	
                printInfo();    
                getch();
            } while(true);
            break;
         }
        case 3:{
            endwin();
            return;
        }
    }
    endwin();
}

vector<int> game::getShuffledCards() const {
    int cardsArray[] = {
        16, 17, 18 , 19, 10, 11, 12, 13, 14,
        26, 27, 28 , 29, 20, 21, 22, 23, 24,
        36, 37, 38 , 39, 30, 31, 32, 33, 34, 
        46, 47, 48 , 49, 40, 41, 42, 43, 44 
    };
    vector<int> cards (cardsArray, cardsArray + sizeof(cardsArray) / sizeof(cardsArray[0]) );
    srand((unsigned)time(NULL));
    for(int i = 0; i < 36; ++i) {
        int j = rand() % 36;
        int tmp = cards[i];
        cards[i] = cards[j];
        cards[j] = tmp;
    }
    return cards;
} 

vector<int> game::getCardsFromDeck() const {
    fstream f;
    string data;
    f.open(address, ios::in);	
    getline(f, data); // ignoring player's name
    getline(f, data); // ignoring empty line
    getline(f, data); // cards
    vector<int> cards ;
    char * splitData;
    char  charData[250] ;
    strcpy(charData, data.c_str());
    splitData = strtok (charData , " ");
    while (splitData != NULL) {
        cards.push_back(atoi(splitData));
        splitData = strtok (NULL, " ");
    }
    f.close();    
    return cards;
}

vector<int> game::getCardsFromBoard() const {
    vector<int> cards  ;
    fstream f;
    string data;
    f.open(address, ios::in);
    getline(f, data); // ignoring player's name
    getline(f, data); // ignoring empty line
    getline(f, data); // ignoring cards in deck
    getline(f, data); // ignoring empty line
    getline(f, data); // cards from board
    char  buf[250] ;  // Have a buffer string
    stringstream ss(data); // Insert the string into a stream
    while (ss >> buf)
        cards.push_back(atoi(buf));
    f.close(); 
    return cards;
}

void game::input_card_on_page(int i, int j, int card, vector<string>& page) const {
    for(int n = 0; n < 5; ++n) page[i+1][j+n+6] = '-'; //      -----  
    page[i+2][j+5] = '|'; page[i+2][j+11] = '|';       //     |     | 
    page[i+3][j+5] = '|'; page[i+3][j+11] = '|';       //     |     | 
    page[i+4][j+5] = '|'; page[i+4][j+11] = '|';       //     |     | 
    for(int n = 0; n < 5; ++n) page[i+5][j+n+6] = '-'; //      -----      
    switch(card%10){
        case 6 :page[i+2][j+6]= '6';  break;
        case 7 :page[i+2][j+6]= '7';  break; 
        case 8 :page[i+2][j+6]= '8';  break;
        case 9 :page[i+2][j+6]= '9';  break;
        case 0 :{ 
                    page[i+2][j+6]= '1'; 
                    page[i+2][j+7] = '0'; break; 
                }
        case 1 :page[i+2][j+6]= 'J';  break;
        case 2 :page[i+2][j+6]= 'Q';  break;
        case 3 :page[i+2][j+6]= 'K';  break;
        case 4 :page[i+2][j+6]= 'T';  break;  
    }
    switch(card/10) {
        case 1: page[i+3][j+8] = 'H';  break; // ♥
        case 2:	page[i+3][j+8] = 'D';  break; // ♦
        case 3: page[i+3][j+8] = 'C';  break; // ♣
        case 4:	page[i+3][j+8] = 'S';  break; // ♠
        case 5: page[i+3][j+8] = 'X';  break; // 55 hidden card
    }  
}

vector<string> game::get_page_with_cards(const vector<int>& cards) const {
    vector<string> page;
    int size = cards.size();
    int count = 0;
    int height = size % 9 > 0 ? (size / 9 + 1 ) * 6 :  size / 9 * 6;
    for(int j = 0; j < height; ++j)
        page.push_back("                                                                                                    ");  
    for(int i = 0; i < size/9; ++i)
       for(int j = 0; j < 9; ++j)
            input_card_on_page(6*i,11*j, cards[count++], page);
    if(size % 9 > 0)
        for(int j = 0; j < size % 9; ++j)
            input_card_on_page(6*(size/9),11*j, cards[count++], page);
    return page;
}      

vector<int> game::get_hidden_cards(const vector<int>& cards) const {
    vector<int> hiddencards(cards.size(), 55);
    return hiddencards;
}

void game::updateCards(const vector<int>& cardsInDeck, const vector<int>& cardsOnBoard, int nextPlayersIndex) {
    fstream f;
    f.open(address, ios::out);	
    std::ostringstream ss;
    ss << nextPlayersIndex;
    f << "Player_" << ss.str();
    f << "\n---Cards in Deck---\n";
    for(int i=0; i<cardsInDeck.size(); ++i){
        f << cardsInDeck[i] << " ";
    }
    f << "\n---Cards on Board---\n";
    for(int i=0; i<cardsOnBoard.size(); ++i){
        f << cardsOnBoard[i] << " ";
    }    
    f.close();
}

void game::print_page(const vector<string>& page) const {
	for(int i(0); i<page.size(); i++){
		for(int j(0); j<page[i].size(); j++)
            printw("%c", page[i][j]);
		printw("\n");	
	}
}

void game::clean_page(vector<string>& page) {
    for(int i=0; i<page.size(); ++i)
        page[i] = ("                                                                                                    "); 
}

void game::move_card_up(vector<string>& page,int x, int y) const {
	for(int i = y; i < y+5; ++i)  //rows
		for(int j = x; j <x+7; ++j)  //columns
			page[i-1][j] = page[i][j];
    for(int j = x; j <x+7; ++j)
        page[y+4][j] = ' '; 
}

void game::move_card_down(vector<string>& page,int x,int y) const {
    for(int i = y+4; i >= y; --i)  //rows
        for(int j = x; j <x+7; ++j) //columms
        page[i][j] = page[i-1][j];
    for(int j = x; j <x+7; ++j)
        page[y-1][j] = ' ';
}
              
void game::printInfo() const {
    clear();
    printw("==={ IN DECK  }=======================================================================================\n");
    print_page(get_page_with_cards(get_hidden_cards(getCardsFromDeck())));attroff(COLOR_PAIR(1));    
    printw("\n==={ ON BOARD }=======================================================================================\n");
    print_page(get_page_with_cards(getCardsFromBoard()));
    printw("\n==={ MY CARDS }=======================================================================================\n");
    print_page(get_page_with_cards(myCards));
    printw("\n");
}

int game::print_moveable_page(const string& name1, const vector<int>& cards1, 
                              const string& name2, const vector<int>& cards2, 
                              const string& name,  const vector<int>& cards) const {
    int x = 5 ; //5
    int y = 1 ; //1
    vector<string> page	= get_page_with_cards(cards); 
	move_card_up(page,x,y);
	while(true){
        int size = cards.size();

        clear();         
        printw(name1.c_str());printw("\n");
        print_page(get_page_with_cards(cards1)); printw("\n");
        printw(name2.c_str());printw("\n");
        print_page(get_page_with_cards(cards2)); printw("\n");
        printw(name.c_str());printw("\n");
        print_page(page); printw("\n");
        
		char c = getch();
		switch(c){
            case ERR: break;   
			case 65: { //up
			    move_card_down(page,x,y); 
			    if(y>1) y-=6; 
			    else if(size%9*11-6 >= x) y = (size/9 + 1)*6-5; 
			    else y = size/9*6-5; 
			    move_card_up(page,x,y); 
			    break; 
			} 
			case 66: { //down
			    move_card_down(page,x,y); 
			    if(size-((y/6+1)*9+x/11+1) >= 0)  y += 6; 
			    else y = 1; 
			    move_card_up(page,x,y); 
			    break;
			}  
			case 67: { //right              
                move_card_down(page,x,y);
                if((size - y/6*9) >= 9) {
                    if( x == 93) x = 5;
                    else x += 11;
                } else if(x == (((size - y/6*9)*11)-6))  x = 5;
                       else x += 11;
                move_card_up(page,x,y);
                break;
            }                                   
            case 68: { //left  
                move_card_down(page,x,y); 
                if((size - y/6*9) >= 9) {
                    if( x == 5) x = 93;
                    else x -= 11;
                } else if( x == 5 ) x = (size - y/6*9)*11-6;
                       else x -= 11;
                move_card_up(page,x,y);
                break;
            }          
            case '\n':  return(y/6*9+x/11);
		}
	}
}

void game::chooseCardForComp() {
    vector<int> cardsOnBoard = getCardsFromBoard();
    vector<int> cardsInDeck = getCardsFromDeck();
    int choosenIndex ;
    srand (time(NULL));
    
    if(compCards.size() > 0){
        choosenIndex =  rand() % compCards.size();         
        if(cardsOnBoard.size()!=0 && compCards[choosenIndex]/10 == cardsOnBoard[cardsOnBoard.size()-1]/10){
            for(int i = 0; i<cardsOnBoard.size(); ++i){
                compCards.push_back(cardsOnBoard[i]);
            }
            cardsOnBoard.clear();
        }
        else{
            cardsOnBoard.push_back(compCards[choosenIndex]);
            compCards.erase(compCards.begin() + choosenIndex);
        }
    }
    else{
        choosenIndex =  rand() % cardsInDeck.size(); 
        if((cardsOnBoard.size() != 0 ) && (cardsInDeck[choosenIndex]/10 == cardsOnBoard[cardsOnBoard.size()-1]/10)){
            compCards.push_back(cardsInDeck[choosenIndex]);
            cardsInDeck.erase(cardsInDeck.begin()+choosenIndex);
            for(int i = 0; i<cardsOnBoard.size(); ++i){
                compCards.push_back(cardsOnBoard[i]);
            }
            cardsOnBoard.clear();
        }
        else{
            cardsOnBoard.push_back(cardsInDeck[choosenIndex]);
            cardsInDeck.erase(cardsInDeck.begin() + choosenIndex);
       }
   }        
   updateCards(cardsInDeck, cardsOnBoard, 0);  
}

void game::chooseCard() {
    vector<int> cardsOnBoard = getCardsFromBoard();
    vector<int> cardsInDeck = getCardsFromDeck();
    
    int choosenIndex ;
    if(myCards.size() > 0){
        choosenIndex = print_moveable_page(
        "==={ IN DECK  }=======================================================================================",
                                            get_hidden_cards(cardsInDeck), 
        "==={ ON BOARD }=======================================================================================", 
                                            cardsOnBoard, 
        "==={ MY CARDS }=======================================================================================",  
                                            myCards);      
        if(!cardsOnBoard.empty() && myCards[choosenIndex]/10 == cardsOnBoard[cardsOnBoard.size()-1]/10){
            for(int i = 0; i<cardsOnBoard.size(); ++i){
                myCards.push_back(cardsOnBoard[i]);
            }
            cardsOnBoard.clear();
        }
        else{
            cardsOnBoard.push_back(myCards[choosenIndex]);
            myCards.erase(myCards.begin() + choosenIndex);
        }
    }
    else{
        choosenIndex = print_moveable_page(
        "==={ MY CARDS }=======================================================================================",  
                                           myCards, 
        "==={ ON BOARD }=======================================================================================", 
                                           cardsOnBoard, 
        "==={ IN DECK  }=======================================================================================", 
                                           get_hidden_cards(cardsInDeck));                                                                                                             
        if(!cardsOnBoard.empty() && (cardsInDeck[choosenIndex]/10 == cardsOnBoard[cardsOnBoard.size()-1]/10)){
            myCards.push_back(cardsInDeck[choosenIndex]);
            cardsInDeck.erase(cardsInDeck.begin()+choosenIndex);
            for(int i = 0; i<cardsOnBoard.size(); ++i){
                myCards.push_back(cardsOnBoard[i]);
            }
            cardsOnBoard.clear();
        }
        else{
            cardsOnBoard.push_back(cardsInDeck[choosenIndex]);
            cardsInDeck.erase(cardsInDeck.begin() + choosenIndex);
       }
   }
    switch (current_player.turn) {
        case 1 : updateCards(cardsInDeck, cardsOnBoard, 2); break;
        case 2 : updateCards(cardsInDeck, cardsOnBoard, 1); break;
        default : updateCards(cardsInDeck, cardsOnBoard, 0); break;   
    }
}

bool game::isGameOver() const {
    if(myCards.size()+getCardsFromBoard().size() == 36){
        clear();
        printw("\n\n\n\n\n\n\n\n\n\n                          You Lose");
        getch();
        usleep(3000000);
        return true;
    } else if (myCards.size()+getCardsFromDeck().size() == 0){
        clear();
        printw("\n\n\n\n\n\n\n\n\n\n                           You Win");
        getch();
        usleep(3000000);
        return true;
    }
    return false;
}
