#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <cctype>
using namespace std;

// Hàm định dạng VND
string dinhDangVND(long long so) {
	string num = to_string(so);
	string res;
	long long dem = 0;

	for (long long i = num.length() - 1; i >= 0; --i) {
		res.insert(0, 1, num[i]);
		++dem;
		if (dem % 3 == 0 && i != 0) {
			res.insert(0, 1, '.');
		}
	}

	res += " VND";
	return res;
}
//Hàm xóa màn hình
void clearScreen() {
	system("cls");
}
//Hàm dừng màn hình
void pauseScreen() {
	cout << "\n\nNhan Enter de tiep tuc...";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	clearScreen();
}
//Hàm kiểm tra giá trị nhập có phải là số hay không va kiem tra phai so duong khong
int ktNhap(const string& prompt) {
	int value;
	while (true) {
		cout << prompt;
		if (cin >> value && value >= 0) {
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return value;
		}
		else {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\n Vui long nhap gia tri  hop le!\n\n";
		}
	}
}
// Lớp cơ sở đại diện cho một xe cơ bản
// Bao gồm thông tin: biển số, tài xế, số ghế, loại xe
class Xe {
private:
	string bienso, taixe, loai;
	int stt, soghe;
	static int i;
public:
	Xe(string loai = "Xe", string bienso = "", string taixe = "", int soghe = 0)
		: bienso(bienso), taixe(taixe), loai(loai), soghe(soghe) {
		i++;
		stt = i;
	}
	virtual void nhap() {
		cout << "Nhap bien so xe: "; getline(cin, bienso);
		cout << "Nhap ten tai xe: "; getline(cin, taixe);
		cout << "Nhap so ghe: "; cin >> soghe; cin.ignore();
	}
	virtual void xuat() {
    	cout << "| "<<setw(3) << left<<stt
         << " | " << setw(11) << loai
         << " | " << setw(13) << bienso
         << " | " << setw(11) << taixe
         << " | " << setw(6) << soghe;
}
	virtual void ghifile(ofstream& of) {
		of << bienso << "|" << taixe << "|" << soghe;
	}
	virtual ~Xe() {
		i--;
	}

	string get_loai() {
		return loai;
	}
	string get_bienso() { return bienso; }
	int get_stt() const { return stt; }
	static int get_i() { return i; }
	static void set_i(int new_i) { i = new_i; }
	void set_stt(int new_stt) { stt = new_stt; }
	void set_bienso(string newbienso) { bienso = newbienso; }
	void set_taixe(string newtaixe) { taixe = newtaixe; }
	void set_soghe(int newsoghe) { soghe = newsoghe; }
	int get_soghe() const { return soghe; }
};
int Xe::i = 0;
// Lớp đại diện cho xe Bus, có thêm thông tin điểm đón, điểm đến, giá vé
class Bus : public Xe {
	string diemdon, diemden;
	long long giave;
public:
	Bus(string bienso = "", string taixe = "", string diemdon = "", string diemden = "", int soghe = 0, long long giave = 0)
		: Xe("Bus", bienso, taixe, soghe), diemdon(diemdon), diemden(diemden), giave(giave) {
	}

	void nhap() override {
		Xe::nhap();
		cout << "Nhap diem don: "; getline(cin, diemdon);
		cout << "Nhap diem den: "; getline(cin, diemden);
		cout << "Nhap gia ve (VND): "; cin >> giave; cin.ignore();
	}

	void xuat() override {
    	Xe::xuat(); // gọi xuất cơ bản
    	cout << " | " << setw(32) << (diemdon + " - " + diemden)
         << " | " << setw(13) << dinhDangVND(giave)
         << " |"<<endl;
}

	void ghifile(ofstream& of) override {
		of << "Bus|";
		Xe::ghifile(of);
		of << "|" << diemdon << "|" << diemden << "|" << giave << endl;
	}

	~Bus() override {}
	void set_diemdon(string newdiemdon) { diemdon = newdiemdon; }
	void set_diemden(string newdiemden) { diemden = newdiemden; }
	void set_giave(long long g) { giave = g; }
	string get_diemdon() { return diemdon; }
	string get_diemden() { return diemden; }
	long long get_giave() const { return giave; }
};
// Lớp đại diện cho xe Limousine, có thêm tiện nghi và giá tính theo km
class Limousine : public Xe {
	string tiennghi;
	long long gia_km;
public:
	Limousine(string bienso = "", string taixe = "", string tiennghi = "", int soghe = 0, long long gia_km = 0.0)
		: Xe("Limousine", bienso, taixe, soghe), tiennghi(tiennghi), gia_km(gia_km) {
	}

