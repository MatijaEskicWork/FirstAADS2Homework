#include <iostream>
#include <stack>
#include <queue>
#include <stdlib.h>
using namespace std;
#define FLAG 1000000


struct Node {
	int info;
	int height;
	struct Node *left;
	struct Node *right;
};


int subtreeHeight(struct Node *node) {
	if (!node)      return -1;
	return 1 + max(subtreeHeight(node->left), subtreeHeight(node->right));
}

int treeHeight(struct Node *root) {
	if (!root) return -1;
	return subtreeHeight(root);
}



struct Node* MainBSTFunc(int arr[10000]);


struct Node* newNode(int data)
{
	Node* temp = new Node;

	temp->info = data;
	temp->height = 0;
	temp->left = NULL;
	temp->right = NULL;

	return temp;
}

void InitTable(int(*arr)[10000], int(*bit)[10000]);

void InsertKey(int(*arr)[10000], int(*bit)[10000]);

int SearchKey(int(*arr)[10000], int(*bit)[10000]);

int RemoveKey(int(*arr)[10000], int(*bit)[10000]);

int BinSearchFirstLower(int arr[10000], int bit[10000], int key, int low, int high);

int BinarySearch(int arr[10000], int bit[10000], int key, int low, int high);

void OutputTable(int arr[10000], int bit[10000]);

int FindRange(int arr[10000], int key);

struct Node* FormBST(int arr[10000], int low, int high);

int SearchBST(struct Node *root, int key);

struct Node* InsertNode(struct Node* root, int key);

void OutputBST(struct Node* root);

void DeleteBST();

void FindCriticalNode();

int PostOrder(struct Node *root1);

