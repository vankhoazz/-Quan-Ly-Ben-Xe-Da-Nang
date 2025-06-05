#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include<iomanip>
#include<cstring>
#include <cstdlib>
#include <limits> 
#include <chrono>
#include <thread>
using namespace std;

class Xe {
private:
        string bienso,mauxe,tentaixe,tuyenduong,sdttx;
        int chongoi,namsx; 
public:
        Xe() {};
        Xe(string bienso,string mauxe,int chongoi,int namsx,string tentaixe,string sdttx,string tuyenduong)
        {
                this->bienso = bienso;
                this->mauxe = mauxe;
                this->chongoi = chongoi;
                this->namsx = namsx;
                this->tentaixe = tentaixe;
                this->sdttx = sdttx;
                this->tuyenduong = tuyenduong;
        }
        virtual void nhapthongtinxe() {
                cout<<"Nhap bien so phuong tien: ";
                getline(cin,bienso);
                cout<<"Nhap mau phuong tien: ";
                getline(cin,mauxe);
                cout<<"So luong cho ngoi: ";
                cin>>chongoi;
                cout<<"Nam san xuat cua xe: ";
                cin>>namsx;
                cout<<"Nhap ten tai xe: ";
                cin.ignore();
                getline(cin,tentaixe);
                cout<<"Nhap so dien thoai tai xe: ";
                getline(cin,sdttx);
                cout<<"Nhap tuyen duong (A-B): ";
                getline(cin,tuyenduong);
        }
        virtual void xuatthongtinxe() {
                cout << "| " << setw(11) << left << loaixe()
                << "| " << setw(8)  << bienso
                << "| " << setw(12) << mauxe
                << "| " << setw(9)  << chongoi
                << "| " << setw(8)  << namsx
                << "| " << setw(12) << tentaixe
                << "| " << setw(14) << sdttx
                << "| " << setw(12) << tuyenduong;
        }
        virtual string loaixe() = 0;
        virtual long long getPhiRaVao() const = 0;
        virtual void ghifilexe(ofstream& of) {
                of<<bienso<<"|"<<mauxe<<"|"<<chongoi<<"|"<<namsx<<"|"<<tentaixe<<"|"<<sdttx<<"|"<<tuyenduong;
        }
        string hthibienso() const { return bienso; }
        string hthimauxe() const { return mauxe; }
        int hthichongoi() const { return chongoi; }
        int hthinamsx() const { return namsx; }
        string hthitentaixe() const { return tentaixe; }
        string hthisdttx() const { return sdttx; }
        string hthituyenduong() const { return tuyenduong; }
        void suatentx(string tentaixemoi) { tentaixe = tentaixemoi; }
        void suasdttx(string sdttxmoi) { sdttx = sdttxmoi; }
        void suatuyenduong(string tuyenduongmoi) { tuyenduong = tuyenduongmoi; }
};
class Xekhach : public Xe {
private:
        long long phidvravaoxkh;
public:
        Xekhach() {}
        Xekhach(string bienso,string mauxe,int chongoi,int namsx,string tentaixe,string sdttx,string tuyenduong,long long phidvravaoxkh)
         : Xe(bienso,mauxe,chongoi,namsx,tentaixe,sdttx,tuyenduong) {
                this->phidvravaoxkh = phidvravaoxkh;
        }
        void nhapthongtinxe() {
                Xe::nhapthongtinxe();
                cout<<"Nhap phi ra vao cua xe khach: ";
                cin>>phidvravaoxkh;
        }
        void xuatthongtinxe() {
                Xe::xuatthongtinxe();
                cout<<"|   "<<phidvravaoxkh<<"VND"<<"    |"<<"\n";
        }
        string loaixe() override {
                return "Xe Khach";
        }
        void ghifilexe(ofstream& of) {
                of<<loaixe()<<"|";
                Xe::ghifilexe(of);
                of<<"|"<<phidvravaoxkh<<"\n";
        }
        long long getPhiRaVao() const { return phidvravaoxkh; }
};

