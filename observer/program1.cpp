#include<iostream>
using namespace std;
class observer;
class cricketmatch{
	int score=0,wicket=0,overleft=0;
	vector<observer*> view;
	public:
	cricketmatch();
	void set_state(int score,int wicket){
		for(int i=0;i<;view.size();i++){
			view[0]->update(this);
		}
	}
	
	void get_state(){
		cout<<"score = "<<score;<<"\n"
		cout<<"wicket ="<<wicket<<"\n";
	}
	
	void attach(observer* o){
		view.push_back(o);
	}
};

class observer{
	public: 
		   virtual void update(cricketmatch*)=0;
};

class scoreavg:public observer{
	public:
		void update(cricketmatch* c){
			cout<<"average score required : "<<c->score/c->overleft<<" per over. \n";
		}
	
};

class wicketsleft:public observer{
	public:
		void update(cricketmatch* c){
			cout<<"wicket left : "<< (12)-(c->wicket)<<" .\n";
		}
};

int main(){
	
	cricketmatch c;
	scoreavg avg;
    wicketsleft w;
		
	c->attach(&avg);
	c->attach(&w);
	
	c.setstate(50,6,15);
}