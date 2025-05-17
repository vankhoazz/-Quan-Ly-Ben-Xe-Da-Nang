#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <chrono>
#include <thread>
#include<iomanip>
#include<ctime>
#include<cstring>
#include<algorithm>
#include <cstdlib>
#include <limits> 	

using namespace std;
class Xe {
protected:
	string bienso, taixe;
public:
	Xe() {}
	Xe(string bienso,string taixe)
	{
		this->bienso = bienso;
		this->taixe = taixe;
	}
	virtual void nhap() {
		cout << "Nhap bien so xe: "; getline(cin, bienso);
		cout << "Nhap ten tai xe: "; getline(cin, taixe);

	}
	virtual void xuat() {
		cout << left << setw(8)<< loai() << setw(8) << bienso << setw(8)<< taixe;

	};
	string getbienso() const { return bienso; }
	string gettaixe() const { return taixe; }
	void thaydoitaixe(const string& tx) { taixe = tx; }
	virtual void ghifile(ofstream& of) {
		of << bienso << "," << taixe << ",";
	}
	virtual string loai() = 0;
};
class Bus :public Xe {
	int soghe;
	string diemdon,diemden;
public:
	Bus() {}
	Bus(string bienso,string taixe,int soghe,string diemdon,string diemden) : Xe(bienso, taixe) {
		this->soghe = soghe;
		this->diemdon = diemdon;
		this->diemden = diemden;
	}
	void nhap() {
		Xe::nhap();
		cout << "Nhap diem don: "; getline(cin, diemdon);
		cout << "Nhap diem den: "; getline(cin, diemden);
		cout << "Nhap so ghe: "; cin >> soghe; cin.ignore(); 
	}
	string getdiemdon() const { return diemdon; }
	string getdiemden() const { return diemden; }
	void xuat() {
		Xe::xuat();
		cout << left << setw(5) << soghe << setw(8) <<diemdon<< setw(8) <<diemden<< endl;
	}
	void ghifile(ofstream& of) {
		of << "Bus" <<",";
		Xe::ghifile(of);
		of << soghe <<","<<diemdon<<","<<diemden<< endl;
	}
	string loai() override {
        return "Bus";
    }
};
class Taxi :public Xe {
	double km;
public:
	Taxi() {}
	Taxi(string bienso, string taixe, double km) : Xe(bienso, taixe) {
		this->km = km;
	}
	void nhap() {
		Xe::nhap();
		cout << "Nhap so km: "; cin >> km; cin.ignore();
	}
	double getkm() const { return km; }
	void xuat() {
		Xe::xuat();
		cout << left << setw(8) << km << endl; 
	}
	void ghifile(ofstream& of) {
		of << "Taxi"<<",";
		Xe::ghifile(of);
		of << km << endl;
	}
	string loai() override {
        return "Taxi";
    }
};
class khachhang {
	string tenkh;
	int sdt;
public:
	khachhang() {}
	khachhang(string tenkh,int sdt) 
	{
		this->tenkh = tenkh;
		this->sdt = sdt;
	}
	void nhap() {
		cout << "Nhap ho ten khach hang: "; getline(cin, tenkh);
		cout << "Nhap so dien thoai khach hang: "; cin >> sdt; cin.ignore();
	}
	void xuat() {
		cout << "Ho ten: " << tenkh << endl;
		cout << "Dien thoai: " << sdt << endl;
	}
	void ghifile(ofstream& of) {
		of << tenkh << "," << sdt;
	}
};
class Benxe {
public:
	vector<Xe*> phtien;
	~Benxe() {
		for (Xe* x : phtien)
			delete x;
	}
	void thempt() {
		int choice;
		cout << "1.Bus\n2.Taxi\nLua chon: "; cin >> choice; cin.ignore();
		Xe* v;
		if (choice == 1)
			v = new Bus();
		else if (choice == 2)
			v = new Taxi();
		else return;
		v->nhap();
		phtien.push_back(v);
		cout<<"Them thanh cong.";
		this_thread::sleep_for(chrono::milliseconds(2000));
		system("cls");
	}
	void xuattatca() {
		cout<<"+--------------------------------------------------+\n";
		for (Xe* v : phtien) {
			v->xuat();
			cout << "-------------------------------------\n";
		}
	}
	void luufile() {
		ofstream f("QuanLyXe.txt",ios::trunc);
		for (Xe* v : phtien) {
			v->ghifile(f);
		}
		f.close();
	}

};
void docfile(vector<Xe*>& phtien)
{
	ifstream read("QuanLyXe.txt");
	if (!read) {
	    cout << "Khong mo duoc file!\n";
	    	return ;
	}
	string line;
	while(true)
	{
		if (!getline(read, line)) break;
		stringstream s1(line);
		string loaixe,bienso,taixe;
		getline(s1,loaixe,',');
		getline(s1,bienso,',');
		getline(s1,taixe,',');

		if (loaixe == "Bus") 
		{
			string soghe_str,diemdonx,diemdenx;
			getline(s1,soghe_str,',');
			getline(s1,diemdonx,',');
			getline(s1,diemdenx,',');
			int soghe = stoi(soghe_str);
			Bus* b = new Bus(bienso, taixe, soghe , diemdonx, diemdenx);
			phtien.push_back(b);
		}
		else if (loaixe == "Taxi")
		{
			string sokm;
			getline(s1,sokm,',');
			int km = stoi(sokm);
			Taxi* t = new Taxi(bienso, taixe, km);
			phtien.push_back(t);
		}

	}
}
void timkiem(const vector<Xe*>& phtien) 
{
	string timkiem1;
	cout<<"Nhap phuong tien can tim: ";
	getline(cin,timkiem1);
	bool tikiem = false;
	for (Xe* v : phtien)
	{
		if(v->loai() == timkiem1) {
			cout<<"-------------------------\n";
			cout<<"Tim thay phuong tien can tim thong tin.\n";
			v->xuat();
			cout<<"\n";
			tikiem = true;
		}
		else if(v->loai() == timkiem1) {
			cout<<"-------------------------\n";
			cout<<"Tim thay phuong tien can tim thong tin.\n";
			v->xuat();
			cout<<"\n";
			tikiem = true;
		}
	}
	if(!tikiem) {
		cout<<"Khong tim thay thong tim xe\n";
	}
}
void xoa(vector<Xe*>& phtien) 
{
	string xoa1;
	cout<<"Nhap phuong tien can xoa: ";
	getline(cin,xoa1);
	vector<Xe*> phtien1;
	bool xoa = false;
	for(Xe* v : phtien) 
	{
		if(v->loai() != xoa1)
		{
			phtien1.push_back(v);
		}
		else {
			xoa = true;
		}
	}
	if(!xoa)
	{
		cout<<"K tim thay thong tim xe can xoa.";
	}
	else 
	{
		phtien = phtien1;
		cout<<"Da xoa phuong tien.";
	}

}
void suataixe(vector<Xe*>& phtien)
{
	string sua1;
	cout<<"Nhap ten tai xe can sua: ";
	getline(cin,sua1);
	bool sua = false;
	for(Xe* v : phtien)
	{
		if(v->gettaixe() == sua1)
		{
			string sua2;
			cout<<"Sua tanh ten moi: ";
			getline(cin,sua2);
			v->thaydoitaixe(sua2);
			sua = true;
			cout<<"Da sua thanh cong.";
		}
	}
	if(!sua) {
		cout<<"Khong tim thay tai xe co ten "<<sua1<<endl;
	}

}
int main()
{
	Benxe quanly;
	docfile(quanly.phtien);
	int choice;
	do {
		cout << "===== Quan ly ben xe Da Nang =====\n";
		cout << "1. Them phuong tien\n2. Hien thi tat ca\n3. Luu vao file\n4. Tim kiem xe\n5. Xoa phuong tien\n6. Sua thong tin tai xe.\n0. Thoat\nChon: ";
		cin >> choice; cin.ignore();
		switch (choice)
		{
		case 1: quanly.thempt(); break;
		case 2: quanly.xuattatca(); break;
		case 3: {
			quanly.luufile();
			cout << "Dang tai";
			for (int i = 0; i < 3; i++) {
				cout << ".";
				cout.flush();
				this_thread::sleep_for(chrono::milliseconds(100));
			}
			cout << "\nDa luu vao file QuanLyXe.txt\n";
			break;
		}
		case 4: {
			timkiem(quanly.phtien);
			break;
		}
		case 5: {
			xoa(quanly.phtien);
			break;
		}
		case 6: {
			suataixe(quanly.phtien);
			break;
		}
		default :
			cout<<"Lua chon ko hop le moi nhap lai.\n\n";
		}
	} while (choice != 0);

	return 0;
}