class Limousine : public Xe {
private:
        long long phidvravaolimo;
public:
        Limousine() {}
        Limousine(string bienso,string mauxe,int chongoi,int namsx,string tentaixe,string sdttx,string tuyenduong,long long phidvravaolimo)
         : Xe(bienso,mauxe,chongoi,namsx,tentaixe,sdttx,tuyenduong) {
                this->phidvravaolimo = phidvravaolimo;
        }
        void nhapthongtinxe() {
                Xe::nhapthongtinxe();
                cout<<"Nhap phi ra vao cua Limousine: ";
                cin>>phidvravaolimo; 
        }
        void xuatthongtinxe() {
                Xe::xuatthongtinxe();
                cout<<"|   "<<phidvravaolimo<<"VND"<<"    |"<<"\n";
        }
        string loaixe() override {
                return "Limousine";
        }
        void ghifilexe(ofstream& of) {
                of<<loaixe()<<"|";
                Xe::ghifilexe(of);
                of<<"|"<<phidvravaolimo<<"\n";
        }
        long long getPhiRaVao() const { return phidvravaolimo; }
};
void themvaodsachxe(vector<Xe*>& v1) {
        int luachon;
        cout << "(1). Xe khach\n(2). Limousine\n";
        cout<<"Nhap lua chon: ";
        cin >> luachon; cin.ignore();
        Xe* xe;
        if (luachon == 1)
                xe = new Xekhach();
        else if (luachon == 2)
                xe = new Limousine();
        else return;
        xe->nhapthongtinxe();
        v1.push_back(xe);
        cout<<" =>Them xe thanh cong!"; 
        cout<<endl;
        system("pause");
        system("cls");
}
void xuatdsachxe(const vector<Xe*>& v1) {
        cout<<"+----------------------------------------------------------------------------------------------------------------------+\n";
        cout<< "| " << setw(11) << left << "Loai xe"
        << "| " << setw(8)  << "Bien so"
        << "| " << setw(12) << "  Mau xe"
        << "| " << setw(8)  << "Cho ngoi "
        << "| " << setw(8)  << "Nam sx"
        << "| " << setw(12) << "Ten tai xe"
        << "| " << setw(12) << "So dien thoai "
        << "| " << setw(12) << "Tuyen duong"
        << "| " << setw(12) << "  Phi dvu"<<"   |";
        cout<<"\n+----------------------------------------------------------------------------------------------------------------------+\n";
        for(Xe* xe : v1) {
                xe->xuatthongtinxe();
        }
        cout<<"+----------------------------------------------------------------------------------------------------------------------+\n";
        system("pause");
        system("cls");

}
void luufiledsachxe(const vector<Xe*>& v1) {
        ofstream of1("QuanLyXe.txt", ios::trunc);
        if (!of1) {
            cout << "Khong mo duoc file!\n";
                return ;
        }
        for(Xe* xe : v1) {
                xe->ghifilexe(of1);
        }
        of1.close();
}
void docfiledsachxe(vector<Xe*>& v1) {
        ifstream if1("QuanLyXe.txt");
        if(!if1) {
                cout<<"Khong mo duoc file!\n";
                return ;
        }
        string line;
        while(true) {
                if(!getline(if1,line)) break;
                stringstream ss(line);
                string loaixef,biensof,mauxef,sochof,namsxf,tentaixef,sdttxf,tuyenduongf,phidvxef;
                getline(ss,loaixef,'|');
                getline(ss,biensof,'|');
                getline(ss,mauxef,'|');
                getline(ss,sochof,'|');
                getline(ss,namsxf,'|');
                getline(ss,tentaixef,'|');
                getline(ss,sdttxf,'|');
                getline(ss,tuyenduongf,'|');
                getline(ss,phidvxef,'|');
                int sochof1 = stoi(sochof);
                int namsxf1 = stoi(namsxf);
                long long phidvxef1 = stoll(phidvxef);
                if(loaixef == "Xe Khach") {
                        Xekhach* xk = new Xekhach(biensof,mauxef,sochof1,namsxf1,tentaixef,sdttxf,tuyenduongf,phidvxef1);
                        v1.push_back(xk);
                }
                else if(loaixef == "Limousine") {
                        Limousine* limo = new Limousine(biensof,mauxef,sochof1,namsxf1,tentaixef,sdttxf,tuyenduongf,phidvxef1);
                        v1.push_back(limo);
                }
        }
        if1.close();
}
void xoaTtxe(vector<Xe*>& v1) {
        vector<Xe*> v1m;
        bool ktraxoaxe = false;
        bool xoaxe = true;
        int luachonxoaxe;
        while(xoaxe) {
                cout<<"(1). Xoa xe thong qua bien so.\n(2). Xoa xe thong qua ten tai xe.\n(3). Thoat\n";
                cout<<"Nhap lua chon: ";
                cin>>luachonxoaxe;
                switch(luachonxoaxe) {
                        case 1: {
                                string biensoxoa;
                                cout<<"Nhap bien so cua xe can xoa: ";
                                cin.ignore();
                                getline(cin,biensoxoa);
                                for(Xe* xe : v1) {
                                        if(xe->hthibienso() != biensoxoa) {
                                                v1m.push_back(xe);
                                        }
                                        else {
                                                ktraxoaxe = true;      
                                        }       
                                }
                                if(!ktraxoaxe) {
                                        cout<<"Khong tim thay xe co bien so "<<biensoxoa<<"\n";
                                }
                                else {
                                        v1 = v1m;
                                        cout<<"Da xoa xe co bien so "<<biensoxoa<<"\n";
                                }
                                break;
                        }
                        case 2: {
                                string tentxxoa;
                                cout<<"Nhap ten tai xe cua xe can xoa: ";
                                cin.ignore();
                                getline(cin,tentxxoa);
                                for(Xe* xe : v1) {
                                        if(xe->hthitentaixe() != tentxxoa) {
                                                v1m.push_back(xe);
                                        }
                                        else {
                                                ktraxoaxe = true;      
                                        }       
                                }
                                if(!ktraxoaxe) {
                                        cout<<"Khong tim thay tai xe co ten "<<tentxxoa<<"\n";
                                }
                                else {
                                        v1 = v1m;
                                        cout<<"Da xoa xe cua tai xe co ten "<<tentxxoa<<"\n";
                                }
                                break;
                        }
                        case 3: {
                                xoaxe = false;
                                system("cls");
                                break;  
                        }
                        default : 
                                cout<<"Lua chon khong hop le vui long nhap lai\n";  
                }
        }
}
void timkiemTtxe(const vector<Xe*>& v1) {
        bool timkiemXe = true;
        bool ktratimkiemxe = false;
        while(timkiemXe) {
                int luachontimxe;
                cout<<"(1). Tim kiem xe theo bien so.\n(2). Tim kiem xe theo tuyen.\n(3). Tim kiem xe theo ten tai xe\n(4). Thoat\n";
                cout<<"Nhap lua chon: ";
                cin>>luachontimxe;
                switch(luachontimxe) {
                        case 1: {
                                string biensoTk;
                                cout<<"Nhap bien so can tim kiem: ";
                                cin.ignore();
                                getline(cin,biensoTk);
                                cout<<"Tim thay thong tin xe co bien so "<<biensoTk<<" co thong tin nhu sau: "<<"\n";
                                cout<<"+----------------------------------------------------------------------------------------------------------------------+\n";
                                cout<< "| " << setw(11) << left << "Loai xe"
                                << "| " << setw(8)  << "Bien so"
                                << "| " << setw(12) << "  Mau xe"
                                << "| " << setw(8)  << "Cho ngoi "
                                << "| " << setw(8)  << "Nam sx"
                                << "| " << setw(12) << "Ten tai xe"
                                << "| " << setw(12) << "So dien thoai "
                                << "| " << setw(12) << "Tuyen duong"
                                << "| " << setw(12) << "  Phi dvu"<<"   |";
                                cout<<"\n+----------------------------------------------------------------------------------------------------------------------+\n";
                                for(Xe* xe : v1) {
                                        if(xe->hthibienso() == biensoTk) {
                                                xe->xuatthongtinxe();
                                                ktratimkiemxe = true;
                                        }
                                }
                                cout<<"+----------------------------------------------------------------------------------------------------------------------+\n";
                                if(!ktratimkiemxe) {
                                        cout<<"Khong tim thay thong tin cua xe co bien so "<<biensoTk;
                                }
                                break;
                        }
                        case 2: {
                                string tuyenxeTk;
                                cout<<"Nhap tuyen xe tim kiem: ";
                                cin.ignore();
                                getline(cin,tuyenxeTk);
                                cout<<"\nTim thay tuyen xe "<<tuyenxeTk<<" co thong tin nhu sau: "<<"\n";
                                cout<<"+----------------------------------------------------------------------------------------------------------------------+\n";
                                cout<< "| " << setw(11) << left << "Loai xe"
                                << "| " << setw(8)  << "Bien so"
                                << "| " << setw(12) << "  Mau xe"
                                << "| " << setw(8)  << "Cho ngoi "
                                << "| " << setw(8)  << "Nam sx"
                                << "| " << setw(12) << "Ten tai xe"
                                << "| " << setw(12) << "So dien thoai "
                                << "| " << setw(12) << "Tuyen duong"
                                << "| " << setw(12) << "  Phi dvu"<<"   |";
                                cout<<"\n+----------------------------------------------------------------------------------------------------------------------+\n";
                                for (Xe* xe : v1) {
                                        if(xe->hthituyenduong() == tuyenxeTk) {
                                                xe->xuatthongtinxe();
                                                ktratimkiemxe = true;
                                        }
                                }
                                cout<<"+----------------------------------------------------------------------------------------------------------------------+\n";
                                if(!ktratimkiemxe) {
                                        cout<<"Khong tim thay thong tin cua xe co tuyen "<<tuyenxeTk;
                                }
                                break;
                        }
                        case 3: {
                                string tentxeTk;
                                cout<<"Nhap ten tai xe cua xe can tim kiem : ";
                                cin.ignore();
                                getline(cin,tentxeTk);
                                cout<<"Tim thay ten tai xe "<<tentxeTk<<" co thong tin nhu sau: "<<"\n";
                                cout<<"+----------------------------------------------------------------------------------------------------------------------+\n";
                                cout<< "| " << setw(11) << left << "Loai xe"
                                << "| " << setw(8)  << "Bien so"
                                << "| " << setw(12) << "  Mau xe"
                                << "| " << setw(8)  << "Cho ngoi "
                                << "| " << setw(8)  << "Nam sx"
                                << "| " << setw(12) << "Ten tai xe"
                                << "| " << setw(12) << "So dien thoai "
                                << "| " << setw(12) << "Tuyen duong"
                                << "| " << setw(12) << "  Phi dvu"<<"   |";
                                cout<<"\n+----------------------------------------------------------------------------------------------------------------------+\n";
                                for (Xe* xe : v1) {
                                        if(xe->hthitentaixe() == tentxeTk) {
                                                xe->xuatthongtinxe();
                                                ktratimkiemxe = true;
                                        }
                                }
                                cout<<"+----------------------------------------------------------------------------------------------------------------------+\n";
                                if(!ktratimkiemxe) {
                                        cout<<"Khong tim thay thong tin cua xe co ten tai xe "<<tentxeTk;
                                }
                                break;
                        }
                        case 4: {
                                timkiemXe = false;
                                system("cls");
                                break;      
                        }
                }
        }    
}
void chinhsuaTtxe(vector<Xe*>& v1) {
        cout<<"Nhap bien so xe can chinh sua: ";
        cin.ignore();
        string biensoxeCS;
        getline(cin,biensoxeCS);
        bool suaxe = false;
        for(Xe* xe : v1)
        {
                if(xe->hthibienso() == biensoxeCS)
                {
                        suaxe = true;
                        bool ktrasuaxe = true;
                        while(ktrasuaxe) {
                                int luachonsuaTtxe;
                                cout<<"(1). Sua ten tai xe cua xe\n(2). Sua so dien thoai cua tai xe xe\n(3). Sua tuyen duong cua xe\n(4). Thoat\n";
                                cout<<"Nhap lua chon: ";
                                cin>>luachonsuaTtxe;
                                switch(luachonsuaTtxe) {
                                        case 1: {
                                                string tentxecsua;
                                                cout<<"Nhap ten tai xe can thay doi thanh: ";
                                                cin.ignore();
                                                getline(cin,tentxecsua);
                                                xe->suatentx(tentxecsua);
                                                ktrasuaxe = false;
                                                cout << "Dang luu lai thong tin ";
                                                for (int i = 0; i < 5; i++) {
                                                        cout << ".";
                                                        cout.flush();
                                                        this_thread::sleep_for(chrono::milliseconds(150));
                                                }
                                                cout<<"\nDa sua va cap nhat thanh cong thong tin.";
                                                system("cls");
                                                break;
                                        }
                                        case 2: {
                                                string sdttxsua;
                                                cout<<"Nhap so dien thoai cua tai xe can thay doi thanh: ";
                                                cin.ignore();
                                                getline(cin,sdttxsua);
                                                xe->suasdttx(sdttxsua);
                                                ktrasuaxe = false;
                                                cout << "Dang luu lai thong tin ";
                                                for (int i = 0; i < 5; i++) {
                                                        cout << ".";
                                                        cout.flush();
                                                        this_thread::sleep_for(chrono::milliseconds(150));
                                                }
                                                cout<<"\nDa sua va cap nhat thanh cong thong tin.";
                                                system("cls");
                                                break;
                                        }
                                        case 3: {
                                                string tuyenduongsua;
                                                cout<<"Nhap tuyen duong can thay doi thanh: ";
                                                cin.ignore();
                                                getline(cin,tuyenduongsua);
                                                xe->suatuyenduong(tuyenduongsua);
                                                ktrasuaxe = false;
                                                cout << "Dang luu lai thong tin ";
                                                for (int i = 0; i < 5; i++) {
                                                        cout << ".";
                                                        cout.flush();
                                                        this_thread::sleep_for(chrono::milliseconds(150));
                                                }
                                                cout<<"\nDa sua va cap nhat thanh cong thong tin.\n";
                                                system("cls");
                                                break;
                                        }
                                        case 4: {
                                                ktrasuaxe = false;
                                                break;      
                                        }
                                }
                        }
                }
        }
        if(!suaxe) {
                cout<<"Khong tim thay xe co bien so "<<biensoxeCS<<endl;
        }
}
class Khachhang
{
private:
        string hotenKH,diaChiKH,tuyenduong,loaixee,thoigiandatve,trangthai,sdtKH;
        long long tongthanhtoan;
        int soluongve;
        static int STT;
public:
        Khachhang() {}
        Khachhang(string hotenKH,string diaChiKH,string sdtKH,string tuyenduong,string loaixee,int soluongve,long long tongthanhtoan,string thoigiandatve,string trangthai) {
                this->hotenKH = hotenKH;
                this->diaChiKH = diaChiKH;
                this->sdtKH = sdtKH;
                this->tuyenduong = tuyenduong;
                this->loaixee = loaixee;
                this->soluongve = soluongve;
                this-> tongthanhtoan = tongthanhtoan;
                this->thoigiandatve = thoigiandatve;
                this->trangthai = trangthai;
        }
        void themthongtinKH() {
                cin.ignore();
                cout<<"Nhap ten khach hang :";
                getline(cin,hotenKH);
                cout<<"Nhap dia chi khach hang: ";
                getline(cin,diaChiKH);
                cout<<"Nhap so dien thoai cua khach hang: ";
                getline(cin,sdtKH);              
        }
        void xuatthongtinKH() {
                cout<<"\n+----------------------------IN VE XE-------------------------------------+\n";
                cout<<"|"<<"   Ten khach hang: "<<hotenKH<<setw(47)<<"|"<<"\n";
                cout<<"|"<<"   Dia chi khach hang: "<<diaChiKH<<setw(49)<<"|"<<"\n";
                cout<<"|"<<"   So dien thoai khach hang: "<<sdtKH<<setw(35)<<"|"<<"\n";
                cout<<"|"<<"   Tuyen duong: "<<tuyenduong<<setw(53)<<"|"<<"\n";
                cout<<"|"<<"   Loai xe: "<<loaixee<<setw(54)<<"|"<<"\n";
                cout<<"|"<<"   So luong ve dat: "<<soluongve<<setw(53)<<"|"<<"\n";
                cout<<"|"<<"   Tong tien thanh toan: "<<tongthanhtoan<<"VND"<<setw(40)<<"|"<<"\n";
                cout<<"|"<<"   Thoi gian dat ve: "<<thoigiandatve<<setw(34)<<"|"<<"\n";
                cout<<"|"<<"   Trang thai thanh toan: "<<trangthai<<setw(34)<<"|"<<"\n";
                cout<<"+-------------------------------------------------------------------------+\n";
                cout<<" =>Xuat ve thanh cong.\n";
                system("pause");
                system("cls");
        }
        void ghifileKH(ofstream& of) {
                of<<hotenKH<<"|"<<diaChiKH<<"|"<<sdtKH<<"|"<<tuyenduong<<"|"<<loaixee<<"|"<<soluongve<<"|"<<tongthanhtoan<<"|"<<thoigiandatve<<"|"<<trangthai<<"\n";
        }
        void capnhatthoigiandve() {
        time_t now = time(nullptr);
        char buffer[100];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&now));
        thoigiandatve = buffer;
        }
        static int demstt() {
                STT++;
                return STT; 
        }
        string xuathotenKH() { return hotenKH; }
        string xuattrangthai() { return trangthai; }
        long long tongthanhtoanve() { return tongthanhtoan; }      
        void settrangthai(string trangthaimoi) { trangthai = trangthaimoi; }
        void setoluongve(int soluongvemoi) { soluongve = soluongvemoi; }
        void setTuyenduong(string tuyenduongmoii) { tuyenduong = tuyenduongmoii; }      
        void setLoaixee(string loaixxemoi) { loaixee = loaixxemoi; }
        void settongthanhtoan(long long tongthanhtoanmoi) { tongthanhtoan = tongthanhtoanmoi; }           
};
int Khachhang::STT = 0;

