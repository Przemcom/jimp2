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
			
			int rozmiar,tmpa = this->r - 1,tmpb = b.r - 1, x, y, z, *tab, popr;
			bool dycha = false, poprawka = false;
			char temp;
			static duza_liczba wynik;
			
			
			cout << "'+' pracuje" << endl;
			
			if(wynik.r != 0){
				wynik.~duza_liczba();
			}
			
			if(this->r > b.r){
				rozmiar = this->r;
			}
			else{
				rozmiar = b.r;
			}
			
			wynik.wsk = new char[rozmiar + 1];
			wynik.r = rozmiar+1;
			//tab = new int[rozmiar +1];
			
			for(int i = rozmiar; i>0; --i){
				
				/*if (tmpa < 0){  //znaczy, ¿e koniec liczby
					x = 0;
				}
				else{
					x = this->wsk[tmpa] - 48;
				}
				
				if (tmpb < 0){
					y = 0;
				}
				else{
					y = b.wsk[tmpb] - 48;
				}
				
				
				if(dycha){  //przesuniecie o 10
					x++;
					dycha = false;
				}
				if(x+y > 9){
					dycha = true;
					x-=10;
				}
				z = x+y;
				//z = static_cast<char>(z);
				//temp = static_cast<char>(z);
				//tab[i] = z;
				
				wynik.wsk[i] = z;
				*/
				//cout << char(z) << " ";
				
				//cout << wynik.wsk[i] << " ";
				//cout << temp << " ";
				
				
				if(tmpa >= 0 && tmpb >= 0){
					wynik.wsk[i] = ((this->wsk[tmpa] + b.wsk[tmpb] - 96) % 10) + 48;
					//cout << "po dodaniu: " << wynik.wsk[i]  << endl;
					 
				}
				
				if(tmpa >= 0 && tmpb < 0){
					wynik.wsk[i] = ((this->wsk[tmpa] - 48) % 10) + 48;
				
				}
				
				if(tmpa < 0 && tmpb >= 0){
					wynik.wsk[i] = ((b.wsk[tmpb] - 48) % 10) + 48;
				
				}
				
				if(dycha){
				
						wynik.wsk[i] += 1;
						dycha = false;
					
					
					//cout << "dycha na i =" << i-1  << "bo suma: " << this->wsk[tmpa] + b.wsk[tmpb] - 96 << endl;
					
				}
				if(wynik.wsk[i] == ':'){
					wynik.wsk[i] = '0';
					dycha = true;
				}
				//if(wynik.wsk[i] == 'A'){
				//	wynik.wsk[i] = ' ';
				//}
				
				if((this->wsk[tmpa] + b.wsk[tmpb] - 96) > 9 && this->wsk[tmpa] < 57 && b.wsk[tmpb] < 57){
					dycha = true;
					
					//cout << "dycha na i =" << i-1  << "bo suma: " << this->wsk[tmpa] + b.wsk[tmpb] - 96 << endl;
				}
				cout << tmpa << " " << tmpb << " " << dycha << endl;
				if((tmpa == 0 || tmpb == 0) && dycha){
					poprawka = true;
					popr = i-1;
					cout << "popr na " << i << endl;
				}
				
				if(i == 1 && dycha){
					wynik.wsk[0] == '1';
				}
			//	if (this->wsk[tmpa] - 48 <= 9 || b.wsk[tmpb] - 48 <= 9){
			//		dycha = false;
			//2	}
				
				//cout << (this->wsk[tmpa] + b.wsk[tmpb] - 96) % 10 << " ";
				tmpa--;
				tmpb--;
			}

			//cout << endl;
			/*for(int i=0; i <= rozmiar; ++i){
				cout << tab[i];
			}
			*/
			//cout << endl;
			
			return wynik;
		}
};





int main() {
	
	duza_liczba a,c,d;
	
	cin >> a;
	cin >> c;

	d = (a+c);

	cout << a;
	cout << c;
	cout << d;
	
	return 0;
}