	void nhap() override {
		Xe::nhap();
		cout << "- Danh sach tien nghi co the nhap:\n";
		cout << "  + Ghe massage\n";
		cout << "  + Wifi\n";
		cout << "  + Dieu hoa\n";
		cout << "  + USB\n";
		cout << "  + Man hinh cam ung\n";
		cout << "  + Toilet tren xe\n";
		cout << "=> Nhap tien nghi (phan cach bang dau phay): ";
		getline(cin, tiennghi);
		cout << "Nhap gia moi km (VND): "; cin >> gia_km; cin.ignore();
	}

	void xuat() override {
    	Xe::xuat();
    	cout << " | " << setw(32) << tiennghi
         << " | " << setw(13) << dinhDangVND(gia_km)
         << " |"<<endl;
}
	void ghifile(ofstream& of) override {
		of << "Limousine|";
		Xe::ghifile(of);
		of << "|" << tiennghi << "|" << gia_km << endl;
	}

	~Limousine() override {}
	void set_tiennghi(string newtiennghi) { tiennghi = newtiennghi; }
	void set_giakm(long long g) { gia_km = g; }
	string get_tiennghi() { return tiennghi; }
	long long get_giakm()const { return gia_km; }
};
// Lớp thông tin cá nhân khách hàng: họ tên, số điện thoại
class KhachHang {
public:
	string hoten;
	string sdt;

	void nhap() {
		cout << "Nhap ho ten: "; getline(cin, hoten);
		cout << "Nhap so dien thoai: "; getline(cin, sdt);
	}

	void xuat() const {
		cout << "Ho ten: " << hoten << "| SDT: " << sdt;
	}
};
//Lớp thông tin vé đã đặt: khách hàng, xe, số ghế, đơn giá, thời gian đặt
class VeXe {
	string hoten, sdt;
	string bienso, loaixe;
	int soghe;
	long long dongia;
	string thoigiandat;
public:
	VeXe(string hoten, string sdt, string bienso, string loaixe, int soghe, long long dongia)
		: hoten(hoten), sdt(sdt), bienso(bienso), loaixe(loaixe), soghe(soghe), dongia(dongia) {
		time_t now = time(nullptr);
		char buf[64];
		strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
		thoigiandat = buf;
		thoigiandat.pop_back();
	}
	VeXe(const KhachHang& kh, const string& bienso, const string& loaixe, int soghe, long long dongia)
		: hoten(kh.hoten), sdt(kh.sdt), bienso(bienso), loaixe(loaixe), soghe(soghe), dongia(dongia) {
		time_t now = time(0);
		char buf[64];
		strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
		thoigiandat = buf;
		thoigiandat.pop_back();
	}


	string luu_ve() const {
		stringstream ss;
		ss << "Khach hang: " << hoten << "| SDT: " << sdt
			<< "| Loai xe: " << loaixe << "| Bien so: " << bienso
			<< "| So ghe dat: " << soghe
			<< "| Don gia: " << dinhDangVND(dongia)
			<< "| Thoi gian dat: " << thoigiandat;
		return ss.str();
	}

	static VeXe doc_ve(const string& line) {
		stringstream ss(line);
		string hoten, sdt, loaixe, bienso, thoigiandat;
		string token;
		int soghe = 0, dongia = 0;
		string dongiaStr;

		getline(ss, token, ':'); getline(ss, hoten, '|'); hoten = hoten.substr(1);
		getline(ss, token, ':'); getline(ss, sdt, '|'); sdt = sdt.substr(1);
		getline(ss, token, ':'); getline(ss, loaixe, '|'); loaixe = loaixe.substr(1);
		getline(ss, token, ':'); getline(ss, bienso, '|'); bienso = bienso.substr(1);
		getline(ss, token, ':'); ss >> soghe; ss.ignore();
		getline(ss, token, ':'); getline(ss, dongiaStr, '|');
		size_t pos = dongiaStr.find(" VND");
		if (pos != string::npos) dongiaStr = dongiaStr.substr(0, pos);
		dongiaStr.erase(remove(dongiaStr.begin(), dongiaStr.end(), '.'), dongiaStr.end());
		dongia = stoi(dongiaStr);
		getline(ss, token, ':'); getline(ss, thoigiandat);
		VeXe ve(hoten, sdt, bienso, loaixe, soghe, dongia);
		ve.thoigiandat = thoigiandat;
		return ve;
	}
	void xuat() const {
			cout<<"+===========================IN VE XE=============================+\n";
            cout<<"  		+Ten khach hang: "<<hoten<<"\n";
            cout<<"   		+So dien thoai khach hang: "<<sdt<<"\n";
            cout<<"  		+Loai xe: "<<loaixe<<"\n";
            cout<<"   		+Tong tien thanh toan: "<<dinhDangVND(dongia)<<"\n";
            cout<<"   		+Thoi gian dat ve: "<<thoigiandat<<"\n";
            cout<<"  =>Xuat ve thanh cong.";		
	}
	string get_sdt() const { return sdt; }
	int get_dongia() const { return dongia; }
};
// Điều phối toàn bộ,quản lý xe và vé
// Bao gồm: thêm/xóa/sửa/tìm xe, đặt vé, thống kê, đọc/ghi file
class Benxe {
	vector<Xe*> phtien;
	vector<VeXe> danhSachVe;
public:
	~Benxe() {
		for (Xe* x : phtien) delete x;
	}

