
#include<iostream>
#include<vector>
using namespace std;

struct TrieNode{
    bool wordEnd;
    trieNode* children[26];
}

TrieNode* getTrieNode(){
  TrieNode* temp = new TrieNode();
  temp->wordEnd = false;
  for(int i = 0 ; i < 26;i++){
     temp->children[i] = NULL;
  }
  return temp;
}

void insertTrie(TrieNode* root,string str){

     TrieNode* crawler = root;

     for(char ch:str){
         int idx = ch-'0';
         TrieNode* temp = getTrieNode();
         if(crawler->children[idx] == NULL){
             crawler->children[idx] = temp;
         }
         crawler = crawler->children[idx];
     }
     crawler->wordEnd = true;

}

bool searchWordTrie(TrieNode* root,string str){
     TrieNode* crawler = root;

     for(char ch:str){
        int idx = ch-'0';
        if(crawler->children[idx] == NULL){
            return false;
        }
        crawler = crawler->children[idx];
     }
     return crawler->wordEnd;
}
int main()
 {
	int T;
	cin >> T;
	while(T--) {
	    int N;
	    cin >> N;
	    string elements;
	   
	}
	return 0;
}