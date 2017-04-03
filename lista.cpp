#include <iostream>
// jebac wszystkie boty
using namespace std;
//skonczyc dodawanie i sortowanie!!!!!!!!!!!!!!!
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
class el{
	public:
		//konstruktor niepotrzebny
		
		int wart;
		el *nast;
		friend class lista;
};


class lista{
	public:
		el *pierwszy;
		
		
		
		//kontruktor
		lista(){
			cout << "konstruktor bezargumentowy listy: checked"<<endl;
			pierwszy = NULL;

			
		}
		//destruktor
		~lista(){
			cout<< "destruktor bezargumentowy listy: checked" << endl;
			el *wsk, *tmp;
			wsk = this->pierwszy;
			this->pierwszy = NULL;
			while(wsk!=NULL){
				tmp = wsk->nast;
				delete wsk;
				wsk = tmp;
			}
		}
		
		friend ostream& operator<<(ostream &s, lista &a){
			el *wsk;
			wsk=a.pierwszy;
			
				while(wsk!=NULL){
					s << wsk->wart<<" ";
					wsk = wsk->nast;
				}
				s << endl;
			return s;
		}
		
		friend istream& operator>>(istream &s, lista &a){
			
			el *nowy = new el;
			nowy->nast = NULL;
			s >> nowy->wart; 
			
		
			if (a.pierwszy == NULL){
				a.pierwszy = nowy;
			}
			
			else{
			el *wsk = a.pierwszy;
				while (wsk->nast!=NULL){
					wsk = wsk->nast;
					
				}
			
			wsk->nast = nowy;
			
		}
		return s;
	}
	
	lista& operator=(lista &b){
			cout << "Operator '=' pracuje" << endl;
			
			if(this==&b){
				return *this;
			}
			
			this->~lista();
			el *wsk,*wsk2;
			
			wsk = b.pierwszy;
			
			while(wsk!=NULL){
				el *nowy = new el;
				nowy->nast = NULL;
				nowy->wart = wsk->wart;
				if(this->pierwszy == NULL){
					this->pierwszy = nowy;
				}
				else{
					wsk2->nast = nowy;
				}
				wsk2 = nowy;
				wsk = wsk->nast;
				
			}
			
			return *this;
		}
		
	lista& operator+(lista &b){
		cout << "operator '+' pracuje" << endl;
		
		static lista pomocnicza;
		
		el *wsk,*wsk2;
		
		pomocnicza=*this;
		
		wsk = b.pierwszy;
		wsk2 = pomocnicza.pierwszy;
		if(wsk2!=NULL){
			wsk2=wsk2->nast;
		}
		while(wsk!=NULL){
			el *nowy = new el;
			nowy->nast = NULL;
			nowy->wart = wsk->wart;
			wsk2 = nowy;
			wsk = wsk->nast;
			wsk2 = wsk2->nast;
			
		}
		
		return pomocnicza;
	}	
};

//skonczyc dodawanie i sortowanie!!!!!!!!!!!!!!!
int main(int argc, char** argv) {
	
	lista a,b,c;
	
	cin>>a>>a>>a;
	cin>>b>>b;
	//cout<<a;
	//cout<<(b=a);
	c=a+b;
	//c=a;
	cout<<c;
	//a.~lista();
	
	//cout<<a;
	
	return 0;
}//copyright R by Fryderyk Muras & Przemyslaw Michalek 2017