int main() {

	int choice, i, j;
	int bit[10000], arr[10000] = { 0 };
	cout << "Odaberite jednu od opcija(upisite broj):" << endl << "1. Inicijalno formirajte povecanu tabelu" << endl;
	cout << "2. Ubacite novi kljuc" << endl << "3. Pretrazite postojanje kljuca" << endl << "4. Uklonite vec postojeci kljuc" << endl << "5. Ispisite tabelu" << endl << "6. Formiraj BST od napravljene tabele" << endl;
	cout << "7. Pretrazi kljuc unutar BST-a" << endl << "8. Ubaci novi kljuc u BST" << endl << "9. Ispisi BST" << endl << "10. Obrisi BST" << endl << "11. Proveri koji je kritican cvor u BST-u" << endl << "12. Izadji iz programa" << endl;
	cin >> choice;
	int pom;
	struct Node *root = NULL;




	while (choice != 12) {
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

		else if (choice == 6) {
			int new_arr[10000] = {0};
			int high = FindRange(arr, 100000);
			high++;
			int cnt = 0;
			for (int i = 0; i < high; i++) {
				if (bit[i] == 1) {
					new_arr[cnt] = arr[i];
					cnt++;
				}
			}
			for (int i = 0; i < cnt; i++) cout << new_arr[i] << " ";
			cout << endl;
			root = MainBSTFunc(new_arr);
		}

		else if (choice == 7) {
			int key;
			cout << "Unesite kljuc za pretragu" << endl;
			cin >> key;
			int sol = SearchBST(root, key);
			if (sol) cout << "Postoji trazeni kljuc u BST-u" << endl;
			else cout << "Ne postoji trazeni kljuc u BST-u" << endl;
		}

		else if (choice == 9) {
			OutputBST(root);
		}

		else if (choice == 8) {
			cout << "Unesite vrednost kljuca kojeg ubacujete" << endl;
			int key;
			cin >> key;
			InsertNode(root, key);
		}

		else if (choice == 10) {
			DeleteBST();
		}

		else if (choice == 11) {
			int sol = PostOrder(root);
			if (sol == -1) cout << "Stablo je balansirano, nema kriticnih cvorova" << endl;
			else cout << "Stablo nije balansirano, kritican cvor je cvor " << sol << endl;
		}
		cout << "Odaberite jednu od opcija(upisite broj):" << endl << "1. Inicijalno formirajte povecanu tabelu" << endl;
		cout << "2. Ubacite novi kljuc" << endl << "3. Pretrazite postojanje kljuca" << endl << "4. Uklonite vec postojeci kljuc" << endl << "5. Ispisite tabelu" << endl << "6. Formiraj BST od napravljene tabele" << endl;
		cout << "7. Pretrazi kljuc unutar BST-a" << endl << "8. Ubaci novi kljuc u BST" << endl << "9. Ispisi BST" << endl << "10. Obrisi BST" << endl << "11. Proveri koji je kritican cvor u BST-u" << endl << "12. Izadji iz programa" << endl;
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
		int coeff = (high_pos / length);
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
		if ((*arr)[low_pos] == key - 1) { // UKOLIKO JE ZA JEDAN VECI OD PRVOG MANJEG, TJ. TREBA DA SE STAVI ODMAH IZA NJEGA
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

struct Node* MainBSTFunc(int arr[10000]) {
	int low = 0;
	int high = FindRange(arr, 100000);
	return FormBST(arr, low, high);
}


struct Node* FormBST(int arr[10000], int low, int high) {
	int mid;
	if (low <= high) {
		mid = (low + high) / 2;
		struct Node* root = newNode(arr[mid]);
		root->left = FormBST(arr, low, mid - 1);
		root->right = FormBST(arr, mid + 1, high);
		return root;
	}
	else
		return NULL;
}

int SearchBST(struct Node* root, int key)
{
	while (root != NULL) {
		if (key > root->info)
			root = root->right;
		else if (key < root->info)
			root = root->left;
		else
			return 1;
	}
	return 0;
}

struct Node* InsertNode(struct Node* root, int key)
{
	struct Node* new_node = newNode(key);

	struct Node* root_cpy = root;

	struct Node* y = NULL;

	while (root_cpy != NULL) {
		y = root_cpy;
		if (key < root_cpy->info)
			root_cpy = root_cpy->left;
		else
			root_cpy = root_cpy->right;
	}
	if (y == NULL)
		y = new_node;

	else if (key < y->info)
		y->left = new_node;
	else
		y->right = new_node;
	return y;
}

void OutputBST(struct Node *root) {
	//void printTree(BinTree *tree) 
	if( !root )   return;
	else {
		queue<struct Node*> q;
		int i, line_len = 62;
		int first_skip = line_len, in_between_skip;
		//if( q.empty()) return;
		q.push(root);
		int tree_height = treeHeight(root);
		cout << tree_height;
			for( i = 0; i <= tree_height; i++ ) {
			int j = 1 << i, k, l;
				   in_between_skip = first_skip;
				   first_skip = (first_skip-2)/2;
				   for( k = 0; k < first_skip; k++) cout<<" ";
				   for(k = 0; k < j; k++) {
						struct Node *btn = (struct Node *)q.front();
					    q.pop();
						if(btn) {
							q.push(btn->left);
							q.push(btn->right);
						} 
						else  {
							q.push(NULL);
							q.push(NULL);
						}
						if(btn) cout <<  btn->info;
						else cout<< "  ";
						for( l = 0; l < in_between_skip; l++) cout <<" ";
					  }
				  cout<< endl << endl;
			}
	  }
}

int PostOrder(struct Node *root1) {
	int max = 0;
	int pos = 0;
	{
		struct Node* root = root1; 
		if (root == NULL)
			return -1;
		stack<struct Node*> s1, s2;
		struct Node* node;	
		s1.push(root);	
		while (!s1.empty())
		{ 
				node = s1.top();
				s1.pop();
				s2.push(node); 
				if (node->left)
					s1.push(node->left);
				if (node->right)
					s1.push(node->right);
		}
		while (!s2.empty()) {
			node = s2.top();
			s2.pop();
			if (!node->left && !node->right) node->height = 0;
			else if (!node->left && node->right) node->height = 0 - (node->right->height + 1);
			else if (node->left && !node->right) node->height = 0 + (node->left->height + 1);
			else node->height = node->left->height - node->right->height;
			if (abs(node->height) > max) {
				max = node->height;
				pos = node->info;
			}
		}
			
	}
	if (max == 1 || max == 0) return -1;
	return pos;
}


void DeleteBST() {

}

void FindCriticalNode() {

}


