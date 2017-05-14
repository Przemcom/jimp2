#include <iostream>
#include <fstream>


using namespace std;

class duza_liczba{
	public:
		int r;
		char *wsk, *tmp;
		
		
		
		duza_liczba(){
			cout << "Konstruktor bezargumentowy pracuje"<<endl;
			r = 0;
		}
		
		~duza_liczba(){
		cout << "Destruktor pracuje"<< endl;
		if(r != 0){
			delete[] wsk;
			r = 0;
		}
		}
		
		
		friend istream& operator>>(istream &s, duza_liczba &obiekt1){
			
			int ile_miejsc = 10, i=0;
			bool flag = true;
			
			// zabezp przed wyciekiem pam
			if(obiekt1.r != 0){
				obiekt1.~duza_liczba();
			}
	
			obiekt1.wsk = new char[ile_miejsc];
			
			while(flag){
				obiekt1.wsk[i] = s.get();
				if ((int)obiekt1.wsk[i] < 58 && (int)obiekt1.wsk[i] > 47){
					obiekt1.r++;
					i++;
				}
				else{
					flag = false;
				}
				
				if(obiekt1.r == ile_miejsc){
					
					obiekt1.tmp = new char[ile_miejsc];
					for(int j=0; j<obiekt1.r; ++j){
						obiekt1.tmp[j] = obiekt1.wsk[j];
					}
					delete[] obiekt1.wsk;
					ile_miejsc += 10;
					obiekt1.wsk = new char[ile_miejsc];
					for(int j=0; j<obiekt1.r; ++j){
						obiekt1.wsk[j] = obiekt1.tmp[j];
					}
					delete[] obiekt1.tmp;
				}	
			}
			return s;
		}
		
		friend ostream& operator<<(ostream &s, duza_liczba &obiekt1){
			
			for(int i=0; i<obiekt1.r; ++i){
				s << obiekt1.wsk[i];
			}
			s << " rozmiar: " << obiekt1.r;
			s << endl;
			return s;
		}
		
		duza_liczba& operator=(duza_liczba &b){
			if(this==&b){
				return *this;
			}
			
			if(this->r != 0){
				this->~duza_liczba();
			}
			
			this->wsk = new char[b.r + 1];
			this->r = b.r;
			
			for(int i=0; i <= b.r; ++i){
				this->wsk[i] = b.wsk[i];
			}
			
			return *this;
		}
		
		
		
		duza_liczba& operator+(duza_liczba &b){
			
			int rozmiar, mniejszy, i, j, k;
			bool dycha = false;
			char *temp, *tempmin;
			static duza_liczba wynik;
			
			
			cout << "'+' pracuje" << endl;
			
			if(wynik.r != 0){
				wynik.~duza_liczba();
			}
			//*******************ustawiam wskazniki na krotsza i dluzsza liczbe**************************
			if(this->r > b.r){
				rozmiar = this->r;
				mniejszy = b.r;
				temp = this->wsk;
				tempmin = b.wsk;
			}
			else{
				rozmiar = b.r;
				mniejszy = this->r;
				temp = b.wsk;
				tempmin = this->wsk;
			}
			//____________________________________________________________________________________________
			
			
			wynik.wsk = new char[rozmiar + 1];
			wynik.r = rozmiar + 1;
			
			wynik.wsk[0] = '0';
			for(i=1; i <= rozmiar; ++i){
				wynik.wsk[i] = temp[i-1];  //przepisanie dluzszej liczby do wyniku
			}
			
			i = rozmiar;
			j = mniejszy-1;
			
			while(j>=0){  //petla tylko na dlugosc krotszej liczby
				

				if(wynik.wsk[i] + tempmin[j] - 96 > 9){
					dycha = true;
					
				}
				
				k = i;
				while(dycha){
					wynik.wsk[k-1] += 1;
					if(wynik.wsk[k-1] - 48 == 10){
						wynik.wsk[k-1] = '0';
						k--;
					}
					else{
						dycha = false;
					}
				}
				
				wynik.wsk[i] = (wynik.wsk[i] + tempmin[j] - 96) % 10 + 48;
				

				i--;
				j--;

			}
		
			return wynik;
		}
		
		duza_liczba& operator+=(duza_liczba &b){
			
			return (*this + b);
			
			
			
		}
};



/*class wieksza_liczba : public duza_liczba{
	
	public:
		
		wieksza_liczba& operator*(wieksza_liczba &b){
			
			static wieksza_liczba wynik;
			wieksza_liczba temp;
			int wiekszy, i, j, tmp = 1;
			
			if (this->r > b.r){
				temp = b;
				wiekszy = this->r;
			}
			else{
				temp = *this;
				wiekszy = b.r;
			}
			
			wynik.wsk = new char[wiekszy + temp.r + 1];
			wynik.r = wiekszy + temp.r + 1;
			
			for(int z = 0; z < wynik.r; z++){
				wynik.wsk[z] = '0';
			}

			

			
			i = 0;
			
			while(i <= temp.r){
				
				tmp = 1;
				
				for(int w = 0; w < temp.r - i; w++){
					tmp *= 10;
				}
				
				tmp = tmp * (temp.wsk[i] - 48);
				
				for(j = 0; j < tmp; j++){
					wynik = (wynik + temp);
				}
				
				i++;
				
			}
			
			wynik += temp;
			
			return wynik;	
		}
	
};

*/

int main() {
	
	duza_liczba a,c,d;
	
	cin >> a;
	cin >> c;

	d = (a+c);

	cout << a;
	cout << c;
	cout << d;
	
	//d+=c;
	
	
	
	return 0;
}
