#include <iostream>
using namespace std;
template <class T>


class el{
	public:
		//konstruktor niepotrzebny
		
		T wart;
		el<T> *nast;

};

class Macierz{
	int *wsk;
	int rozmiar;
	
	public:
		//Konstruktory//
		
		Macierz(){
			cout << "Konstruktor bezargumentowy macierzy pracuje"<<endl;
			wsk = NULL;
			rozmiar = 0;
		}
		
		Macierz(int roz){
			cout << "Konstruktor macierzy z argumentem <roz> pracuje"<<endl;
			rozmiar = roz;
			wsk = new int[rozmiar*rozmiar];
			for(int i = 0; i < rozmiar*rozmiar ; ++i){
				wsk[i] = i;
			}
		}
		//konstruktor kopiujacy
		Macierz(Macierz &macierz_zrodlowa){
			cout << "Konstruktor kopiujacy macierzy pracuje"<<endl;
			rozmiar = macierz_zrodlowa.rozmiar;
			wsk = new int[rozmiar*rozmiar];
			
			for (int i = 0; i < rozmiar*rozmiar; ++i){
				wsk[i] = macierz_zrodlowa.wsk[i];
			}
		}
		~Macierz(){
			cout << "Destruktor macierzy pracuje"<< endl;
			if(wsk != NULL){
				delete[] wsk;
				wsk = 0;
			}
		}
		
		//Operatory tutaj - do operatow strumieniowych wejscia/wyjscia
		//                  uzywamy tylko nalezyty ostream &s
		friend ostream& operator<<(ostream &s, Macierz &obiekt1){
			for(int i = 0; i < obiekt1.rozmiar*obiekt1.rozmiar; ++i){
				s << obiekt1.wsk[i];
				
				if (i % obiekt1.rozmiar == obiekt1.rozmiar - 1){
					s << endl;
				}
				else{
					s << " ";
				}
			}
			cout << endl;
			return s;
		}
		friend istream& operator>>(istream &s, Macierz &obiekt1){
			s >> obiekt1.rozmiar;
			
			// zabezp przed wyciekiem pam
			if(obiekt1.wsk){
				obiekt1.~Macierz();
			}
			obiekt1.wsk = new int[obiekt1.rozmiar*obiekt1.rozmiar];
			for(int i=0; i < obiekt1.rozmiar*obiekt1.rozmiar; ++i){
				s >> obiekt1.wsk[i];
			}
			
			return s;
		}
		
		Macierz& operator=(const Macierz &obiekt1){
			cout << "Operator '=' pracuje" << endl;
			if(&obiekt1 != this){
				delete[] wsk;
				wsk = new int[obiekt1.rozmiar*obiekt1.rozmiar];
				
				rozmiar = obiekt1.rozmiar;
				for(int i=0; i < rozmiar*rozmiar; ++i){
					wsk[i] = obiekt1.wsk[i];
				}
			}
			return *this;
		}
		
		Macierz& operator+(Macierz &b){
			cout << "Operator '+' pracuje" << endl;
			
			static Macierz pomocnicza;
			
			if(pomocnicza.wsk){
				pomocnicza.~Macierz();
			}
			
			if(rozmiar != b.rozmiar){
				cout << "Macierze maja rozne rozmiary" << endl;
			}
			else{
				pomocnicza.wsk = new int[rozmiar*rozmiar];
				pomocnicza.rozmiar = rozmiar;
				for(int i=0; i < rozmiar*rozmiar; ++i){
					pomocnicza.wsk[i] = wsk[i] + b.wsk[i];
				}
			}
			
			return pomocnicza;
		}
		
		int operator==(Macierz &b){
			if(rozmiar == b.rozmiar){
				for(int i=0; i < rozmiar*rozmiar; ++i){
					if(wsk[i] != b.wsk[i]){
						return 0;
					}
				}
				return 1;
			}
			else{
				return 0;
			}
		}
		
		int operator!=(Macierz &b){
			if(rozmiar == b.rozmiar){
				for(int i=0; i < rozmiar*rozmiar; ++i){
					if(wsk[i] != b.wsk[i]){
						return 1;
					}
				}
				return 0;
			}
			else{
				return 1;
			}
		}
		
		int operator<(Macierz &b){
			int suma_a = 0, suma_b = 0;
			for(int i=0; i < rozmiar * rozmiar; ++i){
				suma_a += wsk[i];
			}
			for(int i=0; i < b.rozmiar * b.rozmiar; ++i){
				suma_b += b.wsk[i];
			}
			if(suma_a < suma_b){
				return 1;
			}
			else{
				return 0;
			}
		}
		
