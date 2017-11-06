#include<iostream>
#include<vector>
using namespace std;
class observer;
class cricketmatch{

	vector<observer*> view;
	public:
		int score=0,wicket=0,overleft=0;
	cricketmatch(){};
	void set_state(int score,int wicket,int over){
		this->score=score;
		this->wicket=wicket;
		this->overleft=over;
		notify();
	}
	void notify();
	void get_state(){
		cout<<"score = "<<score<<"\n";
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
			c->get_state();
			cout<<"average score required : "<<(float)c->score/c->overleft<<" rpo. \n";
		}
	
};

class wicketsleft:public observer{
	public:
		void update(cricketmatch* c){
			c->get_state();
			cout<<"wicket left : "<< (12)-(c->wicket)<<" .\n";
		
		}
};

	void cricketmatch::notify(){
			for(int i=0;i<view.size();i++){
				view[i]->update(this);//can pass other local info if do not want to send "this pointer"
			}

	}	
int main(){
	
	cricketmatch c;
//	observer* co[]={ new scoreavg,new wicketsleft};
    scoreavg avg;
    wicketsleft w;
		
	
	c.attach(&avg);
	c.attach(&w);
	
	c.set_state(50,6,15);
}