	// Các hàm làm việc với Phương Tiện

	// Thêm phương tiện mới (Bus hoặc Limousine) vào danh sách
	void thempt() {
		int choice;
		choice = ktNhap("Chon phuong tien muon them\n1. Bus\n2. Limousine\nNhap so bat ky de quay lai.\n\nNhap lua chon: ");
		Xe* v = nullptr;
		if (choice == 1) v = new Bus();
		else if (choice == 2) v = new Limousine();
		else {
			return;
		}
		v->nhap();
		phtien.push_back(v);
		cout << "Them thanh cong.";
		pauseScreen();
	}
	// Hiển thị toàn bộ danh sách xe
	void xuattatca() {
	clearScreen();
	cout<<"+=============================================================================================================+\n";
    cout << "|" "                                          DANH SACH XE TRONG HE THONG                                        " "|" << endl;
    cout<<"+=============================================================================================================+\n";
    cout << "| STT |   Loai xe   |    Bien so    |   Tai xe    | So ghe |         Thong tin rieng          |    Gia Ve     |" << endl;
    cout << "|     |             |               |             |        | (Tien nghi/Diem don - diem den)  | (Gia tien/km) |" << endl;
    cout << "+-----+-------------+---------------+-------------+--------+----------------------------------+---------------+" << endl;
	for (Xe* v : phtien) {
		v->xuat();
	}
	cout << "+-----+-------------+---------------+-------------+--------+----------------------------------+---------------+" << endl;

	}
	void luufile() {
		ofstream f;
		f.open("QuanLyXe.txt", ios::trunc);
		if (!f) {
			cout << "Khong mo duoc file de ghi!\n";
			return;
		}

		for (Xe* v : phtien) v->ghifile(f);
		f.close();

		cout << "    Dang tai";
		for (int i = 0; i < 3; i++) {
			cout << "."; cout.flush();
			this_thread::sleep_for(chrono::milliseconds(100));
		}
		cout << "\n=>Da luu vao file QuanLyXe.txt\n";
		this_thread::sleep_for(chrono::seconds(2));
		clearScreen();
	}
	void docfile() {
		for (Xe* x : phtien) delete x;
		phtien.clear();
		ifstream file("QuanLyXe.txt");
		if (!file) {
			cout << "Khong mo duoc file!\n";
			return;
		}
		string line;
		while (getline(file, line)) {
			stringstream ss(line);
			string loai;
			getline(ss, loai, '|');
			string bienso, taixe, diemdon, diemden, soghe_str, tiennghi, giave_str, giakm_str;
			if (loai == "Bus") {
				getline(ss, bienso, '|');
				getline(ss, taixe, '|');
				getline(ss, soghe_str, '|');
				getline(ss, diemdon, '|');
				getline(ss, diemden, '|');
				getline(ss, giave_str);
				long long soghe = stoi(soghe_str);
				long long giave = stoi(giave_str);
				phtien.push_back(new Bus(bienso, taixe, diemdon, diemden, soghe, giave));
			}
			else if (loai == "Limousine") {
				getline(ss, bienso, '|');
				getline(ss, taixe, '|');
				getline(ss, soghe_str, '|');
				getline(ss, tiennghi, '|');
				getline(ss, giakm_str);
				long long soghe = stoi(soghe_str);
				long long giakm = stod(giakm_str);
				phtien.push_back(new Limousine(bienso, taixe, tiennghi, soghe, giakm));
			}
		}
		file.close();
		clearScreen();
		xuattatca();
	}
	void timkiem_bienso() {
		int count = 0;
	    string bien;
		cout << "Nhap bien so: ";
		getline(cin, bien);
		cout<<"+====================================THONG TIN TIM CO TRONG DANH SACH=========================================+\n";
    	cout << "| STT |   Loai xe   |    Bien so    |   Tai xe    | So ghe |         Thong tin rieng          |    Gia Ve     |" << endl;
    	cout << "|     |             |               |             |        | (Tien nghi/Diem don - diem den)  | (Gia tien/km) |" << endl;
    	cout << "+-----+-------------+---------------+-------------+--------+----------------------------------+---------------+" << endl;
		for (Xe* v : phtien) {
			if (v->get_bienso() == bien) {
				v->xuat();
				count++;
			}
		}
		cout << "+-----+-------------+---------------+-------------+--------+----------------------------------+---------------+" << endl;
		if (count > 0) {
			cout << "  \nDa tim thay " << count << " phuong tien voi bien so \"" << bien << "\".\n";
		}
		else {
			cout << "  \nKhong tim thay phuong tien voi bien so tren.\n";
		}
	}
	void xoatheostt(int stt_xoa) {
		bool kt = false;
		for (auto it = phtien.begin(); it != phtien.end(); ++it) {
			if ((*it)->get_stt() == stt_xoa) {
				delete* it;
				phtien.erase(it);
				kt = true;
				cout << "Da xoa phuong tien co STT " << stt_xoa << " thanh cong!";
				capnhatSTT();
				break;
			}
		}
		if (!kt) {
			cout << "Khong tim thay xe voi STT:  '" << stt_xoa << "'!\n\n";
		}
	}
	void xoabienso(const string& bien) {
		bool kt = false;
		for (auto it = phtien.begin(); it != phtien.end(); ++it) {
			if ((*it)->get_bienso() == bien) {
				delete* it;
				it = phtien.erase(it);
				kt = true;
				cout << "Da xoa xe co bien so '" << bien << "' thanh cong!\n";
				capnhatSTT();
				break;
			}
		}
		if (!kt) {
			cout << "Khong tim thay xe voi bien so: '" << bien << "'!\n\n";
		}
	}
	void suaThongTin() {
		clearScreen();
		if (phtien.empty()) {
			cout << "Danh sach phuong tien rong!";
			return;
		}
		int stt_sua;
		Xe* xe_sua = nullptr;
		cout << "Thong tin hien tai:\n";
		xuattatca();
		cout << "Chon STT can sua thong tin: ";
		cin >> stt_sua;
		cin.ignore();
		for (Xe* x : phtien) {
			if (x->get_stt() == stt_sua) {
				xe_sua = x;
				break;
			}
		}
		if (xe_sua == nullptr) {
			cout << "Khong tim thay phuong tien voi STT " << stt_sua << " !\n";
			return;
		}
		clearScreen();
			cout<<"+=====================================THONG TIN PHUONG TIEN CAN SUA===========================================+\n";
    		cout << "| STT |   Loai xe   |    Bien so    |   Tai xe    | So ghe |         Thong tin rieng          |    Gia Ve     |" << endl;
    		cout << "|     |             |               |             |        | (Tien nghi/Diem don - diem den)  | (Gia tien/km) |" << endl;
    		cout << "+-----+-------------+---------------+-------------+--------+----------------------------------+---------------+" << endl;
			xe_sua->xuat();
			cout << "+-----+-------------+---------------+-------------+--------+----------------------------------+---------------+" << endl;
		cout << endl;
		int luachonSua;
		cout << "Chon thong tin can sua:\n";
		cout << "   1. Bien so\n   2. Ten tai xe\n   3. So ghe\n";
		if (xe_sua->get_loai() == "Bus") {
			cout << "   4. Diem don\n   5. Diem den\n   6.Gia ve";
		}
		else if (xe_sua->get_loai() == "Limousine") {
			cout << "   4. Tien nghi\n   5.Gia/km";
		}
		cout << "\n\nNhap lua chon: ";
		cin >> luachonSua;
		cin.ignore();
		switch (luachonSua) {
		case 1: {
			string newbienSo;
			cout << "Nhap bien so moi: ";
			getline(cin, newbienSo);
			xe_sua->set_bienso(newbienSo);
			cout << "Da cap nhat bien so!";
			break;
		}
		case 2: {
			string newtaiXe;
			cout << "Nhap ten tai xe moi: ";
			getline(cin, newtaiXe);
			xe_sua->set_taixe(newtaiXe);
			cout << "Da cap nhat ten tai xe!";
			break;
		}
		case 3: {
			int newsoghe;
			cout << "Nhap so ghe moi: ";
			cin >> newsoghe;
			cin.ignore();
			xe_sua->set_soghe(newsoghe);
			cout << "Da cap nhat so ghe!";
			break;
		}
		case 4: {
			if (xe_sua->get_loai() == "Bus") {
				Bus* bus = dynamic_cast<Bus*>(xe_sua);
				string newDiemDon;
				cout << "Nhap diem don moi: ";
				getline(cin, newDiemDon);
				bus->set_diemdon(newDiemDon);
				cout << "Da cap nhat diem don!";
			}
			else if (xe_sua->get_loai() == "Limousine") {
				Limousine* limo = dynamic_cast<Limousine*>(xe_sua);
				string newtiennghi;
				cout << "Nhap tien nghi moi: ";
				getline(cin, newtiennghi);
				limo->set_tiennghi(newtiennghi);
				cout << "Da cap nhat tien nghi!";
			}
			break;
		}
		case 5: {
			if (xe_sua->get_loai() == "Bus") {
				Bus* bus = dynamic_cast<Bus*>(xe_sua);
				string newdiemden;
				cout << "Nhap diem den moi: ";
				getline(cin, newdiemden);
				bus->set_diemden(newdiemden);
				cout << "Da cap nhat diem den!";
			}
			else if (xe_sua->get_loai() == "Limousine") {
				Limousine* limo = dynamic_cast<Limousine*>(xe_sua);
				long long newgiakm;
				cout << "Nhap gia/km moi: ";
				cin >> newgiakm; cin.ignore();
				limo->set_giakm(newgiakm);
				cout << "Da cap nhat gia/km!";
			}
			break;
		}
		case 6: {
			if (xe_sua->get_loai() == "Bus") {
				Bus* bus = dynamic_cast<Bus*>(xe_sua);
				long long newgiave;
				cout << "Nhap gia ve moi: ";
				cin >> newgiave; cin.ignore();
				bus->set_giave(newgiave);
				cout << "Da cap nhat gia ve!";
			}
			break;
		}
		default:
			cout << "Lua chon khong hop le!";
		}
	}
	void capnhatSTT() {
		for (size_t i = 0; i < phtien.size(); i++) {
			phtien[i]->set_stt(i + 1);
		}
		Xe::set_i(phtien.size());
	}

