#include <iostream>
using namespace std;
#define FLAG 1000000

void InitTable(int(*arr)[10000], int(*bit)[10000]);

void InsertKey(int(*arr)[10000], int(*bit)[10000]);

int SearchKey(int(*arr)[10000], int(*bit)[10000]);

int RemoveKey(int(*arr)[10000], int(*bit)[10000]);

int BinSearchFirstLower(int arr[10000], int bit[10000], int key, int low, int high);

int BinarySearch(int arr[10000], int bit[10000], int key, int low, int high);

void OutputTable(int arr[10000], int bit[10000]);

int FindRange(int arr[10000], int key);

int main() {

	int choice, i, j;
	int bit[10000], arr[10000] = { 0 };
	cout << "Odaberite jednu od opcija(upisite broj):" << endl << "1. Inicijalno formirajte povecanu tabelu" << endl;
	cout << "2. Ubacite novi kljuc" << endl << "3. Pretrazite postojanje kljuca" << endl << "4. Uklonite vec postojeci kljuc" << endl << "5. Ispisite tabelu" << endl << "6. Izadjite iz programa" << endl;
	cin >> choice;
	int pom;
	while (choice != 6) {
		if (choice == 1) {
			InitTable(&arr, &bit);
		}

		else if (choice == 2) {
			InsertKey(&arr, &bit);
		}

		else if (choice == 3) {
			pom = SearchKey(&arr, &bit);
		}

		else if (choice == 4) {
			pom = RemoveKey(&arr, &bit);
		}

		else if (choice == 5) {
			OutputTable(arr, bit);
		}

		cout << "Odaberite jednu od opcija(upisite broj):" << endl << "1. Inicijalno formirajte povecanu tabelu" << endl;
		cout << "2. Ubacite novi kljuc" << endl << "3. Pretrazite postojanje kljuca" << endl << "4. Uklonite vec postojeci kljuc" << endl << "5. Ispite tabelu" << endl << "6. Izadjite iz programa" << endl;
		cin >> choice;
	}


	return 0;
}