void themthongtinKHdVe(vector<Xe*>& v1,vector<Khachhang>& v2) {
        Khachhang kh;
        kh.themthongtinKH();
        cout<<setw(36)<<"Tim thay cac tuyen duong sau"<<"\n";
        cout<<"|"<<"STT"
            <<"| "<< setw(10) <<"  Tuyen duong  "
            <<"| "<< setw(10) <<"  Loai phuong tien  "<<"|"<<"\n";
        cout<<"+------------------------------------------+";
        cout<<endl;
        for(Xe* xe : v1) { 
                cout << "| " <<Khachhang::demstt() <<" |";
                cout<<setw(10)<<xe->hthituyenduong()<<"      |"<<setw(15)<<xe->loaixe()<<setw(7)<<"|";
                cout<<endl;
        }
        bool ktrathemtuyen = true;
        while(ktrathemtuyen) {
        string tuyenduongdat,loaixedat;
        cout<<"Nhap thong tin tuyen duong va loai xe can dat ve.\n";
        cout<<"+Nhap tuyen duong can dat ve: ";
        getline(cin,tuyenduongdat);
        cout<<"+Nhap loai xe can dat ve: ";
        getline(cin,loaixedat);
        for(Xe* xe : v1) {
                if(xe->hthituyenduong() == tuyenduongdat && xe->loaixe() == loaixedat) {
                        cout<<"=>Dang xu ly yeu cau";
                        for(int i = 0;i<3;i++) {
                                cout<<".";
                                cout.flush();
                                this_thread::sleep_for(chrono::milliseconds(100));
                        }
                        cout<<endl;
                        ktrathemtuyen = false;
                        int soluongvetemp;
                        cout<<"+So luong ve can dat: ";
                        cin>>soluongvetemp;
                        kh.setoluongve(soluongvetemp);
                        kh.capnhatthoigiandve();
                        kh.setTuyenduong(tuyenduongdat);
                        kh.setLoaixee(loaixedat);
                        if(loaixedat == "Xe Khach") {
                                long long tongtienxekhach = 200000*soluongvetemp;
                                kh.settongthanhtoan(tongtienxekhach);                                
                        }
                        else if(loaixedat == "Limousine") {
                                long long tongtienlimo = 300000*soluongvetemp;
                                kh.settongthanhtoan(tongtienlimo);        
                        }
                        cout<<"+Ban muon thanh toan ve khong?\n"
                                <<"(1). Thanh toan ve.\n(2). Chua thanh toan.\n";
                        int luachonthanhtoan;
                        cout<<"Nhap lua chon: ";
                        cin>>luachonthanhtoan;
                        if(luachonthanhtoan == 1) {
                                kh.settrangthai("Da thanh toan");
                        }
                        else if(luachonthanhtoan == 2) {
                                kh.settrangthai("Chua thanh toan");
                        }
                        else {
                                return ;
                        }
                        v2.push_back(kh);
                        cout<<"Dat ve thanh cong!";
                }
        }
        if(ktrathemtuyen) {
                cout<<"Thong tin dat ve sai vui long kiem tra lai.\n";
        }
        }
}
void docfiledsachKH(vector<Khachhang>& v2) {
        ifstream if2("QuanLyKH.txt");
        if(!if2) {
                cout<<"Khong mo duoc file!\n";
                return ;
        }
        string linee;
        while(true) {
                if(!getline(if2,linee)) break;
                stringstream sss(linee);
                string hotenKHf,diaChiKHf,sdtKHf,tuyenduongf,loaixeef,soluongvef,tongthanhtoanf,thoigiandatvef,trangthaif;
                getline(sss,hotenKHf,'|');
                getline(sss,diaChiKHf,'|');
                getline(sss,sdtKHf,'|');
                getline(sss,tuyenduongf,'|');
                getline(sss,loaixeef,'|');
                getline(sss,soluongvef,'|');
                getline(sss,tongthanhtoanf,'|');
                getline(sss,thoigiandatvef,'|');
                getline(sss,trangthaif,'|');
                int soluongvef1 = stoi(soluongvef);
                long long tongthanhtoanf1 = stoll(tongthanhtoanf);
                Khachhang kh(hotenKHf,diaChiKHf,sdtKHf,tuyenduongf,loaixeef,soluongvef1,tongthanhtoanf1,thoigiandatvef,trangthaif);
                v2.push_back(kh);
        }
        if2.close();
}       
void luufiledsachKH(const vector<Khachhang>& v2) {
        ofstream of2("QuanLyKH.txt", ios::trunc);
        if (!of2) {
            cout << "Khong mo duoc file!\n";
                return ;
        }
        for(Khachhang kh : v2) {
                kh.ghifileKH(of2);
        }
        of2.close();              
}
void xoathongtinKHhVe(vector<Khachhang>& v2) {
        vector<Khachhang> v2m;
        bool ktrahuyve = false;
        string tenKHhuyve;
        cin.ignore();
        cout<<"Nhap ten khach hang can huy ve: ";
        getline(cin,tenKHhuyve);
        for(Khachhang kh : v2) {
                if(kh.xuathotenKH() != tenKHhuyve) {
                        v2m.push_back(kh);
                }
                else {
                        ktrahuyve = true;
                }
        }
        if(!ktrahuyve) {
                cout<<"Khong tim thay thong tin khach hang "<<tenKHhuyve<<"\n";
                system("pause");
                system("cls");
        }
        else {
                v2 = v2m;
                cout<<" =>Huy ve thanh cong cho khach hang "<<tenKHhuyve;
                system("pause");
                system("cls");
        }      
}
void xuatvechoKH(const vector<Khachhang>& v2) {
        string tenKHxuatve;
        cin.ignore();
        cout<<"Nhap ten khach hang xuat ve: ";
        getline(cin,tenKHxuatve);
        bool ktravexe = false;
        for(Khachhang kh : v2) {
                if(kh.xuathotenKH() == tenKHxuatve) {
                        kh.xuatthongtinKH();
                        ktravexe = true;
                }
        }
        if(!ktravexe) {
                cout<<"Khong tim thay thong tin khach hang can tim.\n";
        }
}
void thongkedoanhthubxe(const vector<Xe*>& v1,const vector<Khachhang>& v2) {
        long long phivaoraa = 0,tongtiendatve = 0,tongtatca = 0;
        int demchthanhtoan = 0;
        for(Xe* xe : v1) {
                phivaoraa +=xe->getPhiRaVao();  
        }
        cout<<"+Tong tien thu tu phi ra vao: "<<phivaoraa<<"\n";
        for(Khachhang kh : v2) {
                if(kh.xuattrangthai() == "Da thanh toan") {
                        tongtiendatve += kh.tongthanhtoanve();
                }
                else if (kh.xuattrangthai() == "Chua thanh toan") {
                        demchthanhtoan++;              
                }      
        }
        cout<<"+Tong so tien thu tu viec dat ve la: "<<tongtiendatve<<"\n";
        tongtatca = phivaoraa + tongtiendatve;
        cout<<"+Doanh thu cua ben xe la: "<<tongtatca<<"\n";
        cout<<"+So khach hang chua thanh toan ve :"<<demchthanhtoan;
        cout<<"\n";
        system("pause");
        system("cls");
}
void luulaitatca(vector<Xe*>& v1,vector<Khachhang>& v2) {
        luufiledsachxe(v1);
        luufiledsachKH(v2);      
}
int main()
{
        vector<Xe*> v1;
        vector<Khachhang> v2;
        docfiledsachxe(v1);
        docfiledsachKH(v2);
        int luachonmain;
        bool ktramain = true;
        while(ktramain)
        {
            cout << "\n+-------------------------------------------------------------------------------------+\n";
            cout << "|" << "                               " << "MENU QUAN LY BEN XE" << "                                   " << "|\n";
            cout << "+-------------------------------------------------------------------------------------+\n";
            cout << "|" << left << setw(42) << "   (1). Them phuong tien moi." 
                 << "|" << left << setw(42) << "   (6). Dat ve xe." << "|\n";
            cout << "|" << left << setw(42) << "   (2). Xoa thong tin phuong tien." 
                 << "|" << left << setw(42) << "   (7). Huy ve xe." << "|\n";
            cout << "|" << left << setw(42) << "   (3). Tim kiem thong tin phuong tien." 
                 << "|" << left << setw(42) << "   (8). Xuat ve theo ten khach hang." << "|\n";
            cout << "|" << left << setw(42) << "   (4). Chinh sua thong tin phuong tien." 
                 << "|" << left << setw(42) << "   (9). Thong ke doanh thu cua ben xe." << "|\n";
            cout << "|" << left << setw(42) << "   (5). Xuat thong tin phuong tien." 
                 << "|" << left << setw(42) << "  (10). Luu thong tin vao file." << "|\n";
            cout << "|" << setw(52) << right << "(11). Thoat chuong trinh." <<setw(35)<< "|\n";
            cout << "+-------------------------------------------------------------------------------------+\n";
                cout<<"Nhap lua chon: ";
                cin>>luachonmain;
                switch(luachonmain) {
                        case 1: {
                                themvaodsachxe(v1);
                                break;
                        }
                        case 2: {
                                xoaTtxe(v1);
                                break;                               
                        }
                        case 3: {
                                timkiemTtxe(v1);
                                break;       
                        }
                        case 4: {
                                chinhsuaTtxe(v1);
                                break;        
                        }
                        case 5: {
                                xuatdsachxe(v1); 
                                break;       
                        }
                        case 6: {
                                themthongtinKHdVe(v1,v2);
                                break;        
                        }
                        case 7: {
                                xoathongtinKHhVe(v2);
                                break;        
                        }
                        case 8: {
                                xuatvechoKH(v2);
                                break;       
                        }
                        case 9: {
                                thongkedoanhthubxe(v1,v2);
                                break;        
                        }
                        case 10: {
                                luulaitatca(v1,v2);
                                cout<<"Dang luu tat ca thay doi ";
                                for (int i = 0; i < 3; i++) {
                                cout << ".";
                                cout.flush();
                                this_thread::sleep_for(chrono::milliseconds(100));
                                }
                        }
                        case 11: {
                                ktramain = false;
                                break;
                        }
                        default:
                                cout<<"Lua chon khong hop le, vui long nhap lai.\n";
                }
        }
        for (Xe* xe : v1) {
                delete xe;
        }
        v1.clear();
        return 0;
}