		int operator>(Macierz &b){
			int suma_a = 0, suma_b = 0;
			for(int i=0; i < rozmiar * rozmiar; ++i){
				suma_a += wsk[i];
			}
			for(int i=0; i < b.rozmiar * b.rozmiar; ++i){
				suma_b += b.wsk[i];
			}
			if(suma_a > suma_b){
				return 1;
			}
			else{
				return 0;
			}
		}
		
		Macierz& operator*(Macierz &b){
			static Macierz pomocniczab;
			
			int wynik;
			
			if(pomocniczab.wsk){
				pomocniczab.~Macierz();
			}
			
			if(rozmiar != b.rozmiar){
				cout << "Macierze maja rozne rozmiary" << endl;
			}
			else{
			pomocniczab.wsk = new int[rozmiar*rozmiar];
			pomocniczab.rozmiar = rozmiar;
			for(int y=0; y < rozmiar; ++y){
				for(int x=0; x < rozmiar; ++x){
					wynik = 0;
					
					for (int i=0; i < rozmiar; ++i){
						wynik += wsk[i+y*rozmiar]*b.wsk[x+i*rozmiar];
					}
					pomocniczab.wsk[x+y*rozmiar] = wynik;
				}
				}
				
			}
			return pomocniczab;
		}
};



template <class T>
class lista{
	
	public:
		//friend class el;
		el<T> *pierwszy;
		
		
		
		//kontruktor
		lista(){
			cout << "konstruktor bezargumentowy listy: checked"<<endl;
			pierwszy = NULL;

			
		}
		//destruktor
		~lista(){
			cout<< "destruktor bezargumentowy listy: checked" << endl;
			el<T> *wsk, *tmp;
			wsk = this->pierwszy;
			this->pierwszy = NULL;
			while(wsk!=NULL){
				tmp = wsk->nast;
				delete wsk;
				wsk = tmp;
			}
		}
		
		friend ostream& operator<<(ostream &s, lista<T> &a){
			el<T> *wsk;
			wsk = a.pierwszy;
			
				while(wsk!=NULL){
					s << wsk->wart<<" ";
					wsk = wsk->nast;
				}
				s << endl;
			return s;
		}
		
		friend istream& operator>>(istream &s, lista<T> &a){
			
			el<T> *nowy = new el<T>;
			nowy->nast = NULL;
			s >> nowy->wart; 
			
		
			if (a.pierwszy == NULL){
				a.pierwszy = nowy;
			}
			
			else{
			el<T> *wsk = a.pierwszy;
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
			el<T> *wsk,*wsk2;
			
			wsk = b.pierwszy;
			
			while(wsk!=NULL){
				el<T> *nowy = new el<T>;
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
		
		el<T> *wsk,*wsk2;
		
		if(this->pierwszy == NULL){
			pomocnicza = b;
			return pomocnicza;
		}
		
		pomocnicza=*this;
		
		wsk = b.pierwszy;
		wsk2 = pomocnicza.pierwszy;
		
		while(wsk2->nast!=NULL){
			wsk2 = wsk2->nast;
		}
		while(wsk!=NULL){
			el<T> *nowy = new el<T>;
			nowy->nast = NULL;
			nowy->wart = wsk->wart;
			wsk2->nast = nowy;
			wsk = wsk->nast;
			wsk2 = wsk2->nast;
		}
		
		return pomocnicza;
	}
	
	void sortuj(){
		
		el<T> *wsk,*wsk2,*min,*max,*tmp,*prevmin;

		
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

int tablica[100];

int main(int argc, char** argv) {
	
	lista<Macierz> a,b,c;
	//lista<Macierz> d;
	//cin>>a>>a>>a>>a>>a;
	cin>>b>>b;
	cin>>a>>a>>a;
	
	cout<<"lista a: "<< a << endl;
	cout<<"lista b: "<< b << endl;
	c = (b+a);
	c = (b+a);
	
	cout<<"lista c: "<< c << endl;
	
	cout<<"sortowanie listy c "<<endl;
	c.sortuj();
	
	cout<<c;
	
	//cin >> d >> d >> d >> d >> d;
	//cout << "lista d: " << endl << d << endl;
	
	//d.sortuj();
	
	//cout << "posortowana lista d: " << endl << d;
	
	return 0;
}