void InitTable(int(*arr)[10000], int(*bit)[10000]) {
	int high, coeff;
	cout << "Unesite velicinu tabele:" << endl;
	cin >> high;
	cout << "Unesit koeficijent uvecanja:" << endl;
	cin >> coeff;
	for (int i = 0; i < high; i++) {
		int num;
		cout << "Unesite vrednost jednog od kljuceva:" << endl;
		cin >> num;

		for (int j = 0; j < coeff; j++) {
			(*arr)[i * coeff + j] = num;
			(*bit)[i * coeff + j] = 0;
		}
		(*bit)[i * coeff] = 1;
	}
	for (int i = 0; i < high * coeff; i++) {
		cout << (*arr)[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < high * coeff; i++) {
		cout << (*bit)[i] << " ";
	}
	cout << endl;
}

int BinarySearch(int arr[10000], int bit[10000], int key, int low, int high) {
	int mid;
	while (low <= high) {
		mid = (low + high) / 2;
		if (arr[mid] == key && bit[mid] == 1)
			return mid;
		else if (arr[mid] == key && bit[mid] == 0)
			high = mid - 1;
		else if (arr[mid] < key)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return -1;

}

int BinSearchFirstLower(int arr[10000], int bit[10000], int key, int low, int high) {
	int mid;
	if (key < arr[0]) return FLAG;
	while (low <= high) {
		mid = (low + high) / 2;
		if (arr[mid] < key)
			low = mid + 1;
		else if (arr[mid] > key)
			high = mid - 1;
		else
			high = mid - 1;
	}
	while (bit[high] == 0 && high > 0)
		high--;

	return high;
}

void InsertKey(int(*arr)[10000], int(*bit)[10000]) {
	int key;
	cout << "Unesite vrednost kljuca, koji zelite da ubacite:" << endl;
	cin >> key;
	int high = FindRange(*arr, key);
	int low_pos = BinSearchFirstLower(*arr, *bit, key, 0, high);
	if (low_pos == FLAG) low_pos = -1;
	int high_pos = low_pos;
	high = FindRange(*arr, 100000);
		int real_keys = 0;
		for (int i = high_pos + 1; i < high + 1; i++) {
			if ((*bit)[i] == 1)
				real_keys++;
		}
		//1. PROSIRIVANJE TABELE : KAD JE POSLEDNJI ILI SU SAMO PRAVI KLJUCEVI ISPRED NJEGA
		if (high_pos == high || high - high_pos == real_keys) {
			cout << "LOW POS: " << low_pos << endl << "HIGH POS: " << high_pos << endl;
			if ((*arr)[high] < key) { // UKOLIKO JE NAJVECI
				(*arr)[high + 1] = key;
				(*bit)[high + 1] = 1;
			}
			else { // UKOLIKO NIJE NAJVECI ALI IMA SAMO PRAVIH KLJUCEVA ISPRED NJEGA
				for (int i = high; i > high_pos; i--)
					(*arr)[i + 1] = (*arr)[i];
				(*arr)[high_pos + 1] = key;
			}
			high++;
			high_pos = (high + 1) * 2;
			int new_arr[10000] = { 0 };
			int length = -1;
			for (int i = 0; i < high + 1; i++) {
				if ((*bit)[i] == 1) {
					length++;
					new_arr[length] = (*arr)[i];
				}
			}
			length++;
			if (high_pos % length != 0) // DOPUNA DO TOGA DA BUDE EKVIDISTANTNO
				high_pos = high_pos + (length - (high_pos % length));
			int coeff = (high_pos / length) ;
			for (int i = 0; i < length; i++) {
				for (int j = 0; j < coeff; j++) {
					(*arr)[i * coeff + j] = new_arr[i];
					(*bit)[i * coeff + j] = 0;
				}
				(*bit)[i * coeff] = 1;
			}
		}
		else { // NEMA PROSIRIVANJA
			high_pos++;
			while ((*arr)[high_pos] != 0 && (*bit)[high_pos] == 0) {
				high_pos++;
			}
			cout << "LOW POS: " << low_pos << endl << "HIGH POS: " << high_pos << endl;
			if ((*arr)[low_pos] == key - 1){ // UKOLIKO JE ZA JEDAN VECI OD PRVOG MANJEG, TJ. TREBA DA SE STAVI ODMAH IZA NJEGA
				if ((*bit)[low_pos + 1] == 0) { // A TAJ IMA FAKE KOPIJE SEBE, TJ NE MORA NISTA DA SE POMERA
					(*arr)[low_pos + 1] = key;
					(*bit)[low_pos + 1] = 1;
					for (int i = low_pos + 2; i < high_pos; i++) {
						(*arr)[i] = key;
						(*bit)[i] = 0;
					}
				}
				else { // UKOLIKO JE IZA TOG PRVOG MANJEG PRAVI KLJUC, TJ MORA DA SE POMERAJU
					int cnt = high_pos;
					while ((*bit)[cnt] == 1)
						cnt++;
					for (int i = cnt - 1; i > low_pos; i--) {
						(*arr)[i + 1] = (*arr)[i];
						(*bit)[i + 1] = 1;
					}
					(*arr)[low_pos + 1] = key;
					(*bit)[low_pos + 1] = 1;
				}
			}
			else { // UKOLIKO NIJE PRVI MANJI SAMO ZA JEDAN MANJI
				if (high_pos - low_pos == 1) { // A PRVI IZA JE PRAVI KLJUC
					int cnt = high_pos;
					while ((*bit)[cnt] == 1)
						cnt++;
					for (int i = cnt - 1; i > low_pos; i--) {
						(*arr)[i + 1] = (*arr)[i];
						(*bit)[i + 1] = 1;
					}
					(*arr)[low_pos + 1] = key;
					(*bit)[low_pos + 1] = 1;
				}
				else { // IZA JE FAKE KLJUC
					int pos = (high_pos + low_pos) / 2;
					for (int i = pos; i < high_pos; i++) {
						(*arr)[i] = key;
						(*bit)[i] = 0;
					}
					(*bit)[pos] = key;
				}
			}
		}
	}

int SearchKey(int(*arr)[10000], int(*bit)[10000]) {
	int key, low = 0, high;
	cout << "Unesite vrednost kljuca, koji zelite da pretrazite:" << endl;
	cin >> key;
	high = FindRange(*arr, key);
	int sol = BinarySearch(*arr, *bit, key, low, high);
	if (sol != -1) cout << "Trazeni element se nalazi u tabeli na poziciji broj " << sol + 1 << endl;
	else cout << "Trazeni element se ne nalazi u tabeli" << endl;
	return sol;

}

int FindRange(int arr[10000], int key) {
	int low = 0, high = 1;
	while (key > arr[high] && arr[high] != 0) {
		if (high != 0) high = high * 2;
		else high = 1;
	}
	while (arr[high] == 0)
		high--;
	return high;
}

int RemoveKey(int(*arr)[10000], int(*bit)[10000]) {
	int key, low = 0, high;
	cout << "Unesite vrednost kljuca, koji zelite da obrisete:" << endl;
	cin >> key;
	high = FindRange(*arr, key);
	int sol = BinarySearch(*arr, *bit, key, 0, high);
	(*bit)[sol] = 0;
	cout << endl;
	return 0;
}



void OutputTable(int arr[10000], int bit[10000]) {
	
	int length = FindRange(arr, 1000000);

	for (int i = 0; i < length + 1; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < length + 1; i++) {
		cout << bit[i] << " ";
	}
	cout << endl;
}