	// Các hàm làm việc với Vé Xe

	vector<Xe*> timkiem_tuyen(const string& diemdon, const string& diemden) {
		vector<Xe*> ketqua;
		string dd = diemdon, den = diemden;
		transform(dd.begin(), dd.end(), dd.begin(), ::tolower);
		transform(den.begin(), den.end(), den.begin(), ::tolower);
		for (Xe* x : phtien) {
			if (x->get_loai() == "Bus") {
				Bus* b = dynamic_cast<Bus*>(x);
				string bdd = b->get_diemdon();
				string bden = b->get_diemden();
				transform(bdd.begin(), bdd.end(), bdd.begin(), ::tolower);
				transform(bden.begin(), bden.end(), bden.begin(), ::tolower);
				if (bdd == dd && bden == den) {
					ketqua.push_back(x);
				}
			}
		}
		return ketqua;
	}
	vector<Xe*> timkiem_tiennghi(const string& tiennghi_tk) {
		vector<Xe*> ketqua;
		string tk = tiennghi_tk;
		transform(tk.begin(), tk.end(), tk.begin(), ::tolower);
		for (Xe* x : phtien) {
			if (x->get_loai() == "Limousine") {
				Limousine* limo = dynamic_cast<Limousine*>(x);
				string tg = limo->get_tiennghi();
				transform(tg.begin(), tg.end(), tg.begin(), ::tolower);
				if (tg.find(tk) != string::npos) {
					ketqua.push_back(x);
				}
			}
		}
		return ketqua;
	}
	void hienthi_tiennghi() {
		string tiennghi_tk;
		cout << "Nhap tien nghi can tim: ";
		getline(cin, tiennghi_tk);
		vector<Xe*> ds = timkiem_tiennghi(tiennghi_tk);
		if (ds.empty()) {
			cout << "Khong tim thay xe limousine voi tien nghi tren!";
		}
		else {
			cout<<"+=======================================THONG TIN CO TRONG DANH SACH==========================================+\n";
    		cout << "| STT |   Loai xe   |    Bien so    |   Tai xe    | So ghe |         Thong tin rieng          |    Gia Ve     |" << endl;
    		cout << "|     |             |               |             |        | (Tien nghi/Diem don - diem den)  | (Gia tien/km) |" << endl;
    		cout << "+-----+-------------+---------------+-------------+--------+----------------------------------+---------------+" << endl;
			for (Xe* x : ds) {
				x->xuat();
			}
			cout << "+-----+-------------+---------------+-------------+--------+----------------------------------+---------------+" << endl;
		}
	}
	void hienthi_Tuyen() {
		string diemdon, diemden;
		cout << "Nhap diem don: "; getline(cin, diemdon);
		cout << "Nhap diem den: "; getline(cin, diemden);

		vector<Xe*> ketqua = timkiem_tuyen(diemdon, diemden);

		if (ketqua.empty()) {
			cout << "Khong tim thay xe nao theo tuyen nay!\n";
			return;
		}	
		cout<<"+=======================================THONG TIN CO TRONG DANH SACH==========================================+\n";
    	cout << "| STT |   Loai xe   |    Bien so    |   Tai xe    | So ghe |         Thong tin rieng          |    Gia Ve     |" << endl;
    	cout << "|     |             |               |             |        | (Tien nghi/Diem don - diem den)  | (Gia tien/km) |" << endl;
    	cout << "+-----+-------------+---------------+-------------+--------+----------------------------------+---------------+" << endl;
		for (Xe* x : ketqua) {
			x->xuat(); 
		}
		cout << "+-----+-------------+---------------+-------------+--------+----------------------------------+---------------+" << endl;
	}
	// Đặt vé xe theo tuyến đường (chỉ áp dụng cho Bus)
	void datVeTheoTuyen() {
		string diemdon, diemden;
		cout << "Nhap diem don: "; getline(cin, diemdon);
		cout << "Nhap diem den: "; getline(cin, diemden);
		vector<Xe*> ds = timkiem_tuyen(diemdon, diemden);
		if (ds.empty()) {
			cout << "Khong tim thay xe theo tuyen nay!\n";
			return;
		}
		clearScreen();
		cout<<"+=============================================DANH SACH XE BUS================================================+\n";
    	cout << "| STT |   Loai xe   |    Bien so    |   Tai xe    | So ghe |         Thong tin rieng          |    Gia Ve     |" << endl;
    	cout << "|     |             |               |             |        | (Tien nghi/Diem don - diem den)  | (Gia tien/km) |" << endl;
    	cout << "+-----+-------------+---------------+-------------+--------+----------------------------------+---------------+" << endl;
		for (Xe* x : ds) {
			x->xuat();
		}
		cout << "+-----+-------------+---------------+-------------+--------+----------------------------------+---------------+" << endl;
		int stt_chon;
		cout << "Nhap STT xe muon dat ve: "; cin >> stt_chon; cin.ignore();
		Xe* chon = nullptr;
		for (Xe* x : ds) {
			if (x->get_stt() == stt_chon) { chon = x; break; }
		}
		if (!chon) {
			cout << "Khong tim thay xe voi STT da nhap!\n";
			return;
		}
		int soGheDat;
		cout << "Nhap so ghe muon dat: "; cin >> soGheDat; cin.ignore();
		if (soGheDat <= 0 || soGheDat > chon->get_soghe()) {
			cout << "So ghe khong hop le hoac vuot qua so ghe con lai!\n";
			return;
		};
		KhachHang kh;
		kh.nhap();
		Bus* bus = dynamic_cast<Bus*>(chon);
		long long dongia = bus->get_giave() * soGheDat;
		danhSachVe.emplace_back(kh.hoten, kh.sdt, chon->get_bienso(), chon->get_loai(), soGheDat, dongia);
		chon->set_soghe(chon->get_soghe() - soGheDat);
		cout << "\nDat ve thanh cong!";
	}
	// Đặt vé Limousine theo tiện nghi hoặc hiển thị toàn bộ nếu bỏ trống
	void datVeTheoTienNghi() {
		string tiennghi;
		cout << "=> Nhap tien nghi (phan cach bang dau phay): ";
		getline(cin, tiennghi);
		vector<Xe*> ds;
		if (tiennghi.empty()) {
			for (Xe* x : phtien) {
				if (x->get_loai() == "Limousine") {
					ds.push_back(x);
				}
			}
		}
		else {
			ds = timkiem_tiennghi(tiennghi);
		}

		if (ds.empty()) {
			cout << "Khong tim thay xe voi tien nghi nay!\n";
			return;
		}
		clearScreen();
		cout<<"+==========================================DANH SACH XE LIMOUSINE=============================================+\n";
    	cout << "| STT |   Loai xe   |    Bien so    |   Tai xe    | So ghe |         Thong tin rieng          |    Gia Ve     |" << endl;
    	cout << "|     |             |               |             |        | (Tien nghi/Diem don - diem den)  | (Gia tien/km) |" << endl;
    	cout << "+-----+-------------+---------------+-------------+--------+----------------------------------+---------------+" << endl;
		for (Xe* x : ds) {
			x->xuat();
		}
		cout << "+-----+-------------+---------------+-------------+--------+----------------------------------+---------------+" << endl;
		int stt_chon;
		cout << "Nhap STT xe muon dat ve: "; cin >> stt_chon; cin.ignore();
		Xe* chon = nullptr;
		for (Xe* x : ds) {
			if (x->get_stt() == stt_chon) { chon = x; break; }
		}
		if (!chon) {
			cout << "Khong tim thay xe voi STT da nhap!\n";
			return;
		}

		int soGheDat;
		cout << "Nhap so ghe muon dat: "; cin >> soGheDat; cin.ignore();
		if (soGheDat <= 0 || soGheDat > chon->get_soghe()) {
			cout << "So ghe khong hop le hoac vuot qua so ghe con lai!\n";
			return;
		}

		int sokm;
		cout << "Nhap so km di chuyen: "; cin >> sokm; cin.ignore();
		if (sokm <= 0) {
			cout << "So km khong hop le!\n";
			return;
		}

		KhachHang kh;
		kh.nhap();
		Limousine* limo = dynamic_cast<Limousine*>(chon);
		long long dongia = (limo->get_giakm() * sokm * soGheDat);
		danhSachVe.emplace_back(kh,chon->get_bienso(), chon->get_loai(), soGheDat, dongia);
		chon->set_soghe(chon->get_soghe() - soGheDat);
		cout << "\nDat ve thanh cong!";
	}
	void huyVexe() {
		vector<VeXe> danhSachVetemp;
		string sdthuyVe;
		bool kiemtra = false;
		cout<<"Nhap so dien thoai can huy ve: ";
		getline(cin,sdthuyVe);
		for(VeXe& ve : danhSachVe) {
			if(ve.get_sdt() != sdthuyVe) {
				danhSachVetemp.push_back(ve);
			}
			else {
				kiemtra = true;
			}
		}
		if(!kiemtra) {
			cout<<"Khong tim thay khach hang co sdt: "<<sdthuyVe;
		}
		else {
			danhSachVe = danhSachVetemp;
			cout<<"Huy ve cho khach hang co sdt: "<<sdthuyVe<<" thanh cong";
		}
	}
	void hienThiVe() {
		if (danhSachVe.empty()) {
			cout << "Chua co ve nao duoc dat.";
			return;
		}
		for (const VeXe& ve : danhSachVe) {
			ve.xuat();
			cout << endl;
		}
	}
	void luuVeFile() {
		ofstream out("QuanLyKH.txt", ios::trunc);
		for (const VeXe& ve : danhSachVe) {
			out << ve.luu_ve() << endl;
		}
		out.close();
		cout<<"Dang tai";
		for(int i = 0;i<3;i++) {
			cout.flush();
			this_thread::sleep_for(chrono::milliseconds(100));
			cout<<".";
		}
		cout << "\n    Da luu danh sach ve vao file VeXe.txt";
	}
	void docVeFile() {
		ifstream in("QuanLyKH.txt");
		if (!in) {
			cout << "Khong mo duoc file VeXe.txt";
			return;
		}
		danhSachVe.clear();
		string line;
		while (getline(in, line)) {
			danhSachVe.push_back(VeXe::doc_ve(line));
		}
		in.close();
		cout << "\nDoc file ve thanh cong!";
	}
	void timVeTheoSDT() {
		string sdt_tk;
		cout << "Nhap so dien thoai can tim: ";
		getline(cin, sdt_tk);
		bool found = false;
		for (const VeXe& ve : danhSachVe) {
			if (ve.get_sdt() == sdt_tk) {
				ve.xuat();
				found = true;
			}
		}
		if (!found) cout << "Khong tim thay ve nao voi SDT: " << sdt_tk << endl;
	}
	// Tính tổng doanh thu từ tất cả các vé đã đặt
	void thongKeDoanhThu() {
		if (danhSachVe.empty()) {
			cout << "Chua co ve nao de thong ke doanh thu.\n";
			return;
		}
		long long tong = 0;
		long long bus_total = 0, limo_total = 0;
		for (const VeXe& ve : danhSachVe) {
			tong += ve.get_dongia();
			if (ve.luu_ve().find("Loai xe: Bus") != string::npos)
				bus_total += ve.get_dongia();
			else if (ve.luu_ve().find("Loai xe: Limousine") != string::npos)
				limo_total += ve.get_dongia();
		}
		cout << "\n=============THONG KE DOANH THU=============\n";
		cout << "   +Doanh thu tu xe Bus: " << dinhDangVND(bus_total) << endl;
		cout << "   +Doanh thu tu xe Limousine: " << dinhDangVND(limo_total) << endl;
		cout << "   +Tong doanh thu: " << dinhDangVND(tong);
	}
};
int main() {
	Benxe quanly;
	int choice;
	cout << "                                 TRUONG DAI HOC BACH KHOA - DAI HOC DA NANG\n";
	cout << "                                         KHOA DIEN TU VIEN THONG\n";
	cout <<setw(72)<<"                            ---------------------------------\n\n";
	cout << "                                      DE TAI: QUAN LY BEN XE DA NANG\n\n\n";
	cout << "                              SINH VIEN THUC HIEN:  1. Hoang Vu Quang\n";
	cout << "                                                    LOP: 24VDT - MSSV: 106240354\n\n";
	cout << "                                                    2. Cap Van Khoa\n";
	cout << "                                                    LOP: 24KTMT1 - MSSV: 106240228\n\n";
	cout << "                              GIANG VIEN HUONG DAN: TS. Dao Duy Tuan\n";
	pauseScreen();
	clearScreen();
	quanly.docfile();
	quanly.docVeFile();
	do {
		clearScreen();
		cout <<"+=================================+\n";
		cout << "|     QUAN LY BEN XE DA NANG      |\n";
		cout << "|---------------------------------|\n";
		cout << "|                                 |\n";
		cout << "|     1. Quan ly phuong tien.     |\n";
		cout << "|     2. Quan ly ve.              |\n";
		cout << "|                                 |\n";
		cout << "|     Nhap 0 de thoat             |\n";
		cout << "+=================================+\n\n";
		choice = ktNhap("Nhap lua chon: ");
		switch (choice) {
		case 1: {
			int sub_choice;
			do {
				clearScreen();
				cout << "+=================================+\n";
				cout << "|       QUAN LY PHUONG TIEN       |\n";
				cout << "|---------------------------------|\n";
				cout << "|     1. Them phuong tien         |\n";
				cout << "|     2. Hien thi tat ca          |\n";
				cout << "|     3. Luu vao file             |\n";
				cout << "|     4. Tim kiem                 |\n";
				cout << "|     5. Xoa phuong tien          |\n";
				cout << "|     6. Sua thong tin            |\n";
				cout << "|     0. Quay lai                 |\n";
				cout << "+=================================+\n\n";
				sub_choice = ktNhap("Nhap lua chon: ");
				switch (sub_choice) {
				case 1: quanly.thempt(); break;
				case 2: quanly.xuattatca(); pauseScreen(); break;
				case 3: quanly.luufile(); break;
				case 4: {
					clearScreen();
					int tk;
					tk = ktNhap("Tim kiem theo: \n   1: Bien so \n   2: Tuyen duong (Bus)\n   3: Tien nghi (Limousine)\nNhap so bat ky de quay lai.\nChon: ");
					if (tk == 1) {
						quanly.timkiem_bienso();
						pauseScreen();
					}
					else if (tk == 2) {
						quanly.hienthi_Tuyen();
						pauseScreen();
					}
					else if (tk == 3) {
						quanly.hienthi_tiennghi();
						pauseScreen();
					}
					else  break;
					break;
				}
				case 5: {
					int tmp_xoa = ktNhap("1. Xoa theo STT ( Hien thi tat ca ).\n2. Xoa theo bien so.\nNhap so bat ky de quay lai.\nNhap lua chon: ");
					if (tmp_xoa == 1) {
						quanly.xuattatca();
						int stt_xoa = ktNhap("Nhap STT can xoa: ");
						quanly.xoatheostt(stt_xoa);
						pauseScreen();
					}
					else if (tmp_xoa == 2) {
						string bien;
						cout << "Nhap bien so: ";
						getline(cin, bien);
						quanly.xoabienso(bien);
						pauseScreen();
					}
					else break;
					break;
				}
				case 6:
					quanly.suaThongTin();
					pauseScreen();
					break;
				case 0: break;
				default: cout << "\nLua chon khong hop le!";
					pauseScreen();
				}

			} while (sub_choice != 0);
			break;
		}
		case 2: {
			int ve_choice;
			do {
				clearScreen();
				cout << "+=================================+\n";
				cout << "|         QUAN LY VE XE           |\n";
				cout << "|---------------------------------|\n";
				cout << "|     1. Dat ve xe Bus            |\n";
				cout << "|     2. Dat ve xe Limousine      |\n";
				cout << "|     3. Huy ve xe                |\n";
				cout << "|     4. Hien thi ve da dat       |\n";
				cout << "|     5. Luu vao file             |\n";
				cout << "|     6. Tim ve theo SDT          |\n";
				cout << "|     7. Thong ke doanh thu       |\n";
				cout << "|     0. Quay lai                 |\n";
				cout << "+=================================+\n\n";
				ve_choice = ktNhap("Nhap lua chon: ");
				switch (ve_choice) {
				case 1: quanly.datVeTheoTuyen(); pauseScreen(); break;
				case 2: quanly.datVeTheoTienNghi(); pauseScreen(); break;
				case 3: quanly.huyVexe(); pauseScreen(); break;
				case 4: quanly.hienThiVe(); pauseScreen(); break;
				case 5: quanly.luuVeFile(); pauseScreen(); break;
				case 6: quanly.timVeTheoSDT(); pauseScreen(); break;
				case 7: quanly.thongKeDoanhThu(); pauseScreen(); break;
				case 0:
					break;
				default:cout << "\nLua chon khong hop le!";
					pauseScreen();
				}
			} while (ve_choice != 0);
			break;
		}
		case 0:
			cout << "\nThoat chuong trinh...\n";
			break;
		default:
			cout << "\nLua chon khong hop le!";
			pauseScreen();
		}
	} while (choice != 0);

	return 0;
}