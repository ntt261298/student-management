#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

using namespace std;
//Dinh nghia kieu du lieu sinh vien
struct sinhVien{
	int MSSV;
	char hoTen[30];
	int tuoi;	
};
//Dinh nghia kieu cay
struct Node{
	sinhVien data;
	Node* left;
	Node* right;
};
//Ten kieu du lieu la Tree
typedef Node* Tree;
//Ham nhap thong tin sinh vien va luu vao x
sinhVien nhapsinhVien(){
	sinhVien x;
	cout << "\nMSSV: ";
	cin >> x.MSSV;
	cout << "Ho va ten: ";
	fflush(stdin);
	gets(x.hoTen);
	cout << "Tuoi: ";
	cin >> x.tuoi;
	return x;
}
//Tao cay rong
void Init(Tree &t){
	t = NULL;
};
//Them sinh vien x vao cay t
int insertNode(Tree &t, sinhVien x){
	if (t == NULL){
		Node* p = new Node;
		p->data = x;
		p->left = p->right = NULL;
		t = p;
		return 1;
	}
	if (t != NULL){
		if (t->data.MSSV < x.MSSV) 
			return insertNode(t->right, x);
		if (t->data.MSSV > x.MSSV)
			return insertNode(t->left, x);
		else if(t->data.MSSV == x.MSSV);
			return -1;
	}
};
int classcounter = 0;//Bien dem so lop da tao
Tree Tr[1000];//Mang luu goc cua cac cay
//Ham tao lop moi
void createTree(){
	char test;
	classcounter++;
	Init(Tr[classcounter]);
	do{	
		sinhVien x;
		x = nhapsinhVien();
		int check = insertNode(Tr[classcounter], x);
		if (check == -1)
			cout << "\nSinh vien da ton tai";
		else if (check == 0)
			cout << "\nBo nho day";
		else cout << "\nThem thanh cong";
		cout << "\nBan co muon nhap tiep (y/n): ";	
		fflush(stdin);
		cin >> test;
		if (test != 'y') cout << "\nTao thanh cong lop " << classcounter;
	}while(test == 'y');
}
//Tim kiem sinh vien MSSV la maso trong lop t
Node* findNode(Tree &t, int maso){
	if (t == NULL){
		return t ;
	}
	if (t->data.MSSV < maso){
		return findNode(t->right, maso);
	}
	if (t->data.MSSV > maso){
		return findNode(t->left, maso);
	}
	else if (t->data.MSSV == maso){
		return t;
	}
}
//In thong tin sinh vien
void printNode(Tree &t){
	cout << "\nMa so sinh vien: " << t->data.MSSV <<" - " << "Ho va ten: " << t->data.hoTen <<" - " << "Tuoi: " << t->data.tuoi;
}
//Duyet cay theo kieu LNR 
void LNR(Tree &t){
	if (t != NULL){
		LNR(t->left);
		printNode(t);
		LNR(t->right);
	}
}
//Xoa sinh vien maso trong lop t
int deleteNode(Tree &t, int maso){
	if (t == NULL) return 0;
	else if (t->data.MSSV > maso) return deleteNode(t->left, maso);
	else if (t->data.MSSV < maso) return deleteNode(t->right, maso);
	else{
		Node *p = t;
		if (t->left == NULL) t = t->right;
		else if (t->right == NULL) t = t->left;
		else{
			Node *s = t, *q = s->left;
			while (q->right != NULL){
				s = q;
				q = q->right;
			}
			p->data = q->data;
			deleteNode(t->left, q->data.MSSV);
		}
	}
	return 1;
}
//Ghep cay t2 vao t1
void mergeTree(Tree &t1, Tree &t2){
	if (t2 == NULL) return;
	insertNode(t1, t2->data);
	mergeTree(t1, t2->left);
	mergeTree(t1, t2->right);
	return;
}
//Ham thuc hien tim sinh vien
void do_findNode(){
	Node* x =NULL;
	int maso, find;
	cout << "\nNhap lop can tim sinh vien: ";
	cin >> find;
	cout << "\nNhap MSSV can tim: ";
	cin >> maso;
	x = findNode(Tr[find], maso);
	if (x != NULL){
		cout << "\nThong tin sinh vien:";
		cout << "\nMa so sinh vien: " << x->data.MSSV;
		cout << "\nHo va ten: " << x->data.hoTen;
		cout << "\nTuoi: " << x->data.tuoi;
	}
	else cout << "Khong tim thay sinh vien";
}
//Ham thuc hien them sinh vien
void do_insertNode(){
	sinhVien x;
	char test;
	do{
		int whichclass;
		cout << "\nNhap lop can them sinh vien: ";
		cin >> whichclass;
		if (Tr[whichclass] == NULL){
			cout <<"\nLop khong ton tai. Ban can tao lop truoc.";
			break;
		}
		x = nhapsinhVien();
		int check = insertNode(Tr[whichclass], x);
		if (check == -1)
			cout << "\nSinh vien da ton tai";
		else if (check == 0)
			cout << "\nBo nho day";
		else cout << "\nThem thanh cong";
		cout << "\nBan co muon nhap tiep (y/n): ";	
		fflush(stdin);
		cin >> test;
	}while(test == 'y');
}
//Ham thuc hien noi cay con vao cay to
void do_merge_childTree(){
	while(1){
		int class1, class2;
		cout << "\nNhap lop lon: ";
		cin >> class1;
		cout << "\nNhap lop nho: ";
		cin >> class2;
		mergeTree(Tr[class1], Tr[class2]);
		Tr[class2] = NULL;
		cout << "\nDa them cay con thanh cong. Ban muon them cay con khac (y/n): ";
		char test;
		cin >> test;
		if (test == 'n') break;
	}
}
//Ham xoa sinh vien trong lop
void do_delete(){
	int lop, maso;
	cout << "\nNhap lop can xoa sinh vien: ";
	cin >> lop;
	if (Tr[lop] == NULL) {
		cout <<"\nLop khong ton tai";
	}
	else{
		char test;
		do{
			cout << "\nNhap MSSV can xoa: ";
			cin >> maso;
			int x = deleteNode(Tr[lop], maso);
			if (x == 0) {
				cout << "\nKhong co sinh vien nay";
				break;
			}
			else if (x == 1) {
				cout << "\nXoa thanh cong. Ban co muon xoa tiep (y/n) : ";
				fflush(stdin);
				cin >> test;
			}
		}while(test == 'y');
	}
}
//Ham xoa cac phan tu o cay con
void deletechildTree(Tree &t, Node* x){
	Node* p = x;
	if (p->left != NULL) deletechildTree(t, p->left);
	if (p->right != NULL) deletechildTree(t, p->right);
	deleteNode(t, p->data.MSSV);
	delete x;
}
//Ham xoa cay con
void do_delete_child_tree(){
	int lop, maso;
	Node* x = NULL;
	cout << "\nNhap lop lon chua lop con can xoa: ";
	cin >> lop;
	if (Tr[lop] == NULL){
		cout << "\nLop khong ton tai";
	}
	else{
		cout << "\nNhap MSSV tai goc cay con can xoa: ";
		cin >> maso;
		x = findNode(Tr[lop], maso);
		if (x == NULL) cout <<"\nKhong tim thay sinh vien";
		else{
			deletechildTree(Tr[lop], x);
			cout << "\nXoa cay con thanh cong";	
		}
	}	
}	
//Ham in danh sach lop	
void do_print(){
	int lop;
	cout << "\nNhap lop can hien thi: ";
	cin >> lop;
	if (Tr[lop] != NULL){
		cout << "\nDanh sach lop " << lop;
		LNR(Tr[lop]);	
	}
	else cout << "\nLop khong co sinh vien";
}
int main(){
	do{
		int lc;
		cout << "\n\t\t\t ================MENU============================\n";
	    cout << "\t\t\t |1. Tao 1 lop hoc                   		|\n";
	    cout << "\t\t\t |2. Tim kiem sinh vien                  	|\n";
	    cout << "\t\t\t |3. Them sinh vien                   		|\n";
	    cout << "\t\t\t |4. Them lop con				|\n";
	    cout << "\t\t\t |5. Xoa sinh vien                       	|\n";
	    cout << "\t\t\t |6. Xoa lop con                     		|\n";
	    cout << "\t\t\t |7. In danh sach lop                        	|\n";
	    cout << "\t\t\t |8. Thoat                                   	|\n";
	    cout << "\t\t\t ================================================\n";
    	cout << "\nBan chon: ";
    	cin >> lc;
    	switch(lc){
    		case 1:{
    			createTree();
				break;
			}
			case 2:{
				do_findNode();	
				break;
			}
			case 4:{
				do_merge_childTree();
				break;
			}
			case 3:{
				do_insertNode();
				break;
			}
			case 5:{
				do_delete();
				break;
			}
			case 6:{
				do_delete_child_tree();
				break;
			}
			case 7:{
				do_print();
				break;
			}
			case 8: return 0;
		}	
	}while(1);
}	
