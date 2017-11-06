#include<iostream>
using namespace std;

class memento{//memento....created and read by originator
	
	int _state;
	public:
		  memento(int i){
			  set_state(i);
		  }
		  int get_state(){
			   return _state;
		  }
		  void set_state(int i){
			_state=i;
		  }
	//friend class number;//originator
};

class number{//originator...create memento...know ow to create memento which get restore in future
			 
	int _state;
	public: 
		   number(int i):_state(i){
		   }
		   
		   memento* create_memento(){
			   return new memento(_state);//care taker keep it and use in redo/undo operations//checkpoint
			}
			
			void reinstate(memento* m){//caretaker send memento which it keep with it
				_state=m->get_state(); //restore of  state happen here
			}
			
			void  half(){//operations on  state
				_state=_state/2;
			}
			
			void  doublee(){//operations on state
				_state=_state*2;
			}
			
			int get_value(){
				return _state;
			}
};

class command{//know when and why  originator save and reetore
      typedef void (number::*action)();
	   number* _receiver;
	   action _action;
	   static command* _commandList[20];
	   static memento* _mementoList[20];
	   static int _numcommand; 
	   static int uplimit;
	   public:
	     // typedef void (number::*action)();
	 
	   command(number* n,action ac){
			 _receiver=n;
			 _action=ac;
	   }
	   
	   static void undo(){
			if (_numcommand>0){
			  	_commandList[_numcommand-1]->_receiver->reinstate(_mementoList[_numcommand-1]);
				_numcommand--;
			}
			else{
				cout<<"nothing = ";
				return;
			}
	   }
	   static void redo(){
		   if(_numcommand>uplimit){
			   cout<<"exceed";
			   return;
			}else{
				
				(_commandList[_numcommand]->_receiver->*(_commandList[_numcommand]->_action))();
				_numcommand++;
			}
	   }
	   
	   void execute(){
		_commandList[_numcommand]=this;
		_mementoList[_numcommand]=_receiver->create_memento();//know when save memento
		
		if(_numcommand>uplimit)
			uplimit=_numcommand;
		
		
		_numcommand++;
		(_receiver->*_action)();
      }
		
};

command* command::_commandList[];
memento* command::_mementoList[];

int command::_numcommand=0;
int command::uplimit=0;
//void comvmand::undo();
//void command::redo();

int main(){
	
	int i=4;
	number *object=new number(4);
    command * com[2];
	com[0]=new command(object,&number::half);
	com[1]=new command(object,&number::doublee);
	cout<<"half operation on ";
	cout<<object->get_value()<<endl;
    com[0]->execute();
    cout<<"output =  ";
    cout<<object->get_value()<<endl;
	cout<<"double operation on =  ";
    cout<<object->get_value()<<endl;
    com[1]->execute();
    cout<<"output =  ";
    cout<<object->get_value()<<endl;
	cout<<"redo double on  ";
	cout<<object->get_value()<<endl;
	command::undo();
	command::redo();
	cout<<"output =  ";
    cout<<object->get_value()<<endl;
	
}