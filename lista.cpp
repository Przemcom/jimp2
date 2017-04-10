#include <iostream>

using namespace std;


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
		while(wsk2->nast!=NULL){
			wsk2 = wsk2->nast;
		}
		while(wsk!=NULL){
			el *nowy = new el;
			nowy->nast = NULL;
			nowy->wart = wsk->wart;
			wsk2->nast = nowy;
			wsk = wsk->nast;
			wsk2 = wsk2->nast;
		}
		
		return pomocnicza;
	}
	
	void sortuj(){
		
		el *wsk,*wsk2,*min,*max,*tmp,*prevmin;

		
		max = this->pierwszy;
		
		wsk = this->pierwszy;
		min = max;
		while(wsk!=NULL){ //tutaj przepinam pierwszy element tak, ze zanim zaczne wlasciwa petle, na pierwszym miejscu w liscie jest najmniejszy element
			
			if(wsk->wart < min->wart){
				min = wsk;
				
			}
			if(wsk->wart > max->wart){  //jednorazowe znalezienie najwiekszego elementu
				max = wsk;
			}
			wsk = wsk->nast;
		}
		if(min != this->pierwszy){
			prevmin = this->pierwszy;
			while(prevmin->nast != min){
				prevmin = prevmin->nast;
			}	
			prevmin->nast = min ->nast;
			tmp = this->pierwszy;
			min->nast = tmp;
			this->pierwszy = min;
			
		}
		
		wsk2 = this->pierwszy->nast;
		
		//cout<< *this;
		while(wsk2!=NULL){
			wsk = wsk2;
			min = wsk2;
			while(wsk->nast != NULL){
				
				if(wsk->nast->wart < min->wart){
					min = wsk->nast;
					prevmin = wsk;
				}
				wsk = wsk->nast;
			}
			
			if(wsk2 != this->pierwszy){
				tmp = this->pierwszy;
				while(tmp->nast != wsk2){
					tmp = tmp->nast;
				}
				
			}
			//cout << "minimum to: " << min->wart << " prevmin to: " <<prevmin->wart << " tmp to: " <<tmp->wart<< " wsk2: " << wsk2->wart << " wsk: " << wsk->wart <<endl;
			
			
			
			if(min != wsk2){
				tmp->nast = min;
				prevmin->nast = min->nast;
				min->nast = wsk2;
				
			}
			else{
				wsk2 = wsk2->nast;
			}
			
			//cout << *this;
			if(min->wart == max->wart){
				wsk2 = NULL;
			}
			
		} 
		
	}	
};


int main(int argc, char** argv) {
	
	lista a,b,c;
	
	cin>>a>>a>>a>>a>>a;
	cin>>b>>b>>b;
	
	
	cout<<"lista a: "<< a << endl;
	cout<<"lista b: "<< b << endl;
	c = (a+b);
	
	cout<<"lista c: "<< c << endl;
	
	cout<<"sortowanie listy c "<<endl;
	c.sortuj();
	
	cout<<c;
	
	
	
	return 0;
}
